#ifndef PRODUCTCONSTVISITORINTERFACE_H
#define PRODUCTCONSTVISITORINTERFACE_H

class Clothing;
class Electronics;
class PrintedMedia;

class ProductConstVisitorInterface{
public:
    virtual ~ProductConstVisitorInterface() = default;
    virtual void visitClothing(const Clothing& c) const = 0;
    virtual void visitPrintedMedia(const PrintedMedia& p) const = 0;
    virtual void visitElectronics(const Electronics& e) const = 0;
};

#endif // PRODUCTVISITORINTERFACE_H
