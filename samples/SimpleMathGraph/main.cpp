#include <QtGui/QApplication>
#include "graphdrawer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GraphDrawer gd;
    gd.show();
    gd.resize( 500, 500 );

    QPen pen;
    pen.setWidth( 2 );

    gd.setVertice( "one", QPointF(0,0) )->setPen( pen );
    gd.setVertice( "two", QPointF(20,40) )->setPen( pen );
    gd.setVertice( "three", QPointF(60,60) )->setPen( pen );
    gd.setVertice( "four", QPointF(80,-20) )->setPen( pen );
    gd.setVertice( "five", QPointF(100,40) )->setPen( pen );
    gd.setVertice( "six", QPointF(120,100) )->setPen( pen );    

    gd.setEdge( "one", "two", GraphEdge::UNDIRECTED );
    gd.setEdge( "two", "three", GraphEdge::UNDIRECTED );
    gd.setEdge( "two", "four", GraphEdge::UNDIRECTED );
    gd.setEdge( "four", "three", GraphEdge::UNDIRECTED );
    gd.setEdge( "three", "five", GraphEdge::UNDIRECTED );
    gd.setEdge( "four", "five", GraphEdge::UNDIRECTED );
    gd.setEdge( "five", "six", GraphEdge::UNDIRECTED );
    
    return a.exec();
}
