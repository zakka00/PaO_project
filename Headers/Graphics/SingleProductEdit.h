#ifndef SINGLEPRODUCTEDIT_H
#define SINGLEPRODUCTEDIT_H
#include "../Logic/Product.h"
#include "../../Headers/Logic/Visitors/ProductEditorVisitor.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class SingleProductEdit: public QWidget {
    Q_OBJECT
private:
    Product* product;
    ProductEditorVisitor* visitor;
    QLineEdit* nameEdit;
    QPushButton* image;
    QTextEdit* descEdit;
    QDoubleSpinBox* priceSpin;
    // quella caricata sul tasto image
    QString imagePath;
public:
    SingleProductEdit(Product* product, QWidget* parent = 0);
    ~SingleProductEdit() = default;
signals:
    void refresh(); // fa fare il refresh alla Homapage
    void closeRequested(); // fa chiudere la visualizzazione estesa del product
    void delProduct(Product* p); // passa a Homepage il puntatore al prodotto che si vorrebbe eliminare
public slots:
    void edit(); // fa controlli ed apporta modifiche al product
    void clickDelete(); // passa emette delProduct passando a Homepage il product da eliminare
    void editImage(); // permette al modofica di ciò che viene visualizzato sul tasto image
};

#endif // SINGLEPRODUCTEDIT_H
