#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string text;
long long prefixHash[100001];
long long const p = 19;
long long pPow[100001];

void prefixCalc() {
	pPow[0] = 1;
	for (unsigned i = 1; i < text.length(); i++) {
		pPow[i] = pPow[i - 1] * p;
	}

	prefixHash[0] = text[0] - (long long)'a' + 1;
	for (unsigned i = 1; i < text.length(); i++) {
		prefixHash[i] = (text[i] - (long long)'a' + 1) * pPow[i];
		prefixHash[i] += prefixHash[i - 1];
	}
}

long long movedHash(int i, int j){
	return i > 0
		? prefixHash[j] - prefixHash[i - 1]
		: prefixHash[j];
}

bool isHashEqual(int a, int b, int c, int d) {
	long long hash1 = movedHash(a, b);
	long long hash2 = movedHash(c, d);

	return a > c
		? hash2 * pPow[a - c] == hash1
		: hash2 == hash1 * pPow[c - a];
}

int main() {
	ifstream in("substrcmp.in");
	in >> text;

	prefixCalc();

	ofstream out("substrcmp.out");
	int n;
	in >> n;
	for (int i = 0; i < n; i++) {
		int a;
		in >> a;
		
		int b;
		in >> b;
		
		int c;
		in >> c;
		
		int d;
		in >> d;

		if (
			(d - c == b - a)
			&&
			(isHashEqual(a - 1, b - 1, c - 1, d - 1))
		) {
			out << "Yes\n";
		} else {
			out << "No\n";
		}
	}

	in.close();
	out.close();
}
