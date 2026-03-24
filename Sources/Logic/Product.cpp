#include "../../Headers/Logic/Product.h"

Product::Product(QString n, QString d, double p, QString image_file_name): name(n), description(d), price(p),isWished(false), image_file_name(image_file_name){}

bool Product::operator==(const Product& pr) const{
    return typeid(*this) == typeid(pr) && description==pr.description &&
           name==pr.name && price==pr.price && image_file_name==pr.image_file_name;
}

QString Product::getName() const {return name;}
QString Product::getDescription() const {return description;}
double Product::getPrice() const {return price;}
QString Product::getImageFileName() const{return image_file_name;}
bool Product::getIsWished() const{return isWished;}
void Product::setName(QString n) {name = n;}
void Product::setDescription(QString d) {description = d;}
void Product::setPrice(double p) {price = p;}
void Product::setImageFileName(QString image_file_name){this->image_file_name=image_file_name;}
void Product::setIsWished(bool w){this->isWished=w;}
QJsonObject Product::toJson() const{
    QJsonObject obj;
    obj["type"] = this->getType();
    obj["name"] = name;
    obj["description"] = description;
    obj["price"] = price;
    obj["image_file_name"] = image_file_name;
    obj["wished"] = isWished;
    return obj;
}

void Product::fromJson(const QJsonObject& obj){
    name = obj["name"].toString();
    description = obj["description"].toString();
    price = obj["price"].toDouble();
    image_file_name = obj["image_file_name"].toString();
    isWished = obj["wished"].toBool();
}
