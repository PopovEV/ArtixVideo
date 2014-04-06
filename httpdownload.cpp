#include "httpdownload.h"
#include "httpdialog.h"

HttpDownload::HttpDownload(QObject *parent) :
    QObject(parent)
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
}

//void HttpDownload::setUrl(QDateTime currentDateTime)
//{
//    selectDateTime = currentDateTime;

//    QString date;
//    date = currentDateTime.date().toString("yyyyMMdd");

//    if(pUrl->host().isEmpty() || pUrl->port() == -1)
//    {
//        HttpDialog *pInputUrl = new HttpDialog();
//        pInputUrl->setHostName(pUrl->host());
//        if(pUrl->port() == -1)
//            pInputUrl->setPortName("80");
//        else
//            pInputUrl->setPortName(QString::number(pUrl->port()));

//        if (pInputUrl->exec() == QDialog::Accepted)
//        {
//            if(!pInputUrl->getHostName().isEmpty())
//                pUrl->setHost(pInputUrl->getHostName());
//            if(!pInputUrl->getPortName().isEmpty())
//                pUrl->setPort(pInputUrl->getPortName().toInt());

//            //QMessageBox::information(0, "", "");
//        }
//        else
//        {
//            return;
//        }
//    }

//    if(UrlInput)
//    {
//        pUrl->setPath(Path + "/" + date);
//    }
//    else
//    {
//        bool bOk;
//        Path = QInputDialog::getText(0,
//                                     tr("Ввод пути до места хранения видеофайлов"),
//                                     tr("Путь"),
//                                     QLineEdit::Normal,
//                                     "",
//                                     &bOk);
//        if(!bOk) //была нажата клавиша Cancel
//        {
//            if(!UrlInput)
//            {
//                QMessageBox::information(0, tr("Ошибка"), tr("Не удается выполнить поиск видеофайла. Не введен путь! "));
//                return;
//            }
//        }

//        UrlInput = true;
//        pUrl->setPath(Path + "/" + date);
//    }

//    if(!checkUrl(pUrl)) // проверка каждой составляющей части Url
//        return;

//    qDebug() << pUrl->toString();

//    QTime *currentTime = new QTime(currentDateTime.time());
//    setFileName(currentTime);
//}

//void HttpDownload::setFileName(QTime *currentTime)
//{
//    qDebug() << currentTime->toString("hhmmss");
//    bDownloadFile = false;

//    QTime *time = new QTime();
//    time->setHMS(currentTime->hour(), currentTime->minute(), currentTime->second());

//    QString pathUrl = pUrl->path();
//    QUrl tempUrl = QUrl(pUrl->toString());

//    qint32 count = 0;

//    //уменьшаем время посекундно в поисках ближайшего названия файла
//    while(count <= lenghtMove)
//    {
//        while(count <= lenghtMove)
//        {
//            while(count <= lenghtMove)
//            {
//                tempUrl.setPath(pathUrl + "/" + time->toString("hhmmss") + "-INJ.flv");
////                qDebug() << tempUrl.toString();

//                doDownload(tempUrl);

//                if(time->second() == 0)
//                {
//                    time->setHMS(time->hour(), time->minute(), 59);
//                    break;
//                }
//                else
//                    time->setHMS(time->hour(), time->minute(), time->second()-1);

//                count++;
//            }

//            if(time->minute() == 0)
//            {
//                time->setHMS(time->hour(), 59, time->second());
//                break;
//            }
//            else
//                time->setHMS(time->hour(), time->minute()-1, time->second());

//            count++;
//        }
//        if(time->hour() == 0)
//        {
//            time->setHMS(23, time->minute(), time->second());
//        }
//        else
//            time->setHMS(time->hour()-1, time->minute(), time->second());

//        count++;
//    }

//}

bool HttpDownload::doDownload(const QUrl &url)
{
    lastUrl = url;
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);
}

void HttpDownload::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    QString fileName;
    lastFileName = "";
    if(reply->error()) {
        QMessageBox::information(0, "Download error...", QString("Download of %1 failed: %2")
                                 .arg(url.toEncoded().constData())
                                 .arg(reply->errorString()));

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

bool HttpDownload::saveToDisk(const QString &filename, QIODevice *data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << tr("Не возможно открыть %1 для записи: %2").arg(filename).arg(file.errorString());
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

    if (QFile::exists(basename))
    {
        QFile::remove(basename);
    }

    return "download/" + basename;
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
        QMessageBox::critical(0, tr("Ошибка"), tr("Url: %1  не существует!").arg(url->toString()));
        return false;
    }

    return true;
}
