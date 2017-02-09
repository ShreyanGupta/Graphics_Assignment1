#include "Object.h"
#include "VCS.h"
#include <fstream>
using namespace std;

VCS parse_vcs(istream &fin);

int main(int argc, char const *argv[])
{
	ifstream fin((string)(argv[1]));
	// ifstream fin("inputs/input1.txt");
	string s;

	VCS vcs = parse_vcs(fin);
	cout << "Parsing done! \n";
	vcs.generate_Rays();
	vcs.render();
	
	return 0;
}