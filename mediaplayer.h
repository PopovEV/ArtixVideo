#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>
#include <phonon>

namespace Phonon{
class MediaObject;
class AudioOutput;
}

class QLabel;
class QTime;

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

    QTime *startTime; //vremya nachala rolika
    QTime *selectedTime; //vremya operacii iz rezultata poiska

public:
    explicit MediaPlayer(VideoPlayer *videoPlayer, SeekSlider *seekSlider, VolumeSlider *volumeSlider,
                         QObject *parent = 0);
    ~MediaPlayer();
    void playVideo(const QString &path, const QTime &startTime, const QTime &selectedTime);
    
    QLabel *getCurrentTimeLabel() const;
    void setCurrentTimeLabel(QLabel *value);

    QLabel *getMaxTimeLabel() const;
    void setMaxTimeLabel(QLabel *value);

signals:
    
public slots:
    void stateChanged(Phonon::State newstate, Phonon::State oldstate);
    void setCurrentTime();
    
};

#endif // MEDIAPLAYER_H
