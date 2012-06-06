#include <cstdio>
#include <memory.h>
#include <vector>
#include <list>
#include <utility>

using namespace std;

int n;
int m;
int start;
int end;

int const maxN = 100000 + 1;
int const maxM = 100000 + 1;

struct Edge {
	int a;
	int b;
	int f;
	int c;

	int next;
};

Edge edges[maxM * 2];

// guards for list of vertex edges
int head[maxN];
int tail[maxN];

void addEdgeToVertexList(int edgeNumber) {
	if (head[edges[edgeNumber].a] == -1) {
		head[edges[edgeNumber].a] = edgeNumber;
		tail[edges[edgeNumber].a] = edgeNumber;

		return;
	}

	edges[ tail[edges[edgeNumber].a] ].next = edgeNumber;
	tail[edges[edgeNumber].a] = edgeNumber;

	return;
}

vector<int> resultEdges;
vector<int> resultGraph[maxN];

int isVertexVisited[maxN];

bool dfs(int v) {
	if (isVertexVisited[v]) {
		return false;
	}
	isVertexVisited[v] = 1;

	if (v == end) {
		return true;
	}

	int curEdgeNumber = head[v];
	while (curEdgeNumber != -1) {
		Edge& curEdge = edges[curEdgeNumber];

		if (curEdge.f < curEdge.c) {
			curEdge.f++;

			if (dfs(curEdge.b)) {
				resultEdges.push_back(curEdgeNumber);

				if (edges[curEdgeNumber ^ 1].c == 0) {
					edges[curEdgeNumber ^ 1].c = 1;
				}

				return true;
			}

			curEdge.f--;
		}

		curEdgeNumber = edges[curEdgeNumber].next;
	}

	return false;
}


//bool isFirstEdgeUsed[maxN];
int isFirstEdgeUsed[maxN];

int main() {
	memset(head, -1, maxN * sizeof(int));
	memset(tail, -1, maxN * sizeof(int));

	FILE* in = fopen("snails.in", "r");
	fscanf(in, "%d %d %d %d", &n, &m, &start, &end);

	for (int i = 0; i < m; i++) {
		int a;
		int b;

		fscanf(in, "%d %d", &a, &b);

		if (a == b) {
			continue;
		}

		edges[2 * i].a = a;
		edges[2 * i].b = b;
		edges[2 * i].c = 1;
		edges[2 * i].f = 0;
		edges[2 * i].next = -1;

		edges[2 * i + 1].a = b;
		edges[2 * i + 1].b = a;
		edges[2 * i + 1].c = 0;
		edges[2 * i + 1].f = 0;
		edges[2 * i + 1].next = -1;

		addEdgeToVertexList(2 * i);
		addEdgeToVertexList(2 * i + 1);
	}

	fclose(in);
	
	bool result = true;	
	
	memset(isVertexVisited, 0, maxN * sizeof(int));
	result = result && dfs(start);
	
	memset(isVertexVisited, 0, maxN * sizeof(int));
	result = result && dfs(start);	


	for (unsigned i = 0; i < resultEdges.size(); i++) {
		if (edges[resultEdges[i] ^ 1].f == 0) {
			// не использовалось обратное ребро
			resultGraph[ edges[resultEdges[i]].a ].push_back( edges[resultEdges[i]].b );
		}
	}

	FILE* out = fopen("snails.out", "w");

	if (result) {
		fprintf(out, "YES\n");
		for (unsigned i = 0; i < 2; i++) {
			fprintf(out, "%d ", start);

			int curPlainNum = resultGraph[start][i];
			while (true) {
				fprintf(out, "%d ", curPlainNum);

				if (curPlainNum == end) {
					break;
				}

				int newPlainNum = resultGraph[curPlainNum][isFirstEdgeUsed[curPlainNum]];
				isFirstEdgeUsed[curPlainNum]++;

				curPlainNum = newPlainNum;
			}

			fprintf(out, "\n");
		}
	} else {
		fprintf(out, "NO");
	}

	fclose(out);

	return 0;
}
