#ifndef HTTPDOWNLOAD_H
#define HTTPDOWNLOAD_H

#include <QObject>
#include <QtGui>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class HttpDownload : public QObject
{
    Q_OBJECT
private:
    QUrl *pUrl;
    QString Path;
    QString filename;
    QDateTime selectDateTime;
    qint32 lenghtMove; //длина записываемого видеофрагмента (в секундах)
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    bool UrlInput;
    bool bDownloadFile;
    bool checkUrl(const QUrl *url);

public:
    explicit HttpDownload(QObject *parent = 0);

    void setUrl(QDateTime currentDateTime);
    void setFileName(QTime *currentTime);
    void execute();
    bool doDownload(const QUrl &url);
    bool saveToDisk(const QString &filename, QIODevice *data);
    QString saveFileName(const QUrl &url);


    
signals:
    void fileDownloaded(const QString &, const QDateTime &);
    
public slots:
    void downloadFinished(QNetworkReply *reply);
    
};

#endif // HTTPDOWNLOAD_H
