#include "mediaplayer.h"
#include <QObject>

MediaPlayer::MediaPlayer(QWidget *parent) :
    QWidget(parent)
{
    pMediaObject = new MediaObject(this);
    pVideoWidget = new VideoWidget;
    pAudioOutput = new AudioOutput(Phonon::VideoCategory, this);

    createPath(pMediaObject, pVideoWidget);
    createPath(pMediaObject, pAudioOutput);

    connect(this, SIGNAL(seekChanged(qint64)), pMediaObject, SLOT(seek(qint64)));
    connect(pMediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(seek(Phonon::State,Phonon::State)));
}

MediaObject *MediaPlayer::getMediaObject()
{
    return pMediaObject;
}

void MediaPlayer::setParentForVideoWidget(QWidget *p)
{
    pVideoWidget->setParent(p);
    pVideoWidget->move(0,0);
    pVideoWidget->setFixedSize(p->parentWidget()->width(), p->parentWidget()->height() - 40);
}

VideoWidget *MediaPlayer::getVideoWidget()
{
    return pVideoWidget;
}

void MediaPlayer::setSeekSlider(QHBoxLayout *layout)
{
    pSeekSlider = new SeekSlider(pMediaObject);
    layout->insertWidget(4, pSeekSlider, 0, 0);
}

void MediaPlayer::setVolumeSlider(QHBoxLayout *layout)
{
    pVolumeSlider = new VolumeSlider(pAudioOutput);
    pVolumeSlider->setOrientation(Qt::Horizontal);
    layout->insertWidget(6, pVolumeSlider, 0, 0);
}

void MediaPlayer::slotLoad()
{
    QString str = QFileDialog::getOpenFileName(0, "Load", "", "*.*");
    if (!str.isEmpty())
    {
        pMediaObject->setCurrentSource(MediaSource(str));
        emit pMediaObject->play();
    }
}

void MediaPlayer::LoadVideo(const QString &path, const QDateTime &selectDateTime)
{
    if (!path.isEmpty())
    {
        QTime timeStartVideo;
        timeStartVideo = QTime::fromString(path.mid(9, 6), "hhmmss");
        timeDifference = timeStartVideo.msecsTo(selectDateTime.time());
        //timeDifference -= 5000;

        pMediaObject->setCurrentSource(MediaSource(path));
        emit pMediaObject->play();
    }
}

void MediaPlayer::seek(State newstate, State oldstate)
{
    if(newstate == Phonon::PlayingState || newstate == Phonon::BufferingState || newstate == Phonon::PausedState)
    {
        emit seekChanged(timeDifference);
    }
}
