#ifndef BOOK_H_
#define BOOK_H_

#include "chrono.h"

enum class Genre
{
	fiction, non_fiction, periodical, biography, children
};

class Book
{
	public:
		Book(std::string author, std::string title, std::string ISBN, Chrono::Date copyright_date,
				Genre genre, bool is_checked_out = false);

		std::string get_author()const {return author;}
		std::string get_title()const {return title;}
		std::string get_ISBN()const {return ISBN;}
		Chrono::Date get_copyright_date() const {return copyright_date;}
		bool get_is_checked_out() const {return is_checked_out;}
		std::string get_genre() {return genre_to_string();}

		void check_in() const {is_checked_out = false;} 
		void check_out() const {is_checked_out = true;}

		bool operator == (const Book& other) {return ISBN == other.ISBN;}
		bool operator != (const Book& other) {return !(*this == other);}
		friend std::ostream& operator << (std::ostream&, const Book&);

	private:
		std::string author;
		std::string title;
		std::string ISBN;
		Chrono::Date copyright_date;
		Genre genre;
		mutable bool is_checked_out{false};

		static const std::unordered_map<Genre, std::string>genre_mapping;
		std::string genre_to_string() const {return genre_mapping.at(genre);}
};

#endif
