#include <cstdio>
#include <iostream>
#include <algorithm> 
#include <set>

using namespace std;

#define PROBLEM_IN_FILE "heaps2.in"
#define PROBLEM_OUT_FILE "heaps2.out"

static int alreadyCalculated[1000001];
static int a[30];
static int n_size[10001];

int k;
int minA;

int m;
int maxN;

void reading() {
	FILE* in = fopen(PROBLEM_IN_FILE, "r");

	scanf(in, "%d", &k);
	minA = 1000001;
	for (int i = 0; i < k; i++) {
		scanf(in, "%d", a + i);
		if (a[i] < minA)
			minA = a[i];
	}

	scanf(in, "%d", &m);
	maxN = 0;
	for (int i = 0; i < m; i++) {
		scanf(in, "%d", n_size + i);

		if (n_size[i] > maxN)
			maxN = n_size[i];
	}

	fclose(in);
}

void writing() {
	FILE* out = fopen(PROBLEM_OUT_FILE, "w");

	for (int i = 0; i < m; i++)
		if ((alreadyCalculated[n_size[i]] - 1) != 0) {
			fprintf(out, "First\n");
		} else {
			fprintf(out, "Second\n");
		}

	fclose(out);
}

int func(int n) {
	if ((alreadyCalculated[n] - 1) != -1)
		return alreadyCalculated[n] - 1;

	set<int> curSet;

	for (int i = 0; i < k; i++) {
		if (n - a[i] >= 0) {
			curSet.insert(func(n - a[i]));
		}
	}

	for (int i = 0; ; i++) {
		if (curSet.find(i) == curSet.end()) {
			alreadyCalculated[n] = i + 1;
			return i;
		}
	}
}

void work() {
	for (int i = 0; i <= maxN; i++) {
		func(n_size[i]);
	}
}

int main() {
	reading();
	work();
	writing();
}
