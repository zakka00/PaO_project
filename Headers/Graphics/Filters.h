#ifndef FILTERS_H
#define FILTERS_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>

class Filters: public QWidget {
    Q_OBJECT
private:
    QLineEdit* searchTitle;
    QDoubleSpinBox* minPrice;
    QDoubleSpinBox* maxPrice;
    QComboBox* typeCombo;
    // wishlist
    bool wishedCheck;
    QPushButton* wishedButton;
    //
    QVBoxLayout* extraLayout;
    QGroupBox* extraBox;
    // Clothing
    QComboBox* sizeCombo = nullptr;
    QComboBox* genderCombo = nullptr;
    // Electronics
    QLineEdit* brandEdit = nullptr;
    // PrintedeMdia
    QLineEdit* authorEdit = nullptr;
public:
    Filters(QWidget* parent = 0);
    ~Filters() = default;
signals:
    void filterChanged(const QString& name, double minPrice, double maxPrice,bool wished, const QString& type, const QString& extraData); // segnale per raccogliere i dati inseriti e mandarli alla Homepage
    void refreshProducts(); // segnale per far fare il refresh alla Homepage dopo aver applicato il filtro
public slots:
    void filterProduct(); // funzione base che raccoglie i campi compilati ed emette i segnali filterChanged e refreshProducts
    void updateExtraFields(const QString& type); // aggiunge i campi extra caratteristici del tipo di rodotto
    void resetFilters(); // resetta i campi dei filtri
    void updateWishButton();
};

#endif // FILTERS_H
