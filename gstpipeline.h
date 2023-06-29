#ifndef GSTPIPELINE_H
#define GSTPIPELINE_H

#include <QObject>
//#include <QQuickWindow>
#include <gst/video/videooverlay.h>
#include <gst/app/gstappsink.h>
#include <gst/gst.h>
#include <QThread>
#include <QMouseEvent>

#include "producer.h"

#include <fstream>

class Gstpipeline : public QThread
{
    Q_OBJECT
public:
    explicit Gstpipeline();
    ~Gstpipeline();

    typedef struct _CustomData {
        GstElement *pipeline;
        GstElement *appsinkLcd;        
    } CustomData;

    CustomData data;
    //QQuickWindow *object;

    int gstpipeline_init();
    int gstpipeline_deinit();
    static GstFlowReturn newSampleCallbackLcd (GstAppSink *appsink, gpointer user_data);
    void emitSampleReadySignal();

    GstAppSink *appsink();

  signals:    
    void sendToQmlOneAiText(QString text);
    void sampleReady();

private:
    Producer * m_pFrameProvider;
};

#endif // GSTPIPELINE_H
