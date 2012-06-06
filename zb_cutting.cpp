#include <cstdio>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>

using namespace std;

int n;
int m;
int k;

int const maxVertexNumber = 50000 + 2;
int const maxEdgeNumber = 100000 + 2;

set<int> vertexEdges[maxVertexNumber];

struct Command {
	enum Type {
		ASK
		, CUT
	} type;

	int start;
	int end;
};

stack<Command> cmdStack;
stack<bool> answer;

int parent[maxVertexNumber];
int rank[maxVertexNumber];

void makeSet(int const v) {
	parent[v] = v;
	rank[v] = 0;
}

int findSet(int const v) {
	if (v == parent[v]) {
		return v;
	}

	return parent[v] = findSet(parent[v]);
}

void unionSets(int first, int second) {
	first = findSet(first);
	second = findSet(second);

	if (first != second) {
		if (rank[first] < rank[second]) {
			swap(first, second);
		}
		parent[second] = first;
		if (rank[first] == rank[second]) {
			rank[first]++;
		}	
	}
}

int main() {
	FILE* in = fopen("cutting.in", "r");
	fscanf(in, "%d %d %d", &n, &m, &k);
	
	int u;
	int v;
	for (int i = 0; i < m; i++) {
		fscanf(in, "%d %d", &u, &v);

		vertexEdges[u].insert(v);
		vertexEdges[v].insert(u);
	}

	char buf[5];
	for (int i = 0; i < k; i++) {
		fscanf(in, "%s %d %d", buf, &u, &v);
		
		Command cmd;
		cmd.start = u - 1;
		cmd.end = v - 1;

		if (buf[0] == 'c') {
			if (
				vertexEdges[u].find(v)
				== vertexEdges[u].end()
			) {
				continue;
			}

			cmd.type = Command::CUT;
		} else {
			cmd.type = Command::ASK;
		}

		cmdStack.push(cmd);
	}
	fclose(in);

	for (int i = 0; i < n; i++) {
		makeSet(i);
	}

	while (!cmdStack.empty()) {
		Command curCmd = cmdStack.top();

		if (curCmd.type == Command::ASK) {
			answer.push(findSet(curCmd.start) == findSet(curCmd.end));
		} else {
			unionSets(curCmd.start, curCmd.end);
		}

		cmdStack.pop();
	}

	FILE* out = fopen("cutting.out", "w");
	
	while (!answer.empty()) {
		if (answer.top()) {
			fprintf(out, "YES\n");
		} else {
			fprintf(out, "NO\n");
		}

		answer.pop();
	}

	fclose(out);

	return 0;
}
