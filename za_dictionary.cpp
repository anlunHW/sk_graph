//#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

static int const maxSize = 100000; // 10 ^ 5

struct Vertex {
	map<char, int> next;
	int leaf; // number of string that ends in this vertex
	int parent;
	char parentChar;
	int sufLink;
	map<char, int> go;

	// quit function
	set<int> quitFunc;
	bool isQuitFuncCalculated;
};

Vertex mNode[maxSize + 1];

class Trie {
	public:
		Trie()
		{
			mNode[0].parent = -1;
			mNode[0].sufLink = -1;
			mNode[0].leaf = -1;
			mSize = 1;
			mAddedStringNumber = 0;
		}

		void addString(string const &str) {
			int v = 0;
			for (unsigned i = 0; i < str.length(); i++) {
				char curCh = str[i];
				if (mNode[v].next.find(curCh) == mNode[v].next.end()) {
					mNode[mSize].sufLink = -1;
					mNode[mSize].parent = v;
					mNode[mSize].parentChar = curCh;
					mNode[mSize].leaf = -1;
					mNode[mSize].isQuitFuncCalculated = false;

					mNode[v].next[curCh] = mSize;
					mSize++;
				}
				v = mNode[v].next[curCh];
			}
			mNode[v].leaf = mAddedStringNumber;

			mAddedStringNumber++;
			mWords.push_back(false);
		}

		int getLink(int v) {
			if (mNode[v].sufLink == -1) {
				if (v == 0 || mNode[v].parent == 0) {
					mNode[v].sufLink = 0;
					//mNode[v].sufLink = -1;
				} else {
					mNode[v].sufLink = go(getLink(mNode[v].parent), mNode[v].parentChar);
				}
			}

			return mNode[v].sufLink;
		}

		int go(int v, char c) {
			if (mNode[v].go.find(c) == mNode[v].go.end()) {
				if (mNode[v].next.find(c) != mNode[v].next.end()) {
					mNode[v].go[c] = mNode[v].next[c];
				} else {
					mNode[v].go[c] = v == 0 ? 0 : go(getLink(v), c);
				}
			}
		
			return mNode[v].go[c];
		}

		int goWithWordMarking(int v, char c) {
			set<int>* out = quitFunc(mNode[v].go[c]);

			for (set<int>::iterator it = out->begin(); it != out->end(); it++) {
				mWords[*it] = true;
			}

			return mNode[v].go[c];
		}

		vector<bool>* foundedWords() {
			return &mWords;
		}

		void check(string const &text) {
			int curState = 0;
			for (unsigned i = 0; i < text.size(); i++) {
				curState = go(curState, text[i]);
			}

			curState = 0;
			for (unsigned i = 0; i < text.size(); i++) {
				curState = goWithWordMarking(curState, text[i]);
			}
		}

	private:
		set<int>* quitFunc(int v) {
			if (mNode[v].isQuitFuncCalculated) {
				return &mNode[v].quitFunc;
			}

			int link = getLink(v);
			if (link != -1 && link != v) {
				mNode[v].quitFunc = *quitFunc(link);
			}
			if (mNode[v].leaf != -1) {
				mNode[v].quitFunc.insert(mNode[v].leaf);
			}
			mNode[v].isQuitFuncCalculated = true;

			return &mNode[v].quitFunc;
		}

		int mSize;
		int mAddedStringNumber;

		vector<bool> mWords;

		set<int> mSetBuffer;
};

int main() {
	ifstream in("dictionary.in");

	string text;
	in >> text;

	int n;

	in >> n;
	Trie trie;
	string tmp;
	for (int i = 0; i < n; i++) {
		in >> tmp;
		trie.addString(tmp);
	}

	in.close();

	trie.check(text);

	ofstream out("dictionary.out");
	vector<bool>* wordResult = trie.foundedWords();
	for (int i = 0; i < n; i++) {
		if ((*wordResult)[i]) {
			out << "Yes\n";
		} else {
			out << "No\n";
		}
	}
	out.close();

	return 0;
}
