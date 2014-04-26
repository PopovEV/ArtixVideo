#include "downloadindicator.h"

#include <QDebug>

DownloadIndicator::DownloadIndicator(QObject *parent) :
    QObject(parent), progressBar(NULL), reply(NULL)
{
}

void DownloadIndicator::setProgressBar(QProgressBar *progressBar)
{
    this->progressBar = progressBar;
}

void DownloadIndicator::setReply(QNetworkReply *reply)
{
    this->reply = reply;
    progressBar->setValue(0);
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(setProgress(qint64,qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(finishedDownload()));
}

void DownloadIndicator::setProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    progressBar->setMaximum(bytesTotal);
    progressBar->setValue(bytesReceived);
}

void DownloadIndicator::finishedDownload()
{
    disconnect(reply, SIGNAL(downloadProgress(qint64,qint64)), 0, 0);
    disconnect(reply, SIGNAL(finished()), 0, 0);
}
