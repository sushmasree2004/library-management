#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book {
    int accession_number;
    char title[50];
    char author[50];
    float price;
    int issued;
};

struct Library {
    struct Book books[MAX_BOOKS];
    int count;
};

void add_book(struct Library *lib) {
    if (lib->count >= MAX_BOOKS) {
        printf("Library is full, cannot add more books\n");
        return;
    }

    struct Book book;
    printf("Enter book details:\n");
    book.accession_number = rand() % 1000 + 1;
    printf("Accession Number: %d\n", book.accession_number);
    printf("Title: ");
    fgets(book.title, 50, stdin);
    book.title[strcspn(book.title, "\n")] = 0;
    printf("Author: ");
    fgets(book.author, 50, stdin);
    book.author[strcspn(book.author, "\n")] = 0;
    printf("Price: ");
    char price_str[10];
    fgets(price_str, 10, stdin);
    book.price = atof(price_str);
    book.issued = 0;

    lib->books[lib->count] = book;
    lib->count++;

    printf("Book added successfully\n");
}

void display_books(struct Library lib) {
    if (lib.count == 0) {
        printf("Library is empty\n");
        return;
    }

    printf("Accession Number\tTitle\t\tAuthor\t\tPrice\tIssued\n");
    for (int i = 0; i < lib.count; i++) {
        struct Book book = lib.books[i];
        printf("%d\t\t%s\t\t%s\t\t%.2f\t%s\n", book.accession_number, book.title, book.author, book.price, book.issued ? "Yes" : "No");
    }
}

void list_books_by_author(struct Library lib, char author[50]) {
    if (lib.count == 0) {
        printf("Library is empty\n");
        return;
    }

    printf("Books by %s:\n", author);
    printf("Accession Number\tTitle\t\tAuthor\t\tPrice\tIssued\n");
    for (int i = 0; i < lib.count; i++) {
        struct Book book = lib.books[i];
        if (strcmp(book.author, author) == 0) {
            printf("%d\t\t%s\t\t%s\t\t%.2f\t%s\n", book.accession_number, book.title, book.author, book.price, book.issued ? "Yes" : "No");
        }
    }
}

void list_title(struct Library lib, int accession_number) {
    if (lib.count == 0) {
        printf("Library is empty\n");
        return;
    }

    for (int i = 0; i < lib.count; i++) {
        struct Book book = lib.books[i];
        if (book.accession_number == accession_number) {
            printf("Title of book with accession number %d: %s\n", book.accession_number, book.title);
            return;
        }
    }

    printf("Book with accession number %d not found\n", accession_number);
}

void list_count(struct Library lib) {
    printf("Number of books in library: %d\n", lib.count);
}


        
void list_by_accession_number(struct Library lib) {
    if (lib.count == 0) {
        printf("Library is empty\n");
        return;
    }

    printf("Books sorted by accession number:\n");
    printf("Accession Number\tTitle\t\tAuthor\t\tPrice\tIssued\n");

    struct Book temp;
    for (int i = 0; i < lib.count; i++) {
        for (int j = i + 1; j < lib.count; j++) {
            if (lib.books[i].accession_number > lib.books[j].accession_number) {
                temp = lib.books[i];
                lib.books[i] = lib.books[j];
                lib.books[j] = temp;
            }
        }
    }

    for (int i = 0; i < lib.count; i++) {
        struct Book book = lib.books[i];
        printf("%d\t\t%s\t\t%s\t\t%.2f\t%s\n", book.accession_number, book.title, book.author, book.price, book.issued ? "Yes" : "No");
    }
}

int main() {
    struct Library lib;
    lib.count = 0;

    int choice;
    char author[50];
    int accession_number;

    do {
        printf("\nLibrary Management System\n");
        printf("1. Add book information\n");
        printf("2. Display book information\n");
        printf("3. List all books of given author\n");
        printf("4. List title of specified book\n");
        printf("5. List the count of books in library\n");
        printf("6. List the books in the order of accession number\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_book(&lib);
                break;
            case 2:
                display_books(lib);
                break;
            case 3:
                printf("Enter author name: ");
                getchar();
                fgets(author, 50, stdin);
                author[strcspn(author, "\n")] = 0;
                list_books_by_author(lib, author);
                break;
            case 4:
                printf("Enter accession number: ");
                scanf("%d", &accession_number);
                list_title(lib, accession_number);
                break;
            case 5:
                list_count(lib);
                break;
            case 6:
                list_by_accession_number(lib);
                break;
            case 7:
                printf("Exiting program\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 7);

}

