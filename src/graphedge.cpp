#include "graphedge.h"

GraphEdge::GraphEdge(GraphVertice *beginVertice, GraphVertice *endVertice) :
    beginVertice(beginVertice), endVertice(endVertice)
{
    pen.setColor( Qt::black );
    pen.setWidth( 2 );

    line = NULL;
    polygon = NULL;
    textItem = NULL;

//    text = "";
}

GraphEdge::~GraphEdge()
{
    if ( line )
        delete line;
    if ( polygon )
        delete polygon;
    if ( textItem )
        delete textItem;

//    qDebug() << "~GraphEdge";
}

void GraphEdge::setText(const QString &text)
{
    this->text = text;
}

QString GraphEdge::getText() const
{
    return text;
}

GraphEdge::EdgeType GraphEdge::getType() const
{
    return edgeType;
}

void GraphEdge::setType(EdgeType type)
{
    edgeType = type;
}

void GraphEdge::setPen(const QPen &pen)
{
    this->pen = pen;
}

void GraphEdge::setPenWidth(int width)
{
    pen.setWidth( width );
}

void GraphEdge::setLine(QGraphicsLineItem *line)
{
    this->line = line;
    this->line->setPen( pen );
}

void GraphEdge::setPolygon(QGraphicsPolygonItem *polygon)
{
    this->polygon = polygon;
    polygon->setPen( pen );
}

void GraphEdge::setTextItem(QGraphicsTextItem *textItem)
{
    this->textItem = textItem;
    textItem->setDefaultTextColor( pen.color() );
}

