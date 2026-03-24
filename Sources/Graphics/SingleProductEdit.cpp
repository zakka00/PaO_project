#include "../../Headers/Graphics/SingleProductEdit.h"
#include <QLabel>
#include <QGridLayout>
#include <QFile>
#include <QDialog>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDir>
#include <QFileDialog>
#include "../../Headers/Logic/FileUtils.h"
#include "../../Headers/Graphics/DialogMessage.h"
#include <QMessageBox>
#include <QTimer>
#include <QScrollArea>

SingleProductEdit::SingleProductEdit(Product* product, QWidget* parent) : QWidget(parent), product(product) {
    this->setMinimumWidth(400);
    this->setMaximumWidth(500);
    imagePath = QString(FileUtils::getProjectPath() + "/Images/" + product->getImageFileName());
    QString stylesheet = R"(
        QPushButton {
            border-radius: 15px;
            color: white;
            border: none;
            padding: 6px 12px;
            font-weight: 600;
        }
        QPushButton:hover {
            background-color: #A9A9A9;
        }
    )";
    QString deleteButtonStyle = R"(
        QPushButton {
            background-color: #FFCCCB;
            border-radius: 15px;
            color: white;
            border: none;
            padding: 6px;
            font-weight: 600;
        }
        QPushButton:hover {
            background-color: #E0666A;
        }
    )";

    // Pulsanti in alto
    QPushButton* close = new QPushButton(QPixmap(":/Icons/close.png").scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation),"");
    close->setIconSize(QSize(25,25));
    close->setFixedSize(50,30);
    close->setToolTip("Close this tab");
    close->setStyleSheet(stylesheet);

    QPushButton* edit = new QPushButton(QPixmap(":/Icons/save.png").scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation),"");
    edit->setIconSize(QSize(25,25));
    edit->setFixedSize(50,30);
    edit->setToolTip("Save changes");
    edit->setStyleSheet(stylesheet);

    QPushButton* del = new QPushButton(QPixmap(":/Icons/delete.png").scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation),"");
    del->setIconSize(QSize(25,25));
    del->setFixedSize(50,30);
    del->setToolTip("Delete this product");
    del->setStyleSheet(deleteButtonStyle);

    QHBoxLayout* topLayout = new QHBoxLayout();
    topLayout->addWidget(close, 0, Qt::AlignLeft);
    topLayout->addWidget(del,   0, Qt::AlignCenter);
    topLayout->addWidget(edit,  0, Qt::AlignRight);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);

    QWidget* scrollWidget = new QWidget();
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollWidget);

    // Immagine prodotto
    image = new QPushButton();
    image->setFixedSize(370, 250);
    QString stylesheetImage = "color: #888; font-style: italic; background-color: lightgray;";
    QString path = FileUtils::getProjectPath() + "/Images/" + product->getImageFileName();
    QPixmap img = QPixmap(path);
    if (!img.isNull()) {
        QPixmap scaledImg = img.scaled(image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        image->setIcon(QIcon(scaledImg));
        image->setIconSize(QSize(400, 250));
        image->setStyleSheet(stylesheetImage);
    } else {
        image->setText("No Image selected \n( optional )");
        image->setStyleSheet(stylesheetImage);
    }
    image->setToolTip(FileUtils::getProjectPath() + "/Images/" + product->getImageFileName());
    QHBoxLayout* imageLayout = new QHBoxLayout();
    imageLayout->addStretch();
    imageLayout->addWidget(image);
    imageLayout->addStretch();
    mainLayout->addLayout(imageLayout);

    scrollLayout->addWidget(new QLabel("Name:"));
    nameEdit = new QLineEdit(product->getName());
    scrollLayout->addWidget(nameEdit);

    scrollLayout->addWidget(new QLabel("Description:"));
    descEdit = new QTextEdit();
    descEdit->setText(product->getDescription());
    scrollLayout->addWidget(descEdit);

    scrollLayout->addWidget(new QLabel("Price:"));
    priceSpin = new QDoubleSpinBox();
    priceSpin->setRange(0, 99999);
    priceSpin->setValue(product->getPrice());
    scrollLayout->addWidget(priceSpin);

    // Visitor
    visitor = new ProductEditorVisitor();
    product->accept(*visitor);
    scrollLayout->addLayout(visitor->getLayout());

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

    mainLayout->addWidget(scrollArea);

    // Connessioni
    connect(close, &QPushButton::clicked, this, &SingleProductEdit::closeRequested);
    connect(edit,  &QPushButton::clicked, this, &SingleProductEdit::edit);
    connect(del,   &QPushButton::clicked, this, &SingleProductEdit::clickDelete);
    connect(image, &QPushButton::clicked, this, &SingleProductEdit::editImage);
}

void SingleProductEdit::edit() {
    QString errors;
    QString newName = nameEdit->text().trimmed();
    QString newDesc = descEdit->toPlainText().trimmed();
    double newPrice = priceSpin->value();
    if (newName.isEmpty()) {
        errors += " - name\n";
    }
    if (newDesc.isEmpty()) {
        errors += " - description\n";
    }
    if (newPrice <= 0) {
        errors += " - valid price (> 0)\n";
    }
    try {
        product->rewrite(*visitor);
    }
    catch (const std::exception& e) {
        errors += e.what();
    }

    if (!errors.isEmpty()) {
        DialogMessage::message(this, "Not compiled right", "You forgot to compile:\n" + errors);
        return;
    }
    visitor->getCommon(product,newName, newDesc, newPrice, QFileInfo(imagePath).fileName());
    DialogMessage::message(this, "Product saved", "The product has been edited correctly");
    emit refresh();
}

void SingleProductEdit::clickDelete(){
    emit delProduct(product);
    emit refresh();
}

void SingleProductEdit::editImage() {
    QString fileName = QFileDialog::getOpenFileName(this,tr("Select an image"),FileUtils::getProjectPath(),tr("Immagini (*.png *.jpg *.jpeg *.bmp)"));
    if (!fileName.isEmpty()) {
        QPixmap img(fileName);
        if (!img.isNull()) {
            image->setIcon(QIcon(img));
            image->setIconSize(QSize(400, 250));
            image->setText("");
            image->setStyleSheet("background-color: lightgray;");
            imagePath = fileName;
            image->setToolTip("Current image:"+ fileName + "\nClick to change it!");
        }
    }
}
