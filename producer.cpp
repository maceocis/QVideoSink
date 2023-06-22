#include <QImage>
#include <QPainter>
#include <QSize>
#include <QVideoFrame>
#include <QFile>
#include <QRandomGenerator>
#include <QDateTime>

#include "producer.h"
#include "videoBuffer.h"

Producer::Producer(QObject *parent):QObject(parent)
{

}

QVideoSink *Producer::videoSink() const
{    
    return m_videoSink.get();
}

void Producer::setVideoSink(QVideoSink *newVideoSink)
{    
    if (m_videoSink == newVideoSink)
        return;
    m_videoSink = newVideoSink;
    //emit videoSinkChanged();
}

void Producer::start(uchar *pData)
{
    int video_size;
    int bytes_per_line;
    //gsize size;
    int video_with;
    int video_height;

    video_with = 480;
    video_height = 800;

    if(!m_videoSink)
        return;

    video_size = video_with * video_height * 4;
    bytes_per_line = video_with * 4;

#if 0
    QVideoFrame video_frame(QVideoFrameFormat(QSize(480, 800),QVideoFrameFormat::Format_RGBX8888));
    if(!video_frame.isValid())
    {
        qWarning() << "QVideoFrame is not valid";
        return;
    }

    if(!video_frame.map(QVideoFrame::WriteOnly))
    {
        qWarning() << "QVideoFrame is not writable";
        return;
    }

    memcpy(video_frame.bits(0), pData, video_size);

    video_frame.unmap();

    m_videoSink->setVideoFrame(video_frame);
#else
    VideoBuffer *vbuffer = new VideoBuffer(pData, video_size, bytes_per_line);//there is lots of magic going on here. Unfortunatelly we cannot easilly pass simple pointer.
    m_videoSink->setVideoFrame(QVideoFrame(vbuffer, QVideoFrameFormat(QSize(video_with, video_height),QVideoFrameFormat::Format_RGBX8888)));
#endif
}
