#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QObject>
#include <QDateTime>
#include <QPair>
#include <QMap>
#include "httpdownload.h"

class VideoManager : public QObject
{
    Q_OBJECT
public:
    static VideoManager *getInstance();

    /**
     * @brief getVideo
     * @param selectedDateTime - data i vremya fayla, kotoriy nugno nayti
     * @return Path to video file in download dir (absolute file path)
     */
    QPair<QString, QTime> getVideo(QDateTime &selectedDateTime);
    /**
     * @brief getNextVideo
     * @param startVideoDateTime - vremya nachala video fayla i data
     * @return Path to video file in download dir (absolute file path)
     */
    QString getNextVideo(QDateTime &startVideoDateTime);
    /**
     * @brief getForwardVideo
     * @param startVideoDateTime - vremya nachala video fayla i data
     * @return Path to video file in download dir (absolute file path)
     */
    QString getForwardVideo(QDateTime &startVideoDateTime);

private:
    explicit VideoManager(QObject *parent = 0);
    ~VideoManager();
    static VideoManager *instance;
    static HttpDownload *httpDownload;

    QString downloadFile(QUrl &url, QString &folderName);
    bool downloadIndexFile(QDateTime &selectedTime);
    QStringList getVideoFileNames(QString indexFileName);
    QPair<QString, QTime> searchSuitableFileName(const QList<QTime> &timeStartVideo,
                                                 QTime selectedTime);

    QList<QTime> convertStringToTime(const QStringList &videoFileNames);

    QMap<QDate, QList<QTime> > cache;

signals:

public slots:

};

#endif // VIDEOMANAGER_H
