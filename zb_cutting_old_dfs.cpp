#include <cstdio>
#include <vector>
#include <set>

using namespace std;

int n;
int m;
int k;

int const maxVertexNumber = 50000 + 2;
int const maxEdgeNumber = 100000 + 2;

set<int> vertexEdges[maxVertexNumber];

int color[maxVertexNumber];
int curColor;

// also makes checking
bool colorComponent(int vertex, int vertexToCheck) {
	bool result;
	
	color[vertex] = curColor;

	for (set<int>::iterator it = vertexEdges[vertex].begin();
			it != vertexEdges[vertex].end(); it++ ) {
		int edgeEnd = *it;

		if (color[edgeEnd] != curColor) {
			result = colorComponent(edgeEnd, vertexToCheck);
		}
	}

	return (vertex == vertexToCheck) || result;
}

void cut(int start, int end) {
	if (
		vertexEdges[start].find(end)
		==
		vertexEdges[start].end()
	) {
		return;
	}

	vertexEdges[start].erase(end);
	vertexEdges[end].erase(start);

	bool inOneComponent = colorComponent(start, end);
	curColor++;

	if (!inOneComponent) {
		colorComponent(end, start);
		curColor++;
	}
}

int main() {
	curColor = 1;

	FILE* in = fopen("cutting.in", "r");
	fscanf(in, "%d %d %d", &n, &m, &k);
	
	int u;
	int v;
	for (int i = 0; i < m; i++) {
		fscanf(in, "%d %d", &u, &v);

		vertexEdges[u].insert(v);
		vertexEdges[v].insert(u);
	}

	// first coloring
	for (int i = 0; i < n; i++) {
		if (color[i] == 0) {
			colorComponent(i, 0);
			curColor++;
		}
	}

	FILE* out = fopen("cutting.out", "w");

	char buf[5];
	for (int i = 0; i < k; i++) {
		fscanf(in, "%s %d %d", buf, &u, &v);

		if (buf[0] == 'c') {
			cut(u, v);
		} else {
			if (color[u] == color[v]) {
				fprintf(out, "YES\n");
			} else {
				fprintf(out, "NO\n");
			}
		}
	}

	fclose(out);
	fclose(in);

	return 0;
}
