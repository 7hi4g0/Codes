#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define MAX 20000

struct Edge {

	int id, w;
};

struct Noh {

	vector<Edge> edge;
};

vector<Noh> g(MAX);
int n, dist[MAX];

class Compare {

	public: bool operator() (int a, int b) {
		return dist[a] > dist[b];
	}
};

int djkst (vector<Noh> g, int src, int dest) {

	int i, u, v;
	char c[n];
	priority_queue<int, vector<int>, Compare> pq;
	Edge ed;

	for (i = 0; i < n; i++) {
		dist[i] = -1;
		c[i] = 'w';
	}

	dist[src] = 0; c[src] = 'g';
	pq.push(src);
	while (!pq.empty()) {
		u = pq.top();
		pq.pop();
		for (v = 0; v < g[u].edge.size(); v++) {
			ed = g[u].edge[v];
			if (ed.w + dist[u] < dist[ed.id] || dist[ed.id] == -1) {
				dist[ed.id] = ed.w + dist[u];
				c[ed.id] = 'g';
				if (ed.id != dest) pq.push(ed.id);
			}
		}
		c[u] = 'b';
	}
	
	return dist[dest];
}

int main () {

	int test, t, edges, src, dest, u, v, w;

	scanf("%d", &test);
	for (t = 0; t < test; t++) {
		scanf("%d %d %d %d", &n, &edges, &src, &dest);
		
		while (edges--) {
			scanf("%d %d %d", &u, &v, &w);
			Edge e1, e2;
			e1.id = v; e1.w = w;
			g[u].edge.push_back(e1);
			e2.id = u; e2.w = w;
			g[v].edge.push_back(e2);
		}
		w = djkst(g, src, dest);
		if(w == -1) printf("Case #%d: unreachable\n", t+1);
		else printf("Case #%d: %d\n", t+1, w);
		
		for (u = 0; u < n; u++)
			g[u].edge.clear();
	}

	return 0;
}
