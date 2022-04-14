#ifndef XMLTOSQL_HH
#define XMLTOSQL_HH

#include <QSqlQuery>

#include <QDebug>

#include <QObject>

#include <QDomDocument>

class xmlToSql : public QObject
{
public:
    xmlToSql();
    //makes XML into SQL format
    void parseXML(QDomDocument dom, bool electricity, QVector<QString> tagName, QVector<QString> insertTo, QSqlQuery query);
private:
    QVector<QDomNodeList> qDomNodevec;
};

#endif // XMLTOSQL_HH
