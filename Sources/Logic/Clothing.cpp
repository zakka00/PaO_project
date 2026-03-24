#include "../../Headers/Logic/Clothing.h"

Clothing::Clothing(QString name, QString description, double price, QString image_file_name, QString size, QString material, QChar gender):
    Product(name, description, price, image_file_name), size(size), material(material), gender(gender)
{}

bool Clothing::operator==(const Product& pr) const {
    return this->Product::operator==(pr)
    && size==static_cast<const Clothing&>(pr).size
    && material==static_cast<const Clothing&>(pr).material
    && gender==static_cast<const Clothing&>(pr).gender;
}

QString Clothing::getSize() const{return size;}
QString Clothing::getMaterial() const{return material;};
QChar Clothing::getGender() const{return gender;};
void Clothing::setSize(QString size){this->size=size;}
void Clothing::setMaterial(QString material){this->material=material;}
void Clothing::setGender(QChar gender){this->gender=gender;}

// visitor
void Clothing::accept(ProductConstVisitorInterface& visitor) const {
    visitor.visitClothing(*this);
}

void Clothing::accept(ProductVisitorInterface& visitor) const {
    visitor.visitClothing(*this);
}

void Clothing::rewrite(ProductVisitorInterface& visitor) {
    visitor.getClothing(this);
}

// Json
QJsonObject Clothing::toJson() const {
    QJsonObject obj = Product::toJson();
    obj["size"] = size;
    obj["material"] = material;
    obj["gender"] = QString(gender);
    return obj;
}

void Clothing::fromJson(const QJsonObject& obj) {
    Product::fromJson(obj);
    size = obj["size"].toString();
    material = obj["material"].toString();
    gender = obj["gender"].toString()[0];
}

QString Clothing::getType() const { return "Clothing"; }
