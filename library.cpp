//
// Created by sudosriram on 30-06-2025.
//

#include "library.h"
#include "library_helper.h"


#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <map>
#include <set>
#include <chrono>

void Library::add_book(std::shared_ptr<Book> &book) {
    std::string new_title = book->get_title();
    std::string new_author = book->get_author();

    for (const auto& b : books) {
        if (b->get_title() == new_title && b->get_author() == new_author) {
            std::cout << new_title << ": Already Exists!" << std::endl;
            return;
        }
    }

    books.push_back(book);
    std::cout << new_title << ": Added to the library!" << std::endl;
}



// START OF VIEWS

void Library::summary_view() const {
    for (const auto& b : books) {
        std::cout << std::setw(60) << std::setfill('-') << "" << std::setfill(' ') << std::endl;
        b->display_book_summary();
    }
    std::cout << std::setw(60) << std::setfill('-') << "" << std::setfill(' ') << std::endl;
}

void Library::table_view() const{
    table_header();
    int index = 1;
    for (const auto& b : books) {
        b->display_book_table(index);
        index++;
    }
    table_footer();
}

// END OF VIEWS

// START OF SEARCH HELPERS
std::vector<std::string> Library::search_clean(const std::string &t) {
    std::string search = t;
    std::transform(search.begin(), search.end(), search.begin(), ::tolower);
    search.erase(std::remove_if(search.begin(), search.end(), ::ispunct), search.end());

    std::istringstream iss(search);
    std::string search_words;
    std::vector<std::string> key_words;
    while (iss >> search_words) {
        key_words.push_back(search_words);
    }
    return key_words;
}

bool Library::is_exact_match(const std::string& input, const std::string& t){
    return input == t;
}

int Library::compute_match_score(const std::vector<std::string> &key, const std::vector<std::string> &title) {
    std::set<std::string> match;
    for (const auto &key_word : key) {
        for (const auto &title_word : title) {
            if (title_word == key_word) {
                match.insert(key_word);
            }
        }
    }
    return static_cast<int>(match.size());
}


std::vector<std::pair<std::shared_ptr<Book>, int>> Library::rank_results(const std::map<std::shared_ptr<Book>, int> &res) {
    std::vector<std::pair<std::shared_ptr<Book>, int>> ranked;
    for (const auto &[k, v]: res) {
        ranked.emplace_back(k, v);
    }
    std::sort(ranked.begin(), ranked.end(), [] (auto &a, auto &b) { return a.second > b.second; });

    return ranked;
}

void Library::display_results(const std::vector<std::pair<std::shared_ptr<Book>, int>> &ranked, long long int duration) {
    std::cout << "About " << ranked.size() << " results (" << duration << " μs)" << std::endl;
    table_header();
    int index = 1;
    for (const auto& r : ranked) {
        r.first->display_book_table(index);
        index++;
    }
    table_footer();
}

void Library::display_results_nospeed(const std::vector<std::pair<std::shared_ptr<Book>, int>> &ranked) {
    table_header();
    int index = 1;
    for (const auto& r : ranked) {
        r.first->display_book_table(index);
        index++;
    }
    table_footer();
}




// START OF SEARCH

template<typename FieldGetter>
void Library::searchBy(const std::string &query, FieldGetter getter) const{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::string> key_words = search_clean(query);

    std::map<std::shared_ptr<Book>, int> results;
    std::set<std::string> match;


    for (const auto& b : books) {
        match.clear();
        std::string title = getter(b);
        if (is_exact_match(query, title)) {
            int index = 1;
            table_header();
            b->display_book_table(index);
            table_footer();
            return;
        }
        std::vector<std::string> title_words = search_clean(title);

        int score = compute_match_score(key_words, title_words);
        if (score > 0) {
            results[b] = score;
        }
    }
    if (static_cast<int>(results.size()) == 0) {
        std::cout << "No matches found!" << std::endl;
        return;
    }
    const auto ranked = rank_results(results);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    display_results(ranked, duration.count());
}

// START OF SEARCH BY TITLE
void Library::searchT(const std::string &t) const {
    searchBy(t, [](const std::shared_ptr<Book> &b) { return b->get_title(); });
    // getter is lambda that takes parameter b and returns its title.
}
// END OF SEARCH BY TITLE

// START OF SEARCH BY AUTHOR
void Library::searchA(const std::string &a) const {
    searchBy(a, [](const std::shared_ptr<Book> &b) { return b->get_author(); });
}
// END OF SEARCH BY AUTHOR

// START OF SEARCH BY ISBN
void Library::searchI(long long int isbn) const {
    bool found = false;


    for (const auto& b : books) {
        if (b->get_isbn() == isbn) {
            int index = 1;
            std::cout << "Book found:\n";
            table_header();
            b->display_book_table(index);
            table_footer();
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "No book found for ISBN: " << isbn << std::endl;
    }
}
// END OF SEARCH BY ISBN

// END OF SEARCH


// START OF REMOVE

void Library::delete_book(std::shared_ptr<Book> &name) {
    for (auto it = books.begin(); it != books.end(); it++) {
        if (*it == name) {
            books.erase(it);
            break;
        }
    }
}


template<typename FieldGetter>
void Library::removeBy(const std::string &query, FieldGetter getter) {

    for (auto& b : books) {
        std::string title = getter(b);
        if (is_exact_match(query, title)) {
            int index = 1;
            table_header();
            b->display_book_table(index);
            table_footer();
            std::cout << std::endl;
            bool ask = confirm();
            if (ask) {
                delete_book(b);
                std::cout << "Book deleted!" << std::endl;
            }
            else {
                std::cout << "Book not deleted!" << std::endl;
            }
            return;
        }
    }

    std::vector<std::string> key_words = search_clean(query);

    std::map<std::shared_ptr<Book>, int> results;
    std::set<std::string> match;

    for (const auto& b : books) {
        match.clear();
        std::string title = getter(b);
        std::vector<std::string> title_words = search_clean(title);

        int score = compute_match_score(key_words, title_words);
        if (score > 0) {
            results[b] = score;
        }
    }
    if (static_cast<int>(results.size()) == 0) {
        std::cout << "No matches found!" << std::endl;
        return;
    }
    auto ranked = rank_results(results);
    display_results_nospeed(ranked);

    int raw_input = todelete();
    if (raw_input == 0) {
        std::cout << "Delete cancelled." << std::endl;
        return;
    }
    int index = raw_input - 1;
    bool is_valid = checkValid(index, static_cast<int>(ranked.size()));
    if (is_valid) {
        auto &selected_pair = ranked[index];
        auto &b = selected_pair.first;
        delete_book(b);
        ranked.erase(ranked.begin() + index);
        std::cout << "Book deleted!" << std::endl;
    } else {
        std::cout << "Invalid book number!" << std::endl;
    }
}

void Library::removeT(const std::string &t) {
    removeBy(t, [](const std::shared_ptr<Book> &b) { return b->get_title(); });
}

void Library::removeA(const std::string &a) {
    removeBy(a, [](const std::shared_ptr<Book> &b) { return b->get_author(); });
}

void Library::removeI(long long int isbn) {
    bool found = false;

    for (auto &b : books) {
        if (b->get_isbn() == isbn) {
            found = true;
            delete_book(b);
            std::cout << "Book deleted!" << std::endl;
            break;
        }
    }

    if (!found) {
        std::cout << "No book found for ISBN: " << isbn << std::endl;
    }
}

// END OF REMOVE



