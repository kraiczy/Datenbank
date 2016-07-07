#include "database.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>

Database::Database()
{

}
/**
 * @brief Database::SHOW
 * @param params
 */
void Database::SHOW(QStringList params) {
    QFile file("../Datenbank/" + params[1] + ".csv");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    } else {
        // gather all date from the file
        while (!file.atEnd()) {
            QString line = file.readLine().trimmed();
            QList<QString> words = line.split(";");
            data.append(words);
        }

        // call a function to output the gathered data
        outputData();
   }
}
/**
 * @brief Database::SELECT
 * @param params
 */
void Database::SELECT(QStringList params) {
    QString selection = params.at(1).toUpper();
    QString database;
    QString column;
    QString value;
    QList<QString> headers;
    int columnIndex;
    QList<QString> words;
    QTextStream output(stdout);

    if(params.at(2).toUpper() == "FROM") {
        database = params.at(3).toLower();

        if(params.at(4).toUpper() == "WHERE") {
            QList<QString> whereparams = params.at(5).split("=");
            column = whereparams.at(0).trimmed().toUpper();
            value = whereparams.at(1).trimmed();
        } else {
            output << "Error!" << endl;
        }
    } else {
        output << "Error!" << endl;
    }

    // Open File and get the data
    QFile file("../Datenbank/" + database + ".csv");
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << file.errorString();
    }
    else {
        while (!file.atEnd()) {
            QString line = file.readLine();
            if(headers.length() == 0) {
                headers = line.split(";");
                data.append(headers);
                columnIndex = headers.indexOf(column);
                if(columnIndex < 0) {
                    output << "Error!" << endl;
                }
            }
            words = line.split(";");
            if(words.at(columnIndex).trimmed().toLower() == value)
                data.append(words);
        }
    }

    outputData();
}
/**
 * @brief Database::INSERT
 * @param params
 */
void Database::INSERT(QStringList params) {
    QString database;
    QString valueString;
    QTextStream output(stdout);

    if(params.at(1).toUpper() == "INTO") {
        database = params.at(2).toLower();

        for(int i=3; i < params.length(); i++) {
            valueString += " " + params.at(i);
        }


        if(valueString.trimmed().left(6).toUpper() == "VALUES") {
            valueString = "\r\n" + valueString.trimmed().remove(0,7).remove(')').trimmed().split(",").join(";") + ";";

            // insert the data into the file
            QFile file("../Datenbank/" + database + ".csv");
            if (!file.open(QIODevice::Append)) {
                qDebug() << file.errorString();
            } else {
                file.write(valueString.toLocal8Bit().data());
                file.close();
            }
        } else {
            output << "Error!" << endl;
        }
    } else {
        output << "Error!" << endl;
    }
}
/**
 * @brief Database::DELETE
 * @param params
 */
void Database::DELETE(QStringList params) {
    QString database;
    QString column;
    QString value;
    QTextStream output(stdout);

    if(params.at(1).toUpper() == "FROM") {
        database = params.at(2).toLower();

        if(params.at(3).toUpper() == "WHERE") {
            QList<QString> whereparams = params.at(4).split("=");
            column = whereparams.at(0).trimmed().toUpper();
            value = whereparams.at(1).trimmed();
        } else {
            output << "Error!" << endl;
        }
    } else {
        output << "Error!" << endl;
    }

    QFile file("../Datenbank/" + database + ".csv");
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << file.errorString();
    }
    else {
        QList<QString> headers;
        int columnIndex;
        while (!file.atEnd()) {
            QString line = file.readLine();
            if(headers.length() == 0) {
                headers = line.split(";");
                columnIndex = headers.indexOf(column);
                if(columnIndex < 0) {
                    output << "Error!" << endl;
                }
            }
            QList<QString> words = line.split(";");
            if(words.at(columnIndex).trimmed().toLower() != value)
                data.append(words);
        }
    }

    // update the file;
    file.resize(0);
    QTextStream stream(&file);
    stream << "Test";
}
/**
 * @brief Database::outputData
 */
void Database::outputData() {
    QTextStream output(stdout);

    for(int i = 0; i < data.length(); i++) {
        for(int j = 0; j < data.at(i).length(); j++) {
            output << data.at(i).at(j).trimmed() << " ";
        }
        output << endl;
    }

    output << endl;

    data.clear();
}
