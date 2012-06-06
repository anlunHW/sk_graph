#include <iostream>

#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

// 2 ** 15 > 30 000
int const maxSize = 1 << 15;

int n;
int m;

struct TreeNode {
	/*
	TreeNode() {
		isLabeled = false;
	}
	*/

	long long sum;
	int treeSize;

	bool isLabeled;
};

int array[maxSize];
long long arraySum[maxSize];
TreeNode tree[maxSize * 2];

// returns number of elements in subtree
int buildTree(int v, int tl, int tr) {
	//cerr << "-----------" << endl;
	//cerr << "v: " << v << endl;
	//cerr << "tl: " << tl << endl;
	//cerr << "tr: " << tr << endl;
	//cerr << endl;

	if (tl > n) {
		return 0;
	}

	tree[v].isLabeled = false;

	if (tl == tr) {
		tree[v].sum = array[tl];
		tree[v].treeSize = 1;
		cerr << "sum: " << tree[v].sum << endl;
		return 1;
	} else {
		int middle = (tl + tr) / 2;
		int subTreeSize = buildTree(v * 2, tl, middle);
		subTreeSize += buildTree(v * 2 + 1, middle + 1, tr);
		tree[v].sum = tree[v * 2].sum + tree[v * 2 + 1].sum;
		tree[v].treeSize = subTreeSize;

		//cerr << "subTreeSize: " << subTreeSize << endl;
		cerr << "sum: " << tree[v].sum << endl;

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
	/*
	cerr << "-----------" << endl;
	cerr << "v: " << v << endl;
	cerr << "tl: " << tl << endl;
	cerr << "tr: " << tr << endl;
	cerr << "l: " << l << endl;
	cerr << "r: " << r << endl;
	cerr << endl;
	*/

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
	return get(1, 1, n, pos);
}


long long getSum(int v, int tl, int tr, int l, int r) {
	if (l == tl && r == tr) {
		return tree[v].sum;
	}

	int middle = (tl + tr) / 2;

	if (r <= middle) {
		return getSum(2 * v, tl, middle, l, r);
	}

	if (l >= middle) {
		return getSum(2 * v + 1, middle, r, l, r);
	}

	return getSum(v, tl, middle, l, middle)
		+
		getSum(v, middle + 1, tr, middle + 1, r);
}

long long getSum(int l, int r) {
	//return getSum(1, 1, n, l, r);
	return getSum(1, 1, maxSize, l, r);
}

int main() {
	FILE* in = fopen("middle.in", "r");
	fscanf(in, "%d %d", &n, &m);

	arraySum[0] = 0;
	fscanf(in, "%d", array + 1);
	arraySum[1] = array[1];
	for (int i = 2; i <= n; i++) {
		fscanf(in, "%d", array + i);
		arraySum[i] = arraySum[i - 1] + array[i];
	}

	//cerr << "AAA" << endl;

	// making tree
	buildTree(1, 1, n);

	//cerr << "AAA" << endl;

	// requests
	int l;
	int r;
	for (int i = 0; i < m; i++) {
		//cerr << "AAA" << endl;
		fscanf(in, "%d %d", &l, &r);

		// request implementing
		//long long curSum = getSum(l, r);
		//cerr << "getSum: " << curSum << endl;

		/*
		long long firstSum = arraySum[r] - arraySum[l - 1];

		int newValue;
		if (curSum <= firstSum) {
			newValue = ceil(curSum / (double(r - l + 1)));
		} else {
			newValue = floor(curSum / (double(r - l + 1)));
		}

		//cerr << "newValue: " << newValue << endl;

		//update(1, 0, n, l, r, newValue);
		*/
		update(1, 0, n, l, r, i);
	}
	
	//cerr << "AAA" << endl;

	fclose(in);

	FILE* out = fopen("middle.out", "w");

	for (int i = 1; i <= n; i++) {
		fprintf(out, "%lld ", get(i));
	}

	fclose(out);

	return 0;
}
