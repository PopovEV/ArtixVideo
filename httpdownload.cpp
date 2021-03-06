#include "httpdownload.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>

HttpDownload::HttpDownload(QObject *parent) :
    QObject(parent)
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
}

QNetworkReply *HttpDownload::doDownload(const QUrl &url, QString &nameFolder)
{
    if (queueUrl.contains(url.toString()))
        return NULL;

    if (!checkUrl(&url))
        return NULL;

    lastUrl = url;
    queueUrl.insert(url.toString(), nameFolder);
    QNetworkRequest request(url);
    return manager.get(request);
}

void HttpDownload::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    QString fileName;
    lastFileName = "";
    if(reply->error()) {
        qDebug() << QString("Download error! Download of %1 failed: %2")
                    .arg(url.toEncoded().constData())
                    .arg(reply->errorString());

    } else {
        fileName = saveFileName(url);
        lastFileName = fileName;
        if (saveToDisk(fileName, reply)) {
            qDebug() << fileName;
        }
    }
    emit fileDownloaded();
    reply->deleteLater();
}

bool HttpDownload::saveToDisk(const QString &fileName, QIODevice *data)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << tr("Не возможно открыть %1 для записи: %2").arg(fileName).arg(file.errorString());
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}

QString HttpDownload::saveFileName(const QUrl &url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if (basename.isEmpty())
        basename = "index.html";

    QDir dir = QDir::currentPath();
    if(!dir.exists("download"))
        dir.mkdir("download");
    dir.cd("download");

    QString folderName = queueUrl.take(url.toString());
    if(!dir.exists(folderName))
        dir.mkdir(folderName);
    dir.cd(folderName);

    if (QFile::exists(basename))
        QFile::remove(basename);

    return dir.absolutePath() + "/" + basename;
}


QString HttpDownload::getLastFileName() const
{
    return lastFileName;
}

void HttpDownload::setLastFileName(const QString &value)
{
    lastFileName = value;
}
bool HttpDownload::checkUrl(const QUrl *url)
{
    if (!url->isValid())
    {
        qDebug() << tr("Ошибка: Url: %1  не существует!").arg(url->toString());
        return false;
    }

    return true;
}
