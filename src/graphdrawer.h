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

//! ������������ ����� ����� - ����������� ���� ��� ��������� �����.
/**
  ������������: ������� (@ref GraphVertice), ����� ����� ���� (@ref GraphEdge).
  ������� ����� ���� ��������� � ���� (@ref GraphPath).
*/
class GraphDrawer : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphDrawer(QWidget *parent = 0);
    ~GraphDrawer();

        //! ������� ����� ������� � ���������� ������ �� ���.
        /**
          @param name - �����, ������������ ������ �������
          @param pos - ������� ������� �� @ref scene
          @return ������ �� ��������� �������
        */
    GraphVertice * setVertice(const QString &name, const QPointF &pos);

        //! ������� ����� ���� � ���������� ������ �� ����.
    GraphPath * setPath();

        //! ���������� � ���� �������.
        /**
            @param path - ����, � �������� ������������ ���������� �������,
            a@param vertice - �������.
        */
    void addToPath(GraphPath *path, GraphVertice *vertice);

        //! ������� ����� ����� ����� ��������� � ���������� ������ �� ���.
        /**
          @param v1 - ������ �������
          @param v2 - ������ �������
          @param t - ��� �����
          @param text - �����, ������������ ����� � ������
        */
    GraphEdge * setEdge(GraphVertice *v1, GraphVertice *v2, GraphEdge::EdgeType t, const QString &text = QString());

        //! ������� ����� ����� ����� ��������� � ���������� ������ �� ���.
        /**
          @param name1 - ����� ������ �������
          @param name2 - ����� ������ �������
          @param t - ��� �����
          @param text - �����, ������������ ����� � ������
        */
    GraphEdge * setEdge(const QString &name1, const QString &name2, GraphEdge::EdgeType t, const QString &text = QString());

private:
        //! �������
    QList <GraphVertice *> vertices;
        //! �����
    QList <GraphEdge *> edges;
        //! ����
    QList <GraphPath *> paths;

protected:
    void wheelEvent(QWheelEvent *event);

        //! ��� ����� +
    void zoomIn();

        //! ��� ����� -
    void zoomOut();

        //! ��������� ��� ������ ��������� � ����
        /**
          @param vertice - �������, ������� ����������� � ����
          @param select - ����� ��� ���������� ���������
        */
    void selectPath(GraphVertice *vertice, bool select);

        //! ��������� ����� �����
    void drawEdge(GraphEdge *e);

        //! ���������� �����, ����������� � ��������.
    void drawVerticeEdges(GraphVertice *v);

        //! �������� @ref edges.
    void clearEdges();

private:
        //! �����
        /**
          ���� ��� ��������� �����
        */
    QGraphicsScene *scene;

public slots:
        //! ������� @ref scene
    void clear();

        //! ������ ��������� �� ���� ���������
    void unselectAll();

private slots:
    void verticePressed(GraphVertice *vertice);
    void verticeReleased(GraphVertice *vertice);
    void verticeSelected(GraphVertice *vertice);
    void verticeMoved(GraphVertice *vertice, QPointF pos);

};

#endif // QGRAPHDRAWER_H
