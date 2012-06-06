#include <fstream>
#include <iostream>

using namespace std;

int main() {
	ifstream in("sum0.in");
	
	int n;
	int x;
	int y;
	int a0;
	in >> n;
	in >> x;
	in >> y;
	in >> a0;

	long long sum[n];
	long long a[n];
	sum[0] = a0;
	a[0] = a0;

	for (int i = 1; i < n; i++) {
		a[i] = (x * a[i - 1] + y) % (1 << 16);
		sum[i] = sum[i - 1] + a[i];
	}

	int m;
	int z;
	int t;
	int b0;
	in >> m;
	in >> z;
	in >> t;
	in >> b0;

	int c[2 * m];
	long long curB = b0;
	for (int i = 0; i < 2 * m; i++) {
		c[i] = curB % n;
		curB = (curB * z + t + (1 << 30)) % (1 << 30);
	}

	in.close();

	ofstream out("sum0.out");

	long long result = 0;
	for (int i = 0; i < m ; i++) {
		int left = min(c[2 * i], c[2 * i + 1]);
		int right = max(c[2 * i], c[2 * i + 1]);

		result += sum[right] - sum[left] + a[left];
	}

	out << result;

	out.close();

	return 0;
}
