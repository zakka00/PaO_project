#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include <QMainWindow>
#include <QLabel>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QToolBar>
#include <QLayout>
#include <QScrollArea>
#include <QDateTime>
#include <QSpinBox>
#include "../../Headers/Logic/Store.h"
#include "../../Headers/Graphics/Filters.h"
#include "../../Headers/Graphics/ProductsView.h"
#include "../../Headers/Graphics/Filters.h"

class Homepage: public QMainWindow{
    Q_OBJECT
private:
    Store* store;
    Filters* filters;
    ProductsView* productsView;
    QHBoxLayout *mainLayout;
    QSpinBox* columnsSpin;
    QAction* Grid;
    QAction* Vertical;
    QLabel* elements;
    int mod; // modalità di visualizzazione ( 1->grid oppure 2-> vertical ) di default=1
public:
    Homepage(Store* store, QWidget* parent = 0);
    ~Homepage() = default;
public slots:
    void openProduct(Product* product); // riceve dalla productsView che prodotto deve visualizzare ( SingleProduct )
    void removeLayout(); // elimina l'eventuale visualizzazione singola del product ( SingleProduct ) oppure l'interfaccia di modifica ( SingleProductEdit )
    void deleteProduct(Product* p); // riceve dall'eventuale SingleProductEdit aperto quale product eliminare
    void openEditProduct(Product* product); // riceve dal SingleProduct il puntatore al product che si vuole modificare ( per cui serve un SingleProductEdit )
    void addProductRequest(); // apre il dialog per la creazione di un nuovo product ( SingleProductCreation )
    void saveProduct(Product* p); // permette il salvataggio per product creato da un SingleProductCreation
    void refreshProductView(); // fa il refresh in base alla modalità ( mod ) in cui si trova la productView
    void onGridClicked(); // fa l'aggiornamento della modalità di visualizzazione a grid ( mod=1 )
    void onVerticalClicked(); // fa l'aggiornamento della modalità di visualizzazione vertical ( mod=2 )
    // parte di salvataggio
    void saveJson();
    void loadJson();
    void saveasJson();
    // parte filtraggio
    void filterProducts(const QString& name, double minPrice, double maxPrice,bool wished, const QString& type, const QString& extraData);
};

#endif // HOMEPAGE_H
