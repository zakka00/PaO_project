#ifndef DIALOGMESSAGE_H
#define DIALOGMESSAGE_H
#include <QMessageBox>
class DialogMessage{ // classe per evitare ogni volta di settare l'icona ( si potevano usare le chiamate statiche a QMessageBox, ma usano icone predefinite loro )
public:
    static void message(QWidget* parent, const QString& title,const QString& message){
        QMessageBox msgBox(parent);
        msgBox.setWindowTitle(title);
        msgBox.setText(message);
        msgBox.setIconPixmap(QPixmap(":/Icons/logo.png").scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
    }
};

#endif // DIALOGMESSAGE_H
