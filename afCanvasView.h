#ifndef AFCANVASVIEW_H
#define AFCANVASVIEW_H
#include <QGraphicsView>
#include <QMouseEvent>

class afCanvasView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit afCanvasView(QWidget* parent = nullptr) : QGraphicsView(parent) {
    }
    
    void mousePressEvent(QMouseEvent *event) override {
        emit customClickSignal(event->x(), event->y());
    }
    
signals:
    void customClickSignal(int x, int y);
};

#endif // AFCANVASVIEW_H
