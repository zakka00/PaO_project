#include "../../Headers/Graphics/SingleProductCreation.h"
#include "../../Headers/Logic/Clothing.h"
#include "../../Headers/Logic/PrintedMedia.h"
#include "../../Headers/Logic/Electronics.h"
#include "../../Headers/Logic/FileUtils.h"
#include "../../Headers/Graphics/DialogMessage.h"
#include <QScrollArea>
#include <QFileDialog>


SingleProductCreation::SingleProductCreation(QWidget* parent) : QWidget(parent) {
    this->setMinimumWidth(400);
    this->setMaximumWidth(500);
    product = nullptr;
    QString stylesheet = R"(
        QPushButton {
            border-radius: 15px;
            color: white;
            border: none;
            padding: 6px 12px;
            font-weight: 600;
        }
        QPushButton:hover {
            background-color: #A9A9A9;
        }
    )";
    QPushButton* close = new QPushButton(QPixmap(":/Icons/close.png").scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation),"");
    close->setIconSize(QSize(25,25));
    close->setFixedSize(50,30);
    close->setToolTip("Close this page");
    close->setStyleSheet(stylesheet);
    QPushButton* edit = new QPushButton(QPixmap(":/Icons/save.png").scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation),"");
    edit->setIconSize(QSize(25,25));
    edit->setFixedSize(50,30);
    edit->setToolTip("Save changes");
    edit->setStyleSheet(stylesheet);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(close);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(edit);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(buttonsLayout);

    imagePath  = FileUtils::getProjectPath() + "/Images/*"; // non asseggno nulla come immagine di default
    image = new QPushButton();
    image->setFixedSize(370, 250);
    QString stylesheetImage = "color: #888; font-style: italic; background-color: lightgray;";
    image->setText("No Image selected\n( optional )");
    image->setStyleSheet(stylesheetImage);
    image->setToolTip("Click to add an image");

    QHBoxLayout* imageLayout = new QHBoxLayout();
    imageLayout->addStretch();
    imageLayout->addWidget(image);
    imageLayout->addStretch();
    mainLayout->addLayout(imageLayout);

    QWidget* scrollWidget = new QWidget();
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollWidget);

    scrollLayout->addWidget(new QLabel("Name:"));
    nameEdit = new QLineEdit("");
    scrollLayout->addWidget(nameEdit);

    scrollLayout->addWidget(new QLabel("Description:"));
    descEdit = new QTextEdit();
    descEdit->setText("");
    scrollLayout->addWidget(descEdit);

    scrollLayout->addWidget(new QLabel("Price:"));
    priceSpin = new QDoubleSpinBox();
    priceSpin->setRange(0.0, 10000.00);
    priceSpin->setValue(0.00);
    scrollLayout->addWidget(priceSpin);

    scrollLayout->addWidget(new QLabel("Product type:"));
    typeCombo = new QComboBox();
    typeCombo->addItem("--");
    typeCombo->addItem("Clothing");
    typeCombo->addItem("PrintedMedia");
    typeCombo->addItem("Electronics");
    scrollLayout->addWidget(typeCombo);

    // Campi aggiuntivi
    additionalFieldsLayout = new QVBoxLayout();
    scrollLayout->addLayout(additionalFieldsLayout);

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

    mainLayout->addWidget(scrollArea);

    // Connessioni
    connect(typeCombo, &QComboBox::currentTextChanged, this, &SingleProductCreation::updateAdditionalFields);
    connect(image, &QPushButton::clicked, this, &SingleProductCreation::editImage);
    connect(edit, &QPushButton::clicked, this, &SingleProductCreation::createProduct);
    connect(close, &QPushButton::clicked, this, &SingleProductCreation::closeRequest);
}

