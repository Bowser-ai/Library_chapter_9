#include "library.h"

int main()
{
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
                        Book book = Book::stream_in_book(std::cin);
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
            std::cerr << e.what() <<"\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
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
