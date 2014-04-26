#include "videomanager.h"

#include "config.h"

#include <QDebug>
#include <QUrl>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QEventLoop>

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

QPair<QString, QDateTime> VideoManager::getVideo(const QDateTime &selectedDateTime)
{
    return search(selectedDateTime, Current);
}

QPair<QString, QDateTime> VideoManager::getNextVideo(const QDateTime &startVideoDateTime)
{
    return search(startVideoDateTime, Next);
}

QPair<QString, QDateTime> VideoManager::getPreviousVideo(const QDateTime &startVideoDateTime)
{
    return search(startVideoDateTime, Previous);
}

void VideoManager::preloadVideo(const QDateTime &startVideoDateTime)
{
    QDate dateStart = startVideoDateTime.date();
    QString dirNameFormat = Config::getInstance()->getOption("DirNameFormat", "yyyyMMdd").toString();
    QString date = dateStart.toString(dirNameFormat);
    QString webAddress = Config::getInstance()->
            getOption("WebAddress", "http://localhost/artixvideo/", "VideoArchive").toString();

    if(!cache.contains(dateStart))
        return;

    QList<QTime> videoFiles = cache.value(dateStart);

    for (int requestedType = Next; requestedType <= Previous; ++requestedType) {
        QPair<QString, QTime> fileNameAndStartTime = searchSuitableFileName(videoFiles,
                                                                            startVideoDateTime.time(),
                                                                            (TypeRequestedVideo)requestedType);
        if (fileNameAndStartTime.first.isEmpty())
            continue;

        QDir dir(QDir::currentPath());
        dir.cd("download");
        dir.cd(date);
        QString absoluteFilePath = dir.absoluteFilePath(fileNameAndStartTime.first);

        if(QFile::exists(absoluteFilePath))
            continue;

        QUrl videoFileUrl(webAddress + date + "/" + fileNameAndStartTime.first);
        httpDownload->doDownload(videoFileUrl, date);
    }
}

QPair<QString, QDateTime> VideoManager::search(const QDateTime &selectedDateTime,
                                               VideoManager::TypeRequestedVideo typeRequestedVideo)
{
    QDate selectedDate = selectedDateTime.date();
    QString dirNameFormat = Config::getInstance()->getOption("DirNameFormat", "yyyyMMdd").toString();
    QString date = selectedDate.toString(dirNameFormat);
    QString webAddress = Config::getInstance()->
            getOption("WebAddress", "http://localhost/artixvideo/", "VideoArchive").toString();

    QPair<QString, QDateTime> video;
    if(cache.contains(selectedDate)) {
        if (selectedDate == QDate::currentDate()) {
            QStringList videoFileNames = loadFileNamesFromIndexFile(selectedDateTime);
            QList<QTime> timeStartVideo = convertStringToTime(videoFileNames);
            cache.remove(selectedDate);
            cache.insert(selectedDate, timeStartVideo);
        }

        QList<QTime> videoFiles = cache.value(selectedDate);
        QPair<QString, QTime> fileNameAndStartTime = searchSuitableFileName(videoFiles,
                                                                            selectedDateTime.time(),
                                                                            typeRequestedVideo);
        if (fileNameAndStartTime.first.isEmpty()) {
            QMessageBox::information(0, "Поиск видеофайла",
                                     "Не удается найти подходящий по времени видеофрагмент.");
            return video;
        }

        QDir dir(QDir::currentPath());
        dir.cd("download");
        dir.cd(date);
        QString absoluteFilePath = dir.absoluteFilePath(fileNameAndStartTime.first);

        if(QFile::exists(absoluteFilePath)) {
            video.first = absoluteFilePath;
            video.second = QDateTime(selectedDate, fileNameAndStartTime.second);
        } else {
            QUrl videoFileUrl(webAddress + date + "/" + fileNameAndStartTime.first);
            video.first = downloadFile(videoFileUrl, date);
            video.second = QDateTime(selectedDateTime.date(), fileNameAndStartTime.second);
        }

    } else {
        QStringList videoFileNames = loadFileNamesFromIndexFile(selectedDateTime);
        QList<QTime> timeStartVideo = convertStringToTime(videoFileNames);
        //Save start time files list to cache for selected date
        if (!cache.contains(selectedDateTime.date())) {
            cache.insert(selectedDateTime.date(), timeStartVideo);
        }

        QPair<QString, QTime> fileNameAndStartTime = searchSuitableFileName(timeStartVideo,
                                                                            selectedDateTime.time(),
                                                                            typeRequestedVideo);
        if(fileNameAndStartTime.first.isEmpty()) {
            QMessageBox::information(0, "Поиск видеофайла",
                                     "Не удается найти подходящий по времени видеофрагмент.");
            return video;
        }

        QUrl videoFileUrl(webAddress + date + "/" + fileNameAndStartTime.first);
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
        QMessageBox::information(0, "Скачивание файла", "Не удалось скачать подходящий видеофрагмент. "
                                 /*+ url.toString()*/);
        return QString();
    }

    return videoFileName;
}

QStringList VideoManager::loadFileNamesFromIndexFile(const QDateTime &selectedTime)
{
    if(!downloadIndexFile(selectedTime)) {
        return QStringList();
    }

    QString indexFileName = httpDownload->getLastFileName();
    return getVideoFileNames(indexFileName);
}

bool VideoManager::downloadIndexFile(const QDateTime &selectedTime)
{
    QString date;
    QString dirNameFormat = Config::getInstance()->getOption("DirNameFormat", "yyyyMMdd").toString();
    date = selectedTime.date().toString(dirNameFormat);

    QString webAddress = Config::getInstance()->
            getOption("WebAddress", "http://localhost/artixvideo/", "VideoArchive").toString();

    QUrl indexFileUrl(webAddress + date + "/");
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
    QString fileNameSuffix = Config::getInstance()->getOption("FileNameSuffix", "-INJ.flv").toString();
    QString pattern = Config::getInstance()->getOption("TimePattern", "\\d{6,6}").toString();
    QRegExp regExpr(pattern + fileNameSuffix, Qt::CaseInsensitive);
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
    QTime suitableTime, tempTime, nextTime, previousTime;
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
        return QPair<QString, QTime>(QString(), QTime());
    }

    QString fileNameSuffix = Config::getInstance()->getOption("FileNameSuffix", "-INJ.flv").toString();
    QString timeFormat = Config::getInstance()->getOption("TimeFormat", "hhmmss").toString();
    return QPair<QString, QTime> (suitableTime.toString(timeFormat) + fileNameSuffix, suitableTime);
}

QTime VideoManager::searchVideoByTime(const QList<QTime> &timeStartVideo, QTime &selectedTime)
{
    QTime suitableTime;
    foreach (QTime time, timeStartVideo) {
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
    QString timePattern = Config::getInstance()->getOption("TimePattern", "\\d{6,6}").toString();
    QString timeFormat = Config::getInstance()->getOption("TimeFormat", "hhmmss").toString();
    QRegExp regExpr(timePattern);

    foreach (QString fileName, videoFileNames) {
        if (regExpr.indexIn(fileName) != -1) {
            QString timeStr = regExpr.cap(0);
            QTime time = QTime::fromString(timeStr, timeFormat);
            if (time.isValid()) {
                timeStartVideo.push_back(time);
            } else {
                qDebug() << "Time is not valid " << timeStr;
            }
        }
    }

    return timeStartVideo;
}
