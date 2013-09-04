#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include <QGraphicsLineItem>
#include <QObject>
#include <QDebug>
#include <QPen>

#include "graphvertice.h"

//! ������������ ��� ������������� ����� ����� ����� ��������� @ref GraphVertice.
/**
  ����� � ����� ����� ���� ������������ ��� �������������� (��. @ref EdgeType).
*/
class GraphEdge : public QObject
{
    Q_OBJECT

public:
    GraphEdge(GraphVertice *beginVertice, GraphVertice *endVertice);
    ~GraphEdge();

        //! �� ����� ������� ���� �����
    GraphVertice *beginVertice;
        //! � ����� ������� ���� �����
    GraphVertice *endVertice;

        //! ��� �����
    enum EdgeType
    {
            //! ��������������
        UNDIRECTED,
            //! ������������
        DIRECTED
    };

        //! ��������� �������� @ref text
    void setText(const QString &text);
        //! ��������� �������� @ref text
    QString getText() const;

        //! ��������� �������� @ref edgeType
    void setType(EdgeType type);
        //! ��������� �������� @ref edgeType
    EdgeType getType() const;

        //! ��������� @ref pen
    void setPen(const QPen &pen);
        //! ��������� ������ @ref pen
    void setPenWidth(int width);

    QGraphicsLineItem *line;
    void setLine(QGraphicsLineItem *line);

    QGraphicsPolygonItem *polygon;
    void setPolygon(QGraphicsPolygonItem *polygon);

    // ������� �����
    QGraphicsTextItem *textItem;
    void setTextItem(QGraphicsTextItem *textItem);

protected:
        //! �����, ����������� �� �����
    QString text;
        //! ��� �����-���������� ������
    EdgeType edgeType;
        //! ��������� ��������� �����
    QPen pen;

};

#endif // GRAPHEDGE_H
