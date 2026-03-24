#ifndef PRODUCTINFOVISITOR_H
#define PRODUCTINFOVISITOR_H
#include "ProductConstVisitorInterface.h"
#include <QVBoxLayout>

class ProductSingleProductVisitor: public ProductConstVisitorInterface {
private:
    QVBoxLayout* widget;
public:
    ProductSingleProductVisitor();
    QVBoxLayout* getWidget() const;
    void visitClothing(const Clothing& c) const;
    void visitPrintedMedia(const PrintedMedia& p) const;
    void visitElectronics(const Electronics& e) const;
};

#endif // PRODUCTINFOVISITOR_H
