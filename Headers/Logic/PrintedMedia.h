#ifndef PRINTEDMEDIA_H
#define PRINTEDMEDIA_H
#include "Product.h"
class PrintedMedia: public Product{
private:
    QString type;
    QString authorOrEditor;
    unsigned int pages;
    QString publisher;
public:
    PrintedMedia(QString name="", QString description="", double price=0.0, QString image_file_name="",QString type="", QString authorOrEditor="", unsigned int pages=0, QString publisher="");
    ~PrintedMedia() = default;
    bool operator==(const Product& pr) const override;
    void accept(ProductConstVisitorInterface& visitor) const override;
    void accept(ProductVisitorInterface& visitor) const override;
    void rewrite(ProductVisitorInterface& visitor) override;
    // Json
    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;
    virtual QString getType() const override;
    // getter
    QString getTypeP() const;
    QString getAuthorOrEditor() const;
    unsigned int getPages() const;
    QString getPublisher() const;

    // setter
    void setType(QString type);
    void setAuthorOrEditor(QString authorOrEditor);
    void setPages(unsigned int pages);
    void setPublisher(QString publisher);
};

#endif // PRINTEDMEDIA_H
