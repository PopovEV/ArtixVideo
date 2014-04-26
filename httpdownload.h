#ifndef HTTPDOWNLOAD_H
#define HTTPDOWNLOAD_H

#include <QObject>
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
    /**
     * @brief queueUrl
     * key - url, value - название папки, в которую необходимо сохранить скачанный файл
     */
    QMap<QString, QString> queueUrl;
    bool checkUrl(const QUrl *url);

public:
    explicit HttpDownload(QObject *parent = 0);

    void doDownload(const QUrl &url, QString &nameFolder);
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
