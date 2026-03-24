#ifndef PRODUCTSVIEW_H
#define PRODUCTSVIEW_H
#include <QWidget>
#include <QScrollArea>
#include <QHBoxLayout>
#include "../Logic/Store.h"

class ProductsView: public QWidget{
    Q_OBJECT
private:
    QScrollArea* scrollArea;
    QHBoxLayout* mainLayout;
    Store* store;
    void clearLayout(QLayout *layout); // elimina tutte le miniature e il layout che le conteneva
    void noProductsFound(); // se non ci sono prodotti da mostrare
public:
    ProductsView(Store* store, QWidget* parent = 0);
    ~ProductsView() = default;
public slots:
    void gridView(int columns=3); // genera un layout a grid da inserire nell'layout principale ( mainLayout ) chiamando prima il clearLayout
    void VerticalView(); // genera un layout verticale da inserire nell'layout principale ( mainLayout ) chiamando prima il clearLayout
signals:
    void openProduct(Product* product); // riceve dalle miniature il puntatore al prodotto di cui la Homepage deve gestire l'apertura della visualizzazione estesa ( SingleProduct )
};

#endif // PRODUCTSVIEW_H
