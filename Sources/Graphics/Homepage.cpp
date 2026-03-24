#include "../../Headers/Graphics/Homepage.h"
#include "../../Headers/Graphics/SingleProduct.h"
#include "../../Headers/Graphics/SingleProductEdit.h"
#include "../../Headers/Graphics/SingleProductCreation.h"
#include "../../Headers/Logic/FileUtils.h"
#include "../../Headers/Graphics/DialogMessage.h"

Homepage::Homepage(Store* store, QWidget* parent) : QMainWindow(parent), store(store){
    mod = 1; // default visualizzazione a griglia
    QWidget* homepage = new QWidget();
    QVBoxLayout* mainVerticalLayout = new QVBoxLayout(homepage);
    // creo la toolbar
    QToolBar* toolBar = new QToolBar(this);
    toolBar->setMovable(true);
    QWidget* spacer = new QWidget(this);
    QAction* save = new QAction(QIcon(":/Icons/save.png"), tr("Save product"), this);
    QAction* open = new QAction(QIcon(":/Icons/open.png"), tr("Open new set of products"), this);
    QAction* saveas = new QAction(QIcon(":/Icons/saveas.png"), tr("Save product in specific folder"), this);
    QAction* add = new QAction(QIcon(":/Icons/plus.png"),tr("Add new element"), this);
    toolBar->addAction(open);
    toolBar->addSeparator();
    toolBar->addAction(saveas);
    toolBar->addAction(save);
    toolBar->addWidget(spacer);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolBar->addAction(add);
    toolBar->addSeparator();
    Grid = new QAction(QIcon(":/Icons/grid.png"), tr("Grid View"), this);
    Grid->setEnabled(false);
    Vertical = new QAction(QIcon(":/Icons/vertical.png"), tr("List View"), this);
    toolBar->addAction(Grid);
    columnsSpin = new QSpinBox();
    columnsSpin->setRange(3,5);
    toolBar->addWidget(columnsSpin);
    toolBar->addSeparator();
    toolBar->addAction(Vertical);
    this->addToolBar(Qt::TopToolBarArea, toolBar);
    // sistemo i parametri per renderla movile
    toolBar->setAllowedAreas(Qt::AllToolBarAreas);
    toolBar->setMovable(true);
    this->addToolBar(Qt::TopToolBarArea, toolBar);
    // creo la parte principale, in cui compare il widget dei filtri, dei prodotti ecc
    mainLayout = new QHBoxLayout;
    filters = new Filters();
    mainLayout->addWidget(filters, 0, Qt::AlignTop);
    productsView = new ProductsView(store);
    mainLayout->addWidget(productsView);
    mainVerticalLayout->addLayout(mainLayout);
    // stringa sotto che indica quanti prodotti compaiono nel risultato della ricerca
    elements = new QLabel(QString::number(store->getSizeDisplayed()) + " elements displayed.");
    elements->setToolTip(FileUtils::getProjectPath());
    // layout orizzontale per elements
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(elements);
    bottomLayout->addStretch();  // spinge tutto a sinistra

    mainVerticalLayout->addLayout(bottomLayout);
    // connessioni
    // connessione cambio visualizzazione
    connect(Grid, &QAction::triggered, this, &Homepage::onGridClicked);
    connect(Vertical, &QAction::triggered, this, &Homepage::onVerticalClicked);
    connect(columnsSpin, QOverload<int>::of(&QSpinBox::valueChanged),productsView, &ProductsView::gridView);
    // connessione aggiunta product
    connect(add, &QAction::triggered, this, &Homepage::addProductRequest);
    // connessione tasti salvataggio e caricamento file
    connect(save, &QAction::triggered, this, &Homepage::saveJson);
    connect(open, &QAction::triggered, this, &Homepage::loadJson);
    connect(saveas, &QAction::triggered, this, &Homepage::saveasJson);
    // connessione miniature
    connect(productsView, &ProductsView::openProduct, this, &Homepage::openProduct);
    // connessione filtri
    connect(filters, &Filters::filterChanged, this, &Homepage::filterProducts);
    connect(filters, &Filters::refreshProducts, this, &Homepage::refreshProductView);
    this->setCentralWidget(homepage);
}

void Homepage::openProduct(Product* product){
    removeLayout();
    SingleProduct* viewProduct = new SingleProduct(product,this);
    //connect per la close della singelProduct
    connect(viewProduct, &SingleProduct::closeView, this, &Homepage::removeLayout);
    // connessione per aprire l'edit
    connect(viewProduct, &SingleProduct::editProduct, this, &Homepage::openEditProduct);
    mainLayout->addWidget(viewProduct);
}

