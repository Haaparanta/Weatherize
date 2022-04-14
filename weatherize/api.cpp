#include "api.hh"

API::API()
{
    networkManager = new QNetworkAccessManager;
}

void API::fetchData(QUrl url, bool electricity_, QVector<QString> tagName_, QVector<QString> insertTo_, QSqlQuery query_, Counter* counter_)
{
    counter = counter_;
    electricity = electricity_;
    tagName = tagName_;
    insertTo = insertTo_;
    query = query_;
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    if (electricity) {
        request.setRawHeader(QByteArray("x-api-key"), fingridKey.toUtf8());
    }

    connect(networkManager, &QNetworkAccessManager::finished, this, &API::replyFinished);

    reply = networkManager->get(request);
}

void API::replyFinished()
{
    QByteArray data = reply->readAll();
    QDomDocument dom = QDomDocument();
    dom.setContent(data);
    reply->deleteLater();
    networkManager->deleteLater();
    parserXML.parseXML(dom, electricity, tagName, insertTo, query);
    counter->setValue(true);
}


