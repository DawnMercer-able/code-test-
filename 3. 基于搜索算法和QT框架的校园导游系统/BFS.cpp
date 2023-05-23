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

int main() {
    int n = 5, m = 6; // 默认的顶点数和边数
    adj[1].push_back(Edge(2, 1));
    adj[1].push_back(Edge(3, 2));
    adj[2].push_back(Edge(4, 3));
    adj[2].push_back(Edge(5, 4));
    adj[3].push_back(Edge(5, 5));
    adj[4].push_back(Edge(5, 6));

    int s = 1, t = 5; // 默认的起点和目的地

    cout << "请输入起始地点" << endl;
    cin >> s;
    cout << "请输入目的地点" << endl;
    cin >> t;
    memset(dist, INF, sizeof(dist)); // 初始化dist数组

    bfs(s, t);

    return 0;
}
