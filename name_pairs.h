#ifndef NAME_PAIRS_H_
#define NAME_PAIRS_H_

#include <vector>
#include <iostream>

class Name_pairs
{
	public:
		void read_names(std::istream&);
		void read_ages(std::istream&, std::ostream& os = std::cout);
		void sort_();

		unsigned get_age_size() const {return age.size();}
		unsigned get_name_size() const {return name.size();}
		const double& age_at(int index) const {return age.at(index);}
		const std::string& name_at(int index) const {return name.at(index);}

		bool operator == (const Name_pairs& other){return age == other.age && name == other.name;}
		bool operator != (const Name_pairs& other) { return !(*this == other);}

	private:
		std::vector<double> age;
		std::vector<std::string> name;
};

std::ostream& operator << (std::ostream&, const Name_pairs&);


#endif
