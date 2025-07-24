#include "library.h"
#include "book.h"










int main() {

    auto b1 = std::make_shared<Book>("The Midnight Library", "Matt Haig", 304, 3, 9780525559474);
    auto b2 = std::make_shared<Book>("Sapiens: A Brief History of Humankind", "Yuval Noah Harari", 498, 2, 9780062316097);
    auto b3 = std::make_shared<Book>("Harry Potter and the Sorcerer's Stone", "J.K. Rowling", 309, 1, 9780439708180);
    auto b4 = std::make_shared<Book>("Harry Potter and the Chamber of Secrets", "J.K. Rowling", 341, 1, 9780439064873);
    auto b5 = std::make_shared<Book>("Harry Potter and the Prisoner of Azkaban", "J.K. Rowling", 435, 1, 9780439136365);
    auto b6 = std::make_shared<Book>("Don Quixote", "Miguel de Cervantes", 242); // Adding books without copies and isbn

    Library library;
    library.add_book(b1);
    library.add_book(b2);
    library.add_book(b3);
    library.add_book(b4);
    library.add_book(b5);
    library.add_book(b6);

    library.searchT("harry potter");
    library.removeT("harry potter");
    library.table_view();

}