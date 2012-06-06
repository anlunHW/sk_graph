#include <iostream>
#include <cstdio>
#include <algorithm> 
#include <set>
#include <vector>

using namespace std;

#define PROBLEM_IN_FILE "heaps2.in"
#define PROBLEM_OUT_FILE "heaps2.out"

int alreadyCalculated[1000001];
bool needToBeCalculated_Arr[1000001];
int a[30];
int n_size[10001];

// k < 30
int used[30];
int cc = 1;

set<int> needToBeCalculated;

class G_heaps2 {
	public:
		void start() {
			reading();
			work();
			writing();
		}

		void reading() {
			FILE* in = fopen(PROBLEM_IN_FILE, "r");

			fscanf(in, "%d", &k);
			minA = 1000001;
			for (int i = 0; i < k; i++) {
				fscanf(in, "%d", a + i);
				if (a[i] < minA)
					minA = a[i];
			}

			fscanf(in, "%d", &m);
			maxN = 0;
			for (int i = 0; i < m; i++) {
				fscanf(in, "%d", n_size + i);

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

		void work() {
			createVectorOfThatNeedToBeCalculated();

			for (set<int>::iterator it = needToBeCalculated.begin();
					it != needToBeCalculated.end(); it++)
			{
				func(*it);
			}
		}

		int func(int n) {
			if ((alreadyCalculated[n] - 1) != -1)
				return alreadyCalculated[n] - 1;

			// на данный момент все меньшие должны быть уже посчитаны
			cc++;
			for (int i = 0; i < k; i++) {
				if (n - a[i] >= 0) {
					//int tmp = func(n - a[i]);
					int tmp = alreadyCalculated[n - a[i]] - 1;
					if (tmp < k + 3)
						used[tmp] = cc;
				}
			}
			
			for (int i = 0; ; i++) {
				if (used[i] < cc) {
					alreadyCalculated[n] = i + 1;
					return i;
				}
			}
		}

		void createVectorOfThatNeedToBeCalculated() {
			for (int i = 0; i < m; i++) {
				calcForThis(n_size[i]);
			}
		}

		void calcForThis(int number) {
			if (needToBeCalculated_Arr[number])
				return;

			needToBeCalculated.insert(number);
			needToBeCalculated_Arr[number] = true;

			for (int i = 0; i < k; i++) {
				if (number - a[i] >= 0) {
					calcForThis(number - a[i]);
				}
			}
		}

	private:
		int k;
		int minA;

		int m;
		int maxN;
};

int main() {
	G_heaps2 heap;
	heap.start();
}
