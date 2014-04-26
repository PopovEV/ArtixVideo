#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QObject>
#include <QDateTime>
#include <QPair>
#include <QMap>
#include <QProgressBar>
#include "httpdownload.h"
#include "downloadindicator.h"

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
    QPair<QString, QDateTime> getVideo(const QDateTime &selectedDateTime);
    /**
     * @brief getNextVideo
     * @param startVideoDateTime - vremya nachala video fayla i data
     * @return Path to video file in download dir (absolute file path)
     */
    QPair<QString, QDateTime> getNextVideo(const QDateTime &startVideoDateTime);
    /**
     * @brief getForwardVideo
     * @param startVideoDateTime - vremya nachala video fayla i data
     * @return Path to video file in download dir (absolute file path)
     */
    QPair<QString, QDateTime> getPreviousVideo(const QDateTime &startVideoDateTime);

    /**
     * @brief preloadVideo Кэширование следующего и предыдущего видеоролика от заданного
     * @param startVideoDateTime Дата и время начала текущего ролика (совпадает с именем файла)
     */
    void preloadVideo(const QDateTime &startVideoDateTime);

    void setProgressBar(QProgressBar *progressBar);

private:
    explicit VideoManager(QObject *parent = 0);
    ~VideoManager();
    static VideoManager *instance;
    static HttpDownload *httpDownload;

    QProgressBar *progressBar;
    DownloadIndicator *downloadIndicator;

    QPair<QString, QDateTime> search(const QDateTime &selectedDateTime,
                                 TypeRequestedVideo typeRequestedVideo);
    QString downloadFile(QUrl &url, QString &folderName);
    QStringList loadFileNamesFromIndexFile(const QDateTime &selectedTime);
    bool downloadIndexFile(const QDateTime &selectedTime);
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
