#include <cstdio>
#include <list>

using namespace std;

//int const maxObjectNumber = 100001;
int const maxObjectNumber = 22001;
int n;
int m;
int a;
int h;

list<int> edges[maxObjectNumber];

int f[maxObjectNumber][maxObjectNumber];
int c[maxObjectNumber][maxObjectNumber];

list< pair<int, int> > resultEdges;
list<int> resultGraph[maxObjectNumber];

bool dfs(int v) {
	if (v == h) {
		return true;
	}

	for (list<int>::iterator it = edges[v].begin(); it != edges[v].end(); it++) {
		int x = *it;

		if (f[v][x] < c[v][x])
		{
			f[v][x]++;
			
			if (dfs(x)) {
				resultEdges.push_back(pair<int, int>(v, x));
				
				if (c[x][v] == 0) {
					c[x][v] = 1;
					edges[x].push_back(v);
				}

				return true;
			}

			f[v][x]--;
		}
	}

	return false;
}

int main() {
	FILE* in = fopen("snails.in", "r");
	fscanf(in, "%d %d %d %d", &n, &m, &a, &h);
	for (int i = 0; i < m; i++) {
		int x;
		int y;
		fscanf(in, "%d %d", &x, &y);

		edges[x].push_back(y);
		c[x][y] = 1;
	}
	fclose(in);

	bool result = true;	
	result = result && dfs(a);
	result = result && dfs(a);	

	for (list< pair<int, int> >::iterator it = resultEdges.begin();
			it != resultEdges.end(); it++) {
		int x = it->first;
		int y = it->second;

		if (f[y][x] == 0) {
			//не использовалось обратное ребро
			resultGraph[x].push_back(y);
		}
	}

	FILE* out = fopen("snails.out", "w");
	if (result) {
		fprintf(out, "YES\n");
		for (list<int>::iterator it = resultGraph[a].begin();
				it != resultGraph[a].end(); it++) {
			fprintf(out, "%d ", a);

			list<int>::iterator curPlain = it;
			while (true) {
				fprintf(out, "%d ", *curPlain);
				int curPlainNum = *curPlain;

				curPlain = resultGraph[curPlainNum].begin();
				if (curPlain == resultGraph[curPlainNum].end()) {
					break;
				}
			}

			fprintf(out, "\n");
		}
	} else {
		fprintf(out, "NO");
	}

	fclose(out);

	return 0;
}
