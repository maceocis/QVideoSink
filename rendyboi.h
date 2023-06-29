#ifndef RENDYBOI_H
#define RENDYBOI_H

#include <QQuickItem>
#include <memory>

#include "gstpipeline.h"

class Rendyboi : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(Gstpipeline *pipeline READ pipeline WRITE setPipeline)

  public:
    Rendyboi();
    ~Rendyboi();

    Gstpipeline *pipeline() const;
    void setPipeline(Gstpipeline *pipeline);

    QSGNode *updatePaintNode(QSGNode *oldNode,
                             UpdatePaintNodeData *data) override;

  public slots:
    void processSample();

  private:
    Gstpipeline *m_pipeline;
    uint8_t *m_bytes;
    GstMapInfo m_info;
    GstSample *m_sample;
    GstBuffer *m_buffer;
};

#endif
