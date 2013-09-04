#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include <QGraphicsLineItem>
#include <QObject>
#include <QDebug>
#include <QPen>

#include "graphvertice.h"

//! Используется для представления ребра между двумя вершинами @ref GraphVertice.
/**
  Ребро в графе может быть направленным или ненаправленным (см. @ref EdgeType).
*/
class GraphEdge : public QObject
{
    Q_OBJECT

public:
    GraphEdge(GraphVertice *beginVertice, GraphVertice *endVertice);
    ~GraphEdge();

        //! От какой вершины идет ребро
    GraphVertice *beginVertice;
        //! К какой вершине идет ребро
    GraphVertice *endVertice;

        //! Тип ребра
    enum EdgeType
    {
            //! Ненаправленное
        UNDIRECTED,
            //! Направленное
        DIRECTED
    };

        //! Установка значения @ref text
    void setText(const QString &text);
        //! Получение значения @ref text
    QString getText() const;

        //! Установка значения @ref edgeType
    void setType(EdgeType type);
        //! Получение значения @ref edgeType
    EdgeType getType() const;

        //! Установка @ref pen
    void setPen(const QPen &pen);
        //! Установка ширины @ref pen
    void setPenWidth(int width);

    QGraphicsLineItem *line;
    void setLine(QGraphicsLineItem *line);

    QGraphicsPolygonItem *polygon;
    void setPolygon(QGraphicsPolygonItem *polygon);

    // Удалить потом
    QGraphicsTextItem *textItem;
    void setTextItem(QGraphicsTextItem *textItem);

protected:
        //! Текст, находящийся на ребре
    QString text;
        //! Тип ребра-экземпляра класса
    EdgeType edgeType;
        //! Параметры отрисовки ребра
    QPen pen;

};

#endif // GRAPHEDGE_H
