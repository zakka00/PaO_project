#ifndef PRODUCTICONVISITOR_H
#define PRODUCTICONVISITOR_H
#include "ProductConstVisitorInterface.h"
#include <QLabel>
class ProductIconVisitor: public ProductConstVisitorInterface{
private:
    QLabel* widget;
public:
    ProductIconVisitor();
    QLabel* getWidget() const;
    void visitClothing(const Clothing& c) const;
    void visitPrintedMedia(const PrintedMedia& p) const;
    void visitElectronics(const Electronics& e) const;
};

#endif // PRODUCTICONVISITOR_H
