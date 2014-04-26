#ifndef DOWNLOADINDICATOR_H
#define DOWNLOADINDICATOR_H

#include <QObject>
#include <QProgressBar>
#include <QNetworkReply>

class DownloadIndicator : public QObject
{
    Q_OBJECT
public:
    explicit DownloadIndicator(QObject *parent = 0);

    void setProgressBar(QProgressBar *progressBar);
    void setReply(QNetworkReply *reply);

signals:

public slots:
    void setProgress(qint64 bytesReceived, qint64 bytesTotal);
    void finishedDownload();

private:
    QProgressBar *progressBar;
    QNetworkReply *reply;
};

#endif // DOWNLOADINDICATOR_H
