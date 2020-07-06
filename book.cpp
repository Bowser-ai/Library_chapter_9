#include "book.h"
#include <regex>

Book::Book(std::string author, std::string title, std::string ISBN, Chrono::Date copyright_date, 
		Genre genre, bool is_checked_out)
	:author{author}, title{title}, ISBN{ISBN}, copyright_date{copyright_date},
	genre{genre}, is_checked_out{is_checked_out}
{
	std::regex r{"(\\d+-){3}[A-Za-z0-9]"};
	if (!std::regex_match(ISBN, r)) throw std::runtime_error{"invalid ISBN format\n"};
}

std::ostream& operator << (std::ostream& os, const Book& b)
{
	return os << b.title << "\n" << b.author << "\n" << b.genre_to_string() << "\n" << b.ISBN << "\n";
}

const std::unordered_map<Genre, std::string> Book::genre_mapping{
	{Genre::fiction, "fiction"}, {Genre::non_fiction, "non-fiction"},
	{Genre::biography, "biography"}, {Genre::children, "children"},
	{Genre::periodical, "periodical"}
};
