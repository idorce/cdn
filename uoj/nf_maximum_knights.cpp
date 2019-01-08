//------
// B. Maximum Knights

// Description：
// Given a N∗N chessboard. There are M obstacles in the chessboard and the position of i-th obstacle is (Xi,Yi). You are asked to find the maximum number of knights which can be placed in the chessboard at the same time, satisfied that,

// No two knights can attack each other.

// Knights can't be placed in obstacle.

// There can be at most one knight in a grid.

// (A Knight in chess can attack 8 positions, as shown in following figure)

// INPUT:
// Input is given from Standard Input in the following format:

// N M

// X1 Y1

// X2 Y2

// ..

// XM YM

// OUTPUT:
// Print the maximum number of knights.

// Sample Input 1
// 3 2
// 1 1
// 3 3
// Sample Output 1:
// 5
//------

// 棋盘黑白染色，二分图最大独立集问题
// https://blog.csdn.net/MaxMercer/article/details/78230410
// 选出一些点， 使两两之间没有边， 包含顶点数最多的集合称之为最大独立集
// 最大流=最小割=最小点权覆盖集=sum-最大点权独立集
// Dinic

//------
// [martinue], CSDN.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
typedef long long ll;
const int oo = 1e9;        /**oo 表示无穷大*/
const int mm = 119999999;  /**mm 表示边的最大数量，记住要是原图的两倍，在加边的时候都是双向的*/
const int mn = 40010;      /**mn 表示点的最大数量*/
int node, src, dest, edge; /**node 表示节点数，src 表示源点，dest 表示汇点，edge 统计边数*/
int ver[mm], flow[mm], nex[mm];
int head[mn], work[mn], dis[mn], q[mn];
void prepare(int _node, int _src, int _dest) {
    node = _node, src = _src, dest = _dest;
    for (int i = 0; i <= node; ++i) head[i] = -1;
    edge = 0;
}
void addedge(int u, int v, int c) {
    ver[edge] = v, flow[edge] = c, nex[edge] = head[u], head[u] = edge++;
    ver[edge] = u, flow[edge] = 0, nex[edge] = head[v], head[v] = edge++;
}
bool Dinic_bfs() {
    int i, u, v, l, r = 0;
    for (i = 0; i < node; ++i) dis[i] = -1;
    dis[q[r++] = src] = 0;
    for (l = 0; l < r; ++l)
        for (i = head[u = q[l]]; i >= 0; i = nex[i])
            if (flow[i] && dis[v = ver[i]] < 0) {
                dis[q[r++] = v] = dis[u] + 1;
                if (v == dest) return 1;
            }
    return 0;
}
int Dinic_dfs(int u, int exp) {
    if (u == dest) return exp;
    for (int &i = work[u], v, tmp; i >= 0; i = nex[i])
        if (flow[i] && dis[v = ver[i]] == dis[u] + 1 && (tmp = Dinic_dfs(v, min(exp, flow[i]))) > 0) {
            flow[i] -= tmp;
            flow[i ^ 1] += tmp;
            return tmp;
        }
    return 0;
}
int Dinic_flow() {
    int i, ret = 0, delta;
    while (Dinic_bfs()) {
        for (i = 0; i < node; ++i) work[i] = head[i];
        while ((delta = Dinic_dfs(src, oo))) ret += delta;
    }
    return ret;
}
int xx[210][210], fx[8][2] = {{1, 2}, {2, 1}, {-1, -2}, {-2, -1}, {1, -2}, {-2, 1}, {-1, 2}, {2, -1}};
int main() {
    int m, n;
    while (~scanf("%d%d", &n, &m)) {
        memset(xx, 0, sizeof(xx));
        prepare(n * n + 2, 0, n * n + 1);
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            xx[a][b] = 1;
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (!xx[i][j]) {
                    if ((i + j) & 1)
                        addedge(0, (i - 1) * n + j, 1);
                    else
                        addedge((i - 1) * n + j, n * n + 1, 1);
                    for (int k = 0; k < 8; k++) {
                        int x = i + fx[k][0], y = j + fx[k][1];
                        if (x >= 1 && x <= n && y >= 1 && y <= n && !xx[x][y]) {
                            if ((i + j) & 1)
                                addedge((i - 1) * n + j, (x - 1) * n + y, oo);
                            else
                                addedge((x - 1) * n + y, (i - 1) * n + j, oo);
                        }
                    }
                    xx[i][j] = 1;
                }
        printf("%d\n", n * n - m - Dinic_flow());
    }
    return 0;
}
//------