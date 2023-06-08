#include "graph.h"
#include <QQueue>
#include <QDebug>

Graph::Graph(QObject *parent)
    : QObject(parent)
{
}

Graph::~Graph()
{
    for (Node *node : nodes) {
        delete node->item;
        delete node->label;
        for (Edge edge : node->edges) {
            delete edge.label;
        }
        delete node;
    }
}

void Graph::addNode(QGraphicsEllipseItem *nodeItem, QGraphicsTextItem *labelItem) {
    Node *node = new Node(nodeItem->pos(), nodeItem, labelItem);
    nodes.append(node);
}

void Graph::addEdge(int fromNodeIndex, int toNodeIndex, QGraphicsTextItem *labelItem) {
    nodes[fromNodeIndex]->edges.append(Edge(toNodeIndex, labelItem));
    nodes[toNodeIndex]->edges.append(Edge(fromNodeIndex, labelItem));
}

int Graph::getNodeCount() {
    return nodes.length();
}

QPointF Graph::getNodePosition(int nodeIndex) {
    return nodes[nodeIndex]->position + QPointF(25, 25);
}

QGraphicsEllipseItem* Graph::getNodeItem(int nodeIndex) {
    return nodes[nodeIndex]->item;
}

bool Graph::getShortestPath(int nodeIndex) {
    return nodes[nodeIndex]->distance != INT_MAX;
}

int Graph::getShortestPathLength(int endNodeIndex) {
    return nodes[endNodeIndex]->distance;
}

void Graph::calculateShortestPath(int startNodeIndex) {
    clearVisited();

    QQueue<int> queue;
    nodes[startNodeIndex]->visited = true;
    nodes[startNodeIndex]->distance = 0;
    queue.enqueue(startNodeIndex);

    while (!queue.isEmpty()) {
        int currentNodeIndex = queue.dequeue();
        Node *currentNode = nodes[currentNodeIndex];

        for (Edge edge : currentNode->edges) {
            Node *toNode = nodes[edge.toNode];
            if (!toNode->visited) {
                toNode->visited = true;
                toNode->distance = currentNode->distance + edge.label->toPlainText().toInt();
                queue.enqueue(edge.toNode);
            } else if (toNode->distance > currentNode->distance + edge.label->toPlainText().toInt()) {
                toNode->distance = currentNode->distance + edge.label->toPlainText().toInt();
            }
        }
    }
}

void Graph::cancelCalculate() {
    clearVisited();
}

void Graph::clearVisited() {
    for (Node *node : nodes) {
        node->visited = false;
        node->distance = INT_MAX;
    }
}
