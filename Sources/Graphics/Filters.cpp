#include "../../Headers/Graphics/Filters.h"
#include <QScrollArea>

Filters::Filters(QWidget* parent) : QWidget(parent) {
    this->setMinimumHeight(150);
    this->setFixedWidth(190);

    QWidget* container = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(container);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // campo ricerca nome
    QHBoxLayout* topLayout = new QHBoxLayout();
    layout->addLayout(topLayout);
    searchTitle = new QLineEdit();
    searchTitle->setPlaceholderText("search something");
    topLayout->addWidget(searchTitle);

    /* check per i preferiti
    wishedCheck = new QCheckBox("In wish list");
    wishedCheck->setChecked(false);
    wishedCheck->setStyleSheet(R"(
        QCheckBox {
            spacing: 8px;
            font-size: 14px;
        }
    )");
    topLayout->addWidget(wishedCheck, 0, Qt::AlignRight);
    */

    wishedCheck = false;
    wishedButton = new QPushButton();
    wishedButton->setIcon(QIcon(QPixmap(":/Icons/empty.png").scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    wishedButton->setFixedSize(20,20);
    wishedButton->setIconSize(QSize(20,20));
    wishedButton->setToolTip("Search in your wishlist");
    wishedButton->setStyleSheet(R"(
        QPushButton {
            border-radius: 5px;
            color: white;
            border: none;
            font-weight: 600;
        }
        QPushButton:hover {
            background-color: #A9A9A9;
        }
    )");
    topLayout->addWidget(wishedButton, Qt::AlignRight);

    // groupbox con il controllo dei prezzi
    QGroupBox* priceGroup = new QGroupBox("Filter by price", this);
    QVBoxLayout* priceLayout = new QVBoxLayout(priceGroup);
    minPrice = new QDoubleSpinBox(this);
    minPrice->setPrefix("€ ");
    minPrice->setRange(0.0, 99999.0);
    minPrice->setSingleStep(10.0);
    minPrice->setDecimals(2);
    minPrice->setValue(0.00);
    priceLayout->addWidget(new QLabel("Minimum:"));
    priceLayout->addWidget(minPrice);
    maxPrice = new QDoubleSpinBox(this);
    maxPrice->setPrefix("€ ");
    maxPrice->setRange(0.01, 10000.0);
    maxPrice->setSingleStep(10.0);
    maxPrice->setDecimals(2);
    maxPrice->setValue(10000.0);
    priceLayout->addWidget(new QLabel("Maximum"));
    priceLayout->addWidget(maxPrice);
    priceGroup->setLayout(priceLayout);
    layout->addWidget(priceGroup);

    typeCombo = new QComboBox(this);
    typeCombo->addItems({"All", "Clothing", "Electronics", "PrintedMedia"});
    layout->addWidget(new QLabel("Product type:"));
    layout->addWidget(typeCombo);

    // extra fields
    extraBox = new QGroupBox("Extra fields", this);
    extraBox->setVisible(false);
    extraLayout = new QVBoxLayout();
    extraBox->setLayout(extraLayout);
    layout->addWidget(extraBox);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidget(container);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    // layout principale del Filters
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);

    QPushButton* searchButton = new QPushButton("search", this);
    mainLayout->addWidget(searchButton);
    QPushButton* resetButton = new QPushButton("reset", this);
    mainLayout->addWidget(resetButton);

    this->setLayout(mainLayout);

    // connessioni
    connect(searchButton, &QPushButton::clicked, this, &Filters::filterProduct);
    connect(resetButton, &QPushButton::clicked, this, &Filters::resetFilters);
    connect(searchTitle, &QLineEdit::returnPressed, this, &Filters::filterProduct);
    connect(maxPrice, QOverload<double>::of(&QDoubleSpinBox::valueChanged),this, &Filters::filterProduct);
    connect(minPrice, QOverload<double>::of(&QDoubleSpinBox::valueChanged),this,&Filters::filterProduct);
    connect(typeCombo, &QComboBox::currentTextChanged, this, &Filters::updateExtraFields);
    connect(wishedButton, &QPushButton::clicked, this, &Filters::updateWishButton);
}

void Filters::filterProduct(){
    QString type = typeCombo->currentText();
    QString extraData = "";
    if( type != "All" ){
        if(type=="Clothing") extraData = genderCombo->currentText() + "|" + sizeCombo->currentText();
        else if(type=="Electronics") extraData = brandEdit->text();
        else if(type=="PrintedMedia") extraData = authorEdit->text();
    }
    emit filterChanged(searchTitle->text(), minPrice->value(), maxPrice->value(),wishedCheck, type, extraData);
    emit refreshProducts();
}

void Filters::updateWishButton(){
    if(wishedCheck){
        wishedButton->setIcon(QIcon(QPixmap(":/Icons/empty.png").scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        wishedCheck=false;
    }
    else{
        wishedButton->setIcon(QIcon(QPixmap(":/Icons/full.png").scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        wishedCheck=true;
    }
    filterProduct();
}

void Filters::resetFilters(){
    wishedCheck=false;
    wishedButton->setIcon(QIcon(QPixmap(":/Icons/empty.png").scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    searchTitle->clear();
    minPrice->setValue(0.0);
    maxPrice->setValue(10000.0);
    typeCombo->setCurrentIndex(0);
    updateExtraFields("All");
}

void Filters::updateExtraFields(const QString& type) {
    sizeCombo=nullptr;
    genderCombo=nullptr;
    brandEdit=nullptr;
    authorEdit=nullptr;

    // pulisco i campi precedenti
    QLayoutItem* child;
    while ((child = extraLayout->takeAt(0)) != nullptr) {
        if (child->widget()) delete child->widget();
        delete child;
    }
    if (type == "Clothing") {
        extraBox->setVisible(true);
        sizeCombo = new QComboBox();
        sizeCombo->addItems({"", "XS","S","M","L","XL","XXL"});
        genderCombo = new QComboBox();
        genderCombo->addItems({"", "M","F","U"});
        extraLayout->addWidget(new QLabel("Size:"));
        extraLayout->addWidget(sizeCombo);
        extraLayout->addWidget(new QLabel("Gender:"));
        extraLayout->addWidget(genderCombo);
    }
    else if (type == "Electronics") {
        extraBox->setVisible(true);
        brandEdit = new QLineEdit();
        extraLayout->addWidget(new QLabel("Brand:"));
        extraLayout->addWidget(brandEdit);
    }
    else if (type == "PrintedMedia") {
        extraBox->setVisible(true);
        authorEdit = new QLineEdit();
        extraLayout->addWidget(new QLabel("Author/Editor:"));
        extraLayout->addWidget(authorEdit);
    }
    else{
        extraBox->setVisible(false);
    }
}
