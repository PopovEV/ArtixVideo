#include "subtitlesmanager.h"
#include "sql.h"

SubtitlesManager *SubtitlesManager::instance = NULL;

SubtitlesManager::SubtitlesManager(QObject *parent) :
    QObject(parent), queryModel(new QSqlQueryModel()), selectedPositions(QList<int>())
{

}

SubtitlesManager *SubtitlesManager::getInstance()
{
    if(!instance)
        instance = new SubtitlesManager();
    return instance;
}

void SubtitlesManager::loadSubtitles(const QDateTime *startVideo, const QDateTime *endVideo)
{
    QSqlDatabase db = SQL::getInstance()->getArtixVideo();
    if(!db.isValid())
        return;

    QSqlQuery query(db);
    bool b = query.exec(QString("SELECT *, CONCAT_WS(' ', TEXT, CAST(DATE_FORMAT(STIME, '%d %m %Y %T') AS CHAR)) AS SUB "
                                "FROM SUBTITLES WHERE STIME >= '%1' AND STIME <= '%2' ORDER BY STIME, ID_STRING")
                        .arg(startVideo->toString("yyyy-MM-dd hh:mm:ss"))
                        .arg(endVideo->toString("yyyy-MM-dd hh:mm:ss")));
    if(!b) {
        qDebug() << "subtitles does not uploaded " << query.lastError().text();
        return;
    }

    selectedPositions.clear();
    subtitlesTime.clear();
    QDateTime lastTime(*startVideo);
    int pos = -1;
    while (query.next()) {
        QDateTime stime = query.record().field("STIME").value().toDateTime();
        addTimesToMap(lastTime, stime, pos);
        lastTime = stime;
        pos++;
        subtitlesTime.insertMulti(stime.toString("yyyy-MM-dd hh:mm:ss"), pos);
    }

    QDateTime stime = *endVideo;
    addTimesToMap(lastTime, stime, pos);

    queryModel->clear();
    queryModel->setQuery(query);
    listView->setModel(queryModel);
    listView->setModelColumn(6);
}

void SubtitlesManager::addTimesToMap(QDateTime &fromTime, QDateTime &toTime, int position)
{
    while (fromTime < toTime) {
        QString stimeStr = fromTime.toString("yyyy-MM-dd hh:mm:ss");
        subtitlesTime.insertMulti(stimeStr, position);
        fromTime = fromTime.addSecs(1);
    }
}

void SubtitlesManager::changePosition(const QString &currentTime)
{
    if(subtitlesTime.contains(currentTime)) {
        if(!selectedPositions.contains(subtitlesTime.value(currentTime))) {
            selectedPositions.clear();
            if (subtitlesTime.count(currentTime) > 1) {
                //select all items
                QList<int> positions = subtitlesTime.values(currentTime);

                selectedPositions.append(positions);
                QModelIndex fromIndex, toIndex;
                fromIndex = queryModel->index(positions.first(), 6, QModelIndex());
                toIndex = queryModel->index(positions.last(), 6, QModelIndex());
                QItemSelection selection(fromIndex, toIndex);
                listView->scrollTo(fromIndex);
                listView->selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect);
            } else {
                //select one item
                int pos = subtitlesTime.value(currentTime);
                QModelIndex index = queryModel->index(pos, 6);
                listView->scrollTo(index);
                listView->selectionModel()->setCurrentIndex(index,
                                                            QItemSelectionModel::ClearAndSelect);
                selectedPositions.append(pos);
            }
        }
    }
}

ListView *SubtitlesManager::getListView() const
{
    return listView;
}

void SubtitlesManager::setListView(ListView *value)
{
    listView = value;
}


