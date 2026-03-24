#include "../../Headers/Logic/Store.h"
#include "../../Headers/Logic/Electronics.h"
#include "../../Headers/Logic/Clothing.h"
#include "../../Headers/Logic/PrintedMedia.h"

Store::Store(): all_products(), displayedProducts() {}

void Store::deleteProduct(Product* p){all_products.remove(p);applyFilter("", 0.0, 10000.0,false,"All","");}
void Store::addProduct(Product* p){all_products.add(p);applyFilter("", 0.0, 10000.0,false,"All","");}
Container<Product*>::Node* Store::getHead() const{return displayedProducts.getHead();}
int Store::getSizeDisplayed() const{return displayedProducts.getSize();}
int Store::getSizeMemory() const{return all_products.getSize();}

void Store::saveToJson(const QString& filePath, bool mod) const{ // mod == true --> salva solo i prodotti filtrati, altrimenti tutti i prodotti caricati
    QJsonArray array;
    Container<Product*>::Node* current;
    if(mod){
        current = displayedProducts.getHead();
    }
    else{
        current = all_products.getHead();
    }
    while (current != nullptr) {
        array.append(current->getData()->toJson());
        current = current->getNext();
    }
    QJsonDocument doc(array);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
    }
}

void Store::loadFromJson(const QString& filePath){
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "Errore nell'apertura del file";
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) return;

    displayedProducts.clear(); // cancella solo la lista, ma i prodotti vivono ancora
    all_products.clearAll(); // cancella tutti i prodotti dentro alla lista e la lista stessa  ( evito doppia eliminazione )
    QJsonArray array = doc.array();
    for (int i = 0; i < array.size(); ++i) {
        QJsonObject obj = array[i].toObject();
        QString type = obj["type"].toString();
        Product* p = nullptr;

        if (type == "Electronics") p = new Electronics();
        else if (type == "Clothing") p = new Clothing();
        else if (type == "PrintedMedia") p = new PrintedMedia();
        else qDebug() << "Oggetto non identificato, ricontrollare";

        if (p) {
            p->fromJson(obj);
            all_products.add(p);
            applyFilter("", 0.0, 10000.0,0,"All","");
        }
    }
}

void Store::applyFilter(const QString& name, double minPrice, double maxPrice,bool wished, const QString& type, const QString& extraData) {
    displayedProducts.clear();
    Container<Product*>::Node* current = all_products.getHead();
    while (current != nullptr) {
        Product* p = current->getData();
        bool match = true;
        if(type != "All") {
            if(type == "Clothing") match = dynamic_cast<Clothing*>(p) != nullptr;
            else if(type == "Electronics") match = dynamic_cast<Electronics*>(p) != nullptr;
            else if(type == "PrintedMedia") match = dynamic_cast<PrintedMedia*>(p) != nullptr;
            else match = false;
        }

        if(match) {
            if(type == "Clothing") {
                Clothing* c = static_cast<Clothing*>(p);
                QStringList parts = extraData.split("|");
                QString gender = parts.value(0);
                QString size = parts.value(1);

                if(!gender.isEmpty() && c->getGender() != gender[0]) match = false;
                if(!size.isEmpty() && c->getSize() != size) match = false;
            }
            else if(type == "Electronics") {
                Electronics* e = static_cast<Electronics*>(p);
                if(!extraData.isEmpty() && !e->getBrand().contains(extraData, Qt::CaseInsensitive)) match = false;
            }
            else if(type == "PrintedMedia") {
                PrintedMedia* pm = static_cast<PrintedMedia*>(p);
                if(!extraData.isEmpty() && !pm->getAuthorOrEditor().contains(extraData, Qt::CaseInsensitive)) match = false;
            }
        }
        if(match) {
            bool matchesCommon = (name.isEmpty() || p->getName().contains(name, Qt::CaseInsensitive) || p->getDescription().contains(name, Qt::CaseInsensitive));
            matchesCommon &= (minPrice < 0 || p->getPrice() >= minPrice);
            matchesCommon &= (maxPrice < 0 || p->getPrice() <= maxPrice);
            if(wished && !p->getIsWished()) {
                matchesCommon = false;
            }
            match = matchesCommon;
        }
        if(match) {
            displayedProducts.add(p);
        }
        current = current->getNext();
    }
}
