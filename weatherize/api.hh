#ifndef API_HH
#define API_HH

#include <xmltosql.hh>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QDebug>
#include <QDomDocument>
#include <QSqlQuery>
#include <counter.h>

class API : public QObject
{
public:
    API();

    //begins to search for data using internet. If data is from Fingrid key is
    //needed.
    void fetchData(QUrl url, bool electricity_, QVector<QString> tagName_, QVector<QString> insertTo_, QSqlQuery query_, Counter* counter_);

private:

    //reads all data and converts it into XML and calls for parserXML class.
    void replyFinished();

    xmlToSql parserXML;

    QNetworkAccessManager* networkManager;
    QNetworkReply* reply;
    QString fingridKey = "OyY1ISWkR38GFQPnlF42y8VkiPILkDgV9PlLPH8U";

    bool electricity;
    QVector<QString> tagName;
    QVector<QString> insertTo;
    QSqlQuery query;

    Counter* counter;


};

#endif // API_HH
