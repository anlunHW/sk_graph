#include <iostream>
#include <fstream>

using namespace std;

// (1 << 17) > 100 000
//int const step = 17;
int const step = 17;
int const size = 1 << step;

long long array[size * 2];

void print() {
	cout << "array\n";
	for (int i = 0; i < size * 2; i++) {
		cout.width(5);
		cout << array[i];
	}
	cout << endl << endl;
}

void set(int i, int x) {
	int delta = x - array[size + i];

	int curIndex = size + i;
	while (curIndex > 0) {
		array[curIndex] += delta;
		curIndex /= 2;
	}
}

long long get(int v, int L, int R, int l, int r) {
	if (L == l && R == r)
		return array[v];
	if (r <= ((L + R) / 2))
		return get(2 * v, L, (L + R) / 2, l, r);
	if (l >= ((L + R) / 2))
		return get(2 * v + 1, (L + R) / 2, R, l, r);

	return
		get(2 * v, L, (L + R) / 2, l, (L + R) / 2)
		+
		get(2 * v + 1, (L + R) / 2, R, (L + R) / 2, r);
}

long long get(int l, int r) {
	return get(1, 0, size, l, r);
}

int main() {
	ifstream in("sum.in");
	ofstream out("sum.out");
	int n;
	int k;
	
	in >> n;
	in >> k;

	for (int i = 0; i < k; i++) {
		char operation;
		in >> operation;
		if (operation == 'A') {
			int index;
			int value;
			in >> index;
			in >> value;
			set(index, value);
			
			//print();

			continue;
		}

		//operation == 'Q'
		int left;
		int right;
		in >> left;
		in >> right;
		out << get(left, right + 1) << endl;
	}

	out.close();
	in.close();

	return 0;
}
