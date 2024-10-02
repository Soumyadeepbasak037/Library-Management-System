#ifndef BOOK_H
#define BOOK_H

struct Book {
    char title[100];
    char author[100];
    char isbn[18];
    char rack;
    char genre[50];
    char alpha_id[5];
    int copies;
};

struct Book ask_book_data();
void search(char book_alpha_id[], char title[]);
void search_binary(const char* book_alpha_id, const char* title, int* found);
void generate_id(char* new_alpha_id, char rack_alphabet);
void generate_id_binary(char* new_alpha_id, char rack_alphabet);
void append_book(struct Book book);
void append_book_binary(struct Book book);
void read_binary_book();

#endif // BOOK_H