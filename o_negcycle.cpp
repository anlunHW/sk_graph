#include <cstdio>
#include <vector>
#include <memory.h>
#include <algorithm>

using namespace std;

struct Edge {
	Edge(int start, int end, int cost)
		: start(start)
		, end(end)
		, cost(cost)
	{
	}

	int start;
	int end;
	int cost;
};

int n;
vector<Edge> edges;
int const notExistedCost = 100000;
vector<int> negativeCycle;

int const maxN = 100;
int d[maxN];
int previous[maxN];

int main() {
	FILE* in = fopen("negcycle.in", "r");

	fscanf(in, "%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int curCost;
			fscanf(in, "%d", &curCost);

			if (curCost >= notExistedCost) {
				continue;
			}
			edges.push_back(Edge(i, j, curCost));
		}
	}

	fclose(in);

	memset(previous, -1, n * sizeof(int));
	int changedCostVertex = -1;
	for (int j = 0; j < n; j++) {
		changedCostVertex = -1;
		for (int i = 0; i < edges.size(); i++) {
			if (d[edges[i].end] > d[edges[i].start] + edges[i].cost) {
				d[edges[i].end] = max(-notExistedCost, d[edges[i].start] + edges[i].cost);
				previous[edges[i].end] = edges[i].start;
				changedCostVertex = edges[i].end;
			}
		}
	}

	if (changedCostVertex != -1) {
		int startVertex = changedCostVertex;
		for (int i = 0; i < n; i++) {
			startVertex = previous[startVertex];
		}

		for (int curVertex = startVertex; curVertex >= 0; curVertex = previous[curVertex]) {
			negativeCycle.push_back(curVertex);
			if (
				(curVertex == startVertex)
				&&
				negativeCycle.size() > 1
			) {
				break;
			}
		}
	}

	FILE* out = fopen("negcycle.out", "w");	

	if (negativeCycle.size() != 0) {
		fprintf(out, "YES\n");
		fprintf(out, "%d\n", negativeCycle.size() - 1);
		for (int i = negativeCycle.size() - 1; i >= 1; i--) {
			fprintf(out, "%d ", negativeCycle[i] + 1);
		}
	} else {
		fprintf(out, "NO");
	}

	fclose(out);

	return 0;
}
