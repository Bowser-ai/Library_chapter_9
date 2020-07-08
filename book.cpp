#include "book.h"
#include <regex>
#include <iomanip>

Book::Book(std::string author, std::string title, std::string ISBN, Chrono::Date copyright_date, 
		Genre genre, bool is_checked_out)
	:author{author}, title{title}, ISBN{ISBN}, copyright_date{copyright_date},
	genre{genre}, is_checked_out{is_checked_out}
{
	check_isbn(ISBN);
}

Book Book::stream_in_book(std::istream& is)
{
    if (is.peek() == '\n') is.get();
    std::string author, title, ISBN;
	prompt_and_stream_in(author, "Enter author\n", is);
	prompt_and_stream_in(title, "Enter title\n", is);
	while (true)
	{
		try {
			prompt_and_stream_in(ISBN, "Enter ISBN, fomat = ddd-ddd-ddd-d/c\n", is);
			check_isbn(ISBN);
			break;
		}
		catch (std::runtime_error& e)
		{
			report_error_and_clean(e.what(), is);
		}
	}
	std::cout << "Enter date in format (y m d)\n";
    Chrono::Date date;
    is >> date;
    std::cout << "Provide a genre\n";
    std::string genre;
    is >> genre;
    Genre g = string_to_genre(genre);
    return Book{author, title, ISBN, date, g};
}

void Book::check_isbn(const std::string& ISBN)
{
	std::regex r{"(\\d+-){3}[A-Za-z0-9]"};
	if (!std::regex_match(ISBN, r)) throw std::runtime_error{"invalid ISBN format\n"};
}

void Book::prompt_and_stream_in(
		std::string& input, 
		const std::string& prompt, 
		std::istream& is, 
		std::ostream& os)
{
	os << prompt;
	std::getline(is, input);
}

std::ostream& operator << (std::ostream& os, const Book& b)
{
	os << b.title << std::setw(20) << std::right << b.author << std::setw(20) 
       << std::right << Book::genre_to_string(b.genre) << std::right << std::setw(20) << b.ISBN << "\n";
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

void report_error_and_clean(const std::string& error, std::istream& is)
{
	std::cerr << error;
	is.clear();
	//is.ignore(10000, '\n');
}
