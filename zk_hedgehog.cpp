#include <cstdio>
#include <vector>

using namespace std;

int const maxN = 15;

int n;
int m;

int connectedSet[maxN];

int minControlSetSize;
int maxIndependentSetSize;
int minGlobalCuttingSize;

int fullSet;

vector<int> edgeStart;
vector<int> edgeEnd;

int setElementNumber(int set) {
	int result = 0;

	for (int i = 0; (i < maxN) && (set != 0); i++) {
		result += set & 1;

		set >>= 1;
	}

	return result;
}

void checking(
	int v
	, int set
	, int connectedVertexSet
	, bool isIndependentSet
) {
	if (v == n) {
		int setSize = setElementNumber(set);

		if (isIndependentSet && (setSize > maxIndependentSetSize)) {
			maxIndependentSetSize = setSize;
		}

		bool isControlingSet = true;
		for (unsigned i = 0; i < edgeStart.size(); i++) {
			if (
				((set & (1 << edgeStart[i])) == 0)
				&&
				((set & (1 << edgeEnd[i])) == 0)	
			) {
				isControlingSet = false;
				break;
			}
		}
		if (isControlingSet && (setSize < minControlSetSize)) {
			minControlSetSize = setSize;
		}

		if (set == fullSet || set == 0) {
			return;
		}

		//calculating global cutting
		int cuttingSize = 0;
		for (int i = 0; i < n; i++) {
			if ((set & (1 << i)) == 0) {
				cuttingSize += setElementNumber(connectedSet[i] & set);
			}
		}

		if (cuttingSize < minGlobalCuttingSize) {
			minGlobalCuttingSize = cuttingSize;
		}

		return;
	}

	checking(
		v + 1
		, set | (1 << v)
		, connectedVertexSet | connectedSet[v] | (1 << v)
		, isIndependentSet & ((set & connectedSet[v]) == 0)
		);

	checking(
		v + 1
		, set
		, connectedVertexSet
		, isIndependentSet
		);
}

int main() {
	minControlSetSize = maxN + 1;
	maxIndependentSetSize = 0;
	minGlobalCuttingSize = (maxN + 1) * (maxN + 1);

	FILE* in = fopen("hedgehog.in", "r");

	fscanf(in, "%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		int first;
		int second;

		fscanf(in, "%d %d", &first, &second);
		
		if (first == second) {
			continue;
		}

		first--;
		second--;

		if (connectedSet[first] & (1 << second)) {
			continue;
		}

		connectedSet[first] |= 1 << second;
		connectedSet[second] |= 1 << first;

		edgeStart.push_back(first);
		edgeEnd.push_back(second);
	}

	fclose(in);

	fullSet = 0;
	for (int i = 0; i < n; i++) {
		fullSet |= (1 << i);
	}
	
	checking(0, 0, 0, true);

	FILE* out = fopen("hedgehog.out", "w");

	fprintf(out, "%d %d %d", minControlSetSize, maxIndependentSetSize, minGlobalCuttingSize);
	fclose(out);

	return 0;
}
