#include <fstream>
#include "library.h"

class Bad_stream : public std::exception
{
	public:
		Bad_stream(const char* msg): msg{msg}{};
		virtual const char* what() const noexcept override{return msg;}

	private:
		const char* msg;
};



int main()
{
	std::ifstream ifs{"test.txt"};
	if (!ifs) throw Bad_stream{"file stream not ok\n"};
    Library lib;
    while(true)
    {
        try {
            std::cout << "Welcome to the library interface\n"
                      << "Specify what you want to do\n"
                      << "1) Add books to the library\n"
                      << "2) Add patrons to the library\n"
                      << "3) Print all books\n"
                      << "q) to quit program\n";

            char ch{0};
            std::cin >> ch;
            switch (ch)
            {
                case '1':
                    {
                        Book book = Book::stream_in_book(ifs);
                        lib.add_book(book);
                        break;
                    }
                case '2':
                    break;
                case '3':
                    lib.print_books(std::cout);
                    break;
                case 'q': case 'Q':
                    return 0;
                default:
                    throw std::runtime_error{"Invalid choice \n"};
            }
        }
        catch (std::runtime_error& e)
        {
			report_error_and_clean(e.what(), ifs);
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << "\n";
            std::cerr << "unrecoverable error, exiting\n";
            return 100;
        }
    }

    return 0;
}
