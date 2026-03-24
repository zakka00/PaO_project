#ifndef PRODUCT_H
#define PRODUCT_H
#include <QString>
#include "Visitors/ProductConstVisitorInterface.h"
#include "Visitors/ProductVisitorInterface.h"
#include <QJsonObject>

class Product{
private:
    QString name;
    QString description;
    double price;
    bool isWished;
    QString image_file_name;
public:
    Product(QString name, QString descriptio, double price, QString image_file_name);// di base ha il path della cartella Images dentro al progetto
    virtual ~Product() = default;

    //metodi virtuali
    virtual bool operator==(const Product& pr) const;
    // parte per il salvataggio e caricamento di Json
    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject& obj);

    // metodi virtuali puri
    virtual void accept(ProductConstVisitorInterface& visitor) const = 0;
    virtual void accept(ProductVisitorInterface& visitor) const = 0;
    virtual void rewrite(ProductVisitorInterface& visitor) = 0; // serve per salvare le informazioni in più, specifiche del tipo di prodotto
    virtual QString getType() const = 0;

    // metodi soliti
    // Getter
    QString getName() const;
    QString getDescription() const;
    double getPrice() const;
    QString getImageFileName() const;
    bool getIsWished() const;
    // Setter
    void setName(QString name);
    void setDescription(QString description);
    void setPrice(double price);
    void setImageFileName(QString image_file_name);
    void setIsWished(bool w);
};

#endif // PRODUCT_H
