#include "graphdrawer.h"

#include <QtGui/QWidget>
#include <QPainter>

#include <QDebug>
#include <math.h>

#define PI 3.14159

GraphDrawer::GraphDrawer(QWidget *parent) :
    QGraphicsView(parent)
{
    setMouseTracking( true );

    scene = new QGraphicsScene( this );
    this->setScene( scene );
    this->setDragMode( QGraphicsView::ScrollHandDrag );
}

GraphDrawer::~GraphDrawer()
{
    clearEdges();
}

void GraphDrawer::wheelEvent(QWheelEvent *event)
{
    if ( event->delta() > 0 )
    {
        zoomIn();
    }
    else
    {
        zoomOut();
    }
}

void GraphDrawer::zoomIn()
{
    scale( 1.2, 1.2 );
}

void GraphDrawer::zoomOut()
{
    scale( 0.8, 0.8 );
}

void GraphDrawer::verticePressed(GraphVertice *vertice)
{
//    drawVerticeEdges( vertice );
    selectPath( vertice, true );
}

void GraphDrawer::verticeReleased(GraphVertice *vertice)
{
//    drawVerticeEdges( vertice );
    selectPath( vertice, false );
}

void GraphDrawer::verticeSelected(GraphVertice *vertice)
{
    unselectAll();
    vertice->select();
}

void GraphDrawer::verticeMoved(GraphVertice *vertice, QPointF pos)
{
    drawVerticeEdges( vertice );
}

void GraphDrawer::selectPath(GraphVertice *vertice, bool select)
{
    foreach( GraphPath *p, paths )
    {
        if ( p->containsVertice(vertice) )
        {
            p->setSelected( select );
        }
    }
}

void GraphDrawer::drawVerticeEdges(GraphVertice *v)
{
    foreach( GraphEdge *e, edges )
    {
        if ( e->beginVertice == v || e->endVertice == v )
        {
            if ( e->line )
            {
                scene->removeItem( e->line );
            }
            if ( e->polygon )
            {
                scene->removeItem( e->polygon );
            }
            if ( e->textItem )
            {
                scene->removeItem( e->textItem );
            }

//            if ( v->isPressed() )
//            {
//                e->setPenWidth( v->getPenWidthPressed() );
//            }
//            else
//            {
//                e->setPenWidth( v->getPenWidth() );
//            }

            drawEdge( e );
        }
    }

}

GraphPath * GraphDrawer::setPath()
{
    GraphPath *p = new GraphPath(this);
    paths.append( p );

    return p;
}

void GraphDrawer::addToPath(GraphPath *path, GraphVertice *vertice)
{
    path->addVertice( vertice );
}

void GraphDrawer::drawEdge(GraphEdge *e)
{
    // This values are used to move arrow from vertice's center to corner //
    qreal x_correct1 = 0.0;
    qreal y_correct1 = 0.0;
    qreal x_correct2 = 0.0;
    qreal y_correct2 = 0.0;

    //////////////////////////////////////////
    if ( e->beginVertice->getPosition().x() > e->endVertice->getPosition().x()
         &&
         e->beginVertice->getPosition().y() > e->endVertice->getPosition().y() )
    {
        x_correct1 = -e->beginVertice->getWidth() / 2;
        y_correct1 = 0.0;

        x_correct2 = e->endVertice->getWidth() / 2;
        y_correct2 = 0.0;
    }
    else
        if ( e->beginVertice->getPosition().x() > e->endVertice->getPosition().x()
         &&
        e->beginVertice->getPosition().y() < e->endVertice->getPosition().y() )
    {
        x_correct1 = 0.0;
        y_correct1 = e->beginVertice->getHeight() / 2;

        x_correct2 = 0.0;
        y_correct2 = -e->endVertice->getHeight() / 2;
    }
    else
    if ( e->beginVertice->getPosition().x() < e->endVertice->getPosition().x()
         &&
        e->beginVertice->getPosition().y() > e->endVertice->getPosition().y() )
    {
        x_correct1 = 0.0;
        y_correct1 = -e->beginVertice->getHeight() / 2;

        x_correct2 = 0.0;
        y_correct2 = e->endVertice->getHeight() / 2;
    }
    else
    if ( e->beginVertice->getPosition().x() < e->endVertice->getPosition().x()
         &&
         e->beginVertice->getPosition().y() < e->endVertice->getPosition().y() )
    {
        x_correct1 = e->beginVertice->getWidth() / 2;
        y_correct1 = 0.0;

        x_correct2 = -e->endVertice->getWidth() / 2;
        y_correct2 = 0.0;
    }

    if ( e->beginVertice->getPosition().x() > e->endVertice->getPosition().x() )
    {
        x_correct1 = -e->beginVertice->getWidth() / 2;
        x_correct2 = e->endVertice->getWidth() / 2;
    }
    else
    {
        x_correct1 = e->beginVertice->getWidth() / 2;
        x_correct2 = -e->endVertice->getWidth() / 2;
    }
    //////////////////////////////////////////

    if ( e->beginVertice == NULL || e->endVertice == NULL )
        return;

    if ( e->beginVertice->getPosition().y() > e->endVertice->getPosition().y() )
    {
        y_correct1 = -e->beginVertice->getHeight() / 2;
        y_correct2 = e->endVertice->getHeight() / 2;
    }
    else
    {
        y_correct1 = e->beginVertice->getHeight() / 2;
        y_correct2 = -e->endVertice->getHeight() / 2;
    }

    // Направленная вершина //
    if ( e->getType() == GraphEdge::DIRECTED )
    {
        // creates LINE //
        QLineF lineF( e->endVertice->getPosition().x()*2 + e->endVertice->getWidth()/2 + x_correct2,
                      e->endVertice->getPosition().y()*2 + e->endVertice->getHeight()/2 + y_correct2,
                      e->beginVertice->getPosition().x()*2 + e->beginVertice->getWidth()/2 + x_correct1,
                      e->beginVertice->getPosition().y()*2 + e->beginVertice->getHeight()/2 + y_correct1 );

        QGraphicsLineItem *lineItem = scene->addLine( lineF );
        e->setLine( lineItem );
        //////////////////////////////////

        // Отрисовка стрелки на конце ребра //
        double angle = acos( lineF.dx() / lineF.length() );
        if ( lineF.dy() >= 0)
        {
             angle = ( PI * 2) - angle;
        }
        qreal arrowSize = 7;
        QPointF arrowP1 = lineF.p1() + QPointF( sin(angle + PI / 3) * arrowSize,
                                                cos(angle + PI / 3) * arrowSize );
        QPointF arrowP2 = lineF.p1() + QPointF( sin(angle + PI - PI / 3) * arrowSize,
                                                cos(angle + PI - PI / 3) * arrowSize );

        QPolygonF polygon;
        polygon.append( lineF.p1());
        polygon.append( arrowP1 );
        polygon.append( arrowP2 );

        QGraphicsPolygonItem *polygonItem = scene->addPolygon( polygon );
        e->setPolygon( polygonItem );
        //////////////////////////////////

        // Отрисовка текста рядом с ребром //
        if ( e->getText() != "" )
        {
            QGraphicsTextItem *textItem = scene->addText( e->getText() );
            textItem->setPos( e->beginVertice->getPosition().x() + e->endVertice->getPosition().x() ,
                              e->beginVertice->getPosition().y() + e->endVertice->getPosition().y() );

            e->setTextItem( textItem );
        }
    }
    else
    // Ненаправленная вершина //
    if ( e->getType() == GraphEdge::UNDIRECTED )
    {
        QLineF lineF( e->endVertice->getPosition().x()*2 + e->endVertice->getWidth()/2 + x_correct2,
                      e->endVertice->getPosition().y()*2 + e->endVertice->getHeight()/2 + y_correct2,
                      e->beginVertice->getPosition().x()*2 + e->beginVertice->getWidth()/2 + x_correct1,
                      e->beginVertice->getPosition().y()*2 + e->beginVertice->getHeight()/2 + y_correct1 );

        QGraphicsLineItem *lineItem = scene->addLine( lineF );
        e->setLine( lineItem );
    }

}

