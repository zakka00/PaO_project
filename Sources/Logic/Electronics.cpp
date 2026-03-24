#include "../../Headers/Logic/Electronics.h"

Electronics::Electronics(QString name, QString description, double price, QString image_file_name, QString brand, int warrantyMonths, QString alimantationType)
    : Product(name, description, price, image_file_name), brand(brand), warrantyMonths(warrantyMonths), alimentationType(alimantationType)
{};

bool Electronics::operator==(const Product& pr) const{
    return this->Product::operator==(pr)
        && brand==static_cast<const Electronics&>(pr).brand
        && warrantyMonths==static_cast<const Electronics&>(pr).warrantyMonths
        && alimentationType==static_cast<const Electronics&>(pr).alimentationType;
}

QString Electronics::getBrand() const {return brand;}
unsigned int Electronics::getWarrantyMonths() const {return warrantyMonths;}
QString Electronics::getAlimentationType() const {return alimentationType;}
void Electronics::setBrand(QString b) {brand = b;}
void Electronics::setWarrantyMonths(unsigned int m) {warrantyMonths = m;}
void Electronics::setAlimentationType(QString a) {alimentationType = a;}

void Electronics::accept(ProductConstVisitorInterface& visitor) const {
    visitor.visitElectronics(*this);
}

void Electronics::accept(ProductVisitorInterface& visitor) const {
    visitor.visitElectronics(*this);
}

void Electronics::rewrite(ProductVisitorInterface& visitor){
    visitor.getElectronics(this);
}

// Json
QJsonObject Electronics::toJson() const {
    QJsonObject obj = Product::toJson();
    obj["brand"] = brand;
    obj["warrantyMonths"] = warrantyMonths;
    obj["alimentationType"] = alimentationType;
    return obj;
}

void Electronics::fromJson(const QJsonObject& obj) {
    Product::fromJson(obj);
    brand = obj["brand"].toString();
    warrantyMonths = obj["warrantyMonths"].toInt();
    alimentationType = obj["alimentationType"].toString();
}

QString Electronics::getType() const { return "Electronics"; }
