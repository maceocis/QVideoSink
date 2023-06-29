#include <QDebug>
#include <QSGImageNode>
#include <QSGSimpleRectNode>
#include <QQuickWindow>
#include <QImage>
#include <math.h>
#include <gst/app/gstappsink.h>
#include <gst/gst.h>

#include "rendyboi.h"

Rendyboi::Rendyboi() {
    setFlag(ItemHasContents, true);
    m_buffer = new uint8_t[480*800*4];
}

Rendyboi::~Rendyboi() {
    delete m_buffer;
}

Gstpipeline *Rendyboi::pipeline() const {
    return m_pipeline;
}

void Rendyboi::setPipeline(Gstpipeline *pipeline) {
    qDebug() << "Rendyboi::setPipeline " << pipeline;
    m_pipeline = pipeline;
    QObject::connect(m_pipeline, &Gstpipeline::sampleReady, this, &Rendyboi::processSample);
}

void Rendyboi::processSample() {
    GstMapInfo info;
    GstSample *sample = gst_app_sink_pull_sample(GST_APP_SINK(pipeline()->appsink()));
    GstBuffer *buffer = gst_sample_get_buffer(sample);
    gst_buffer_map(buffer, &info, GST_MAP_READ);
    memcpy(m_buffer, info.data, 480*800*4);
    gst_sample_unref(sample);
    gst_buffer_unmap(buffer, &info);
    update();
}

QSGNode *Rendyboi::updatePaintNode(QSGNode *oldNode,
                                   UpdatePaintNodeData *data) {
    Q_UNUSED(data);
    // qDebug() << "Rendyboi::updatePaintNode ";

    QSGSimpleRectNode *background = static_cast<QSGSimpleRectNode *>(oldNode);
    if (!background) {
        background = new QSGSimpleRectNode();
    }
    background->setColor("green");
    background->setRect(boundingRect());

    QSGImageNode *node = static_cast<QSGImageNode *>(background->firstChild());
    if (!node) {
        node = window()->createImageNode();
        background->appendChildNode(node);
    }
    node->setRect(boundingRect());

    QImage image(m_buffer, 480, 800, QImage::Format_RGBX8888);
    QSGTexture *texture = window()->createTextureFromImage(image, QQuickWindow::TextureIsOpaque);
    node->setOwnsTexture(true);
    node->setTexture(texture);

    return background;
}
