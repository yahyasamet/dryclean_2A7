#include "sqleventmodel.h"
#include "connection.h"
#include <QDebug>
#include <QFileInfo>

SqlEventModel::SqlEventModel()
{

}

QList<QObject*> SqlEventModel::eventsForDate(const QDate &date)
{

    QSqlQuery query;

    query.prepare("SELECT * FROM livraisons where DATE_LIVRAISON like :date");
    query.bindValue(":date", date);
    query.exec();

    QList<QObject*> events;
    while (query.next()) {
        Event *event = new Event(this);
        event->setName(query.value("NOM_LIVREUR").toString());

        QDateTime startDate;
        startDate.setDate(query.value("DATE_LIVRAISON").toDate());
        //startDate.setTime(QTime(0, 0).addSecs(query.value("startTime").toInt()));
        QString start="00000";
        startDate.setTime(QTime(0, 0).addSecs(start.toInt()));
        event->setStartDate(startDate);

        QDateTime endDate;
        endDate.setDate(query.value("DATE_LIVRAISON").toDate());
        endDate.setTime(QTime(0, 0).addSecs(start.toInt()));
        event->setEndDate(endDate);

        events.append(event);
    }

    return events;

}



