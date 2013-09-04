#include "graphpath.h"

GraphPath::GraphPath(QObject *parent) :
    QObject(parent)
{
}

GraphPath::~GraphPath()
{
}

void GraphPath::addVertice(GraphVertice *v)
{
    vertices.append( v );
}

bool GraphPath::containsVertice(GraphVertice *v)
{
    return vertices.contains(v);
}

void GraphPath::setSelected(bool selected)
{
    if ( selected )
    {
        foreach ( GraphVertice *v, vertices )
        {
            v->selectPath( true );
        }
    }
    else
    {
        foreach ( GraphVertice *v, vertices )
        {
            v->selectPath( false );
        }
    }
}
