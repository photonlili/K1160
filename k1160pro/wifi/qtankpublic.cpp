#include "qtankpublic.h"
#include "qtankdefine.h"
#include <QSqlQuery>
#include <QSettings>
#include <QUuid>
#include <QDebug>

QSqlDatabase managerDB;
QString gUserName;
QString gPassword;

QSqlDatabase newDatabaseConn()
{
    QUuid uuid = QUuid::createUuid();
    //qDebug() << uuid.toString();
    return QSqlDatabase::addDatabase(DB_TYPE, uuid.toString());
}

void moveCenter(QWidget *w)
{
    w->move((QApplication::desktop()->width() - w->width()) / 2,
           (QApplication::desktop()->height() - w->height()) / 2);
}

//opened
void setDatabaseName(QSqlDatabase &db, QString dbName)
{
    if(db.isOpen())
        db.close();

    db.setDatabaseName(QString("%1.db").arg(dbName));

    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("QSQLITE %1 Error").arg(db.databaseName()),
                             db.lastError().text());
        return;
    }
}


void openDatabase(QSqlDatabase &db)
{
    if(db.isOpen())
        return;

    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("QSQLITE %1 Error").arg(db.databaseName()),
                             db.lastError().text());
        return;
    }
}


void closeDatabase(QSqlDatabase &db)
{
    db.close();
}


void moveRight(QWidget *w)
{
    w->move((QApplication::desktop()->width() - w->width()), 0);
}
