#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QFrame>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QColor>
#include "shape.h"

class DrawingArea : public QFrame
{
    Q_OBJECT

public:
    DrawingArea(QWidget *parent = nullptr);

    void setCurrentMode(const QString &mode);
    void setMoving(bool move);
    void setDeleting(bool del);
    void setOutlineColor(const QColor &color);
    void setFillColor(const QColor &color);  // New method

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QString currentMode;
    MyShape *currentShape;
    QPoint startPoint;
    QVector<MyShape *> shapes;
    QPoint connectionStartPoint;
    QPoint connectionEndPoint;
    int startRectIndex;
    bool moving;
    int movingIndex;
    QPoint lastMousePos;
    QVector<QPair<int, int>> connections;
    bool deleting;
    QColor currentOutlineColor;
    QColor currentFillColor;  // New member variable

    void removeConnections(int rectIndex);
    void removeShape(int index);
    void saveToFile(const QString &fileName);

    friend class MainWindow;
};

#endif // DRAWINGAREA_H
