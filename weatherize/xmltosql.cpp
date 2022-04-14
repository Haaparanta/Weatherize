#include "xmltosql.hh"

xmlToSql::xmlToSql()
{

}

void xmlToSql::parseXML(QDomDocument dom, bool electricity, QVector<QString> tagName, QVector<QString> insertTo, QSqlQuery query)
{
    int tagSize = tagName.size();
    QString table = "weather";
    if (electricity) {
        table = "electricity";
    }
    for (int i = 0; i < tagSize; ++i) {
        QDomNodeList list = dom.elementsByTagName(tagName.at(i));
        qDomNodevec.push_back(list);
    }
    for (int i = 0; i < qDomNodevec.at(0).size(); ++i) {

        if (qDomNodevec.at(0).at(i).isElement()) {

            QString update = "update " + table + " set " + insertTo.at(1) + " = '" +
                    qDomNodevec.at(1).at(i).toElement().text() + "' where time = '" +
                    qDomNodevec.at(0).at(i).toElement().text() + "';";
            query.exec(update);

            if (query.numRowsAffected() < 1) {
                QString insert;
                if (electricity) {
                    insert = "insert into electricity values('" + qDomNodevec.at(0).at(i).toElement().text()
                            + "', null, null, null, null, null, null, null)";
                } else {
                    insert = "insert into weather values('" + qDomNodevec.at(0).at(i).toElement().text() +
                            "', null, null, null, null, null)";
                }
                query.exec(insert);
                query.exec(update);
            }
        }
    }
}

