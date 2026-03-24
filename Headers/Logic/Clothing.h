#ifndef CLOTHING_H
#define CLOTHING_H
#include "Product.h"

class Clothing: public Product{
private:
    QString size; // S,M,L,XL,XXL,XS
    QString material;
    QChar gender; // M,F,U
public:
    Clothing(QString name="", QString description="", double price=0.0, QString image_file_name="", QString size="", QString material="", QChar gender=QChar());
    ~Clothing() = default;
    bool operator==(const Product& pr) const override;
    void accept(ProductConstVisitorInterface& visitor) const override;
    void accept(ProductVisitorInterface& visitor) const override;
    void rewrite(ProductVisitorInterface& visitor) override;
    // Json
    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;
    virtual QString getType() const override;
    // getter
    QString getSize() const;
    QString getMaterial() const;
    QChar getGender() const;
    // setter
    void setSize(QString size);
    void setMaterial(QString material);
    void setGender(QChar gender);
};

#endif // CLOTHING_H
