//
// Created by cre8tivesriram on 30-06-2025.
//

#ifndef LIBRARY_H
#define LIBRARY_H
#include <memory>
#include <vector>
#include <map>


#include "book.h"


class Library {
    std::vector<std::shared_ptr<Book>> books;

    static std::vector<std::string> search_clean(const std::string &t);
    static bool is_exact_match(const std::string &input, const std::string &t);
    static int compute_match_score(const std::vector<std::string> &key, const std::vector<std::string> &title);
    static std::vector<std::pair<std::shared_ptr<Book>, int>> rank_results(const std::map<std::shared_ptr<Book>, int> &res);
    static void display_results(const std::vector<std::pair<std::shared_ptr<Book>, int>> &ranked, long long int duration);
    static void display_results_nospeed(const std::vector<std::pair<std::shared_ptr<Book>, int>> &ranked);

    void delete_book(std::shared_ptr<Book> &name);

    template <typename FieldGetter>
    void searchBy(const std::string &query, FieldGetter getter) const;

    template <typename FieldGetter>
    void removeBy(const std::string &query, FieldGetter getter);



public:
    void add_book(std::shared_ptr<Book> &book);
    void summary_view() const;
    void table_view() const;

    void searchT(const std::string &t) const;
    void searchA(const std::string &a) const;
    void searchI(long long int isbn) const;

    void removeT(const std::string &t);
    void removeA(const std::string &a);
    void removeI(long long int isbn);

};



#endif //LIBRARY_H
