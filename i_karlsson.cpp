#include <cstdio>
#include <memory.h>

using namespace std;

int const maxSize = 5001;
int grundy[maxSize];

void calcGrundy() {
	int mex[10000];

	for (int i = 1; i < maxSize; i++) {
		memset(mex, 0, sizeof(mex));
		for (int j = i - 1; j >= (i + 1) / 2; j--) {
			mex[grundy[j]] = 1;
		}
		
		int gr = 0;
		for (int k = 0; k < 10000 && mex[k] != 0; k++) {
			gr++;
		}

		grundy[i] = gr;
	}
}

int main() {
	calcGrundy();

	FILE* in = fopen("karlsson.in", "r");
	int a;
	int b;
	int c;

	fscanf(in, "%d %d %d", &a, &b, &c);
	fclose(in);

	FILE* out = fopen("karlsson.out", "w");

	if ((grundy[a] ^ grundy[b] ^ grundy[c]) == 0) {
		fprintf(out, "NO");

		fclose(out);
		return 0;
	}

	fprintf(out, "YES\n");
	for (int i = a - 1; i >= (a + 1) / 2; i--) {
		if ((grundy[i] ^ grundy[b] ^ grundy[c]) == 0) {
			fprintf(out, "%d %d %d", i, b, c);
			fclose(out);
			return 0;
		}
	}

	for (int i = b - 1; i >= (b + 1) / 2; i--) {
		if ((grundy[a] ^ grundy[i] ^ grundy[c]) == 0) {
			fprintf(out, "%d %d %d", a, i, c);
			fclose(out);
			return 0;
		}
	}

	for (int i = c - 1; i >= (c + 1) / 2; i--) {
		if ((grundy[a] ^ grundy[b] ^ grundy[i]) == 0) {
			fprintf(out, "%d %d %d", a, b, i);
			fclose(out);
			return 0;
		}
	}

	fclose(out);

	return 0;
}
