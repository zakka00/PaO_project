#include "../../Headers/Logic/PrintedMedia.h"

PrintedMedia::PrintedMedia(QString name, QString description, double price, QString image_file_name,QString type, QString authorOrEditor, unsigned int  pages, QString publisher):
    Product(name, description, price, image_file_name), type(type), authorOrEditor(authorOrEditor), pages(pages), publisher(publisher)
{}

bool PrintedMedia::operator==(const Product& pr) const {
    return this->Product::operator==(pr)
           && type == static_cast<const PrintedMedia&>(pr).type
           && authorOrEditor == static_cast<const PrintedMedia&>(pr).authorOrEditor
           && pages == static_cast<const PrintedMedia&>(pr).pages
           && publisher == static_cast<const PrintedMedia&>(pr).publisher;
}

QString PrintedMedia::getTypeP() const {return type;}
QString PrintedMedia::getAuthorOrEditor() const {return authorOrEditor;}
unsigned int PrintedMedia::getPages() const {return pages;}
QString PrintedMedia::getPublisher() const {return publisher;}
void PrintedMedia::setType(QString t) {type = t;}
void PrintedMedia::setAuthorOrEditor(QString a) {authorOrEditor = a;}
void PrintedMedia::setPages(unsigned int p) {pages = p;}
void PrintedMedia::setPublisher(QString p) {publisher = p;}

void PrintedMedia::accept(ProductVisitorInterface& visitor) const {
    visitor.visitPrintedMedia(*this);
}

void PrintedMedia::accept(ProductConstVisitorInterface& visitor) const {
    visitor.visitPrintedMedia(*this);
}

void PrintedMedia::rewrite(ProductVisitorInterface& visitor){
    visitor.getPrintedMedia(this);
}


// Json
QJsonObject PrintedMedia::toJson() const {
    QJsonObject obj = Product::toJson();
    obj["typeP"] = type;
    obj["authorOrEditor"] = authorOrEditor;
    obj["pages"] = static_cast<int>(pages);
    obj["publisher"] = publisher;
    return obj;
}

void PrintedMedia::fromJson(const QJsonObject& obj) {
    Product::fromJson(obj);
    type = obj["typeP"].toString();
    authorOrEditor = obj["authorOrEditor"].toString();
    pages = static_cast<unsigned int>(obj["pages"].toInt());
    publisher = obj["publisher"].toString();
}

QString PrintedMedia::getType() const { return "PrintedMedia"; }
