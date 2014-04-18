#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>
#include <QDateTime>
#include <QLabel>
#include <phonon>

namespace Phonon{
class MediaObject;
class AudioOutput;
}

using namespace Phonon;

class MediaPlayer : public QObject
{
    Q_OBJECT
private:
    VideoPlayer *videoPlayer;
    MediaObject *mediaObject;
    SeekSlider *seekSlider;
    VolumeSlider *volumeSlider;
    QLabel *currentTimeLabel;
    QLabel *maxTimeLabel;

    qint64 timeDifference;

    QDateTime startDateTime; //vremya nachala rolika
    QDateTime selectedDateTime; //vremya operacii iz rezultata poiska

//    void playVideo();
    void loadSubtitles(const QDateTime &startTime);

public:
    explicit MediaPlayer(VideoPlayer *videoPlayer, SeekSlider *seekSlider, VolumeSlider *volumeSlider,
                         QObject *parent = 0);
    ~MediaPlayer();
    void playVideo(const QString &path, const QDateTime &startDateTime, const QDateTime &selectedDateTime);
    
    QLabel *getCurrentTimeLabel() const;
    void setCurrentTimeLabel(QLabel *value);

    QLabel *getMaxTimeLabel() const;
    void setMaxTimeLabel(QLabel *value);

signals:
    
public slots:
    void stateChanged(Phonon::State newstate, Phonon::State oldstate);
    void setCurrentTime();
    void playNextVideo();
    void playPreviousVideo();
    
};

#endif // MEDIAPLAYER_H
