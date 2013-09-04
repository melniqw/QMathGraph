#ifndef GRAPHDRAWER_H
#define GRAPHDRAWER_H

#include <QWidget>
#include <QDialog>
#include <QtCore>
#include <QtGui>

#include "graphvertice.h"
#include "graphedge.h"
#include "graphpath.h"

namespace Ui {
    class GraphDrawer;
}

//! Представляет собой сцену - графическое окно для отрисовки графа.
/**
  Отрисовывает: вершины (@ref GraphVertice), ребра между ними (@ref GraphEdge).
  Вершины могут быть соединены в пути (@ref GraphPath).
*/
class GraphDrawer : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphDrawer(QWidget *parent = 0);
    ~GraphDrawer();

        //! Создает новую вершину и возвращает ссылку на нее.
        /**
          @param name - текст, отображенный внутри вершины
          @param pos - позиция вершины на @ref scene
          @return ссылку на созданную вершину
        */
    GraphVertice * setVertice(const QString &name, const QPointF &pos);

        //! Создает новый путь и возвращает ссылку на него.
    GraphPath * setPath();

        //! Добавление в путь вершины.
        /**
            @param path - путь, к которому производится добавление вершины,
            a@param vertice - вершина.
        */
    void addToPath(GraphPath *path, GraphVertice *vertice);

        //! Создает ребро между двумя вершинами и возвращает ссылку на нее.
        /**
          @param v1 - первая вершина
          @param v2 - вторая вершина
          @param t - тип ребра
          @param text - текст, отображенный рядом с ребром
        */
    GraphEdge * setEdge(GraphVertice *v1, GraphVertice *v2, GraphEdge::EdgeType t, const QString &text = QString());

        //! Создает ребро между двумя вершинами и возвращает ссылку на нее.
        /**
          @param name1 - текст первой вершины
          @param name2 - текст второй вершины
          @param t - тип ребра
          @param text - текст, отображенный рядом с ребром
        */
    GraphEdge * setEdge(const QString &name1, const QString &name2, GraphEdge::EdgeType t, const QString &text = QString());

private:
        //! Вершины
    QList <GraphVertice *> vertices;
        //! Ребра
    QList <GraphEdge *> edges;
        //! Пути
    QList <GraphPath *> paths;

protected:
    void wheelEvent(QWheelEvent *event);

        //! Зум сцены +
    void zoomIn();

        //! Зум сцены -
    void zoomOut();

        //! Установка или снятие выделения с пути
        /**
          @param vertice - вершина, которая пренадлежит к пути
          @param select - снять или установить выделение
        */
    void selectPath(GraphVertice *vertice, bool select);

        //! Отрисовка ребра графа
    void drawEdge(GraphEdge *e);

        //! Прорисовка ребер, соединенных с вершиной.
    void drawVerticeEdges(GraphVertice *v);

        //! Удаление @ref edges.
    void clearEdges();

private:
        //! Сцена
        /**
          Поле для отрисовки графа
        */
    QGraphicsScene *scene;

public slots:
        //! Очистка @ref scene
    void clear();

        //! Снятие выделения со всех элементов
    void unselectAll();

private slots:
    void verticePressed(GraphVertice *vertice);
    void verticeReleased(GraphVertice *vertice);
    void verticeSelected(GraphVertice *vertice);
    void verticeMoved(GraphVertice *vertice, QPointF pos);

};

#endif // QGRAPHDRAWER_H
