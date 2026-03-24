#include "../../Headers/Graphics/SingleProduct.h"
#include "../../Headers/Logic/Visitors/ProductSingleProductVisitor.h"
#include "../../Headers/Logic/FileUtils.h"
#include <QGridLayout>
#include <QFile>
#include <QScrollArea>

SingleProduct::SingleProduct(Product* product, QWidget* parent)
    : QWidget(parent), product(product)
{
    this->setMinimumWidth(400);
    this->setMaximumWidth(500);

    QVBoxLayout* externalLayout = new QVBoxLayout(this);

    QString buttonStyleSheet = R"(
        QPushButton {
            border-radius: 15px;
            color: white;
            border: none;
            font-weight: 600;
        }
        QPushButton:hover {
            background-color: #A9A9A9;
        }
    )";

    // toolbar
    close = new QPushButton(QPixmap(":/Icons/close.png").scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation),"");
    close->setIconSize(QSize(25,25));
    close->setToolTip("Close");
    close->setFixedSize(50, 30);
    close->setStyleSheet(buttonStyleSheet);

    edit = new QPushButton(QPixmap(":/Icons/edit.png").scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation),"");
    edit->setIconSize(QSize(25,25));
    edit->setToolTip("Edit");
    edit->setFixedSize(50, 30);
    edit->setStyleSheet(buttonStyleSheet);

    QHBoxLayout* topBar = new QHBoxLayout();
    topBar->addWidget(close);
    topBar->addStretch();
    topBar->addWidget(edit);
    externalLayout->addLayout(topBar);


    QLabel* title = new QLabel(product->getName(), this);
    title->setStyleSheet("color: #444; font-weight: bold; font-size: 25px;");
    externalLayout->addWidget(title, 0, Qt::AlignCenter);

    QLabel* image = new QLabel(this);
    image->setFixedSize(350, 350);
    image->setAlignment(Qt::AlignCenter);
    QString path = FileUtils::getProjectPath() + "/Images/" + product->getImageFileName();
    QPixmap img(path);
    if (!img.isNull()) {
        image->setPixmap(img.scaledToHeight(350,Qt::SmoothTransformation));
        image->setStyleSheet("background-color: lightgray;");
    } else {
        image->setText("No Image");
        image->setStyleSheet("color: #888; font-style: italic; background-color: lightgray;");
    }
    externalLayout->addWidget(image, 0, Qt::AlignCenter);


    double prezzo = product->getPrice();
    int parteIntera = static_cast<int>(prezzo);
    int parteDecimale = static_cast<int>((prezzo - parteIntera) * 100 + 0.5);
    QString prezzoFormattato = QString("\n€ <span style='font-size:25px; font-weight:bold;'>%1</span><span style='font-size:15px;'>,%2</span>").arg(parteIntera).arg(parteDecimale, 2, 10, QChar('0'));

    QLabel* price = new QLabel(prezzoFormattato, this);
    price->setStyleSheet("color: #333;");
    price->setTextFormat(Qt::RichText);
    externalLayout->addWidget(price, 0, Qt::AlignLeft);

    QWidget* scrollWidget = new QWidget();
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollWidget);

    // visitor
    ProductSingleProductVisitor visitor;
    product->accept(visitor);
    scrollLayout->addLayout(visitor.getWidget());

    // descrizione scorrevole
    QLabel* desc = new QLabel("<u>Description:</u>");
    desc->setStyleSheet("color: #333; font-size:18px; ");
    scrollLayout->addWidget(desc);
    QLabel* description = new QLabel(product->getDescription(), this);
    description->setWordWrap(true);
    description->setStyleSheet("color: #333; font-size:18px; ");
    description->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    description->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QScrollArea* scroll = new QScrollArea(this);
    scroll->setWidget(description);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollLayout->addWidget(scroll);

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

    externalLayout->addWidget(scrollArea);

    //connessioni
    connect(close, &QPushButton::clicked, this, &SingleProduct::closeView);
    connect(edit, &QPushButton::clicked, this, [this]() {emit editProduct(this->product);});
}
