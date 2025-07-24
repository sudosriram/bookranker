//
// Created by cre8tivesriram on 30-06-2025.
//

#include "book.h"

#include <iostream>
#include <iomanip>

Book::Book(std::string title, std::string author, int pages, int copies, long long int isbn)
    : title(std::move(title)), author(std::move(author)), pages(pages), copies(copies), isbn(isbn) {}

// START OF GETTERS

const std::string &Book::get_title() const {
    return title;
}

const std::string &Book::get_author() const {
    return author;
}

int Book::get_pages() const {
    return pages;
}

int Book::get_copies() const {
    return copies;
}

long long int Book::get_isbn() const {
    return isbn;
}

// END OF GETTERS //


// START OF DISPLAY

void Book::display_book_summary() const {
    std::cout << std::left << "Title" << ": "
              << std::left << std::setw(40) << title << std::endl;
    std::cout << std::left << "Author" << ": "
              << std::left << std::setw(40) << author << std::endl;
    std::cout << std::left << "Pages" << ": "
              << std::left << std::setw(40) << pages << std::endl;
    std::cout << std::left << "Copies" << ": "
              << std::left << std::setw(40) << copies << std::endl;
    std::cout << std::left << "ISBN" << ": "
              << std::left << std::setw(40) << isbn << std::endl;
}

void Book::display_book_table(int index) const {
    std::cout << "| " << std::left << std::setw(4) << index
        << " | " << std::left << std::setw(50) << title
        << " | " << std::left << std::setw(20) << author
        << " | " << std::left << std::setw(5) << pages
        << " | " << std::left << std::setw(6) << copies
        << " | " << std::left << std::setw(15) << isbn
        << " |" << std::endl;
}


// END OF DISPLAY

