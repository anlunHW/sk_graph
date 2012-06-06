#include <fstream>
//#include <iostream>

using namespace std;

/*
int const maxTreeSize = 10;
int const maxDepthLog = 4; //2 ^ (maxDepthLog - 1) > maxTreeSize
*/

int const maxTreeSize = 6 * 10000;
int const maxDepthLog = 18; //2 ^ (maxDepthLog - 1) > maxTreeSize

int const infinityWeight = 10000000;

int parent[maxTreeSize];
int weight[maxTreeSize];
int depth[maxTreeSize];
int up[maxTreeSize][maxDepthLog];
int minWeightOnWay[maxTreeSize][maxDepthLog];

int n; // tree real size

void calculateUpAndWeight() {
	for (int v = 1; v <= n; v++) {
		up[v][0] = parent[v];
		minWeightOnWay[v][0] = weight[v];

		for (int i = 1; i < maxDepthLog; i++) {
			up[v][i] = up[ up[v][i - 1] ][i - 1];

			minWeightOnWay[v][i] = min(
					minWeightOnWay[v][i - 1],
					minWeightOnWay[ up[v][i - 1] ][i - 1]
					);
			//up[ up[v][i - 1] ][i - 1];
		}
	}
}

int minOnPath(int x, int y) {
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
	
	int result = infinityWeight;
		
	int depthDelta = depth[a] - depth[b];
	//cout << "depthDelta: " << depthDelta;

	int curJumpLog = 0;
	while (depthDelta > 0) {
		if (depthDelta % 2) {
			result = min(result, minWeightOnWay[a][curJumpLog]);
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
			result = min(result, minWeightOnWay[a][k]);
			result = min(result, minWeightOnWay[b][k]);

			a = a_cur;
			b = b_cur;
		}
	}

	if (a != b) {
		result = min(result, minWeightOnWay[a][0]);
		result = min(result, minWeightOnWay[b][0]);
	}

	return result;
}

int main() {
	ifstream in("minonpath.in");
	in >> n;

	// 1 - root
	parent[1] = 1;
	depth[1] = 0;
	weight[1] = infinityWeight;
	for (int i = 2; i <= n; i++) {
		int curVertexParent;
		in >> curVertexParent;
		parent[i] = curVertexParent;

		// we know that curVertexParent < i
		depth[i] = depth[curVertexParent] + 1;

		in >> weight[i];
	}

	calculateUpAndWeight();

	/*
	cout << "up" << endl;
	for (int i = 0; i < maxDepthLog; i++) {
		for (int j = 0; j < maxTreeSize; j++) {
			cout << up[j][i] << ' ';
		}
		cout << endl;
	}
	cout << endl << endl;

	cout << "minWeightOnWay" << endl;
	for (int i = 0; i < maxDepthLog; i++) {
		for (int j = 0; j < maxTreeSize; j++) {
			cout << minWeightOnWay[j][i] << ' ';
		}
		cout << endl;
	}
	cout << endl << endl;
	*/

	int m;
	in >> m;

	ofstream out("minonpath.out");
	for (int i = 0; i < m; i++) {
		int x;
		in >> x;

		int y;
		in >> y;
	
		//cout << "########## " << x << ' ' << y << endl;

		out << minOnPath(x, y) << endl;
		
		//cout << endl << endl;
	}

	out.close();
	in.close();

	return 0;
}
