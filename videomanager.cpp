#include "videomanager.h"

#include "config.h"

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

QPair<QString, QDateTime> VideoManager::getVideo(QDateTime &selectedDateTime)
{
    return search(selectedDateTime, Current);
}

QPair<QString, QDateTime> VideoManager::getNextVideo(QDateTime &startVideoDateTime)
{
    return search(startVideoDateTime, Next);
}

QPair<QString, QDateTime> VideoManager::getPreviousVideo(QDateTime &startVideoDateTime)
{
    return search(startVideoDateTime, Previous);
}

QPair<QString, QDateTime> VideoManager::search(QDateTime &selectedDateTime,
                                           VideoManager::TypeRequestedVideo typeRequestedVideo)
{
    QString date = selectedDateTime.date().toString("yyyyMMdd");

    QPair<QString, QDateTime> video;
    if(cache.contains(selectedDateTime.date())) {
        qDebug() << "In cache" << selectedDateTime;
        QList<QTime> videoFiles = cache.value(selectedDateTime.date());
        qDebug() << videoFiles;
        QPair<QString, QTime> fileNameAndStartTime = searchSuitableFileName(videoFiles,
                                                                            selectedDateTime.time(),
                                                                            typeRequestedVideo);
        if (fileNameAndStartTime.first.isEmpty()) {
            return video;
        }

        QDir dir(QDir::currentPath());
        dir.cd("download");
        dir.cd(date);
        QString absoluteFilePath = dir.absoluteFilePath(fileNameAndStartTime.first);

        if(QFile::exists(absoluteFilePath)) {
            video.first = absoluteFilePath;
            video.second = QDateTime(selectedDateTime.date(), fileNameAndStartTime.second);
        } else {
            QUrl videoFileUrl("http://localhost/artixvideo/" + date + "/" + fileNameAndStartTime.first);
            video.first = downloadFile(videoFileUrl, date);
            video.second = QDateTime(selectedDateTime.date(), fileNameAndStartTime.second);
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
                                                                            selectedDateTime.time(),
                                                                            typeRequestedVideo);
        if(fileNameAndStartTime.first.isEmpty()) {
            return video;
        }

        QUrl videoFileUrl("http://localhost/artixvideo/" + date + "/" + fileNameAndStartTime.first);
        video.first = downloadFile(videoFileUrl, date);
        video.second = QDateTime(selectedDateTime.date(), fileNameAndStartTime.second);
    }

    return video;
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
                                                           QTime selectedTime,
                                                           VideoManager::TypeRequestedVideo typeRequestedVideo)
{
    QTime suitableTime ,tempTime, nextTime, previousTime;
    int lenghtVideo = Config::getInstance()->getOption("LenghtVideo", 300).toInt();

    switch (typeRequestedVideo) {
    case Current:
        suitableTime = searchVideoByTime(timeStartVideo, selectedTime);
        break;
    case Next:
        tempTime = searchVideoByTime(timeStartVideo, selectedTime);
        nextTime = tempTime.addSecs(lenghtVideo + (lenghtVideo / 2));
        suitableTime = searchVideoByTime(timeStartVideo, nextTime);
        break;
    case Previous:
        tempTime = searchVideoByTime(timeStartVideo, selectedTime);
        previousTime = tempTime.addSecs(-(lenghtVideo / 2));
        suitableTime = searchVideoByTime(timeStartVideo, previousTime);
        break;
    default:
        break;
    }


    if(suitableTime.isNull()) {
        QMessageBox::information(0, "Поиск видеофайла",
                                 "Не удается найти подходящий по времени видеофрагмент.");
        return QPair<QString, QTime>(QString(), QTime());
    }

    return QPair<QString, QTime> (suitableTime.toString("hhmmss") + "-INJ.flv", suitableTime);
}

QTime VideoManager::searchVideoByTime(const QList<QTime> &timeStartVideo, QTime &selectedTime)
{
    QTime suitableTime;
    foreach (QTime time, timeStartVideo) {
        //TODO: Replace 300 sec by get option "VideoLenght" from config.ini
        int lenghtVideo = Config::getInstance()->getOption("LenghtVideo", 300).toInt();
        if(selectedTime >= time && selectedTime < time.addSecs(lenghtVideo)) {
            suitableTime = time;
            break;
        }
    }
    return suitableTime;
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
