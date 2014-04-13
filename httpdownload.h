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
    QUrl lastUrl;
    QString path;
    QString lastFileName;
    QNetworkAccessManager manager;
    QMap<QString, QString> queueUrl; // key - url, value - name folder kuda nugno sohranit fayl
    bool checkUrl(const QUrl *url);

public:
    explicit HttpDownload(QObject *parent = 0);

    bool doDownload(const QUrl &url, QString &nameFolder);
    bool saveToDisk(const QString &fileName, QIODevice *data);
    QString saveFileName(const QUrl &url);

    QString getLastFileName() const;
    void setLastFileName(const QString &value);

signals:
    void fileDownloaded();
    
public slots:
    void downloadFinished(QNetworkReply *reply);
};

#endif // HTTPDOWNLOAD_H
