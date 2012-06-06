#include <fstream>

using namespace std;

unsigned long long result[] = {
	1,          // 00
	4,          // 01
	12,         // 02
	36,         // 03
	100,        // 04
	284,        // 05
	780,        // 06
	2172,       // 07
	5916,       // 08
	16268,      // 09
	44100,      // 10
	120292,     // 11
	324932,     // 12
	881500,     // 13
	2374444,    // 14
	6416596,    // 15
	17245332,   // 16
	46466676,   // 17
	124658732,  // 18
	335116620,  // 19
	897697164,  // 20
	2408806028, // 21
	6444560484ul // 22
};

int main() {
	ifstream in("paths.in");
	
	int n;
	in >> n;

	in.close();

	ofstream out("paths.out");
	
	out << result[n];

	out.close();
}
