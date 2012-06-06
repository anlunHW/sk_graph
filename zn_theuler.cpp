#include <utility>
#include <list>
#include <cstdio>

using namespace std;

int const maxVertexNum = 102;
int n;
int m;
pair<int, int> coords[maxVertexNum];
list<int> edges[maxVertexNum];

int componentNumber = 0;
int componentEdgeDoubleNumber[maxVertexNum];
int componentVertexNumber[maxVertexNum];
bool used[maxVertexNum];

void dfs(int v) {
	if (used[v])
		return;

	used[v] = true;
	componentVertexNumber[componentNumber]++;
	componentEdgeDoubleNumber[componentNumber] += edges[v].size();

	for (list<int>::iterator it = edges[v].begin(); it != edges[v].end(); it++) {
		int x = *it;
		dfs(x);
	}
}

int main() {
	FILE* in = fopen("theuler.in", "r");
	
	fscanf(in, "%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		//coords reading
		fscanf(in, "%d %d", &coords[i].first, &coords[i].second);
	}

	for (int i = 0; i < m; i++) {
		//edges reading
		int start;
		int end;
		fscanf(in, "%d %d", &start, &end);
		edges[start].push_back(end);
		edges[end].push_back(start);
	}
	fclose(in);

	for (int i = 1; i <= n; i++) {
		if (!used[i]) {
			dfs(i);
			componentNumber++;
		}
	}

	int result = 1 - componentNumber;
	for (int i = 0; i < componentNumber; i++) {
		result += 2 - componentVertexNumber[i] + componentEdgeDoubleNumber[i] / 2;
	}

	FILE* out = fopen("theuler.out", "w");
	fprintf(out, "%d", result);
	fclose(out);

	return 0;
}
