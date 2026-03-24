#ifndef STORE_H
#define STORE_H
#include "Product.h"
#include "Container.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

class Store{
private:
    Container<Product*> all_products;   // tutti i prodotti dentro al file json
    Container<Product*> displayedProducts; // prodotti filtrati e attualmente mostrati
public:
    Store();
    ~Store() = default;
    void deleteProduct(Product* p);
    void addProduct(Product* p);
    Container<Product*>::Node* getHead() const;
    // salvataggio file Json
    int getSizeDisplayed() const;
    int getSizeMemory() const;
    void saveToJson(const QString& filePath, bool mod) const;
    void loadFromJson(const QString& filePath);
    // filtri
    void applyFilter(const QString& name, double minPrice, double maxPrice, bool wished, const QString& type, const QString& extraData);
};

#endif // STORE_H