void SingleProductCreation::updateAdditionalFields(const QString& type) {
    sizeCombo = nullptr;
    materialEdit = nullptr;
    genderCombo = nullptr;
    typeEdit = nullptr;
    authorEdit = nullptr;
    pagesSpin = nullptr;
    publisherEdit = nullptr;
    brandEdit = nullptr;
    warrantySpin = nullptr;
    alimentationEdit = nullptr;

    QLayoutItem* child;
    while ((child = additionalFieldsLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget(); // Elimina immediatamente
        }
        delete child;
    }

    if (type == "Clothing") {
        QLabel* sizeLabel = new QLabel("Size:");
        sizeCombo = new QComboBox();
        sizeCombo->addItems({"--","XS", "S", "M", "L", "XL", "XXL"});
        QLabel* materialLabel = new QLabel("Material:");
        materialEdit = new QLineEdit();
        QLabel* genderLabel = new QLabel("Gender:");
        genderCombo = new QComboBox();
        genderCombo->addItems({"--","M", "F", "U"});
        additionalFieldsLayout->addWidget(sizeLabel);
        additionalFieldsLayout->addWidget(sizeCombo);
        additionalFieldsLayout->addWidget(materialLabel);
        additionalFieldsLayout->addWidget(materialEdit);
        additionalFieldsLayout->addWidget(genderLabel);
        additionalFieldsLayout->addWidget(genderCombo);
    }
    else if (type == "PrintedMedia") {
        QLabel* typeLabel = new QLabel("Type:");
        typeEdit = new QLineEdit();
        QLabel* authorLabel = new QLabel("Author/Editor:");
        authorEdit = new QLineEdit();
        QLabel* pagesLabel = new QLabel("Pages:");
        pagesSpin = new QSpinBox();
        pagesSpin->setRange(1,9999);
        pagesSpin->setValue(1.0);
        QLabel* publisherLabel = new QLabel("Publisher:");
        publisherEdit = new QLineEdit();
        additionalFieldsLayout->addWidget(typeLabel);
        additionalFieldsLayout->addWidget(typeEdit);
        additionalFieldsLayout->addWidget(authorLabel);
        additionalFieldsLayout->addWidget(authorEdit);
        additionalFieldsLayout->addWidget(pagesLabel);
        additionalFieldsLayout->addWidget(pagesSpin);
        additionalFieldsLayout->addWidget(publisherLabel);
        additionalFieldsLayout->addWidget(publisherEdit);
    }
    else if (type == "Electronics") {
        QLabel* brandLabel = new QLabel("Brand:");
        brandEdit = new QLineEdit();
        QLabel* warrantyLabel = new QLabel("Warranty (months):");
        warrantySpin = new QSpinBox();
        warrantySpin->setRange(0,99);
        warrantySpin->setValue(0);
        QLabel* alimentationLabel = new QLabel("Alimentation type:");
        alimentationEdit = new QLineEdit();
        additionalFieldsLayout->addWidget(brandLabel);
        additionalFieldsLayout->addWidget(brandEdit);
        additionalFieldsLayout->addWidget(warrantyLabel);
        additionalFieldsLayout->addWidget(warrantySpin);
        additionalFieldsLayout->addWidget(alimentationLabel);
        additionalFieldsLayout->addWidget(alimentationEdit);
    }
}

void SingleProductCreation::editImage() {
    QString fileName = QFileDialog::getOpenFileName(this,tr("Seleziona un'immagine"),FileUtils::getProjectPath(),tr("Immagini (*.png *.jpg *.jpeg)"));
    if (!fileName.isEmpty()) {
        QPixmap img(fileName);
        if (!img.isNull()) {
            image->setIcon(QIcon(img));
            image->setIconSize(QSize(365, 250));
            image->setText("");
            image->setStyleSheet("background-color: lightgray;");
            imagePath = fileName;
            image->setToolTip("Current image:"+ fileName + "\nClick to change it!");
        }
    }
}

void SingleProductCreation::createProduct(){
    QString type = typeCombo->currentText();
    QFileInfo info(imagePath);
    QString errors = "";

    // controlli comuni
    if(nameEdit->text().isEmpty()) {
        errors += " - name\n";
    }
    if(descEdit->toPlainText().isEmpty()) {
        errors += " - description\n";
    }
    if(priceSpin->value() <= 0  || priceSpin->value() > 10000.00) {
        errors += " - valid price (0.01-10000.00)\n";
    }

    try {
        if(type=="--"){
            errors+=" - type of product\n";
        }
        else if(type == "Clothing") {
            if(sizeCombo->currentText() == "--") {
                errors += " - size\n";
            }
            if(materialEdit->text().isEmpty()) {
                errors += " - material\n";
            }
            if(genderCombo->currentText() == "--") {
                errors += " - gender\n";
            }

            if(errors.isEmpty()){
                product = new Clothing(nameEdit->text(),descEdit->toPlainText(),priceSpin->value(),info.fileName(),sizeCombo->currentText(),materialEdit->text(),genderCombo->currentText().at(0));
            }
        }
        else if(type == "PrintedMedia") {
            if(typeEdit->text().isEmpty()) {
                errors += " - type (e.g. Book, Magazine...)\n";
            }
            if(authorEdit->text().isEmpty()) {
                errors += " - author/editor\n";
            }
            if(pagesSpin->value() <= 0) {
                errors += " - valid number of pages\n";
            }
            if(publisherEdit->text().isEmpty()) {
                errors += " - publisher\n";
            }

            if(errors.isEmpty()){
                product = new PrintedMedia(nameEdit->text(),descEdit->toPlainText(),priceSpin->value(),info.fileName(),typeEdit->text(),authorEdit->text(),pagesSpin->value(),publisherEdit->text());
            }
        }
        else if(type == "Electronics") {
            if(brandEdit->text().isEmpty()) {
                errors += " - brand\n";
            }
            if(warrantySpin->value() == 0) {
                errors += " - valid warranty period (months)\n";
            }
            if(alimentationEdit->text().isEmpty()) {
                errors += " - alimentation type\n";
            }
            if(errors.isEmpty()){
                product = new Electronics(nameEdit->text(),descEdit->toPlainText(),priceSpin->value(),info.fileName(),brandEdit->text(),warrantySpin->value(),alimentationEdit->text());
            }
        }

        if(!errors.isEmpty()) {
            DialogMessage::message(this,"Not compiled right","You forgot to compile:\n" + errors);
            return;
        }
        FileUtils::moveToImages(imagePath);
        emit saveProduct(product);
        emit closeRequest();
        DialogMessage::message(this,"Product saved","The file has been saved correctly");
    }
    catch (const std::exception& e) {
        DialogMessage::message(this,"Error",QString("Product creation failed: %1").arg(e.what()));
    }
}

