#ifndef GRAPHPATH_H
#define GRAPHPATH_H

#include <QObject>
#include "graphvertice.h"

//! Используется для представления пути в графе на основе последовательности вершин @ref GraphVertice.
/**
  Путь графа - последовательность соединенных ребрами @ref GraphEdge между собой вершин @ref GraphVertice.
*/
class GraphPath : public QObject
{
    Q_OBJECT

public:
    explicit GraphPath(QObject *parent = 0);
    ~GraphPath();

        //! Добавление вершины в путь.
    void addVertice(GraphVertice *v);

        //! Возвращает true, если путь содержит вершину v, иначе false.
    bool containsVertice(GraphVertice *v);

        //! Установка/снятие выделения с пути
    void setSelected(bool selected = true);

private:
        //! Список вершин, пренадлежащих пути
    QList <GraphVertice *> vertices;

};

#endif // GRAPHPATH_H
