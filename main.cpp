#include <QCoreApplication>
#include <stdio.h>
#include <iostream>
#include <QTextStream>
#include <string>
#include <QString>
#include <QFile>
#include <QDebug>
#include "database.h"

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Database db;
    QTextStream input(stdin);
    QTextStream output(stdout);
    QString command;

    while(true) {
        command = input.readLine();
        QStringList commands = command.split(" ");

        if(commands.at(0).toUpper() == "SHOW") {
            //outputData(SHOW(commands));
            db.SHOW(commands);
        }
        else if(commands.at(0).toUpper() == "DELETE") {
            db.DELETE(commands);
        }
        else if(commands.at(0).toUpper() == "INSERT") {
            db.INSERT(commands);
        }
        else if(commands.at(0).toUpper() == "SELECT") {
            db.SELECT(commands);
        }
        else {
            output << "Command not valid!" << endl;
        }
    }

    return a.exec();
}
