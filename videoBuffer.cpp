#include "videoBuffer.h"
#include <QDebug>

VideoBuffer::VideoBuffer(uchar *data, int numBytes, int bytesPerLine)
    : QAbstractVideoBuffer(QVideoFrame::NoHandle)
    , m_data(data)
    , m_numBytes(numBytes)
    , m_bytesPerLine(bytesPerLine)
{

}

QAbstractVideoBuffer::MapData VideoBuffer::map(QVideoFrame::MapMode mode)
{
    MapData map_data;
    Q_UNUSED(mode)

    map_data.data[0]=m_data;
    map_data.nPlanes =1;
    map_data.bytesPerLine[0]=m_bytesPerLine;
    map_data.size[0]=m_numBytes;

    return map_data;
}

QVideoFrame::MapMode VideoBuffer::mapMode() const
{
    return QVideoFrame::ReadOnly;
}

void VideoBuffer::unmap()
{
    //do not delete m_data;
}
