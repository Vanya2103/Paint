#include "drawingarea.h"

DrawingArea::DrawingArea(QWidget *parent)
    : QFrame(parent), currentShape(nullptr), moving(false), movingIndex(-1), deleting(false), currentOutlineColor(Qt::black), currentFillColor(Qt::white)
{
}

void DrawingArea::setCurrentMode(const QString &mode)
{
    currentMode = mode;
    moving = false;
    deleting = false;
}

void DrawingArea::setMoving(bool move)
{
    moving = move;
    currentMode = "";
    deleting = false;
}

void DrawingArea::setDeleting(bool del)
{
    deleting = del;
    currentMode = "";
    moving = false;
}

void DrawingArea::setOutlineColor(const QColor &color)
{
    currentOutlineColor = color;
}

void DrawingArea::setFillColor(const QColor &color)
{
    currentFillColor = color;
}

void DrawingArea::mousePressEvent(QMouseEvent *event)
{
    if (moving) {
        if (event->button() == Qt::LeftButton) {
            for (int i = 0; i < shapes.size(); i++) {
                if (shapes[i]->contains(event->pos())) {
                    movingIndex = i;
                    lastMousePos = event->pos();
                    setCursor(Qt::ClosedHandCursor);
                    return;
                }
            }
        } else if (event->button() == Qt::RightButton) {
            movingIndex = -1;
            setCursor(Qt::ArrowCursor);
            update();
        }
    } else if (deleting) {
        if (event->button() == Qt::LeftButton) {
            for (int i = 0; i < shapes.size(); i++) {
                if (shapes[i]->contains(event->pos())) {
                    removeShape(i);
                    deleting = false;
                    update();
                    return;
                }
            }
        } else if (event->button() == Qt::RightButton) {
            deleting = false;
            update();
        }
    } else if (currentMode == "Connection") {
        if (event->button() == Qt::LeftButton) {
            for (int i = 0; i < shapes.size(); ++i) {
                if (shapes[i]->contains(event->pos())) {
                    if (connectionStartPoint.isNull()) {
                        connectionStartPoint = shapes[i]->boundingRect().center();
                        connectionEndPoint = connectionStartPoint;
                        startRectIndex = i;
                    } else {
                        connectionEndPoint = shapes[i]->boundingRect().center();
                        if (startRectIndex != i) {
                            connections.push_back(std::make_pair(startRectIndex, i));
                        }
                        connectionStartPoint = QPoint();
                        connectionEndPoint = QPoint();
                        currentMode = "";
                    }
                    update();
                    return;
                }
            }
            connectionStartPoint = QPoint();
            connectionEndPoint = QPoint();
            currentMode = "";
            update();
        } else if (event->button() == Qt::RightButton) {
            connectionStartPoint = QPoint();
            connectionEndPoint = QPoint();
            currentMode = "";
            update();
        }
    } else if (currentMode != "") {
        if (event->button() == Qt::LeftButton) {
            startPoint = event->pos();
            QRect rect;
            rect.setTopLeft(startPoint);
            rect.setBottomRight(startPoint);
            if (currentMode == "Rectangle") {
                currentShape = new RectangleShape(rect, currentOutlineColor, currentFillColor);
            } else if (currentMode == "Ellipse") {
                currentShape = new EllipseShape(rect, currentOutlineColor, currentFillColor);
            } else if (currentMode == "Triangle") {
                currentShape = new TriangleShape(rect, currentOutlineColor, currentFillColor);
            }
            update();
        }
        update();
    }
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event)
{
    if (moving && movingIndex >= 0) {
        QPoint offset = event->pos() - lastMousePos;
        shapes[movingIndex]->move(offset);
        lastMousePos = event->pos();
        update();
    } else if (currentMode == "Connection" && !connectionStartPoint.isNull()) {
        connectionEndPoint = event->pos();
        update();
    } else if (currentMode != "" && currentShape) {
        currentShape->boundingRect().setBottomRight(event->pos());
        update();
    }
}

void DrawingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (moving && movingIndex >= 0 && event->button() == Qt::LeftButton) {
        movingIndex = -1;
        setCursor(Qt::ArrowCursor);
        update();
    } else if (currentMode != "" && currentShape && event->button() == Qt::LeftButton) {
        shapes.push_back(currentShape);
        currentShape = nullptr;
        currentMode = "";
        update();
    }
}

void DrawingArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    for (const MyShape *shape : shapes) {
        shape->draw(painter);
    }

    for (const auto &connection : connections) {
        painter.drawLine(shapes[connection.first]->boundingRect().center(),
                         shapes[connection.second]->boundingRect().center());
    }

    if (currentShape) {
        currentShape->draw(painter);
    }

    if (currentMode == "Connection" && !connectionStartPoint.isNull()) {
        painter.drawLine(connectionStartPoint, connectionEndPoint);
    }
}

void DrawingArea::removeConnections(int rectIndex)
{
    QVector<QPair<int, int>> newConnections;

    for (const auto &connection : connections) {
        if (connection.first != rectIndex && connection.second != rectIndex) {
            newConnections.push_back(connection);
        }
    }

    for (auto &connection : newConnections) {
        if (connection.first > rectIndex) {
            --connection.first;
        }
        if (connection.second > rectIndex) {
            --connection.second;
        }
    }
    connections = newConnections;
    update();
}

void DrawingArea::removeShape(int index)
{
    removeConnections(index);

    if (index >= 0 && index < shapes.size()) {
        if (shapes[index]) {
            delete shapes[index];
            shapes.remove(index);
        }
    }
}

void DrawingArea::saveToFile(const QString &fileName)
{
    QPixmap pixmap(size());
    render(&pixmap);
    pixmap.save(fileName);
}
