#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

using namespace std;

int n;
int m;

int a1;
int a2;

int x;
int y;
int z;

int const maxSize = 100000;
int const maxDepthLog = 17;
int parent[maxSize];
vector<int> children[maxSize];

int depth[maxSize];
int up[maxSize][maxDepthLog];

map< pair<int, int>, int> alreadyCalculated;

void calcUp(int v) {
	up[v][0] = parent[v];
	for (int i = 1; i < maxDepthLog; i++) {
		up[v][i] = up[ up[v][i - 1] ][i - 1];
	}

	for (unsigned i = 0; i < children[v].size(); i++) {
		calcUp(children[v][i]);
	}
}

void calcUp() {
	calcUp(0);
}

void calcDepth(int node) {
	for (unsigned i = 0; i < children[node].size(); i++) {
		int curChild = children[node][i];
		depth[curChild] = depth[node] + 1;
		calcDepth(curChild);
	}
}

void calcDepth() {
	depth[0] = 0;
	calcDepth(0);
}

int lca(int x, int y) {
	int a;
	int b;

	if (depth[x] > depth[y]) {
		a = x;
		b = y;
	} else {
		a = y;
		b = x;
	}
	//now depth[a] >= depth[b]
	
	int depthDelta = depth[a] - depth[b];

	/*
	pair<int, int> parameters(a, b);
	map< pair<int, int>, int >::iterator it = alreadyCalculated.find(parameters);
	if (it != alreadyCalculated.end()) {
		return it->second;
	}
	*/

	int curJumpLog = 0;
	while (depthDelta > 0) {
		if (depthDelta % 2) {
			a = up[a][curJumpLog];
		}

		depthDelta >>= 1;
		curJumpLog++;
	}
	
	//now depth[a] == depth[b]
	
	/*
	pair<int, int> newParameters(a, b);
	it = alreadyCalculated.find(newParameters);
	if (it != alreadyCalculated.end()) {
		return it->second;
	}
	*/

	for (int k = maxDepthLog - 1; k >= 0; k--) {
		int a_cur = up[a][k];
		int b_cur = up[b][k];

		if (a_cur != b_cur) {
			a = a_cur;
			b = b_cur;
		}
	}

	int result;

	if (a != b) {
		result =  parent[a];
	} else {
		result =  a;
	}

	return result;
}

int lcaForPair(int a, int b) {
	int lcaNumber = lca(a, b);

	//alreadyCalculated[ pair<int, int>(a, b) ] = lcaNumber;

	return lcaNumber;
}

int main() {
	FILE* in = fopen("lca_rmq.in", "r");
	fscanf(in, "%d %d", &n, &m);
	
	for (int i = 1; i < n; i++) {
		fscanf(in, "%d", parent + i);
		children[parent[i]].push_back(i);
	}

	fscanf(in, "%d %d", &a1, &a2);
	fscanf(in, "%d %d %d", &x, &y, &z);
	fclose(in);

	calcDepth();
	calcUp();

	long long result = 0;

	long long a_i = a1;
	long long a_i_1 = a2;
	int curResult = lcaForPair(a1, a2);

	int left_arg = a1;
	int right_arg = a2;

	for (int i = 0; i < m; i++) {
		/*
		printf("---%d---\n", i);
		printf("left_arg: %d\n", left_arg);
		printf("right_arg: %d\n", right_arg);
		printf("curResult: %d\n\n", curResult);
		*/

		result += curResult;
		
		a_i = (x * a_i + y * a_i_1 + z)	% n;
		a_i_1 = (x * a_i_1 + y * a_i + z) % n;

		left_arg = (a_i + curResult) % n;
		right_arg = a_i_1;

		curResult = lcaForPair(left_arg, right_arg);
	}

	FILE* out = fopen("lca_rmq.out", "w");
	fprintf(out, "%lld", result);
	fclose(out);

	return 0;
}
