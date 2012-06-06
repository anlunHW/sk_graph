#include <fstream>
#include <iostream>

using namespace std;

int const maxSize = 51;
int field[maxSize][maxSize];

int w = 5;
int h = 5;

void clear() {
	for (int i = 0; i < maxSize; i++) {
		for (int j = 0; j < maxSize; j++) {
			field[i][j] = 0;
		}
	}
}

long long dominoesLayoutNumber(int x, int y) {
	if (w * h % 2) {
		return 0;
	}

	if (x == (w - 1) && y == (h - 1)) {
		return field[x][y];
	}

	if (x >= w) {
		return dominoesLayoutNumber(0, y + 1);
	}

	if (field[x][y]) {
		// next domino
		return dominoesLayoutNumber(x + 1, y);
	}

	long long result = 0;

	//trying vertical domino
	if ((y + 1 < h) && (field[x][y + 1] == 0)) {
		field[x][y] = field[x][y + 1] = 1;
		
		result += dominoesLayoutNumber(x + 1, y);

		field[x][y] = field[x][y + 1] = 0;
	}
	
	//trying horizontal domino
	if ((x + 1 < w) && (field[x + 1][y] == 0)) {
		field[x][y] = field[x + 1][y] = 1;
		
		result += dominoesLayoutNumber(x + 1, y);

		field[x][y] = field[x + 1][y] = 0;
	}

	return result;
}

int main() {
	int const maxWH = 50;

	for (int i = 1; i <= maxWH; i++) {
		for (int j = 1; j * i <= maxWH; j++) {
			w = i;
			h = j;
			cout << "result[" << i << "][" << j << "]"
				<< " = " << dominoesLayoutNumber(0, 0) << ";" << endl;

			clear();
		}
	}
}
