#include <iostream>

#include <cstdio>
#include <algorithm>
#include <memory.h>
#include <set>

using namespace std;

unsigned n;
unsigned m;
bool edges[25][25];

class Stack {
	public:
		Stack(): mSize(0) {
		}
	
		unsigned size() {
			return mSize;
		}

		void push(unsigned elem) {
			if (mSize >= 25) {
				return;
			}

			mVertex[mSize] = elem;
			mSize++;
		}

		void pop() {
			mSize = max(mSize - 1, (unsigned) 0);
		}

		unsigned top() {
			return mVertex[mSize - 1];
		}

		bool empty() {
			return mSize == 0;
		}

		void clear() {
			mSize = 0;
		}

	private:
		unsigned mVertex[25];
		unsigned mSize;
};

unsigned const vertexStackNumber = 25000;
Stack vertexStacks[vertexStackNumber];
unsigned curStack;

int dfsMark[25];

unsigned dfs(int v) {
	if (dfsMark[v]) {
		return 0;
	}
	dfsMark[v] = 1;

	unsigned result = 1 << v;

	for (unsigned i = 0; i < n; i++) {
		if (edges[v][i]) {
			result |= dfs(i);
		}
	}

	return result;
}

unsigned accessibleSet[25];
void calcAccessibleSets() {
	for (unsigned i = 0; i < n; i++) {
		memset(dfsMark, 0, sizeof(dfsMark));
		accessibleSet[i] = dfs(i);
	}
}

unsigned setElementNumber(unsigned set) {
	unsigned result = 0;

	for (int i = 0; i < 25 && set != 0; i++) {
		result += set & 1;

		set >>= 1;
	}

	return result;
}

Stack* bestPath;

//set< pair<unsigned, unsigned> > alreadySeenStates;
unsigned f[1 << 26];

Stack* go(unsigned set, unsigned vertex) {
	/*
	if (
		alreadySeenStates.find(pair<unsigned, unsigned>(set, vertex))
		!= alreadySeenStates.end()
	) {
		return 0;
	}
	*/
	//alreadySeenStates.insert(pair<unsigned, unsigned>(set, vertex));
	if (f[set] & (1 << vertex)) {
		return 0;
	}
	f[set] |= (1 << vertex);

	//set |= 1 << vertex;

	Stack* result = 0;
	for (unsigned i = 0; i < n; i++) {
		if (edges[vertex][i]
				&& ((set & (1 << i)) == 0)) {
			//if (setElementNumber(set | accessibleSet[i]) < bestPath->size()) {
			//	continue;
			//}

			Stack* curResult = go(set | (1 << i), i);

			if (curResult == 0) {
				continue;
			}

			if ((result == 0) || (curResult->size() > result->size())) {
				result = curResult;

				if (result->size() >= n) {
					return result;
				}
			}
		}
	}

	if (result == 0) {
		//result = new Stack();
		curStack++;
		curStack %= vertexStackNumber;
		vertexStacks[curStack].clear();
		result = vertexStacks + curStack;
	}

	result->push(vertex);
	return result;
}

int main() {
	FILE* in = fopen("path.in", "r");
	fscanf(in, "%u %u", &n, &m);

	for (unsigned i = 0; i < m; i++) {
		unsigned curStartVertex;
		unsigned curEndVertex;
		fscanf(in, "%u %u", &curStartVertex, &curEndVertex);

		edges[curStartVertex - 1][curEndVertex - 1] = true;
	}
	fclose(in);

	//calcAccessibleSets();

	bestPath = new Stack();
	bestPath->push(0);
	for (int i = n - 1; i >= 0; i--) {
		//if (setElementNumber(accessibleSet[i]) < bestPath->size()) {
		//	continue;
		//}

		Stack* curResult = go(1 << i, i);
		if (curResult->size() > bestPath->size())
			bestPath = curResult;

		if (bestPath->size() >= n) {
			break;
		}
	}

	FILE* out = fopen("path.out", "w");
	fprintf(out, "%u\n", bestPath->size() - 1);
	while (!bestPath->empty()) {
		fprintf(out, "%u ", bestPath->top() + 1);
		bestPath->pop();
	}

	fclose(out);

	return 0;
}
