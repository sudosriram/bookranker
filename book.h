//
// Created by cre8tivesriram on 30-06-2025.
//

#ifndef BOOK_H
#define BOOK_H
#include <string>


class Book {
    std::string title;
    std::string author;
    int pages;
    int copies;
    long long int isbn;




public:
    Book(std::string title, std::string author, int pages, int copies, long long int isbn = 0);
    // Getters
    const std::string &get_title() const;
    const std::string &get_author() const;
    int get_pages() const;
    int get_copies() const;
    long long int get_isbn() const;

    void display_book_summary() const;
    void display_book_table(int index) const;


};



#endif //BOOK_H
