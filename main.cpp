#include <QCoreApplication>
#include <stdio.h>
#include <iostream>
#include <QTextStream>
#include <string>
#include <QString>
#include <QFile>
#include <QDebug>

/**
 * @brief SHOW
 * @param params
 * @return A multidimensional List of the requested data
 */
QList<QList<QString>> SHOW(QStringList params){
    QFile file("C:/Users/Fabian/Desktop/Uni/2Semester/Grundlagen der Informatik/Projekt/" + params[1] + ".csv");

    QList<QList<QString>> data;

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
        return data;
   }
}

void DELETE(QStringList params){

    for(int i = 1; i<params.length(); i++) {
        qDebug() << params.at(i);
    }

    QList<QList<QString>> data;
    QString database;
    QString column;
    QString value;

    if(params.at(1).toUpper() == "FROM") {
        database = params.at(2).toLower();

        if(params.at(3).toUpper() == "WHERE") {
            QList<QString> whereparams = params.at(4).split("=");
            column = whereparams.at(0).trimmed().toUpper();
            value = whereparams.at(1).trimmed();
        } else {
            //error
        }
    } else {
        //error
    }

    QFile file("C:/Users/Fabian/Desktop/Uni/2Semester/Grundlagen der Informatik/Projekt/Datenbank" + database + ".csv");
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
                    //error
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
    stream << "Tesz";
}

QList<QList<QString>> INSERT(QStringList params){
    QFile file("C:/Users/Fabian/Desktop/Uni/2Semester/Grundlagen der Informatik/Projekt/" + params[1] + ".csv");

    QList<QList<QString>> data;
}

QList<QList<QString>> SELECT(QStringList params){
    QFile file("C:/Users/Fabian/Desktop/Uni/2Semester/Grundlagen der Informatik/Projekt/" + params[1] + ".csv");

    QList<QList<QString>> data;
}

void outputData(QList<QList<QString>> data) {
    QTextStream output(stdout);

    for(int i = 0; i < data.length(); i++) {
        for(int j = 0; j < data.at(i).length(); j++) {
            output << data.at(i).at(j) << " ";
        }
        output << endl;
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream input(stdin);
    QTextStream output(stdout);
    QString command;

    QStringList rowOfData;
    QStringList rowData;
    QString data;
    QFile importedCSV("Namen.csv");
    rowOfData.clear();
    rowData.clear();

    if (importedCSV.open(QFile::ReadOnly))
    {
        data = importedCSV.readAll();
        rowOfData = data.split("\n");
        importedCSV.close();
    }


    while(true) {
        command = input.readLine();

        QStringList commands = command.split(" ");

        if(commands.at(0).toUpper() == "SHOW") {
            outputData(SHOW(commands));
        }
        else if(commands.at(0).toUpper() == "DELETE") {
            DELETE(commands);
        }
        else if(commands.at(0).toUpper() == "INSERT") {
            INSERT(commands);
        }
        else if(commands.at(0).toUpper() == "SELECT") {
            SELECT(commands);
        }
        else {
            output << "Command not valid!" << endl;
        }
    }

    return a.exec();
}
