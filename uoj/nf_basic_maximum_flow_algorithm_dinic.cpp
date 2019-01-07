#include <queue>
#include <iostream>
#include <cstring>
#include <limits>
using namespace std;

//--------
// [WD Xu] modified.

const long long maxn = 1205;
const long long inf = numeric_limits<long long>::max();
const long long maxm = 120005;
typedef struct Dinic {
  typedef struct Edge {
    long long u, v, w, next;
  }Edge;
  long long head[maxn], hcnt;
  long long cur[maxn];
  long long dep[maxn];
  Edge e[maxm];
  long long S, T, N;

  void init() {
    memset(head, -1, sizeof head);
    hcnt = 0;
    S = T = N = 0;
  }

  void adde(long long u, long long v, long long w) {
    e[hcnt].u = u, e[hcnt].v = v, e[hcnt].w = w;
    e[hcnt].next = head[u]; head[u] = hcnt++;
    e[hcnt].u = v, e[hcnt].v = u, e[hcnt].w = 0;
    e[hcnt].next = head[v]; head[v] = hcnt++;
    // 01 23 45
    // i i^1
  }

  // BFS 分层
  long long bfs() {
    for(long long i = 0; i < N; i++) {
      dep[i] = inf;
    }
    queue<long long> q;
    q.emplace(S); dep[S] = 0;
    while(!q.empty()) {
      long long u = q.front(); q.pop();
      for(long long i = head[u]; ~i; i=e[i].next) {
        long long v = e[i].v, w = e[i].w;
        if(w > 0 && dep[u] + 1 < dep[v]) {
          dep[v] = dep[u] + 1;
          if(v == T) return 1;
          q.emplace(v);
        }
      }
    }
    return dep[T] != inf;
  }

  // DFS 增广
  long long dfs(long long s, long long mw) {
    if(s == T) return mw;
    for(long long i = cur[s]; ~i; i=e[i].next) {
      cur[s] = i;
      long long v = e[i].v, w = e[i].w;
      if(w <= 0 || dep[v] != dep[s] + 1) continue;
      long long cw = dfs(v, min(w, mw));
      if(cw <= 0) continue;
      e[i].w -= cw;
      e[i^1].w += cw;
      return cw;
    }
    // 找一条链 S -> T
    // min w
    return 0;
  }

  long long dinic() {
    long long ret = 0;
    while(bfs()) {
      for(long long i = 0; i < N; i++) {
        cur[i] = head[i];
      }
      while(long long d = dfs(S, inf)) {
        ret += d;
      }
    }
    return ret;
  }

}Dinic;

// 
// 1. 当前弧优化。✔
// 2. BFS分层的时候，只要找到第一个连到T的边就可以停止分层了。 ✔
//--------

int main() {
    ios::sync_with_stdio(false);

    long long N, M, u, v, w;
    Dinic d;
    
    d.init();
    cin >> N >> M >> d.S >> d.T;
    d.N = N + 1;
    for (int i = M; i > 0; --i) {
        cin >> u >> v >> w;
        d.adde(u, v, w);
    }

    cout << d.dinic() << endl;

    return 0;
}
