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
    m_sample = nullptr;
    m_buffer = nullptr;
}

Rendyboi::~Rendyboi() {
}

Gstpipeline *Rendyboi::pipeline() const {
    return m_pipeline;
}

void Rendyboi::setPipeline(Gstpipeline *pipeline) {
    qDebug() << "Rendyboi::setPipeline " << pipeline;
    qDebug() << gst_caps_to_string(gst_app_sink_get_caps(pipeline->appsink()));
    m_pipeline = pipeline;
    QObject::connect(m_pipeline, &Gstpipeline::sampleReady, this, &Rendyboi::processSample);
}

void Rendyboi::processSample() {
    if (m_buffer != nullptr) {
        gst_buffer_unmap(m_buffer, &m_info);
    }
    if (m_sample != nullptr) {
        gst_sample_unref(m_sample);
    }

    m_sample = gst_app_sink_pull_sample(GST_APP_SINK(pipeline()->appsink()));

    if (false) {
        GstCaps *caps = gst_sample_get_caps(m_sample);
        if (!caps) {
            qWarning() << "failed to extract caps from gst sample";
        } else {
            qDebug() << gst_caps_to_string(caps);
        }
    }

    m_buffer = gst_sample_get_buffer(m_sample);
    gst_buffer_map(m_buffer, &m_info, GST_MAP_READ);

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

    QImage image(m_info.data, 480, 800, QImage::Format_RGBX8888);
    QSGTexture *texture = window()->createTextureFromImage(image, QQuickWindow::TextureIsOpaque);
    node->setOwnsTexture(true);
    node->setTexture(texture);

    return background;
}
