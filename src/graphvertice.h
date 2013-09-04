#ifndef GRAPHVERTICE_H
#define GRAPHVERTICE_H

#include <QPainter>
#include <QDebug>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsTextItem>

//! ������������ ��� �������������� ������� �����.
class GraphVertice : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES( QGraphicsItem )

public:
    GraphVertice(const QString &name = "");
    ~GraphVertice();

        //! ��������� �������� @ref name
    void setName(const QString &name);
        //! ��������� �������� @ref name
    QString getName() const { return name; }

        //! ��������� ������� ������� �� ����� @ref GraphDrawer.
    void setPosition(const QPointF &pos);
        //! ��������� ������� ������� ������� �� ����� @ref GraphDrawer.
    QPointF getPosition() const;

        //! ��������� �������� @ref regularPen
    void setPen(const QPen &pen = QPen(Qt::black));
        //! ��������� �������� @ref regularPen
    QPen getPen() const;
        //! ��������� �������� @ref selectedPen
    void setPenSelected(const QPen &pen = QPen(Qt::black));
        //! ��������� �������� @ref selectedPen
    QPen getPenSelected() const;
        //! ��������� �������� @ref pressedPen
    void setPenPressed(const QPen &pen = QPen(Qt::black));
        //! ��������� �������� @ref pressedPen
    QPen getPenPressed() const;

        //! ������������� @ref backgroundColor
    void setBackgroundColor(const QColor &color = Qt::white);
        //! �������� �������� @ref backgroundColor
    QColor getBackgroundColor() const;
        //! ������������� @ref backgroundColorSelected
    void setBackgroundColorSelected(const QColor &color = Qt::green);
        //! �������� �������� @ref backgroundColorSelected
    QColor getBackgroundColorSelected() const;
        //! ������������� @ref backgroundColorPressed
    void setBackgroundColorPressed(const QColor &color = Qt::yellow);
        //! �������� �������� @ref backgroundColorPressed
    QColor getBackgroundColorPressed() const;

        //! ������������� �������� @ref pathSelected
    void selectPath(bool s = true);
        //! ������������� �������� @ref selected
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

        //! �������� = true, ���� ������� ����, � ������� ��������� �������
    bool pathSelected;
        //! �������� = true, ���� ������� ��������
    bool selected;
        //! �������� = true, ���� ������� ������ ������
    bool pressed;
        //! ����� �������
    QString name;

        //! ���� ���� ������� � ���������� ���������
    QColor backgroundColor;
        //! ���� ���� ������� � ��������� ���������
    QColor backgroundColorSelected;
        //! ���� ���� ������� � ��������� ������� ������
    QColor backgroundColorPressed;

        //! ����������� �������� ������� ������� � ���������� ���������
    QPen regularPen;
        //! ����������� �������� ������� ������� � ��������� ���������
    QPen selectedPen;
        //! ����������� �������� ������� ������� � ��������� ������� ������
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
