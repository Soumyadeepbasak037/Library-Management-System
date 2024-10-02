#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "members.h"

int validate_issue_book(const char book_alpha_id[])
{
    FILE *file = fopen("issued_books.txt", "r");
    if (file == NULL)
    {
        return 0;
    }

    int member_id;
    char issued_book_id[6];
    char issue_date[11];
    char return_date[11];
    while (fscanf(file, "%d %5s %10s %10s", &member_id, issued_book_id, issue_date, return_date) != EOF)
    {
        if (strcmp(issued_book_id, book_alpha_id) == 0)
        {
            fclose(file);
            return 1; // already issued
        }
    }

    fclose(file);
    return 0; // Not issues
}

void issue_book(int member_id, const char book_alpha_id[], const char issue_date[], const char return_date[])
{
    // Validate member ID
    struct member member_result;
    int member_found;
    search_members_binary(member_id, "", &member_result, &member_found);
    if (!member_found)
    {
        printf("Member with ID %d not found. Cannot issue book.\n", member_id);
        return;
    }

    // Validate book ID
    int book_found;
    search_binary(book_alpha_id, "", &book_found);
    if (!book_found)
    {
        printf("Book with alpha ID %s not found. Cannot issue book.\n", book_alpha_id);
        return;
    }

    // Check if the book is already issued
    if (validate_issue_book(book_alpha_id))
    {
        printf("Book with alpha ID %s is already issued. Cannot issue again.\n", book_alpha_id);
        return;
    }

    // Append to issued_books.txt
    FILE *file = fopen("issued_books.txt", "a");
    if (file == NULL)
    {
        printf("Failed to open issued_books.txt for appending.\n");
        return;
    }

    fprintf(file, "%d %s %s %s\n", member_id, book_alpha_id, issue_date, return_date);
    fclose(file);

    printf("Book with alpha ID %s issued to member with ID %d.\n", book_alpha_id, member_id);
}

void create_member()
{
    struct member new_member = ask_member_data();
    append_to_binary(new_member);
}

void create_book()
{
    struct Book new_book = ask_book_data();
    append_book_binary(new_book);
}

void show_members()
{
    read_binary_member();
}

void show_books()
{
    read_binary_book();
}

void display_menu()
{
    printf("\nMenu:\n");
    printf("1. Create Member\n");
    printf("2. Create Book\n");
    printf("3. Show Members\n");
    printf("4. Show Books\n");
    printf("5. Issue Book\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main()
{
    int choice;
    char book_alpha_id[6];
    char issue_date[11];
    char return_date[11];
    int member_id;

    do
    {
        display_menu();
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printf("\n");
            create_member();
            printf("\n");
            break;
        case 2:
            printf("\n");
            create_book();
            printf("\n");
            break;
        case 3:
            printf("\nMembers: \n");
            show_members();
            printf("\n");
            break;
        case 4:
            printf("\nBooks: \n");
            show_books();
            printf("\n");
            break;
        case 5:
            printf("Enter Member ID: ");
            scanf("%d", &member_id);
            getchar();

            printf("Enter Book Alpha ID: ");
            scanf("%s", book_alpha_id);

            printf("Enter Issue Date (yyyy-mm-dd): ");
            scanf("%s", issue_date);

            printf("Enter Return Date (yyyy-mm-dd): ");
            scanf("%s", return_date);

            issue_book(member_id, book_alpha_id, issue_date, return_date);
            break;
        case 6:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a number from 1 to 6.\n");
            break;
        }
    } while (choice != 6);

    return 0;
}
