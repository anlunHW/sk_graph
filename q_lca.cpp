#include <fstream>

using namespace std;

int const maxTreeSize = 6 * 10000;
int const maxDepthLog = 18; //2 ^ (maxDepthLog - 1) > maxTreeSize

int parent[maxTreeSize];
int depth[maxTreeSize];
int up[maxTreeSize][maxDepthLog];

int n; // tree real size

void calculateUp() {
	for (int v = 1; v <= n; v++) {
		up[v][0] = parent[v];
		for (int i = 1; i < maxDepthLog; i++) {
			up[v][i] = up[ up[v][i - 1] ][i - 1];
		}
	}
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

	int curJumpLog = 0;
	while (depthDelta > 0) {
		if (depthDelta % 2) {
			a = up[a][curJumpLog];
		}

		depthDelta >>= 1;
		curJumpLog++;
	}
	
	//now depth[a] == depth[b]

	for (int k = maxDepthLog - 1; k >= 0; k--) {
		int a_cur = up[a][k];
		int b_cur = up[b][k];

		if (a_cur != b_cur) {
			a = a_cur;
			b = b_cur;
		}
	}
	
	if (a != b)
		return parent[a];
	else
		return a;
}

int main() {
	ifstream in("lca.in");
	in >> n;

	// 1 - root
	parent[1] = 1;
	depth[1] = 0;
	for (int i = 2; i <= n; i++) {
		int curVertexParent;
		in >> curVertexParent;
		parent[i] = curVertexParent;

		// we know that curVertexParent < i
		depth[i] = depth[curVertexParent] + 1;
	}

	calculateUp();

	int m;
	in >> m;

	ofstream out("lca.out");
	for (int i = 0; i < m; i++) {
		int x;
		in >> x;

		int y;
		in >> y;

		out << lca(x, y) << endl;
	}

	out.close();
	in.close();

	return 0;
}
