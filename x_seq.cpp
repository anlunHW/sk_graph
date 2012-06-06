#include <cstdio>
#include <algorithm>

using namespace std;

int const maxNumber = 100000;

int a[maxNumber];
int n;

long long firstCutSum[maxNumber];

void firstCutSumPreCalc() {
	long long curSum = 0;
	for (int i = 0; i < n; i++) {
		curSum += a[i];
		firstCutSum[i] = curSum;
	}
}

long long minFromTailSum[maxNumber]; 

void minFromTailSumPreCalc() {
	long long curMin = firstCutSum[n - 1];
	for (int i = n - 1; i >= 0; i--) {
		curMin = min(curMin, firstCutSum[i]);
		minFromTailSum[i] = curMin;
	}

	/*
	for (int i = 1; i < n; i++) {
		minFromTailSum[i] -= firstCutSum[i - 1];
	}
	*/
}

void firstCutSumPrint() {
	printf("firstCutSum:\n");
	for (int i = 0; i < n; i++) {
		printf("%lld ", firstCutSum[i]);
	}
	printf("\n\n");
}

void minFromTailSumPrint() {
	printf("minFromTailSum:\n");
	for (int i = 0; i < n; i++) {
		printf("%lld ", minFromTailSum[i]);
	}
	printf("\n\n");
}

void aPrint() {
	printf("a:\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n\n");
}

int main() {
	FILE* in = fopen("seq.in", "r");
	fscanf(in, "%d", &n);
	for (int i = 0; i < n; i++) {
		fscanf(in, "%d", a + i);
	}
	fclose(in);

	firstCutSumPreCalc();
	minFromTailSumPreCalc();

	//aPrint();
	//firstCutSumPrint();
	//minFromTailSumPrint();

	int cutCount = minFromTailSum[0] > 0 ? 1 : 0;
	for (int i = 1; i < n; i++) {
		if (
			(minFromTailSum[i] - firstCutSum[i - 1] > 0)
			&&
			(minFromTailSum[0] + (firstCutSum[n - 1] - firstCutSum[i - 1]) > 0)
		) {
			cutCount++;
		}
	}

	//printf("%d\n", cutCount);

	FILE* out = fopen("seq.out", "w");
	fprintf(out, "%d", cutCount);
	fclose(out);

	return 0;
}
