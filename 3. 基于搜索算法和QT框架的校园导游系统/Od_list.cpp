#include <iostream>
#include <vector>

using namespace std;

// 邻接表节点
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// 图类
class Graph {
private:
    int V; // 顶点数
    vector<AdjListNode*> adj; // 邻接表指针数组

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V, nullptr);
    }

    // 添加边
    void addEdge(int src, int dest) {
        // 创建新节点
        AdjListNode* newNode = new AdjListNode;
        newNode->dest = dest;
        newNode->next = nullptr;

        // 将新节点插入到src的链表头部
        newNode->next = adj[src];
        adj[src] = newNode;

        // 由于是无向图，所以还要将src加入到dest的链表中
        newNode = new AdjListNode;
        newNode->dest = src;
        newNode->next = nullptr;
        newNode->next = adj[dest];
        adj[dest] = newNode;
    }
};
