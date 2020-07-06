#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <vector>

#include "book.h"
#include "patron.h"
#include "chrono.h"


class Library
{
	public:
		void add_book(const Book& book) {books.push_back(book);}
		void add_patron(const Patron& patron) {patrons.push_back(patron);}
		void checkout_book(const Book&, const Patron&, const Chrono::Date&) const;
		void checkin_book(const Book&, const Patron&, const Chrono::Date&) const;
		std::vector<Patron> get_patrons_with_fee() const;

	private:
		struct Transaction;

		mutable std::vector<Book> books;
		mutable std::vector<Patron> patrons;
		mutable std::vector<Transaction> transactions;

		const Book& find_book(const Book&) const;
		const Patron& find_patron(const Patron&) const;
		void create_transaction(const Book&, const Patron&, const Chrono::Date&) const;
};

struct Library::Transaction
{
	Chrono::Date date;
	Patron patron;
	Book book;
};

#endif
