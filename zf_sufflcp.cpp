#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int* kasai(string const & str, int* suffArr) {
	int n = str.length();

	int rank[n];

	for (int i = 0; i < n; i++) {
		rank[suffArr[i]] = i;
	}

	int h = 0;
	int* answer = new int[n - 1];

	for (int i = 0; i < n; i++) {
		if (rank[i] >= 1) {
			int k = suffArr[rank[i] - 1];
			while (
				((i + h) != n)
				&&
				((k + h) != n)
				&&
				(str[i + h] == str[k + h])
			) {
				h++;
			}
			answer[rank[i] - 1] = h;
			if (h > 0) {
				h--;
			}
		}
	}

	return answer;
}

int main() {
	ifstream in("sufflcp.in");
	
	int n;
	string text;
	
	in >> n;
	in >> text;
	int suffArr[n];

	for (int i = 0; i < n; i++) {
		in >> suffArr[i];
		suffArr[i]--;
	}

	in.close();

	int* answer = kasai(text, suffArr);

	ofstream out("sufflcp.out");
	for (int i = 0; i < n - 1; i++) {
		out << answer[i] << " ";
	}
	out.close();
}
