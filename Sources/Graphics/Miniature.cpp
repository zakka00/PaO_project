#include "../../Headers/Graphics/Miniature.h"
#include "../../Headers/Logic/Visitors/ProductIconVisitor.h"
#include "../../Headers/Logic/FileUtils.h"
#include <QFile>
#include <QResource>
#include <QMouseEvent>
#include <QMenu>
#include <QContextMenuEvent>
#include <QTimer>
#include <QDir>

Miniature::Miniature(Product* product,int typeVisualization, QWidget* parent) : QFrame(parent), product{product} {
    this->setObjectName("miniature");
    layout = new QGridLayout(this);
    image = new QLabel();
    title = new QLabel("<span style='font-size:15px;color:#404040'><b>" + product->getName() + "</b></span>");
    title->setToolTip(product->getName());
    // prezzo stile amazon
    double prezzo = product->getPrice();
    int parteIntera = static_cast<int>(prezzo);
    int parteDecimale = static_cast<int>((prezzo - parteIntera) * 100 + 0.5);
    QString prezzoFormattato = QString("\n€ <span style='font-size:18px; font-weight:bold;color:#404040;'>%1</span><span style='font-size:10px;'>,%2</span>").arg(parteIntera).arg(parteDecimale, 2, 10, QChar('0'));
    price = new QLabel(prezzoFormattato);

    // cerca l'immagine prima tra quelle cartella Images apposita, altrimenti la indica come mancante
    QString path = FileUtils::getProjectPath() + "/Images/" + product->getImageFileName();
    if(!QFile::exists(path)){
        path = ":/Icons/NoImage.png";
    }
    QPixmap img(path);

    wished = new QPushButton();
    wished->setStyleSheet(R"(
            QPushButton {
                border-radius: 10px;
                color: white;
                border: none;
                font-weight: 600;
            }
            QPushButton:hover {
                background-color: #A9A9A9;
            }
        )");
    if(product->getIsWished()){
        wished->setIcon(QIcon(QPixmap(":/Icons/full.png").scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    } else {
        wished->setIcon(QIcon(QPixmap(":/Icons/empty.png").scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    }
    wished->setIconSize(QSize(25, 25));
    wished->setFixedSize(35, 35);

    if( typeVisualization == 1 ){ // visualizzazione tipo griglia
        title->setFixedWidth(180);
        title->setWordWrap(false);
        title->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        QFontMetrics metrics(title->font());
        QString elidedText = metrics.elidedText(product->getName(),Qt::ElideRight,title->width());
        title->setText("<span style='font-size:15px;color:#404040'><b>" + elidedText + "</b></span>");
        image->setFixedSize(200,200);
        this->setFixedSize(220,300);
        image->setPixmap(img.scaledToHeight(200, Qt::SmoothTransformation));
        layout->addWidget(image, 0, 0, 6, 2);
        layout->addWidget(title, 7, 0);
        layout->addWidget(price, 8, 0);
        layout->addWidget(wished,8,2,1,1,Qt::AlignRight|Qt::AlignBottom);
        // visitor
        ProductIconVisitor visitor;
        product->accept(visitor);
        layout->addWidget(visitor.getWidget(), 0, 0, 1, 1,Qt::AlignLeft |Qt::AlignTop );
        //tooltip
        this->setToolTip("Description:\n" + product->getDescription());
    }
    else if( typeVisualization == 2 ){ // visualizzazione tipo lista
        image->setFixedHeight(175);
        this->setFixedHeight(200);
        image->setPixmap(img.scaledToHeight(170, Qt::SmoothTransformation));
        layout->addWidget(image, 0, 0, 6, 1);
        layout->addWidget(title, 0, 1);
        layout->addWidget(price, 1, 1);
        // visitor
        ProductIconVisitor visitor;
        product->accept(visitor);
        layout->addWidget(visitor.getWidget(), 0, 2,1,1, Qt::AlignRight | Qt::AlignTop);
        // classica descrizione
        QLabel* description = new QLabel(this);
        description->setText("<div style='font-size:15px;margin-top:2px;'>" + product->getDescription() + "</div>");
        description->setWordWrap(true);
        layout->addWidget(description, 2, 1, 2, 2);
        layout->addWidget(wished, 5, 2, 1, 1, Qt::AlignRight | Qt::AlignBottom);
    }
    image->setStyleSheet("background-color: lightgray;");
    image->setAlignment(Qt::AlignCenter);
    this->setStyleSheet(R"(
        QFrame#miniature {
            border: 1px solid #888;
            border-radius: 8px;
            background-color: #f9f9f9;
        }
        QFrame#miniature:hover {
            border: 1px solid #333;
            background-color: #f0f0f0;
        }
    )");
    // connessioni
    connect(wished,&QPushButton::clicked,this,&Miniature::wishButton);
}

//override dell'evento di click sul mouse dei QFrame...evitabile se avessi usato un Widget cliccabile...
void Miniature::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        emit open(product);
    }
    QFrame::mousePressEvent(event);
}

void Miniature::wishButton(){
    if(product->getIsWished()){
        wished->setIcon(QPixmap(":/Icons/empty.png").scaled(35, 35, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        product->setIsWished(false);
    }
    else{
        wished->setIcon(QPixmap(":/Icons/full.png").scaled(35, 35, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        product->setIsWished(true);
    }
}



