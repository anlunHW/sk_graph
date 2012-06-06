#include <iostream>

#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

// 2 ** 15 > 30 000
//int const maxSize = (1 << 15) + 1;
int const maxSize = 1 << 15;

int n;
int m;

struct TreeNode {
	long long sum;
	int treeSize;

	bool isLabeled;
};

int array[maxSize];
long long arraySum;
TreeNode tree[maxSize * 2];

// returns number of elements in subtree
int buildTree(int v, int tl, int tr) {
	if (tl > n) {
		return 0;
	}

	tree[v].isLabeled = false;

	if (tl == tr) {
		tree[v].sum = array[tl];
		tree[v].treeSize = 1;
		return 1;

	} else {
		int middle = (tl + tr) / 2;
		int subTreeSize = buildTree(v * 2, tl, middle);
		subTreeSize += buildTree(v * 2 + 1, middle + 1, tr);
		tree[v].sum = tree[v * 2].sum + tree[v * 2 + 1].sum;
		tree[v].treeSize = subTreeSize;

		return subTreeSize;
	}
}

void push(int v) {
	if (tree[v].isLabeled) {
		long long value = tree[v].sum / tree[v].treeSize;

		tree[v * 2].isLabeled = true;
		tree[v * 2].sum = value * tree[v * 2].treeSize;

		tree[v * 2 + 1].isLabeled = true;
		tree[v * 2 + 1].sum = value * tree[v * 2 + 1].treeSize;

		tree[v].isLabeled = false;
	}
}

void update(int v, int tl, int tr, int l, int r, int value) {
	if (l > r) {
		return;
	}

	if (l == tl && tr == r) {
		tree[v].sum = value * tree[v].treeSize;
		tree[v].isLabeled = true;
	} else {
		push(v);
		int middle = (tl + tr) / 2;

		update(v * 2, tl, middle, l, min(r, middle), value);
		update(v * 2 + 1, middle + 1, tr, max(l, middle + 1), r, value);

		tree[v].sum = tree[2 * v].sum + tree[2 * v + 1].sum;
	}
}

// getting single element
long long get(int v, int tl, int tr, int pos) {
	if (tl > n) {
		return 0;
	}

	if (tl == tr) {
		return tree[v].sum;
	}

	push(v);
	int middle = (tl + tr) / 2;
	if (pos <= middle) {
		return get(v * 2, tl, middle, pos);
	} else {
		return get(v * 2 + 1, middle + 1, tr, pos);
	}
}

// getting single element
long long get(int pos) {
	return get(1, 1, maxSize, pos);
}

long long getSum(int v, int tl, int tr, int l, int r) {	
	if (l > r) {
		return 0;
	}
	

	if (l == tl && r == tr) {
		return tree[v].sum;
	}

	int middle = (tl + tr) / 2;

	if (r < middle) {
		return getSum(2 * v, tl, middle, l, r);
	}
	if (l > middle) {
		return getSum(2 * v + 1, middle + 1, tr, l, r);
	}

	return getSum(2 * v, tl, middle, l, middle)
		+
		getSum(2 * v + 1, middle + 1, tr, middle + 1, r);
}

long long getSum(int l, int r) {
	return getSum(1, 1, maxSize, l, r);
}

int main() {
	FILE* in = fopen("middle.in", "r");
	fscanf(in, "%d %d", &n, &m);

	arraySum = 0;
	for (int i = 1; i <= n; i++) {
		fscanf(in, "%d", array + i);
		arraySum += array[i];
	}

	// making tree
	buildTree(1, 1, maxSize);

	int l;
	int r;
	for (int i = 0; i < m; i++) {
		fscanf(in, "%d %d", &l, &r);

		// request implementing
		long long curSum = getSum(l, r);

		int newValue;
		if (getSum(1, n) <= arraySum) {
			newValue = ceil(curSum / (double(r - l + 1)));
		} else {
			newValue = floor(curSum / (double(r - l + 1)));
		}

		update(1, 1, maxSize, l, r, newValue);
	}

	fclose(in);

	FILE* out = fopen("middle.out", "w");

	for (int i = 1; i <= n; i++) {
		fprintf(out, "%lld ", get(i));
	}

	fclose(out);

	return 0;
}
