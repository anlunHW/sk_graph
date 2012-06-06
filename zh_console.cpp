#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

#include <cstdio>

using namespace std;

int const p = 127;

unsigned const maxDictWordLength = 80;
set<unsigned long long> dictHashByLength[maxDictWordLength + 1];
//vector<unsigned long long> dictHashByLength[maxDictWordLength + 1];

unsigned const maxCompareStringSize= 250;
unsigned long long pPower[maxCompareStringSize + 1];

vector<string> stringsToCompare;
vector< vector<unsigned long long>* > prefixHash;
vector<bool> resultStringNumber;

void powerCalc() {
	pPower[0] = 1;
	for (unsigned i = 1; i <= maxCompareStringSize; i++) {
		pPower[i] = pPower[i - 1] * p;
	}
}

unsigned long long hash(string const &str) {
	unsigned long long result = 0;
	
	for (unsigned i = 0; i < str.length(); i++) {
		result += pPower[str.length() - 1 - i] * ((unsigned) str[i]);
		//inverse hash
	}

	return result;
}

int main() {
	powerCalc();

	ifstream in("console.in");
	int n;
	in >> n;

	string tmp;
	getline(in, tmp); // getting blank line

	for (int i = 0; i < n; i++) {
		getline(in, tmp);

		int length = tmp.length();
		unsigned long long curHash = hash(tmp);
		dictHashByLength[length].insert(curHash);
		//dictHashByLength[length].push_back(curHash);
	}
	
	while (!in.eof()) {
		getline(in, tmp);
		stringsToCompare.push_back(tmp);

		vector<unsigned long long>* curPrefixHash = new vector<unsigned long long>();
		unsigned long long curHash = (unsigned) tmp[0];
		curPrefixHash->push_back(curHash);
		for (unsigned i = 1; i < tmp.length(); i++) {
			//curHash += pPower[i] * ((unsigned) tmp[i]);
			curHash = ((unsigned) tmp[i]);
			curPrefixHash->push_back(curHash);
		}

		prefixHash.push_back(curPrefixHash);
		resultStringNumber.push_back(false);
	}
	in.close();

	for (unsigned i = 1; i <= maxDictWordLength; i++) {
		// compare strings with i length
		if (dictHashByLength[i].size() == 0) {
			continue;
		}

		for (unsigned j = 0; j < stringsToCompare.size(); j++) {
			// now we have concrete string to compare
			if (resultStringNumber[j] || stringsToCompare[j].length() < i) {
				continue;
			}

			bool isGoodStr = false;

			unsigned long long iHash = 0;
			for (int k = 0; k < i - 1; k++) {
				iHash += (unsigned) stringsToCompare[j][k];
				iHash *= p;
			}
			iHash += stringsToCompare[j][i - 1];

			//unsigned long long iHash = (*prefixHash[j])[i - 1];
			for (unsigned k = i - 1; k < stringsToCompare[j].length(); k++) {
				// hash
				/*
				iHash = k >= i
					? (*prefixHash[j])[k] - (*prefixHash[j])[k - i]
					: (*prefixHash[j])[k];
				*/

				if (dictHashByLength[i].find(iHash) != dictHashByLength[i].end()) {
					isGoodStr = true;
					break;
				}

				/*
				for (unsigned h = 0; h < dictHashByLength[i].size(); h++) {
					unsigned long long curHash = k >= i
						? dictHashByLength[i][h] * pPower[k - i + 1]
						: dictHashByLength[i][h];

					if (curHash == iHash) {
						isGoodStr = true;
						break;
					}
				}
				
				if (isGoodStr) {
					break;
				}
				*/

				iHash -= pPower[i - 1] * stringsToCompare[j][k - i + 1];
				iHash *= p;
				iHash += (unsigned) stringsToCompare[j][k + 1];
			}

			resultStringNumber[j] = isGoodStr;
		}
	}


	FILE* out = fopen("console.out", "w");
	for (unsigned i = 0; i < resultStringNumber.size(); i++) {
		if (resultStringNumber[i]) {
			fprintf(out, "%s\n", stringsToCompare[i].c_str());
		}
	}

	fclose(out);

	return 0;
}
