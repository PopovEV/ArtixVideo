#ifndef SUBTITLESMANAGER_H
#define SUBTITLESMANAGER_H

#include <QObject>
#include <QTableView>
#include "listview.h"
#include <QSqlQueryModel>
#include <QDateTime>

class SubtitlesManager : public QObject
{
    Q_OBJECT
public:
    static SubtitlesManager *getInstance();

    void loadSubtitles(const QDateTime *startVideo, const QDateTime *endVideo);
    void changePosition(const QString &currentTime);
    void clear();

    ListView *getListView() const;
    void setListView(ListView *value);

private:
    explicit SubtitlesManager(QObject *parent = 0);
    static SubtitlesManager *instance;
    void addTimesToMap(QDateTime &fromTime, QDateTime &toTime, int position);

    QMap<QString, int> subtitlesTime;
    QList<int> selectedPositions;
    QSqlQueryModel *queryModel;
    ListView *listView;

signals:

public slots:

};

#endif // SUBTITLESMANAGER_H
