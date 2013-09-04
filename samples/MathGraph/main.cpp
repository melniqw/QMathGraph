#include <QtGui/QApplication>
#include "mainwindow.h"
#include "graphdrawer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GraphDrawer gd;
    gd.show();
    gd.resize( 500, 500 );

    QPen pen;
    pen.setWidth( 2 );

    QPen penPressed;
    penPressed.setWidth( 3 );

    GraphVertice *v[6];
    v[0] = gd.setVertice( "one", QPointF(0,0) );
    v[1] = gd.setVertice( "two", QPointF(20,40) );
    v[2] = gd.setVertice( "three", QPointF(60,60) );
    v[3] = gd.setVertice( "four", QPointF(80,-20) );
    v[4] = gd.setVertice( "five", QPointF(100,40) );
    v[5] = gd.setVertice( "six", QPointF(120,100) );

    v[0]->setPen( pen );
    v[0]->setPenPressed( penPressed );
    v[1]->setPen( pen );
    v[1]->setPenPressed( penPressed );
    v[2]->setPen( pen );
    v[2]->setPenPressed( penPressed );
    v[3]->setPen( pen );
    v[3]->setPenPressed( penPressed );
    v[4]->setPen( pen );
    v[4]->setPenPressed( penPressed );
    v[5]->setPen( pen );
    v[5]->setPenPressed( penPressed );

    gd.setEdge( v[0], v[1], GraphEdge::UNDIRECTED );
    gd.setEdge( v[1], v[2], GraphEdge::UNDIRECTED );
    gd.setEdge( v[1], v[3], GraphEdge::UNDIRECTED );
    gd.setEdge( v[3], v[2], GraphEdge::UNDIRECTED );
    gd.setEdge( v[1], v[4], GraphEdge::UNDIRECTED );
    gd.setEdge( v[3], v[4], GraphEdge::UNDIRECTED );
    gd.setEdge( v[4], v[5], GraphEdge::UNDIRECTED );

    GraphPath *gp = gd.setPath();
    gp->addVertice( v[0] );
    gp->addVertice( v[1] );
    gp->addVertice( v[2] );

    return a.exec();
}
