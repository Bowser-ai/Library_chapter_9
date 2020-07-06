#include "name_pairs.h"
#include <algorithm>

void Name_pairs::read_names(std::istream& is)
{
	std::string input;
	while (is >> input) name.push_back(input);
}

void Name_pairs::read_ages(std::istream& is, std::ostream& os)
{
	if (!is) is.clear();
	double input{0.0};
	for (const auto& n : name)
	{
		os << "Please provide a age for " << n << "\n";
		is >> input;
		age.push_back(input);
	}
}

void Name_pairs::sort_()
{
	std::vector<std::string> name_copy{name};
	std::sort(name.begin(), name.end());
	std::vector<double> new_age;
	for (auto i = 0UL; i < name.size(); ++i)
	{
		auto iter = std::find(name_copy.cbegin(), name_copy.cend(), name[i]);
		auto pos = std::distance(name_copy.cbegin(), iter);
		new_age.push_back(age[pos]);
	}
	age = new_age;
}

std::ostream& operator << (std::ostream& os, const Name_pairs& np)
{
	if (np.get_name_size() < np.get_age_size()) throw std::runtime_error{"Names list is smaller than age list\n"};
	for (auto i = 0UL; i < np.get_name_size(); ++i)
	{
		os << np.name_at(i) <<" " << np.age_at(i) << "\n";
	}
	return os;
}

