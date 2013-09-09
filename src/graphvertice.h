#ifndef GRAPHVERTICE_H
#define GRAPHVERTICE_H

#include <QPainter>
#include <QDebug>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsTextItem>

class GraphVertice : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES( QGraphicsItem )

public:
    GraphVertice(const QString &name = "");
    ~GraphVertice();

    void setName(const QString &name);
    QString getName() const { return name; }

    void setPosition(const QPointF &pos);
    QPointF getPosition() const;

    void setPen(const QPen &pen = QPen(Qt::black));
    QPen getPen() const;
	
    void setPenSelected(const QPen &pen = QPen(Qt::black));
    QPen getPenSelected() const;

    void setPenPressed(const QPen &pen = QPen(Qt::black));
    QPen getPenPressed() const;

    void setBackgroundColor(const QColor &color = Qt::white);
    QColor getBackgroundColor() const;

    void setBackgroundColorSelected(const QColor &color = Qt::green);
    QColor getBackgroundColorSelected() const;

    void setBackgroundColorPressed(const QColor &color = Qt::yellow);
    QColor getBackgroundColorPressed() const;

    void selectPath(bool s = true);
    void select(bool s = true);

    bool isPressed() const { return pressed; }
    int getWidth() const { return boundingRect().width(); }
    int getHeight() const { return boundingRect().height(); }

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	
    bool pathSelected;
    bool selected;
    bool pressed;
    QString name;

    QColor backgroundColor;
    QColor backgroundColorSelected;
    QColor backgroundColorPressed;

    QPen regularPen;
    QPen selectedPen;
    QPen pressedPen;

private:
    int roundness(double size) const;

signals:
    void verticePressed(GraphVertice *square);
    void verticeReleased(GraphVertice *square);

    void verticeUnselected(GraphVertice *square);
    void verticeSelected(GraphVertice *square);

    void verticeMoved(GraphVertice *square, QPointF pos);

};

#endif // GRAPHVERTICE_H
