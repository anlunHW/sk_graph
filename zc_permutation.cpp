#include <cstdio>
#include <cmath>

using namespace std;

int const maxN = 100000 + 10;

//int numbers[maxN];
int n;
int m;

class IntervalTree {
	public:
		IntervalTree(int n, int* array)
			: mArraySize(n)
		{
			mArraySizeLog = (1 << int(log2(n))) == n
				? int(log2(n))
				: int(log2(n)) + 1;

			mRealSize = 1 << mArraySizeLog;

			mTree = new int*[mArraySizeLog];
			for (int i = 0; i < n; i++) {
				mTree[i] = new int[mRealSize];
			}

			memcpy(mTree[0], array, sizeof(array));
			memset(mTree[0] + n, maxN, (mRealSize - n) * sizeof(int));

			// merge sorting
			for (int i = 1; i < mArraySizeLog; i++) {
				// i - layer number
			}
		}

		/* Skipped part :-)
		~IntervalTree() {

		}
		*/

	private:
		int mRealSize;
		int mArraySize;
		int mArraySizeLog;
		int** mTree;
};

int main() {
	FILE* in = fopen("permutation.in", "r");

	fscanf(in, "%d %d", &n, &m);

	int numbers[n];
	for (int i = 0; i < n; i++) {
		fscanf(in, "%d", numbers + i);
	}

	FILE* out = fopen("permutation.out", "w");

	for (int i = 0; i < m; i++) {
		int x;
		int y;
		int k;
		int l;

		fscanf(in, "%d %d %d %d", &x, &y, &k, &l);

		// processing
	}

	fclose(out);
	fclose(in);

	return 0;
}
