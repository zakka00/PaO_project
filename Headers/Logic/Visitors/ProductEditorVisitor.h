#ifndef PRODUCTEDITORVISITOR_H
#define PRODUCTEDITORVISITOR_H
#include "ProductVisitorInterface.h"
#include "../../../Headers/Logic/Product.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QComboBox>

class ProductEditorVisitor : public ProductVisitorInterface {
private:
    QVBoxLayout* layout;
    // Clothing
    QComboBox* sizeCombo;
    QLineEdit* materialEdit;
    QComboBox* genderCombo;
    // Electronics
    QLineEdit* brandEdit;
    QSpinBox* warrantySpin;
    QLineEdit* alimentationEdit;
    // PrintedMedia
    QLineEdit* typeEdit;
    QLineEdit* authorEdit;
    QSpinBox* pagesSpin;
    QLineEdit* publisherEdit;
public:
    // parte di visitor
    ProductEditorVisitor();
    void visitClothing(const Clothing& c) override;
    void visitElectronics(const Electronics& e) override;
    void visitPrintedMedia(const PrintedMedia& p) override;
    QVBoxLayout* getLayout() const;

    void getClothing(Clothing* c) const override;
    void getElectronics(Electronics* e) const override;
    void getPrintedMedia(PrintedMedia* p) const override;
    void getCommon(Product* p,QString name, QString description, int price, QString imageFileName) const;
};
#endif // PRODUCTEDITORVISITOR_H
