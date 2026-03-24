#ifndef SINGLEPRODUCTCREATION_H
#define SINGLEPRODUCTCREATION_H
#include "../../Headers/Logic/Product.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>

class SingleProductCreation: public QWidget {
    Q_OBJECT
private:
    Product* product; // quello che potenzialmente viene creato

    QVBoxLayout* layout;
    QVBoxLayout* additionalFieldsLayout;

    QString imagePath;
    QLineEdit* nameEdit;
    QPushButton* image;
    QTextEdit* descEdit;
    QDoubleSpinBox* priceSpin;
    QComboBox* typeCombo;
    // parti extra
    // Clothing
    QComboBox* sizeCombo;
    QLineEdit* materialEdit;
    QComboBox* genderCombo;
    // Electronics
    QLineEdit* brandEdit;
    QSpinBox* warrantySpin;
    QLineEdit* alimentationEdit;
    // PrintedMedia
    QLineEdit* typeEdit;
    QLineEdit* authorEdit;
    QSpinBox* pagesSpin;
    QLineEdit* publisherEdit;
public:
    SingleProductCreation(QWidget* parent=0);
    ~SingleProductCreation() = default;
public slots:
    void updateAdditionalFields(const QString& type); // aggiunge campi in base alla tipo di prodotto inserito dentro a typeCombo
    void editImage(); // permette l'aggiunta dell'immagine al product
    void createProduct(); // crea effettivamente un product basato sui dati inseriti
signals:
    void saveProduct(Product* p); // permette il salvataggio dello stesso passandolo alla Homepage
    void closeRequest(); // chiude il dialog
};

#endif // SINGLEPRODUCTCREATION_H
