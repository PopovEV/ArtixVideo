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

    connect(this, SIGNAL(seekChanged(qint64)), pMediaObject, SLOT(seek(qint64))); //тест
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

void MediaPlayer::buttonClicked()//тест
{
    emit seekChanged(pMediaObject->currentTime()+1000000);
}
