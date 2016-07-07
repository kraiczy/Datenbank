#ifndef DATABASE_H
#define DATABASE_H

#include <QList>
#include <QString>

/**
 * @brief The Database class
 */
class Database
{
private:
    QList<QList<QString>> data;
    void outputData();

public:
    Database();
    void SHOW(QStringList params);
    void SELECT(QStringList params);
    void INSERT(QStringList params);
    void DELETE(QStringList params);
};

#endif // DATABASE_H
