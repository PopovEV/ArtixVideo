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
public:
    explicit MediaPlayer(VideoPlayer *videoPlayer, SeekSlider *seekSlider, VolumeSlider *volumeSlider,
                         QObject *parent = 0);
    ~MediaPlayer();

    void playVideo(const QDateTime &selectedDateTime);
    
    QLabel *getCurrentTimeLabel() const;
    void setCurrentTimeLabel(QLabel *value);

    QLabel *getMaxTimeLabel() const;
    void setMaxTimeLabel(QLabel *value);

private:
    VideoPlayer *videoPlayer;
    MediaObject *mediaObject;
    SeekSlider *seekSlider;
    VolumeSlider *volumeSlider;
    QLabel *currentTimeLabel;
    QLabel *maxTimeLabel;

    /**
     * @brief differenceTime Разница времени между началом ролика и выбранным событием (msec)
     */
    qint64 differenceTime;

    /**
    * @brief startDateTime Время начала ролика
    */
    QDateTime startDateTime;
    /**
     * @brief selectedDateTime Время события из результатов поиска
     */
    QDateTime selectedDateTime;

    void loadSubtitles(const QDateTime &startTime);

signals:
    
public slots:
    void stateChanged(Phonon::State newstate, Phonon::State oldstate);
    void setCurrentTime();
    void playNextVideo();
    void playPreviousVideo();
    
};

#endif // MEDIAPLAYER_H
