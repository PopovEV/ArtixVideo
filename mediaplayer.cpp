#include "mediaplayer.h"
#include "videomanager.h"
#include "subtitlesmanager.h"
#include "config.h"

MediaPlayer::MediaPlayer(VideoPlayer *videoPlayer, SeekSlider *seekSlider, VolumeSlider *volumeSlider,
                         QObject *parent) : QObject(parent)
{
    this->videoPlayer = videoPlayer;
    mediaObject = this->videoPlayer->mediaObject();
    this->seekSlider = seekSlider;
    this->volumeSlider = volumeSlider;

    seekSlider->setMediaObject(mediaObject);
    volumeSlider->setAudioOutput(videoPlayer->audioOutput());

    mediaObject->setTickInterval(1000);
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(stateChanged(Phonon::State,Phonon::State)));
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(setCurrentTime()));
    connect(mediaObject, SIGNAL(finished()), this, SLOT(playNextVideo()));
}

MediaPlayer::~MediaPlayer()
{

}

void MediaPlayer::playVideo(const QDateTime &selectedDateTime)
{
    QPair<QString, QDateTime> videoFilePathAndStartTime =
            VideoManager::getInstance()->getVideo(selectedDateTime);

    QString path = videoFilePathAndStartTime.first;
    QDateTime startDateTime = videoFilePathAndStartTime.second;

    if (!path.isEmpty()) {
        this->startDateTime = startDateTime;
        this->selectedDateTime = selectedDateTime;
        differenceTime = startDateTime.time().msecsTo(selectedDateTime.time());
        videoPlayer->load(MediaSource(path));
        loadSubtitles(startDateTime);
        videoPlayer->play();

        VideoManager::getInstance()->preloadVideo(startDateTime);
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

        videoPlayer->seek(differenceTime);

        qint64 totalTimeInMsec = mediaObject->totalTime();
        QTime totalTime = startDateTime.time().addMSecs(totalTimeInMsec);
        maxTimeLabel->setText(totalTime.toString("hh:mm:ss"));
    }
}

void MediaPlayer::setCurrentTime()
{
    qint64 currentTimeMsec = mediaObject->currentTime();
    QDateTime currentTime = startDateTime.addMSecs(currentTimeMsec);
    currentTimeLabel->setText(currentTime.time().toString("hh:mm:ss"));

    // Синхронизировать субтитр с видео
    SubtitlesManager::getInstance()->changePosition(currentTime.toString("yyyy-MM-dd hh:mm:ss"));
}

void MediaPlayer::playNextVideo()
{
    if(!mediaObject->hasVideo())
        return;

    QPair<QString, QDateTime> nextVideo = VideoManager::getInstance()->getNextVideo(startDateTime);
    if (nextVideo.first.isEmpty()) {
        return;
    }

    differenceTime = 0;
    startDateTime = nextVideo.second;
    videoPlayer->load(MediaSource(nextVideo.first));
    loadSubtitles(startDateTime);
    videoPlayer->play();

    VideoManager::getInstance()->preloadVideo(startDateTime);
}

void MediaPlayer::playPreviousVideo()
{
    if(!mediaObject->hasVideo())
        return;

    QPair<QString, QDateTime> nextVideo = VideoManager::getInstance()->getPreviousVideo(startDateTime);
    if (nextVideo.first.isEmpty()) {
        return;
    }

    differenceTime = 0;
    startDateTime = nextVideo.second;
    videoPlayer->load(MediaSource(nextVideo.first));
    loadSubtitles(startDateTime);
    videoPlayer->play();

    VideoManager::getInstance()->preloadVideo(startDateTime);
}

void MediaPlayer::loadSubtitles(const QDateTime &startTime)
{
    int lenghtVideo = Config::getInstance()->getOption("LenghtVideo", 300).toInt();
    QDateTime endDateTime(startTime.addSecs(lenghtVideo));
    SubtitlesManager::getInstance()->loadSubtitles(&startTime, &endDateTime);
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

