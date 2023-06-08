#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QList>
#include <QtMath>

class Graph : public QObject
{
    Q_OBJECT

public:
    Graph(QObject *parent = nullptr);
    ~Graph();

    void addNode(QGraphicsEllipseItem *nodeItem, QGraphicsTextItem *labelItem);
    void addEdge(int fromNodeIndex, int toNodeIndex, QGraphicsTextItem *labelItem);
    int getNodeCount();
    QPointF getNodePosition(int nodeIndex);
    QGraphicsEllipseItem* getNodeItem(int nodeIndex);
    bool getShortestPath(int nodeIndex);
    int getShortestPathLength(int endNodeIndex);
    void calculateShortestPath(int startNodeIndex);
    void cancelCalculate();

private:
    struct Edge {
        int toNode;
        QGraphicsTextItem *label;
        Edge(int toNode, QGraphicsTextItem *label) : toNode(toNode), label(label) {}
    };

    struct Node {
        QPointF position;
        QGraphicsEllipseItem *item;
        QGraphicsTextItem *label;
        QList<Edge> edges;
        bool visited;
        int distance;
        Node(QPointF position, QGraphicsEllipseItem *item, QGraphicsTextItem *label) :
            position(position), item(item), label(label), visited(false), distance(INT_MAX) {}
    };

    QList<Node*> nodes;

    void clearVisited();
};

#endif // GRAPH_H
