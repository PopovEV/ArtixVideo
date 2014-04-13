#include "mediaplayer.h"
#include <QLabel>
#include <QTime>

MediaPlayer::MediaPlayer(VideoPlayer *videoPlayer, SeekSlider *seekSlider, VolumeSlider *volumeSlider,
                         QObject *parent) : QObject(parent)
{
    this->videoPlayer = videoPlayer;
    mediaObject = this->videoPlayer->mediaObject();
    this->seekSlider = seekSlider;
    this->volumeSlider = volumeSlider;

    seekSlider->setMediaObject(mediaObject);
    volumeSlider->setAudioOutput(videoPlayer->audioOutput());

    startTime = new QTime();
    selectedTime = new QTime();

    mediaObject->setTickInterval(1000);
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(stateChanged(Phonon::State,Phonon::State)));
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(setCurrentTime()));
}

MediaPlayer::~MediaPlayer()
{

}

void MediaPlayer::playVideo(const QString &path, const QTime &startTime, const QTime &selectedTime)
{
    if (!path.isEmpty()) {
        this->startTime->setHMS(startTime.hour(), startTime.minute(), startTime.second());
        this->selectedTime->setHMS(selectedTime.hour(), selectedTime.minute(), selectedTime.second());
        timeDifference = startTime.msecsTo(selectedTime);
        videoPlayer->load(MediaSource(path));
        videoPlayer->play();
    }
}

void MediaPlayer::stateChanged(State newstate, State oldstate)
{
    if(newstate == Phonon::PlayingState || newstate == Phonon::BufferingState
            || newstate == Phonon::PausedState) {
        if(oldstate == Phonon::PausedState && newstate == Phonon::PlayingState) {
            return;
        }
        if(oldstate == Phonon::PlayingState && newstate == Phonon::PausedState) {
            return;
        }

        videoPlayer->seek(timeDifference);

        qint64 totalTimeInMsec = mediaObject->totalTime();
//        QTime totalTime(totalTimeInMsec / (1000 * 60 * 60) % 60, totalTimeInMsec / (1000 * 60) % 60,
//                        totalTimeInMsec / (1000) % 60);
        QTime totalTime = startTime->addMSecs(totalTimeInMsec);
        maxTimeLabel->setText(totalTime.toString("hh:mm:ss"));
    }
}

void MediaPlayer::setCurrentTime()
{
    qint64 currentTimeMsec = mediaObject->currentTime();
//    QTime totalTime(currentTime / (1000 * 60 * 60) % 60, currentTime / (1000 * 60) % 60,
//                    currentTime / (1000) % 60);
    QTime currentTime = startTime->addMSecs(currentTimeMsec);
    currentTimeLabel->setText(currentTime.toString("hh:mm:ss"));
}

QLabel *MediaPlayer::getCurrentTimeLabel() const
{
    return currentTimeLabel;
}

void MediaPlayer::setCurrentTimeLabel(QLabel *value)
{
    currentTimeLabel = value;
}

QLabel *MediaPlayer::getMaxTimeLabel() const
{
    return maxTimeLabel;
}

void MediaPlayer::setMaxTimeLabel(QLabel *value)
{
    maxTimeLabel = value;
}

