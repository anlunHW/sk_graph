#include <stdio.h>
#include <memory.h>

int const maxN = 22;

unsigned n;
unsigned m;

// Contains for [vertex] its edges in some order
unsigned edges[22][22];
unsigned vertexDegree[22];
unsigned nearVertexSet[22];

unsigned func[1 << 22];

int bestCount;

unsigned bestWaySize;
unsigned curVertexCnt;
unsigned parents[22];
unsigned bestParents[22];
unsigned bestWayEnd;

unsigned curReachableVertexNumber;
unsigned tempSet;
unsigned set;

void dfs(unsigned v) {
	unsigned i;
	unsigned nextVertex;
	unsigned shift;

	for (i = 0; i < vertexDegree[v]; i++)
	{
		nextVertex = edges[v][i];
		shift = 1 << nextVertex;
		if ((tempSet & shift) == 0) {
			tempSet |= shift;
			curReachableVertexNumber++;
			dfs(nextVertex);
		}
	}
}

unsigned reachableVertexNumber(unsigned v, unsigned set) {
	tempSet = set;
	curReachableVertexNumber = 0;
	dfs(v);

	return curReachableVertexNumber;
}

void go(unsigned v, unsigned parent) {
	unsigned i;
	unsigned next;
	int hasContinuation = 0;

	if ((func[set] & (1 << v)) != 0) {
		return;
	}
	func[set] |= (1 << v);

	if (curVertexCnt + reachableVertexNumber(v, set) <= bestWaySize) {
		return;
	}

	parents[v] = parent;

	for (i = 0; i < vertexDegree[v]; i++) {
		next = edges[v][i];
		if ((set & (1 << next)) == 0) {
			hasContinuation = 1;
			set |= (1 << next);
			curVertexCnt++;
			go(next, v);
			set ^= (1 << next);
			curVertexCnt--;
		}
	}

	if (!hasContinuation && (curVertexCnt > bestWaySize)) {
		bestWaySize = curVertexCnt;
		bestWayEnd = v;

		memcpy(bestParents, parents, n * sizeof(unsigned));	
	}
}

int main() {
	int i;
	FILE* in;
	FILE* out;
	unsigned curStartVertex;
	unsigned curEndVertex;
	unsigned bestWay[maxN]; 

	for (i = 0; i < maxN; i++) {
		nearVertexSet[i] = 1 << i;
	}

	in = fopen("path.in", "r");
	fscanf(in, "%u %u", &n, &m);

	for (i = 0; i < m; i++) {
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
	for (i = 0; i < n; i++) {
		curVertexCnt = 1;
		set = (1 << i);
		go(i, -1);
	}

	bestWay[0] = bestWayEnd;
	for (i = 1; i < bestWaySize; i++) {
		bestWay[i] = bestParents[bestWay[i - 1]];
	}
	
	out = fopen("path.out", "w");
	fprintf(out, "%u\n", bestWaySize - 1);
	for (i = bestWaySize - 1; i >= 0; i--)
	{
		fprintf(out, "%u ", bestWay[i] + 1);
	}

	fclose(out);

	return 0;
}
