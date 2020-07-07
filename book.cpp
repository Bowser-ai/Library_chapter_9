#include "book.h"
#include <regex>
#include <iomanip>

Book::Book(std::string author, std::string title, std::string ISBN, Chrono::Date copyright_date, 
		Genre genre, bool is_checked_out)
	:author{author}, title{title}, ISBN{ISBN}, copyright_date{copyright_date},
	genre{genre}, is_checked_out{is_checked_out}
{
	std::regex r{"(\\d+-){3}[A-Za-z0-9]"};
	if (!std::regex_match(ISBN, r)) throw std::runtime_error{"invalid ISBN format\n"};
}

Book Book::stream_in_book(std::istream& is)
{
    if (is.peek() == '\n') is.get();
    std::string author, title, ISBN;
    std::cout << "Enter author\n";
    std::getline(is, author);
    std::cout << "Enter title\n";
    std::getline(is, title);
    std::cout << "Enter ISBN for format digit(s)-digit(s)-digit(s)-digit or character\n";
    std::getline(is, ISBN);
    std::cout << "Enter copyright date with format (yyyy m d)\n";
    Chrono::Date date;
    is >> date;
    std::cout << "Provide a genre\n";
    std::string genre;
    is >> genre;
    Genre g = string_to_genre(genre);
    return Book{author, title, ISBN, date, g};
}

std::ostream& operator << (std::ostream& os, const Book& b)
{
    os << "Title" << std::setw(20) << "Author" << std::setw(20) << "Genre" << std::setw(20) << "ISBN\n";
	os << b.title << std::setw(20) << b.author << std::setw(20) 
       << Book::genre_to_string(b.genre) << std::setw(20) << b.ISBN << "\n";
    return os;
}

Genre Book::string_to_genre(const std::string& genre)
{
    for (const auto& p : genre_mapping)
    {
        if (p.second == genre) return p.first;
    }

    throw std::runtime_error{"Could not find corresponding genre\n"};
}

const std::unordered_map<Genre, std::string> Book::genre_mapping{
	{Genre::fiction, "fiction"}, {Genre::non_fiction, "non-fiction"},
	{Genre::biography, "biography"}, {Genre::children, "children"},
	{Genre::periodical, "periodical"}
};