void GraphDrawer::clear()
{
    scene->clear();

    vertices.clear();
    edges.clear();

    paths.clear();
}

GraphVertice * GraphDrawer::setVertice(const QString &name, const QPointF &pos)
{
    GraphVertice *v = new GraphVertice( name );

    connect( v, SIGNAL(verticeSelected(GraphVertice*)),
          this, SLOT(verticeSelected(GraphVertice*)) );
    connect( v, SIGNAL(verticeMoved(GraphVertice*,QPointF)),
          this, SLOT(verticeMoved(GraphVertice*,QPointF)) );
    connect( v, SIGNAL(verticePressed(GraphVertice*)),
          this, SLOT(verticePressed(GraphVertice*)) );
    connect( v, SIGNAL(verticeReleased(GraphVertice*)),
          this, SLOT(verticeReleased(GraphVertice*)) );

    v->setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );

    scene->addItem( v );
    v->setPosition( pos );

    vertices.append( v );

    return v;
}

GraphEdge * GraphDrawer::setEdge(const QString &name1, const QString &name2, GraphEdge::EdgeType t, const QString &text)
{
    GraphVertice *fromVertice = NULL;
    GraphVertice *toVertice = NULL;

    for ( int i=0; i < vertices.count(); i++ )
    {
        if ( vertices.at(i)->getName() == name1 )
        {
            fromVertice = vertices.at(i);
        }
        else
        if ( vertices.at(i)->getName() == name2 )
        {
            toVertice = vertices.at(i);
        }
    }

    GraphEdge * e = new GraphEdge( fromVertice, toVertice );
    e->setType( t );
    e->setText( text );

    QPen pen = toVertice->getPen();
//    pen.setColor( toVertice->getPenColor() );
//    pen.setWidth( toVertice->getPenWidth() );
    e->setPen( pen );

    edges.append( e );

    drawEdge( e );

    return e;
}

GraphEdge * GraphDrawer::setEdge(GraphVertice *v1, GraphVertice *v2, GraphEdge::EdgeType t, const QString &text)
{
    GraphEdge * e = new GraphEdge( v1, v2 );
    e->setType( t );
    e->setText( text );

    QPen pen = v2->getPen();
//    pen.setColor( v2->getPenColor() );
//    pen.setWidth( v2->getPenWidth() );
    e->setPen( pen );

    edges.append( e );

    drawEdge( e );

    return e;
}

void GraphDrawer::clearEdges()
{
    foreach( GraphEdge *e, edges )
    {
        scene->removeItem( e->line );
        scene->removeItem( e->polygon );
    }

    qDeleteAll( edges );
    edges.clear();
}

void GraphDrawer::unselectAll()
{
    for ( int i=0; i < vertices.count(); i++ )
    {
        vertices.at(i)->select( true );
    }
}
