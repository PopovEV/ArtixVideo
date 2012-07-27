#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <phonon>
#include <QtGui>

namespace Phonon{
    class MediaObject;
    class AudioOutput;
}

using namespace Phonon;

class MediaPlayer : public QWidget
{
    Q_OBJECT
private:
    Phonon::MediaObject *pMediaObject;
    Phonon::VideoWidget *pVideoWidget;
    Phonon::AudioOutput *pAudioOutput;
    Phonon::SeekSlider  *pSeekSlider;
    Phonon::VolumeSlider *pVolumeSlider;

    qint64 timeDifference;


public:
    explicit MediaPlayer(QWidget *parent = 0);
    MediaObject *getMediaObject();
    void setParentForVideoWidget(QWidget *p);
    Phonon::VideoWidget *getVideoWidget();
    void setSeekSlider(QHBoxLayout *layout);
    void setVolumeSlider(QHBoxLayout *layout);

    
signals:
    void seekChanged(qint64 time);//тест
    
public slots:
    void slotLoad();

    void LoadVideo(const QString &path, const QDateTime &selectDateTime);
    void seek( Phonon::State newstate, Phonon::State oldstate);
    
};

#endif // MEDIAPLAYER_H
