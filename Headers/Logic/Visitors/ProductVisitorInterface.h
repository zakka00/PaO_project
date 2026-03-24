#ifndef PRODUCTVISITORINTERFACE_H
#define PRODUCTVISITORINTERFACE_H

class Clothing;
class Electronics;
class PrintedMedia;

class ProductVisitorInterface{
public:
    virtual ~ProductVisitorInterface() = default;
    virtual void visitClothing(const Clothing& c) = 0;
    virtual void visitPrintedMedia(const PrintedMedia& p) = 0;
    virtual void visitElectronics(const Electronics& e) = 0;

    virtual void getClothing(Clothing* c) const = 0;
    virtual void getPrintedMedia(PrintedMedia* p) const = 0;
    virtual void getElectronics(Electronics* e) const = 0;
};

#endif // PRODUCTVISITORINTERFACE_H
