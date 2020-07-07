#include "library.h"
#include <algorithm>

const Book& Library::find_book(const Book& book) const
{
	const auto iter = std::find(books.begin(), books.end(), book);
	if (iter == books.end()) throw std::runtime_error{"book not in library\n"};
	return *iter;
}

const Patron& Library::find_patron(const Patron& patron) const
{
	const auto iter = std::find(patrons.begin(), patrons.end(), patron);
	if (iter == patrons.end()) throw std::runtime_error{"patron not in library\n"};
	return *iter;
}

void Library::checkout_book(const Book& book, const Patron& patron, const Chrono::Date& date) const
{
	create_transaction(book, patron, date);
	book.check_out();
}

void Library::checkin_book(const Book& book, const Patron& patron, const Chrono::Date& date) const
{
	create_transaction(book, patron, date);
	book.check_in();
}

void Library::create_transaction(const Book& book, const Patron& patron, const Chrono::Date& date) const
{
	auto b = find_book(book);
	auto p = find_patron(patron);
	if (p.owes_fee()) throw std::runtime_error{p.get_username() + " still owes a fee\n"};
	transactions.push_back(Transaction{date, patron, book});
}

void Library::print_books(std::ostream& os) const
{
    for (const auto& book : books)
    {
        os << book << "\n";
    }
}

std::vector<Patron> Library::get_patrons_with_fee() const
{
	std::vector<Patron> result;
	result.reserve(patrons.size());
	std::remove_copy_if(patrons.cbegin(), patrons.cend(), result.begin(), 
			[](const Patron& patron){return !patron.owes_fee();});
	return result;
}
