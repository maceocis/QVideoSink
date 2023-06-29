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
    uint8_t *m_buffer;
};

#endif