void Homepage::openEditProduct(Product* product){
    removeLayout();
    SingleProductEdit* productEdit = new SingleProductEdit(product);
    connect(productEdit, &SingleProductEdit::closeRequested, this, &Homepage::removeLayout);
    connect(productEdit, &SingleProductEdit::refresh, this, &Homepage::refreshProductView);
    connect(productEdit, &SingleProductEdit::delProduct, this, &Homepage::deleteProduct);
    mainLayout->addWidget(productEdit);
}

// elimino l'elemento in più nel layout
void Homepage::removeLayout(){
    if (mainLayout->count() > 2) {
        QLayoutItem* item = mainLayout->takeAt(2);
        if (item) {
            if (QWidget* widget = item->widget()) {
                widget->deleteLater();
            }
            delete item;
        }
    }
}

void Homepage::onGridClicked(){
    mod = 1;
    productsView->gridView(columnsSpin->value());
    columnsSpin->setEnabled(true);
    Grid->setEnabled(false);
    Vertical->setEnabled(true);
}
void Homepage::onVerticalClicked(){
    mod = 2;
    productsView->VerticalView();
    columnsSpin->setEnabled(false);
    Grid->setEnabled(true);
    Vertical->setEnabled(false);
}

void Homepage::addProductRequest() {
    removeLayout();
    SingleProductCreation* productCretion = new SingleProductCreation(this);
    connect(productCretion, &SingleProductCreation::saveProduct, this, &Homepage::saveProduct);
    connect(productCretion, &SingleProductCreation::closeRequest, this, &Homepage::removeLayout);
    mainLayout->addWidget(productCretion);
}

void Homepage::saveProduct(Product* p){
    store->addProduct(p);
    refreshProductView();
}

void Homepage::refreshProductView(){
    removeLayout();
    if(mod==1){
        productsView->gridView(columnsSpin->value());
    }
    else{
        productsView->VerticalView();
    }
    elements->setText(QString::number(store->getSizeDisplayed()) + " elements displayed.");
}

void Homepage::deleteProduct(Product* p){
    store->deleteProduct(p);
}

// salvataggio e caricamento Json
void Homepage::saveJson(){
    if(store->getSizeMemory() == 0){
        DialogMessage::message(this,"Nothing to save","Add products before saving something!");
        return;
    }
    QString newFile = FileUtils::getProjectPath() + "/Exaples/"+ QDateTime::currentDateTime().toString("dd-MM-yyyy_HH-mm-ss")+ ".json";
    if(store->getSizeDisplayed() > 0){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,tr("Save filtered products"),tr("Save just filtered products (Yes), or all products created (No)?"),
                                      QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes){
            store->saveToJson(newFile, true);   // salva filtrati
        } else {
            store->saveToJson(newFile, false);  // salva tutti
        }
    }
    else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,tr("No products displayed"),tr("There are no product displayed right now, but you have some products saved in memory.\nWould you like to save them?")
                                      ,QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::No)
            return;
        store->saveToJson(newFile, false);
    }
    DialogMessage::message(this,"File saved correctly","The file that you just created is in " + newFile);
}

void Homepage::loadJson(){
    QString fileName = QFileDialog::getOpenFileName(this,tr("Select a file to load"),FileUtils::getProjectPath()+"/Exaples",tr("File Json (*.json)"));
    if (!fileName.isEmpty()){
        store->loadFromJson(fileName);
        filters->resetFilters();
        refreshProductView();
    }
}

void Homepage::saveasJson(){
    if(store->getSizeMemory() == 0){
        DialogMessage::message(this,"Nothing to save","Add products before saving something!");
        return;
    }
    QString dir = QFileDialog::getExistingDirectory(this,tr("Select folder to save JSON"),FileUtils::getProjectPath() + "/Examples");
    if (dir.isEmpty())
        return;
    bool ok;
    QString defaultName = QDateTime::currentDateTime().toString("dd-MM-yyyy_HH-mm-ss");
    QString fileName = QInputDialog::getText(this,tr("File name"),tr("Enter file name (without extension):"),QLineEdit::Normal,defaultName,&ok);
    if (!ok)
        return;
    if(fileName.isEmpty()){
        DialogMessage::message(this,"File saved incorrectly","You forgot to type a name");
        return;
    }
    QString filePath = dir + "/" + fileName + ".json";
    if(store->getSizeDisplayed() > 0){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,tr("Save filtered products"),tr("Save just filtered products (Yes), or all products created (No)?"),QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes){
            store->saveToJson(filePath, true);
        } else {
            store->saveToJson(filePath, false);
        }
    }
    else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,tr("No products displayed"),tr("There are no product displayed right now, but you have some products saved in memory.\nWould you like to save them?")
                                      ,QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::No)
            return;
        store->saveToJson(filePath, false);
    }
    DialogMessage::message(this,"File saved correctly","The file that you just created is in " + filePath);
}

void Homepage::filterProducts(const QString& name, double minPrice, double maxPrice,bool wished,const QString& type, const QString& extraData){
    store->applyFilter(name,minPrice,maxPrice,wished, type, extraData);
}







