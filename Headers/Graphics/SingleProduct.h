#ifndef SINGLEPRODUCT_H
#define SINGLEPRODUCT_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "../Logic/Product.h"

class SingleProduct: public QWidget{
    Q_OBJECT
private:
    Product* product;
    QPushButton* edit;
    QPushButton* close;
public:
    SingleProduct(Product* product, QWidget* parent = 0);
    ~SingleProduct() = default;
signals:
    void closeView(); // chiusura del widget stesso
    void editProduct(Product* product); // passa a Homepage il puntatore a product che si vorrebbe modificare ( SingleProductEdit )
};

#endif // SINGLEPRODUCT_H

