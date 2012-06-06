#include <iostream>
#include <fstream>
#include <string>
#include <memory.h>

using namespace std;

int* suffArray(string const &source_text) {
	string text = source_text + '\0';
	int n = text.length();

	int const maxLength = 200000;
	int const alphabetSize = 256;

	int p[maxLength];
	int c[maxLength];

	//int cnt[alphabetSize];
	int cnt[maxLength];

	// temporary arrays
	int pn[maxLength];
	int cn[maxLength];

	// first step sort
	for (int i = 0; i < n; i++) {
		cnt[(unsigned) text[i]]++;
	}
	for (int i = 1; i < alphabetSize; i++) {
		cnt[i] += cnt[i - 1];
	}
		
	for (int i = 0; i < n; i++) {
		cnt[(unsigned) text[i]]--;
		p[cnt[(unsigned) text[i]]] = i;
	}
	c[p[0]] = 0;
	int classes = 1;

	for (int i = 1; i < n; i++) {
		if (text[p[i]] != text[p[i - 1]]) {
			classes++;
		}
		c[p[i]] = classes - 1;
	}

	// main part
	for (int step = 0; (1 << step) <= n; step++) {
		for (int i = 0; i < n; i++) {
			pn[i] = p[i] - (1 << step);
			if (pn[i] < 0) {
				pn[i] += n;
			}
		}
		memset(cnt, 0, classes * sizeof(int));

		for (int i = 0; i < n; i++) {
			cnt[c[pn[i]]]++;
		}
		for (int i = 1; i < classes; i++) {
			cnt[i] += cnt[i - 1];
		}
		for (int i = n - 1; i >= 0; i--) {
			cnt[c[pn[i]]]--;
			p[cnt[c[pn[i]]]] = pn[i];
		}
		cn[p[0]] = 0;
		classes = 1;

		for (int i = 1; i < n; i++) {
			int mid1 = (p[i] + (1 << step)) % n;
			int mid2 = (p[i - 1] + (1 << step)) % n;

			if (
				c[p[i]] != c[p[i - 1]]
				||
				c[mid1] != c[mid2]
			) {
				classes++;
			}
			cn[p[i]] = classes - 1;
		}

		memcpy(c, cn, n * sizeof(int));
	}

	return p + 1;
}

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
	ifstream in("substr.in");
	string text;
	getline(in, text);
	in.close();

	int* textSuffArr = suffArray(text);
	int* lcp = kasai(text, textSuffArr);

	int n = text.length();
	long long result = n - textSuffArr[n - 1];
	for (int i = 0; i < n - 1; i++) {
		result += n - textSuffArr[i] - lcp[i];
	}

	ofstream out("substr.out");
	out << result;
	out.close();

	return 0;
}
