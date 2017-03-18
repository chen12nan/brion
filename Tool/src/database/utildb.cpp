#include "utildb.h"
#include <QtSql>
#include <QDir>
#include <QDebug>

static const char *contacts_schema[] =
{
    "PRAGMA encoding = \"UTF-8\"",
    "CREATE TABLE Contacts ( "
    "contactId INTEGER PRIMARY KEY ASC AUTOINCREMENT,"
    "displayLabel TEXT,"
    "firstName TEXT,"
    "lowerFirstName TEXT,"
    "lastName TEXT,"
    "lowerLastName TEXT,"
    "middleName TEXT,"
    "organization TEXT,"
    "gender TEXT,"
    "avatar TEXT,"
    "ringtone TEXT,"
    "syncTarget TEXT NOT NULL,"
    "note TEXT,"
    "pingyinName TEXT,"
    "lowerPingyinName TEXT,"
    "t9Index TEXT,"
    "birthday DATETIME,"
    "created DATETIME,"
    "modified DATETIME,"
    "mdmId INTEGER,"
    "calendarId INTEGER,"
    "isFavorite BOOL,"
    "hasPhoneNumber BOOL,"
    "hasEmailAddresses BOOL,"
    "hasUrls BOOL,"
    "hasAddresses BOOL"
    ")"
};

static const char* zonetime_schema[] =
{
    "PRAGMA encoding = \"UTF-8\"",
    "Create TABLE tzcity ( "
    "geonameid PRIMARY KEY, "
    "name varchar(200),"
    "asciiname varchar(200),"
    "alternatenames varchar(10000),"
    "latitude double,"
    "longitude double,"
    "feature_class char(1),"
    "feature_code varchar(10),"
    "country_code varchar(4),"
    "cc2 varchar(200),"
    "admin1_code varchar(20),"
    "admin2_code varchar(80),"
    "admin3_code varchar(20),"
    "admin4_code varchar(20),"
    "population int,"
    "elevation int,"
    "dem int,"
    "timezone varchar(40),"
    "modification_data varchar(10)"
    ")"
};

static const char* timecity_schema[] = {
    "PRAGMA encoding = \"UTF-8\"",
    "Create TABLE tzcity ( "
    "name varchar(20), "
    "ianaId varchar(20), "
    "lat double, "
    "lon double, "
    "timezone varchar(20)"
    ")"
};

QSqlDatabase UtilDB::createDatabase(const QString &path, const QString &name, bool close)
{
    QDir databaseDir(path);
    bool exist = QFile::exists(path+"/"+name);
    if (!databaseDir.exists())
    {
        qDebug()<<"DB DIR NOT EXIST";
        // create the path
        databaseDir.mkpath(QLatin1String("."));
    }
    const QString databaseFile = databaseDir.absoluteFilePath(name);
    QSqlDatabase database;
    if(QSqlDatabase::contains(name))
    {
        database = QSqlDatabase::database(QLatin1String(name.toStdString().c_str()));
    }
    else
    {
        database = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"), name);
    }
    database.setDatabaseName(databaseFile);

    if (!database.open())
    {
        qWarning() << QString("Failed to open %1 database").arg(name);
        qWarning() << database.lastError();
    }
    QStringList schemas;
    //sqlite3开启了WAL
    schemas<<"PRAGMA temp_store = MEMORY"<<"PRAGMA journal_mode = WAL"<<"PRAGMA foreign_keys = ON";
    schemas<<QString(timecity_schema[1]);
    if(!exist)
        setDatabaseSchema(database, schemas);
    if(close)
        database.close();
    return database;
}

bool UtilDB::setDatabaseSchema(QSqlDatabase& db, const QStringList &schemas)
{
    qDebug()<<Q_FUNC_INFO;
    QSqlQuery query(db);
    foreach(QString schema, schemas)
    {
        if (!query.exec(schema))
        {
            qWarning() << query.lastError();
            qWarning() << schema;
            return false;
        }
    }
    return true;
}

bool UtilDB::createTable(QSqlDatabase &db, const QStringList &schemas)
{
    if(!db.transaction())
    {
        qDebug()<<"\033[31m"<<Q_FUNC_INFO<<"----fail to begin a transaction on the database\033[0m";
        return false;
    }
    QSqlQuery query(db);
    bool error = false;
    foreach(QString schema, schemas)
    {
        if(!query.exec(schema))
        {
            qDebug()<<Q_FUNC_INFO<<__LINE__<<schema;
            qWarning()<<Q_FUNC_INFO<< query.lastError();
            error = true;
        }
    }
    if(error)
    {
        db.rollback();
        return false;
    }
    else
    {
        return db.commit();
    }
}

bool UtilDB::addField(QSqlDatabase &db, const QString &tableName, const QString &schema)
{
    QSqlQuery query(db);
    if(!query.exec(schema))
    {
        qDebug()<<Q_FUNC_INFO<<query.lastError();
        return false;
    }
    return true;
}
