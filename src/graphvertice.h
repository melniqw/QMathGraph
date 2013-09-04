#ifndef GRAPHVERTICE_H
#define GRAPHVERTICE_H

#include <QPainter>
#include <QDebug>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsTextItem>

//! Используется для представляения вершины графа.
class GraphVertice : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES( QGraphicsItem )

public:
    GraphVertice(const QString &name = "");
    ~GraphVertice();

        //! Установка значения @ref name
    void setName(const QString &name);
        //! Получение значения @ref name
    QString getName() const { return name; }

        //! Установка позиции вершины на сцене @ref GraphDrawer.
    void setPosition(const QPointF &pos);
        //! Получение текущей позиции вершины на сцене @ref GraphDrawer.
    QPointF getPosition() const;

        //! Установка значения @ref regularPen
    void setPen(const QPen &pen = QPen(Qt::black));
        //! Получение значения @ref regularPen
    QPen getPen() const;
        //! Установка значения @ref selectedPen
    void setPenSelected(const QPen &pen = QPen(Qt::black));
        //! Получение значения @ref selectedPen
    QPen getPenSelected() const;
        //! Установка значения @ref pressedPen
    void setPenPressed(const QPen &pen = QPen(Qt::black));
        //! Получение значения @ref pressedPen
    QPen getPenPressed() const;

        //! Устанавливает @ref backgroundColor
    void setBackgroundColor(const QColor &color = Qt::white);
        //! Получает значение @ref backgroundColor
    QColor getBackgroundColor() const;
        //! Устанавливает @ref backgroundColorSelected
    void setBackgroundColorSelected(const QColor &color = Qt::green);
        //! Получает значение @ref backgroundColorSelected
    QColor getBackgroundColorSelected() const;
        //! Устанавливает @ref backgroundColorPressed
    void setBackgroundColorPressed(const QColor &color = Qt::yellow);
        //! Получает значение @ref backgroundColorPressed
    QColor getBackgroundColorPressed() const;

        //! Устанавливает параметр @ref pathSelected
    void selectPath(bool s = true);
        //! Устанавливает параметр @ref selected
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

        //! Параметр = true, если выделен путь, в которой находится вершина
    bool pathSelected;
        //! Параметр = true, если вершина выделена
    bool selected;
        //! Параметр = true, если вершина нажата мышкой
    bool pressed;
        //! Текст вершины
    QString name;

        //! Цвет фона вершины в нормальном состоянии
    QColor backgroundColor;
        //! Цвет фона вершины в выделеном состоянии
    QColor backgroundColorSelected;
        //! Цвет фона вершины в состоянии нажатия мышкой
    QColor backgroundColorPressed;

        //! Графическое значение обводки вершины в нормальном состоянии
    QPen regularPen;
        //! Графическое значение обводки вершины в выделеном состоянии
    QPen selectedPen;
        //! Графическое значение обводки вершины в состоянии нажатия мышкой
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
