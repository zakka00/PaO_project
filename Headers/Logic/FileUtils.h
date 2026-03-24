#ifndef FILEUTILS_H
#define FILEUTILS_H
#include <QString>
#include <QDir>
#include <QCoreApplication>

class FileUtils {
public:
    // base, ma funziona solo se si esegue dentro una cartella e-commerce che non è una sotto cartella di un'altra cartella e-commerce
    /*
    static QString getProjectPath(){
        QString currentPath = QCoreApplication::applicationDirPath();
        int pos = currentPath.indexOf("e-commerce");
        if(pos != -1){
            return currentPath.left(pos+QString("e-commerce").length());
        }
        return "";
    }*/

    static QString getProjectPath() {
        // parte dalla cartella più interna nominata e-commerce e continua a risalire di cartella finche non trova quella giusta,
        // ovvero quella con dentro /Images ( in realtà anche /Icons, /Exaples, /Headers e /Sources )
        QString currentPath = QCoreApplication::applicationDirPath();
        int pos = currentPath.lastIndexOf("e-commerce");
        while (pos != -1) {
            QString basePath = currentPath.left(pos + QString("e-commerce").length());
            if (QDir(basePath+"/Images").exists() && QDir(basePath+"/Exaples").exists()) {
                return basePath;
            }
            pos = currentPath.lastIndexOf("e-commerce", pos - 1);
        }

        return "";
    }

    static void moveToImages(const QString& imagePath) {
        QFileInfo info(imagePath);
        QString destination = getProjectPath() + "/Images/" + info.fileName();
        // Se il file scelto si trova già nella cartella Images, non copiare
        if (getProjectPath() + "/Images" == info.absolutePath()) {
            qDebug() << "File già nella cartella Images";
        } else {
            if (QFile::exists(destination)) { // elimino duplicati
                QFile::remove(destination);
            }
            if (QFile::copy(imagePath, destination)) {
                qDebug() << "Copia riuscita in:" << destination;
            } else {
                qDebug() << "Errore durante la copia";
            }
        }
    }
};

#endif // FILEUTILS_H
