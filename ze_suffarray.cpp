#include <fstream>
#include <iostream>
#include <string>

#include <memory.h>

using namespace std;

string text;
int n;

int const maxLength = 200000;
int const alphabetSize = 256;

int p[maxLength];
int c[maxLength];

//int cnt[alphabetSize];
int cnt[maxLength];

// temporary arrays
int pn[maxLength];
int cn[maxLength];

int main() {
	ifstream in("suffarray.in");
	getline(in, text);
	in.close();

	text += '\0'; // adding just for cycle computation
	n = text.length();

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

	ofstream out("suffarray.out");
	
	for (int i = 1; i < n; i++) {
		out << p[i] + 1 << " ";
	}

	out.close();

	return 0;
}
