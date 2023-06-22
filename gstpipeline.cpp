#include<QDebug>
#include "gstpipeline.h"


Gstpipeline::Gstpipeline()
{    

}

Gstpipeline::~Gstpipeline()
{

}

int Gstpipeline::sendNewSample2QML(uchar *pData)
{
    m_pFrameProvider->start(pData);

    return 0;
}


/* called when the appsink notifies us that there is a new buffer ready for
 * processing */
GstFlowReturn Gstpipeline::newSampleCallbackLcd (GstAppSink *appsink, gpointer user_data)
{
    GstSample *sample;
    GstBuffer *buffer;
    GstMapInfo info;

    /* get the sample from appsink */
    sample = gst_app_sink_pull_sample(GST_APP_SINK (appsink));
    buffer = gst_sample_get_buffer(sample);

    gst_buffer_map(buffer, &info, GST_MAP_READ);

    ((Gstpipeline*) user_data)->sendNewSample2QML((uchar *)info.data);

    gst_sample_unref(sample);
    gst_buffer_unmap(buffer, &info);

    return GST_FLOW_OK;
}


int Gstpipeline::gstpipeline_init(Producer * frameProvider)
{
    GError *error = NULL;
    gchar *descr;
    GstStateChangeReturn ret;

    m_pFrameProvider = frameProvider;

    /* Initialize GStreamer */
    gst_init (NULL,NULL);

#if 0
    descr = g_strdup_printf ("v4l2src name=video_source device=/dev/v4l/by-path/platform-vvcam-video.0-video-index0 io-mode=dmabuf ! video/x-raw, width=3840,height=2160 ! tee name=t "
                            "t. ! queue max-size-buffers=1 leaky=downstream ! imxvideoconvert_g2d rotation=3 name=g2d ! video/x-raw, width=480, height=800 ! appsink name=app_sinkLcd max-buffers=1 drop=True ");
#else
    descr = g_strdup_printf ("videotestsrc ! video/x-raw, format=(string)RGBA, width=480,height=800 ! appsink name=app_sinkLcd max-buffers=1 drop=True ");
#endif

    data.pipeline = gst_parse_launch (descr, &error);
    if (error != NULL)
    {
      qDebug() << "launch_gst_pipeline: could not construct gstreamer pipeline:" << error->message;
      g_clear_error (&error);
      return 0;
    }

    data.appsinkLcd = gst_bin_get_by_name (GST_BIN (data.pipeline), "app_sinkLcd");
    g_object_set (G_OBJECT (data.appsinkLcd), "emit-signals", TRUE, "sync", FALSE, NULL);
    g_signal_connect (data.appsinkLcd, "new-sample", G_CALLBACK (newSampleCallbackLcd), this);

    ret = gst_element_set_state(data.pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE)
    {
        qDebug() << "launch_gst_pipeline: Unable to set the gstreamer pipeline to the playing state.";
        gst_object_unref (data.pipeline);
        return 0;
    }

    return 1;
}

int
Gstpipeline::gstpipeline_deinit()
{
    gst_element_set_state (this->data.pipeline, GST_STATE_NULL);
    gst_object_unref (this->data.pipeline);
    gst_deinit ();
    return 0;
}
