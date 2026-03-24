#include "../../Headers/Graphics/ProductsView.h"
#include "../../Headers/Graphics/Miniature.h"
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>


ProductsView::ProductsView(Store* store, QWidget* parent): QWidget(parent), store(store){
    mainLayout = new QHBoxLayout(this);
    this->setMinimumHeight(150);
    this->setMinimumWidth(745);
    gridView();

}


void ProductsView::gridView(int columns) {
    clearLayout(mainLayout);
    if(store->getSizeDisplayed() == 0){
        noProductsFound();
        return;
    }
    QLabel* loading = new QLabel("Caricamento...", this);
    loading->setStyleSheet("background-color: rgba(0,0,0,160); color: white; font-size: 18px;");
    loading->setAlignment(Qt::AlignCenter);
    loading->resize(this->size());
    loading->show();

    QTimer::singleShot(100, this, [this, loading, columns]() {
        scrollArea = new QScrollArea();
        scrollArea->setWidgetResizable(true);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        QWidget* productsContainer = new QWidget();
        QGridLayout* gridLayout = new QGridLayout(productsContainer);
        gridLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        int row = 0;
        int col = 0;
        Container<Product*>::Node* current = store->getHead();
        while (current != nullptr) {
            if (current->getData()) {
                Miniature* m = new Miniature(current->getData(), 1);
                connect(m, &Miniature::open, this, &ProductsView::openProduct);
                gridLayout->addWidget(m, row, col, Qt::AlignLeft );
                col++;
                if (col == columns) {
                    col = 0;
                    row++;
                }
            }
            current = current->getNext();
        }
        productsContainer->setLayout(gridLayout);
        scrollArea->setWidget(productsContainer);
        mainLayout->addWidget(scrollArea, 1);
        loading->deleteLater();
    });
}

void ProductsView::VerticalView() {
    clearLayout(mainLayout);
    if(store->getSizeDisplayed() == 0){
        noProductsFound();
        return;
    }

    QLabel* loading = new QLabel("Caricamento...", this);
    loading->setStyleSheet("background-color: rgba(0,0,0,160); color: white; font-size: 18px;");
    loading->setAlignment(Qt::AlignCenter);
    loading->resize(this->size());
    loading->show();
    QTimer::singleShot(100, this, [this, loading]() {
        scrollArea = new QScrollArea();
        scrollArea->setWidgetResizable(true);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        QWidget* productsContainer = new QWidget();
        QVBoxLayout* verticalLayout = new QVBoxLayout(productsContainer);
        verticalLayout->setAlignment(Qt::AlignTop);
        Container<Product*>::Node* current = store->getHead();
        while (current != nullptr) {
            Miniature* m = new Miniature(current->getData(), 2);
            connect(m, &Miniature::open, this, &ProductsView::openProduct);
            verticalLayout->addWidget(m);
            current = current->getNext();
        }
        productsContainer->setLayout(verticalLayout);
        scrollArea->setWidget(productsContainer);
        mainLayout->addWidget(scrollArea, 1);

        loading->deleteLater();
    });
}

void ProductsView::noProductsFound(){
    QLabel* emptyLabel = new QLabel("There are no products right now", this);
    emptyLabel->setStyleSheet("color: #888; font-style: italic; background-color: lightgray;");
    emptyLabel->setAlignment(Qt::AlignCenter);
    QFont font = emptyLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    emptyLabel->setFont(font);
    mainLayout->addWidget(emptyLabel);
}

void ProductsView::clearLayout(QLayout *layout) {
    if (!layout)
        return;
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget *w = item->widget()) {
            w->setParent(nullptr);
            delete w;
        }
        else if (QLayout *childLayout = item->layout()) {
            clearLayout(childLayout);
            delete childLayout;
        }
        delete item;
    }
}
