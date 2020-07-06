#include "name_pairs.h"
#include <sstream>

int main()
{
	std::istringstream is{"Wouter\nKarel\nRosa"};
	std::istringstream is2{"10\n13\n15"};
	std::istringstream is3{"Wouter\nKarel\nRosa"};
	std::istringstream is4{"11\n13\n15"};
	Name_pairs np;
	Name_pairs np2;
	np.read_names(is);
	np.read_ages(is2);
	np2.read_names(is3);
	np2.read_ages(is4);

	std::cout << (np == np2) << "\n";

	return 0;
}
