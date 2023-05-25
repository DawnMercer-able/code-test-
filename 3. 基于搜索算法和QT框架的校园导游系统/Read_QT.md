# 基于搜索算法和Qt框架的校园导游系统
##  基本逻辑讲解
#### 校园导游系统是一款方便学生在校园内找到目的地的应用程序。
它具有以下特点：
1. 兼容本校和其他学校的地图信息：该系统可以上传多个学校的地图信息，方便用户在多个学校之间切换。
2. 自动分析最佳路径：用户只需输入当前所在地和目的地，该系统就能自动分析出最佳路径，并在地图上显示出来。这样，用户就可以轻松找到目的地，不必担心迷路或浪费时间。
3. 数据结构和算法：该系统采用了邻接矩阵和无向图作为主要数据结构，并使用广度优先算法进行路径分析。这种算法可以快速搜索整个图形，并找到最短路径。
总之，校园导游系统是一款非常实用的应用程序，它可以帮助学生更好地适应大学生活，并让他们更轻松地找到目的地。
### 1 问题分析和任务定义
#### 1.1 问题描述和要求
#### 【问题描述】 根据学生和他们的要求，设计一个简单的小程序exe，帮助同学快速找到最短路径。
#### 【基本要求】 可以储存地图信息，可以由用户点击对应地点自动分析出最优路径。
#### 1.2 问题分析
##### 首先，我们需要解决该程序要求的数据结构，众所周知，地图由地点和连接各地点的路径构成，我们可以将地图抽象为有多个无向线段连接的点，也就是无向图。其次，我们要这个系统可以上传不同学校的地图无向图以达成兼容的效果。最后，根据用户输入的所在地和目的地，该系统可以自动给出一个最佳路径并在地图上标注。我采用了Qt框架作为图形化编程的基础框架，Qt是一个跨平台的C++应用程序开发框架，由Qt公司开发。它提供了一套丰富的GUI（图形用户界面）和功能库，可用于构建高性能、交互式和可扩展的应用程序。Qt还包括一些工具和实用程序，例如Qt Designer（用于创建GUI），Qt Linguist（用于本地化）和Qt Assistant（用于文档）等。
### 2.数据结构的选择和概要设计
#### 2.1 存储无向图的数据结构
##### (1) 存储无向图的数据结构
##### 无向图可以由两种数据结构储存，一种是邻接表，一种是邻接矩阵。
##### 邻接表是一种链式存储结构，它将每个顶点的所有邻接点都存储在一个单独的链表中。具体来说，对于每个顶点i，我们创建一个链表，该链表包含所有与i相邻的顶点。因此，邻接表可以用一个数组和一组链表来表示整个图。
##### 邻接矩阵是一种二维数组，其中第i行第j列的元素表示顶点i和顶点j之间是否有一条边。如果有，则该元素的值为1，否则为0。由于无向图是对称的，因此我们只需要存储上三角或下三角部分即可。
##### (2) 使用邻接表作为存储的数据结构
##### 由于校园的地图无向图的顶点一般是比较多的，假如使用邻接矩阵，需要分配O(n2)的空间，但是使用邻接表，需要分配O(n+m)的空间。为了尽量节省分配的空间，这里我们采用邻接表作为存储的数据结构。

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
  
  #### (3) 广度优先算法
  #### 要求：
#####    1.用户输入当前顶点和目标节点
#####    2.自动搜寻最短的路径
#####    3.保存路径信息并输出
  
    #include <iostream>
    #include <vector>
    #include <queue>

    using namespace std;

    const int MAXN = 100; // 最大顶点数
    const int INF = 0x3f3f3f3f; // 无穷大

    struct Edge {
        int to, weight;
        Edge(int t, int w) : to(t), weight(w) {}
    };

    vector<Edge> adj[MAXN]; // 邻接表
    int dist[MAXN]; // 存储起点到各个顶点的最短距离
    int pre[MAXN]; // 存储搜索路径

    void bfs(int s, int t) {
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        pre[s] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].to;
                if (dist[v] == INF) { // 如果v还没有被访问过
                    dist[v] = dist[u] + 1;
                    pre[v] = u;
                    q.push(v);
                }
            }
        }

        if (dist[t] != INF) { // 如果存在从s到t的路径
            vector<int> path;
            for (int u = t; u != -1; u = pre[u]) {
                path.push_back(u);
            }
            cout << "Shortest Path: ";
            for (int i = path.size() - 1; i >= 0; i--) {
                cout << path[i] << " ";
            }
            cout << endl;
        }
        else {
            cout << "No path from " << s << " to " << t << endl;
        }
    }
#### 2.2 概要设计
##### 2.2.1 概述
######  本实验的编程语言使用了C++，C++具有高效的编程速度，可以直接编译为机器码，同时也支持面对对象，在游戏开发，操作系统和嵌入式系统等领域都有不错的表现。同时，本实验基于Qt框架并进行面对对象和图像化编程实现校园导游系统，实现了最佳路径搜索的需求。
##### 2.2.2 逻辑模块说明



