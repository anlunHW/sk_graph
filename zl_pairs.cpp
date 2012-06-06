#include <cstdio>
#include <list>

using namespace std;

int const size = 252;

int used[size];
int pairArr[size];
list<int> edges[size];

int n;
int m;

int cc = 1;

bool dfs(int v) {
	used[v] = cc;

	for (list<int>::iterator it = edges[v].begin(); it != edges[v].end(); it++) {
		int x = *it;

		if (
			(pairArr[x] == -1) ||
			( (used[pairArr[x]] != cc) && dfs(pairArr[x]) )
		)
		{
			pairArr[x] = v;
			return true;
		}
	}
	
	return false;	
}

void pairsCalculate() {
	for (int i = 1; i <= n; i++) {
		cc++;
		dfs(i);
	}
}

int main() {
	for (int i = 0; i < size; i++) {
		pairArr[i] = -1;
	}

	FILE* in = fopen("pairs.in", "r");
	fscanf(in, "%d", &n);
	fscanf(in, "%d", &m);

	int curVertexA = 1;
	while (!feof(in)) {
		int tmp;
		fscanf(in, "%d", &tmp);
		if (tmp == 0) {
			curVertexA++;
			continue;
		}

		edges[curVertexA].push_back(tmp);
	}
	fclose(in);

	pairsCalculate();

	int count = 0;
	for (int i = 1; i <= m; i++) {
		count = pairArr[i] > 0 ? count + 1 : count;
	}

	FILE* out = fopen("pairs.out", "w");
	fprintf(out, "%d\n", count);
	for (int i = 1; i <= m; i++) {
		if (pairArr[i] > 0) {
			fprintf(out, "%d %d\n", pairArr[i], i);
		}
	}
	fclose(out);
}
