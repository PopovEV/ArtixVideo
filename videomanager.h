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
private:
    enum TypeRequestedVideo {
        Current,
        Next,
        Previous
    };

public:
    static VideoManager *getInstance();

    /**
     * @brief getVideo
     * @param selectedDateTime - data i vremya fayla, kotoriy nugno nayti
     * @return Path to video file in download dir (absolute file path)
     */
    QPair<QString, QDateTime> getVideo(QDateTime &selectedDateTime);
    /**
     * @brief getNextVideo
     * @param startVideoDateTime - vremya nachala video fayla i data
     * @return Path to video file in download dir (absolute file path)
     */
    QPair<QString, QDateTime> getNextVideo(QDateTime &startVideoDateTime);
    /**
     * @brief getForwardVideo
     * @param startVideoDateTime - vremya nachala video fayla i data
     * @return Path to video file in download dir (absolute file path)
     */
    QPair<QString, QDateTime> getPreviousVideo(QDateTime &startVideoDateTime);

private:
    explicit VideoManager(QObject *parent = 0);
    ~VideoManager();
    static VideoManager *instance;
    static HttpDownload *httpDownload;

    QPair<QString, QDateTime> search(QDateTime &selectedDateTime,
                                 TypeRequestedVideo typeRequestedVideo);
    QString downloadFile(QUrl &url, QString &folderName);
    QStringList loadFileNamesFromIndexFile(QDateTime &selectedTime);
    bool downloadIndexFile(QDateTime &selectedTime);
    QStringList getVideoFileNames(QString indexFileName);
    QPair<QString, QTime> searchSuitableFileName(const QList<QTime> &timeStartVideo,
                                                 QTime selectedTime,
                                                 TypeRequestedVideo typeRequestedVideo);
    QTime searchVideoByTime(const QList<QTime> &timeStartVideo, QTime &selectedTime);
    QList<QTime> convertStringToTime(const QStringList &videoFileNames);

    QMap<QDate, QList<QTime> > cache;

signals:

public slots:

};

#endif // VIDEOMANAGER_H
