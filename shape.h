#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QPoint>

class MyShape {
public:
    MyShape(const QColor &outlineColor, const QColor &fillColor) : outlineColor(outlineColor), fillColor(fillColor) {}
    virtual ~MyShape() {}
    virtual void draw(QPainter &painter) const = 0;
    virtual bool contains(const QPoint &point) const = 0;
    virtual void move(const QPoint &offset) = 0;
    virtual QRect &boundingRect() = 0;

    QColor getOutlineColor() const { return outlineColor; }
    void setOutlineColor(const QColor &color) { outlineColor = color; }

    QColor getFillColor() const { return fillColor; }
    void setFillColor(const QColor &color) { fillColor = color; }

protected:
    QColor outlineColor;
    QColor fillColor;
};

class RectangleShape : public MyShape {
private:
    QRect rect;
public:
    RectangleShape(const QRect &otherrect, const QColor &outlineColor, const QColor &fillColor)
        : MyShape(outlineColor, fillColor), rect(otherrect) {}
    void draw(QPainter &painter) const override {
        QPen pen(outlineColor);
        QBrush brush(fillColor);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawRect(rect);
    }
    bool contains(const QPoint &point) const override {
        return rect.contains(point);
    }
    void move(const QPoint &offset) override {
        rect.translate(offset);
    }
    QRect &boundingRect() override {
        return rect;
    }
};

class EllipseShape : public MyShape {
private:
    QRect rect;
public:
    EllipseShape(const QRect &otherrect, const QColor &outlineColor, const QColor &fillColor)
        : MyShape(outlineColor, fillColor), rect(otherrect) {}
    void draw(QPainter &painter) const override {
        QPen pen(outlineColor);
        QBrush brush(fillColor);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawEllipse(rect);
    }
    bool contains(const QPoint &point) const override {
        return rect.contains(point);
    }
    void move(const QPoint &offset) override {
        rect.translate(offset);
    }
    QRect &boundingRect() override {
        return rect;
    }
};

class TriangleShape : public MyShape {
private:
    QRect rect;
public:
    TriangleShape(const QRect &otherrect, const QColor &outlineColor, const QColor &fillColor)
        : MyShape(outlineColor, fillColor), rect(otherrect) {}
    void draw(QPainter &painter) const override {
        QPolygon triangle;
        triangle << QPoint(rect.left() + rect.width() / 2, rect.top())
                 << QPoint(rect.bottomLeft())
                 << QPoint(rect.bottomRight());
        QPen pen(outlineColor);
        QBrush brush(fillColor);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawPolygon(triangle);
    }
    bool contains(const QPoint &point) const override {
        return rect.contains(point);
    }
    void move(const QPoint &offset) override {
        rect.translate(offset);
    }
    QRect &boundingRect() override {
        return rect;
    }
};

#endif // SHAPE_H
