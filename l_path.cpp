#include <iostream>

#include <cstdio>
#include <memory.h>

using namespace std;

int const maxN = 22;

unsigned n;
unsigned m;

// Contains for [vertex] its edges in some order
unsigned edges[maxN][maxN];
unsigned vertexDegree[maxN];
unsigned nearVertexSet[maxN];

unsigned func[1 << maxN];

int bestCount;

unsigned dfs(unsigned v, unsigned set) {
	unsigned result = 1;

	for (unsigned i = 0; i < vertexDegree[v]; i++)
	{
		int nextVertex = edges[v][i];
		if ((set & (1 << nextVertex)) == 0) {
			set |= 1 << nextVertex;
			result += dfs(nextVertex, set);
		}
	}

	return result;
}

/*
unsigned setElementNumber(unsigned set) {
	unsigned result = 0;

	for (int i = 0; i < 25 && set != 0; i++) {
		result += set & 1;

		set >>= 1;
	}

	return result;
}
*/

unsigned reachableVertexNumber(unsigned v, unsigned set) {
	return dfs(v, set) - 1;
}


unsigned bestWaySize;
unsigned curVertexCnt;
unsigned parents[maxN];
unsigned bestParents[maxN];
unsigned bestWayEnd;

void go(unsigned v, unsigned parent, unsigned set) {
	if ((func[set] & (1 << v)) != 0) {
		return;
	}
	func[set] |= (1 << v);

	if (curVertexCnt + reachableVertexNumber(v, set) <= bestWaySize) {
		return;
	}

	parents[v] = parent;

	bool hasContinuation = false;
	for (unsigned i = 0; i < vertexDegree[v]; i++) {
		unsigned next = edges[v][i];
		if ((set & (1 << next)) == 0) {
			hasContinuation = true;
			set |= (1 << next);
			curVertexCnt++;
			go(next, v, set);
			set ^= (1 << next);
			curVertexCnt--;
		}
	}

	if (!hasContinuation && curVertexCnt > bestWaySize) {
		bestWaySize = curVertexCnt;
		bestWayEnd = v;

		memcpy(bestParents, parents, n * sizeof(unsigned));	
	}
}

int main() {
	for (int i = 0; i < maxN; i++) {
		nearVertexSet[i] = 1 << i;
	}

	FILE* in = fopen("path.in", "r");
	fscanf(in, "%u %u", &n, &m);

	for (unsigned i = 0; i < m; i++) {
		unsigned curStartVertex;
		unsigned curEndVertex;
		fscanf(in, "%u %u", &curStartVertex, &curEndVertex);
		
		curStartVertex--;
		curEndVertex--;

		if (
			(nearVertexSet[curStartVertex] & (1 << curEndVertex))
			== 
			0
		) {
			nearVertexSet[curStartVertex] |= 1 << curEndVertex;
			edges[curStartVertex][ vertexDegree[curStartVertex] ] = curEndVertex;
			vertexDegree[curStartVertex]++;
		}
	}
	fclose(in);

	bestWaySize = 0;
	for (unsigned i = 0; i < n; i++) {
		curVertexCnt = 1;
		go(i, -1, (1 << i));
	}

	unsigned bestWay[maxN]; 
	bestWay[0] = bestWayEnd;
	for (unsigned i = 1; i < bestWaySize; i++) {
		bestWay[i] = bestParents[bestWay[i - 1]];
	}
	
	FILE* out = fopen("path.out", "w");
	fprintf(out, "%u\n", bestWaySize - 1);
	for (int i = bestWaySize - 1; i >= 0; i--)
	{
		fprintf(out, "%u ", bestWay[i] + 1);
	}

	fclose(out);

	return 0;
}
