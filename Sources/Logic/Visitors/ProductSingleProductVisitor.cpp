#include "../../../Headers/Logic/Visitors/ProductSingleProductVisitor.h"
#include "../../../Headers/Logic/Clothing.h"
#include "../../../Headers/Logic/PrintedMedia.h"
#include "../../../Headers/Logic/Electronics.h"
#include <QVBoxLayout>
#include <QLabel>

QVBoxLayout* ProductSingleProductVisitor::getWidget() const{
    return widget;
}

ProductSingleProductVisitor::ProductSingleProductVisitor(){
    widget = new QVBoxLayout();
}

void ProductSingleProductVisitor::visitClothing(const Clothing& c) const {
    QString style = "color: #333; font-size:18px;";

    QLabel* genderLabel = new QLabel("<u>Gender:</u> " + QString(c.getGender()));
    genderLabel->setStyleSheet(style);

    QLabel* sizeLabel = new QLabel("<u>Size:</u> " + c.getSize());
    sizeLabel->setStyleSheet(style);

    QLabel* materialLabel = new QLabel("<u>Material:</u> " + c.getMaterial());
    materialLabel->setStyleSheet(style);

    widget->addWidget(genderLabel);
    widget->addWidget(sizeLabel);
    widget->addWidget(materialLabel);
}

void ProductSingleProductVisitor::visitElectronics(const Electronics& e) const{
    QString style = "color: #333; font-size:18px; ";

    QLabel* brandLabel = new QLabel("<u>Brand:</u> " + e.getBrand());
    brandLabel->setStyleSheet(style);

    QLabel* alimentation = new QLabel("<u>Alimentations:</u> " + e.getAlimentationType());
    alimentation->setWordWrap(true);
    alimentation->setStyleSheet(style);

    QLabel* warrantyLabel = new QLabel("<u>Warranty:</u> " + QString::number(e.getWarrantyMonths()) + " months");
    warrantyLabel->setStyleSheet(style);

    widget->addWidget(brandLabel);
    widget->addWidget(alimentation);
    widget->addWidget(warrantyLabel);
}

void ProductSingleProductVisitor::visitPrintedMedia(const PrintedMedia& p) const{
    QString style = "color: #333; font-size:18px; ";
    QLabel* authorOrEditor = new QLabel("<u>" +p.getTypeP() + " by: </u>" + p.getAuthorOrEditor());
    authorOrEditor->setStyleSheet(style);

    QLabel* publisherLabel = new QLabel("<u>Publisher:</u> " + p.getPublisher());
    publisherLabel->setStyleSheet(style);

    QLabel* pagesLabel = new QLabel("<u>Pages:</u> " + QString::number(p.getPages()));
    pagesLabel->setStyleSheet(style);

    widget->addWidget(authorOrEditor);
    widget->addWidget(publisherLabel);
    widget->addWidget(pagesLabel);
}
