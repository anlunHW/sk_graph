#include <cstdio>
#include <cmath>
#include <utility>
#include <list>

using namespace std;

int const maxOrderNumber = 505;
int m = 0; // order number

int orderTime[maxOrderNumber];
int orderEndTime[maxOrderNumber];

pair<int, int> orderStart[maxOrderNumber];
pair<int, int> orderEnd[maxOrderNumber];

list<int> edges[maxOrderNumber];

bool canOrderBeCompletedAfter(int firstOrder, int secondOrder) {
	int deltaX = abs(orderEnd[firstOrder].first - orderStart[secondOrder].first);
	int deltaY = abs(orderEnd[firstOrder].second - orderStart[secondOrder].second);

	return orderEndTime[firstOrder] + deltaX + deltaY < orderTime[secondOrder];
}

void calculateEdges() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (i == j) {
				continue;
			}

			if (canOrderBeCompletedAfter(i, j)) {
				edges[i].push_back(j);
			}
		}
	}
}

// PAIRS CALCULATION
int cc = 1;
int used[maxOrderNumber];
int pairArr[maxOrderNumber];

bool dfs(int v) {
	used[v] = cc;

	for (list<int>::iterator it = edges[v].begin(); it != edges[v].end(); it++) {
		int x = *it;

		if (
			(pairArr[x] == -1) ||
			( (used[pairArr[x]] != cc) && dfs(pairArr[x]) )
		)
		{
			pairArr[x] = v;
			return true;
		}
	}
	
	return false;	
}

void pairsCalculate() {
	for (int i = 0; i < m; i++) {
		cc++;
		dfs(i);
	}
}

int main() {
	for (int i = 0; i < maxOrderNumber; i++) {
		pairArr[i] = -1;
	}

	FILE* in = fopen("taxi.in", "r");
	fscanf(in, "%d", &m);
	
	for (int i = 0; i < m; i++) {
		int hours;
		int minutes;
		int a;
		int b;
		int c;
		int d;

		fscanf(in, "%d:%d %d %d %d %d", &hours, &minutes, &a, &b, &c, &d);

		orderTime[i] = hours * 60 + minutes;
		orderStart[i].first = a;
		orderStart[i].second = b;
		orderEnd[i].first = c;
		orderEnd[i].second = d;

		orderEndTime[i] = abs(a - c) + abs(b - d) + orderTime[i];
	}
	fclose(in);

	calculateEdges();
	pairsCalculate();
	
	int count = 0;
	for (int i = 0; i < m; i++) {
		count = pairArr[i] > -1 ? count + 1 : count;
	}

	FILE* out = fopen("taxi.out", "w");
	fprintf(out, "%d", m - count);
	fclose(out);

	return 0;
}
