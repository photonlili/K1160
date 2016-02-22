#include <QtSql/QSqlQuery>
#include <QObject>
#include <QTextStream>
#include "qdatabasequery.h"



QDatabasequery::QDatabasequery(QObject *parent) :
    QObject(parent)
{
}

QDatabasequery::~QDatabasequery()
{
    _db.close();
}

void QDatabasequery::SetTableName(QString table)
{
    _tableName = table + ".db";
}


/*
    打开数据库.
*/
bool QDatabasequery::opendatabase()
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(_tableName);

    return _db.open();
}

void QDatabasequery::cloesdatabase()
{
    _db.close();
}

/*
    插入函数.
    构造SQL插入语句.
*/
bool QDatabasequery::insert(QString &table, QStringList &names, QStringList &values)
{
    if (names.size() != values.size())
    {
        return false;
    }

    QSqlQuery query(QSqlDatabase::database());

    QString sql = QString("insert into ") + table + QString("(");

    int i;

    for (i=0; i < names.size(); i++)
    {
        sql = sql + names.value(i);
        if (i != names.size() - 1)
        {
            sql+=QString(",");
        }
        else
        {

            sql = sql + QString(")");
        }
    }

    sql = sql + QString("values (");

    for (i = 0; i < values.size(); i++)
    {
        sql = sql + QString("'") + values.value(i) + QString("'");
        if (i != values.size()-1)
        {
            sql = sql + QString(",");
        }
    }

    sql = sql + QString(")");

    QTextStream cout(stdout, QIODevice::WriteOnly);
    cout << sql << endl;
    if (query.exec(sql))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
    修改函数.
    构造SQL修改语句.
*/
bool QDatabasequery::Updata(QString &table, QStringList &names, QStringList &values, QString &expression)
{
    if (names.size() != values.size())
    {
        return false;
    }

    //UPDATE 表名称 SET 列名称 = 新值 WHERE 列名称 = 某值
    QSqlQuery query(QSqlDatabase::database());
    QString sql = QString("update ")+table+QString(" set ");
    for (int i = 0; i < names.size(); i++)
    {
        sql = sql + names.value(i);
        sql = sql + QString(" = '");
        sql = sql + values.value(i);
        sql = sql + QString("'");
        if (i != names.size()-1)
        {
            sql = sql + QString(" ,");
        }
    }

    sql = sql + QString(" where ") + expression;
    if (query.exec(sql))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
    删除函数.
    构造SQL删除语句.
*/
bool QDatabasequery::del(QString &table, QString &srcDatacloum, QString &expression)
{
    //DELETE FROM 表名称 WHERE 列名称 = 值
    QSqlQuery query(QSqlDatabase::database());
    QString sql = QString("delete from ") + table + QString(" where ") + srcDatacloum + QString("='") + expression + QString("'");

    if (query.exec(sql))
    {
        return true;
    }
    else
    {
        return false;
    }
}


void QDatabasequery::GetValues(QString &table, QStringList &values, int index)
{
    QSqlQuery query(QSqlDatabase::database());
    QString sql = QString("select * from ") + table;
    query.exec(sql);
    while (query.next())
    {
        values << query.value(index).toString();
    }
}

int QDatabasequery::GetSize(QString &table)
{
    QSqlQuery query(QSqlDatabase::database());
    QString sql = QString("select * from ") + table;
    query.exec(sql);
    return query.size();
}

void QDatabasequery::GetoneValues(QString &table, QStringList &values, QString &srcDatacloum, QString &strData, int num)
{
    QSqlQuery query(QSqlDatabase::database());
    //QString sql = "select * from method where mingcheng='qq'";//QString("select * from ") + table + QString(" where ") + srcDatacloum + QString("='") + strData + QString("'");
    QString sql = QString("select * from ") + table + QString(" where ") + srcDatacloum + QString("='") + strData + QString("'");


    if(true == query.exec(sql))
    {
        query.next();

        for(int i = 0; i < num; i++)
        {
            values.append(query.value(i).toString());
        }

    }

}

void QDatabasequery::GetSetionValues(QString &table, QStringList &values, int ilimit, int ioffset)
{
    QSqlQuery query(QSqlDatabase::database());
    QString sql = QString("select * from ") + table + QString(" limit ") + ilimit + QString(" offset ") + ioffset;

    if(true == query.exec(sql))
    {
        query.next();
        //values.append(query);

    }
}
