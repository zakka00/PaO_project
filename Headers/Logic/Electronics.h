#ifndef ELECTRONICS_H
#define ELECTRONICS_H
#include "Product.h"

class Electronics: public Product{
private:
    QString brand;
    int warrantyMonths;
    QString alimentationType;
public:
    Electronics(QString name="", QString description="", double price=0.0, QString image_file_name="",QString brand="", int warrantyMonths=0, QString alimantationType="");
    ~Electronics() = default;
    bool operator==(const Product& pr) const override;
    void accept(ProductConstVisitorInterface& visitor) const override;
    void accept(ProductVisitorInterface& visitor) const override;
    void rewrite(ProductVisitorInterface& visitor) override;
    // Json
    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;
    virtual QString getType() const override;
    // getter
    QString getBrand() const;
    unsigned int getWarrantyMonths() const;
    QString getAlimentationType() const;

    // setter
    void setBrand(QString brand);
    void setWarrantyMonths(unsigned int months);
    void setAlimentationType(QString type);
};

#endif // ELECTRONICS_H
