#ifndef MINIATURE_H
#define MINIATURE_H
#include "../Logic/Product.h"
#include <QApplication>
#include <QLabel>
#include <QGridLayout>
#include <QPixmap>
#include <QPushButton>

class Miniature: public QFrame {
    Q_OBJECT
private:
    QGridLayout* layout;
    Product* product;
    QLabel* image;
    QLabel* title;
    QLabel* price;
    QPushButton* wished;
public:
    Miniature(Product* product,int typeVisualization, QWidget* parent = 0 );// 1-> Grid, 2-> Horizontal
signals:
    void open(Product* p);// riceve dalle miniature per quale product si vorrebbe l'apertura del SingleProduct ( visualizzazione estesa del prodotto )
public:
    void mousePressEvent(QMouseEvent* event) override; // override dell'evento di click sulla miniature
    void wishButton();
};

#endif // MINIATURE_H
