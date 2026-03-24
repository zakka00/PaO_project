#include "../../../Headers/Logic/Visitors/ProductEditorVisitor.h"
#include "../../../Headers/Logic/Clothing.h"
#include "../../../Headers/Logic/PrintedMedia.h"
#include "../../../Headers/Logic/Electronics.h"
#include <QFile>
#include <QPushButton>
#include <stdexcept>

ProductEditorVisitor::ProductEditorVisitor() {
    // per precauzione
    sizeCombo=nullptr;
    materialEdit=nullptr;
    genderCombo=nullptr;
    brandEdit=nullptr;
    warrantySpin=nullptr;
    alimentationEdit=nullptr;
    typeEdit=nullptr;
    authorEdit=nullptr;
    pagesSpin=nullptr;
    publisherEdit=nullptr;
    layout = new QVBoxLayout();
}

void ProductEditorVisitor::visitClothing(const Clothing& c) {
    layout->addWidget(new QLabel("Size:"));
    sizeCombo = new QComboBox();
    sizeCombo->addItems({"XS", "S", "M", "L", "XL", "XXL"});
    sizeCombo->setCurrentText(c.getSize());
    layout->addWidget(sizeCombo);
    layout->addWidget(new QLabel("Material:"));
    materialEdit = new QLineEdit(c.getMaterial());
    layout->addWidget(materialEdit);
    layout->addWidget(new QLabel("Gender:"));
    genderCombo = new QComboBox();
    genderCombo->addItems({"M", "F", "U"});
    genderCombo->setCurrentText(QString(c.getGender()));
    layout->addWidget(genderCombo);
}

void ProductEditorVisitor::visitElectronics(const Electronics& e) {
    layout->addWidget(new QLabel("Brand:"));
    brandEdit = new QLineEdit(e.getBrand());
    layout->addWidget(brandEdit);
    layout->addWidget(new QLabel("Warranty (months):"));
    warrantySpin = new QSpinBox();
    warrantySpin->setRange(0, 99);
    warrantySpin->setValue(e.getWarrantyMonths());
    layout->addWidget(warrantySpin);
    layout->addWidget(new QLabel("Alimentation type:"));
    alimentationEdit = new QLineEdit(e.getAlimentationType());
    layout->addWidget(alimentationEdit);
}

void ProductEditorVisitor::visitPrintedMedia(const PrintedMedia& p) {
    layout->addWidget(new QLabel("Type:"));
    typeEdit = new QLineEdit(p.getTypeP());
    layout->addWidget(typeEdit);
    layout->addWidget(new QLabel("Author/Editor:"));
    authorEdit = new QLineEdit(p.getAuthorOrEditor());
    layout->addWidget(authorEdit);
    layout->addWidget(new QLabel("Pages:"));
    pagesSpin = new QSpinBox();
    pagesSpin->setRange(1, 9999);
    pagesSpin->setValue(p.getPages());
    layout->addWidget(pagesSpin);
    layout->addWidget(new QLabel("Publisher:"));
    publisherEdit = new QLineEdit(p.getPublisher());
    layout->addWidget(publisherEdit);
}

QVBoxLayout* ProductEditorVisitor::getLayout() const {
    return layout;
}

void ProductEditorVisitor::getClothing(Clothing* c) const {
    if (materialEdit->text().isEmpty()) {
        throw std::runtime_error(" - material\n");
    }
    c->setGender(genderCombo->currentText().at(0));
    c->setMaterial(materialEdit->text());
    c->setSize(sizeCombo->currentText());
}

void ProductEditorVisitor::getElectronics(Electronics* e) const {
    QString errors;
    if (brandEdit->text().isEmpty()) {
        errors += " - brand\n";
    }
    if (warrantySpin->value() == 0) {
        errors += " - valid warranty period (months)\n";
    }
    if (alimentationEdit->text().isEmpty()) {
        errors += " - alimentation type\n";
    }
    if (!errors.isEmpty()) {
        throw std::runtime_error(errors.toStdString());
    }
    e->setAlimentationType(alimentationEdit->text());
    e->setBrand(brandEdit->text());
    e->setWarrantyMonths(warrantySpin->value());
}

void ProductEditorVisitor::getPrintedMedia(PrintedMedia* p) const {
    QString errors;
    if (typeEdit->text().isEmpty()) {
        errors += " - type (e.g. Book, Magazine...)\n";
    }
    if (authorEdit->text().isEmpty()) {
        errors += " - author/editor\n";
    }
    if (publisherEdit->text().isEmpty()) {
        errors += " - publisher\n";
    }
    if (!errors.isEmpty()) {
        throw std::runtime_error(errors.toStdString());
    }
    p->setAuthorOrEditor(authorEdit->text());
    p->setPages(pagesSpin->value());
    p->setPublisher(publisherEdit->text());
    p->setType(typeEdit->text());
}

void ProductEditorVisitor::getCommon(Product* p,QString name, QString description, int price, QString imageFileName) const {
    p->setName(name);
    p->setDescription(description);
    p->setPrice(price);
    p->setImageFileName(imageFileName);
}


