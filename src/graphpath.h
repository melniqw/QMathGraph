#ifndef GRAPHPATH_H
#define GRAPHPATH_H

#include <QObject>
#include "graphvertice.h"

class GraphPath : public QObject
{
    Q_OBJECT

public:
    explicit GraphPath(QObject *parent = 0);
    ~GraphPath();

    void addVertice(GraphVertice *v);
	
    bool containsVertice(GraphVertice *v);

    void setSelected(bool selected = true);

private:
    QList <GraphVertice *> vertices;

};

#endif // GRAPHPATH_H
