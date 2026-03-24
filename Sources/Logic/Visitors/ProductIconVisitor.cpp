#include "../../../Headers/Logic/Visitors/ProductIconVisitor.h"
#include "../../../Headers/Logic/Clothing.h"
#include "../../../Headers/Logic/PrintedMedia.h"
#include "../../../Headers/Logic/Electronics.h"

QLabel* ProductIconVisitor::getWidget() const{
    return widget;
}

ProductIconVisitor::ProductIconVisitor(){
    widget = new QLabel();
}

void ProductIconVisitor::visitClothing(const Clothing& c) const {
    widget->setPixmap(QPixmap(":/Icons/clothes.png").scaled(35, 35, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    widget->setToolTip(c.getSize() + " in " + c.getMaterial());
}

void ProductIconVisitor::visitElectronics(const Electronics& e) const {
    widget->setPixmap(QPixmap(":/Icons/electronics.png").scaled(35, 35, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    widget->setToolTip(e.getBrand() + " alimentated by a " + e.getAlimentationType());
}

void ProductIconVisitor::visitPrintedMedia(const PrintedMedia& p) const {
    widget->setPixmap(QPixmap(":/Icons/printedmedia.png").scaled(35, 35, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    widget->setToolTip(p.getTypeP() + " by " + p.getAuthorOrEditor());
}
