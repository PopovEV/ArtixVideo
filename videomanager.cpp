#include "videomanager.h"

#include <QDebug>
#include <QUrl>
#include <QMessageBox>

VideoManager *VideoManager::instance = NULL;
HttpDownload *VideoManager::httpDownload = NULL;

VideoManager::VideoManager(QObject *parent) :
    QObject(parent)
{
    httpDownload = new HttpDownload();
}

VideoManager::~VideoManager()
{
    if(httpDownload)
        delete httpDownload;
}

VideoManager *VideoManager::getInstance()
{
    if(!instance)
        instance = new VideoManager();
    return instance;
}

QPair<QString, QTime> VideoManager::getVideo(QDateTime &selectedDateTime)
{
    QString date = selectedDateTime.date().toString("yyyyMMdd");

    QPair<QString, QTime> video;
    if(cache.contains(selectedDateTime.date())) {
        qDebug() << "In cache" << selectedDateTime;
        QList<QTime> videoFiles = cache.value(selectedDateTime.date());
        qDebug() << videoFiles;
        QPair<QString, QTime> fileNameAndStartTime = searchSuitableFileName(videoFiles,
                                                                            selectedDateTime.time());

        QDir dir(QDir::currentPath());
        dir.cd("download");
        dir.cd(date);
        QString absoluteFilePath = dir.absoluteFilePath(fileNameAndStartTime.first);

        if(QFile::exists(absoluteFilePath)) {
            video.first = absoluteFilePath;
            video.second = fileNameAndStartTime.second;
        } else {
            QUrl videoFileUrl("http://localhost/artixvideo/" + date + "/" + fileNameAndStartTime.first);
            video.first = downloadFile(videoFileUrl, date);
            video.second = fileNameAndStartTime.second;
        }

    } else {
        qDebug() << "Not in the cache" << selectedDateTime;

        if(!downloadIndexFile(selectedDateTime)) {
            return video;
        }

        QString indexFileName = httpDownload->getLastFileName();
        QStringList videoFileNames = getVideoFileNames(indexFileName);
        QList<QTime> timeStartVideo = convertStringToTime(videoFileNames);
        //Save list start time files to cache for selected date
         if (!cache.contains(selectedDateTime.date())) {
             qDebug() << "insert into cache";
             qDebug() << timeStartVideo;
            cache.insert(selectedDateTime.date(), timeStartVideo);
         }

        if(videoFileNames.isEmpty()) {
            QMessageBox::information(0, "Information", "There are no videos for the selected day.");
            return video;
        }

        QPair<QString, QTime> fileNameAndStartTime = searchSuitableFileName(timeStartVideo,
                                                                            selectedDateTime.time());
        if(fileNameAndStartTime.first.isEmpty()) {
            return video;
        }

        QUrl videoFileUrl("http://localhost/artixvideo/" + date + "/" + fileNameAndStartTime.first);
        video.first = downloadFile(videoFileUrl, date);
        video.second = fileNameAndStartTime.second;
    }

    return video;
}

QString VideoManager::getNextVideo(QDateTime &startVideoDateTime)
{
    return QString();
}

QString VideoManager::getForwardVideo(QDateTime &startVideoDateTime)
{
    return QString();
}

QString VideoManager::downloadFile(QUrl &url, QString &folderName)
{
    QEventLoop eventLoop;
    connect(httpDownload, SIGNAL(fileDownloaded()), &eventLoop, SLOT(quit()));
    httpDownload->doDownload(url, folderName);
    eventLoop.exec();

    QString videoFileName = httpDownload->getLastFileName();
    if(videoFileName.isEmpty()) {
        QMessageBox::information(0, "Information", "Error download video file " + url.toString());
        return QString();
    }

    return videoFileName;
}

bool VideoManager::downloadIndexFile(QDateTime &selectedTime)
{
    QString date;
    date = selectedTime.date().toString("yyyyMMdd");

    QUrl indexFileUrl("http://localhost/artixvideo/" + date + "/");
    QEventLoop eventLoop;
    connect(httpDownload, SIGNAL(fileDownloaded()), &eventLoop, SLOT(quit()));
    httpDownload->doDownload(indexFileUrl, date);
    eventLoop.exec();

    QString indexFileName = httpDownload->getLastFileName();
    if(indexFileName.isEmpty()) {
        qDebug() << "Error download index file: " << indexFileUrl.toString();
        return false;
    }

    return true;
}

QStringList VideoManager::getVideoFileNames(QString indexFileName)
{
    QStringList fileNamesList;
    QFile indexFile(indexFileName);
    if(!indexFile.open(QFile::ReadOnly)) {
        qDebug() << "Error opening index file!";
        return fileNamesList;
    }

    QString data(indexFile.readAll());
    QRegExp regExpr("\\d*-INJ.flv", Qt::CaseInsensitive);
    int pos = 0;
    while ((pos = regExpr.indexIn(data, pos)) != -1) {
        if(!fileNamesList.isEmpty()) {
            if(fileNamesList.last() != regExpr.cap(0)) {
                fileNamesList.push_back(regExpr.cap(0));
            }
        } else {
            fileNamesList.push_back(regExpr.cap(0));
        }
        pos += regExpr.matchedLength();
    }

    return fileNamesList;
}

QPair<QString, QTime> VideoManager::searchSuitableFileName(const QList<QTime> &timeStartVideo,
                                                           QTime selectedTime)
{
    QTime suitableTime;
    foreach (QTime time, timeStartVideo) {
        //TODO: Replace 300 sec by get option "VideoLenght" from config.ini
        if(selectedTime >= time && selectedTime < time.addSecs(300)) {
            suitableTime = time;
            break;
        }
    }

    if(suitableTime.isNull()) {
        QMessageBox::information(0, "Поиск видеофайла",
                                 "Не удается найти подходящий по времени видеофрагмент.");
        return QPair<QString, QTime>(QString(), QTime());
    }

    return QPair<QString, QTime> (suitableTime.toString("hhmmss") + "-INJ.flv", suitableTime);
}

QList<QTime> VideoManager::convertStringToTime(const QStringList &videoFileNames)
{
    QList<QTime> timeStartVideo;
    QRegExp regExpr("\\d{6,6}");
    foreach (QString fileName, videoFileNames) {
        if (regExpr.indexIn(fileName) != -1) {
            QString timeStr = regExpr.cap(0);
            QTime time = QTime::fromString(timeStr, "hhmmss");
            if (time.isValid()) {
                timeStartVideo.push_back(time);
            } else {
                qDebug() << "Time is not valid " << timeStr;
            }
        }
    }

    return timeStartVideo;
}
