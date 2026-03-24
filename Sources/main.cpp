#include <QApplication>
#include "../Headers/Graphics/Homepage.h"
#include <QRandomGenerator>
#include <QImageReader>
#include <QFile>
#include <QLabel>
#include <QDir>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Store* store = new Store();
    Homepage w = Homepage(store);
    a.setWindowIcon(QPixmap(":/Icons/logo.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    w.show();
    return a.exec();
}
