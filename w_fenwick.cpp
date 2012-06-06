#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

//int const fieldSize = 1024;
int const fieldSize = 1025;
long long field[fieldSize][fieldSize];

long long get(int const r, int const m) {
	long long result = 0;
	for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
		for (int j = m; j >= 0; j = (j & (j + 1)) - 1) {
			result += field[i][j];
		}
	}

	return result;
}	

void add(int const x, int const r, int const m) {
	for (int i = r; i < fieldSize; i |= i + 1) {
		for (int j = m; j < fieldSize; j |= j + 1) {
			field[i][j] += x;
		}
	}
}

char cmd[10];

int main() {
	//ifstream in("fenwick.in");
	//ofstream out("fenwick.out");
	FILE *in = fopen("fenwick.in", "r");
	FILE *out = fopen("fenwick.out", "w");

	int n;
	//in >> n;
	fscanf(in, "%d", &n);
	int k;
	fscanf(in, "%d", &k);
	//in >> k;

	//string cmd;
	for (int i = 0; i < k; i++) {
		//in >> cmd;
		fscanf(in, "%s", cmd);

		//if (cmd == "ADD") {
		if (cmd[0] == 'A') {
			int x;
			int y;
			//in >> x;
			//in >> y;
			fscanf(in, "%d", &x);
			fscanf(in, "%d", &y);

			add(1, x, y);

		} else {
			int x1_a;
			int y1_a;
			int x2_a;
			int y2_a;

			//in >> x1_a;
			//in >> y1_a;
			//in >> x2_a;
			//in >> y2_a;

			fscanf(in, "%d", &x1_a);
			fscanf(in, "%d", &y1_a);
			fscanf(in, "%d", &x2_a);
			fscanf(in, "%d", &y2_a);
			
			int x1 = min(x1_a, x2_a);
			int x2 = max(x1_a, x2_a);
			int y1 = min(y1_a, y2_a);
			int y2 = max(y1_a, y2_a);

			//out << get(x2, y2) - get(x2, y1 - 1) - get(x1 - 1, y2) + get(x1 - 1, y1 - 1) << endl;
			fprintf(out, "%lld\n", get(x2, y2) - get(x2, y1 - 1) - get(x1 - 1, y2) + get(x1 - 1, y1 - 1));
		}
	}

	fclose(in);
	fclose(out);
	//in.close();
	//out.close();

	return 0;
}
