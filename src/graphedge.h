#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include <QGraphicsLineItem>
#include <QObject>
#include <QDebug>
#include <QPen>

#include "graphvertice.h"

class GraphEdge : public QObject
{
    Q_OBJECT

public:
    GraphEdge(GraphVertice *beginVertice, GraphVertice *endVertice);
    ~GraphEdge();

    GraphVertice *beginVertice;
    GraphVertice *endVertice;

    enum EdgeType
    {
        UNDIRECTED,
        DIRECTED
    };

    void setText(const QString &text);
    QString getText() const;

    void setType(EdgeType type);
    EdgeType getType() const;

    void setPen(const QPen &pen);
    void setPenWidth(int width);

    QGraphicsLineItem *line;
    void setLine(QGraphicsLineItem *line);

    QGraphicsPolygonItem *polygon;
    void setPolygon(QGraphicsPolygonItem *polygon);

    QGraphicsTextItem *textItem;
    void setTextItem(QGraphicsTextItem *textItem);

protected:
    QString text;
    EdgeType edgeType;
    EdgeType edgeType;
    QPen pen;

};

#endif // GRAPHEDGE_H
