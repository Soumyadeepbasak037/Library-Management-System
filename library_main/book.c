#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Book{
    // int id;            
    char title[100];
    char author[100];
    char isbn[18];
    char rack;
    char genre[50];
    char alpha_id[5];
    int copies;
};

struct Book ask_book_data(){
    struct Book new_book;

    printf("Book Title: ");
    // scanf("%s",new_book.title);
    scanf("%[^\n]%*c", new_book.title);
    printf("Author Name: ");
    scanf("%s",new_book.author);
    printf("ISBN: ");
    scanf("%s",new_book.isbn);
    printf("Rack Alphabet: ");
    scanf(" %c", &new_book.rack);
    printf("Genre: ");
    scanf("%s",new_book.genre);
    // printf("copies ");
    // scanf(" %d", &new_book.copies);

    // *copies = new_book.copies;

    return new_book;
}


// void generate_id(){
//     FILE* file = fopen("library_final.txt", "r");
//     if (file == NULL) {
//         // return 0; 
//     }

//     char buffer[300];
//     int last_id = 0;
//     char rack_alphabet;
//     char new_alpha_id[5];

//     while (fgets(buffer, sizeof(buffer), file) != NULL) {
//         struct Book new_book;

//         sscanf(buffer,"%5s %100s",new_book.alpha_id,new_book.title);

//         last_id = atoi(&new_book.alpha_id[1]);
//         rack_alphabet = new_book.alpha_id[0];

//         // printf("%c %d",rack_alphabet,last_id);
//         last_id++;
//         sprintf(new_alpha_id, "%c%d", rack_alphabet, last_id);
//     }
//     printf("%s",new_alpha_id);
// }


void search(char book_alpha_id[], char title[]){
    FILE* file = fopen("library_final.txt","r");
    if (file == NULL) {
        printf("Failed to open issued books file.\n");
        return;
    }
    char buffer[300];
    int found = 0;
    struct Book new_book;

     while(fgets(buffer,sizeof(buffer),file)!=NULL){
        sscanf(buffer,"%5s %100s", new_book.alpha_id, new_book.title);

        if(strcmp(book_alpha_id,new_book.alpha_id) == 0){
            found = 1;
            printf("%5s %100s", new_book.alpha_id,new_book.title);
        }
        else if(strcmp(title,new_book.title) == 0){
            found = 1;
            printf("%5s %100s", new_book.alpha_id,new_book.title);
        }
        
     }
    fclose(file);

    // if(found){
    //     printf("%5s %100s", new_book.alpha_id,new_book.title);
    // }
    // else{
    //     printf("Not found");
    // }
}

void search_binary(char book_alpha_id[], char title[], int* found) {
    FILE* file = fopen("book.bin", "rb");
    if (file == NULL) {
        printf("Failed to open book.bin file.\n");
        *found = 0;
        return;
    }

    struct Book book;
    *found = 0;

    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (strcmp(book_alpha_id, book.alpha_id) == 0 || strcmp(title, book.title) == 0) {
            *found = 1;
            printf("Alpha ID: %s, Title: %s, Author: %s, ISBN: %s, Rack: %c, Genre: %s\n",
                   book.alpha_id, book.title, book.author, book.isbn, book.rack, book.genre);
        }
    }
    fclose(file);

    if (!(*found)) {
        printf("Not found\n");
    }
}

void generate_id(char* new_alpha_id, char rack_alphabet) {
    FILE* file = fopen("library_final.txt", "r");
    if (file == NULL) {
        sprintf(new_alpha_id, "%c%d", rack_alphabet, 1); 
        return;
    }

    char buffer[300];
    int last_id = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        struct Book new_book;

        sscanf(buffer, "%5s %100s", new_book.alpha_id, new_book.title);

        last_id = atoi(&new_book.alpha_id[1]);
        rack_alphabet = new_book.alpha_id[0];
    }

    last_id++;
    sprintf(new_alpha_id, "%c%d", rack_alphabet, last_id);

    fclose(file);
}

void generate_id_binary(char* new_alpha_id, char rack_alphabet) {
    FILE* file = fopen("book.bin", "rb");
    if (file == NULL) {
        sprintf(new_alpha_id, "%c%d", rack_alphabet, 1); 
        return;
    }

    char buffer[300];
    int last_id = 0;

    while (fread(&buffer, sizeof(struct Book), 1, file) != 0) {
        struct Book book;
        memcpy(&book, buffer, sizeof(struct Book));
        // Extract the alpha_id and update the last_id value
        sscanf(book.alpha_id, "%c%d", &rack_alphabet, &last_id);
    }

    last_id++;
    sprintf(new_alpha_id, "%c%d", rack_alphabet, last_id);

    fclose(file);
}

void append_book(struct Book book){
    generate_id(book.alpha_id, book.rack);

    FILE* file = fopen("library_final.txt", "a");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    fprintf(file, "%5s %100s %100s %50s \n", book.alpha_id, book.title, book.author, book.genre);
    fclose(file);
}


void append_book_binary(struct Book book){
     generate_id_binary(book.alpha_id, book.rack);  // Updated function call

    FILE* file = fopen("book.bin","ab");
    if(file == NULL){
        printf("Error opening file");
    }
    int flag =0;

    flag = fwrite(&book,sizeof(struct Book),1,file);
    if(!flag){
        printf("Failed\n");
    }
    else{
        printf("Successful\n");
    }
    fclose(file);
}

void read_binary_book(){
    FILE* file = fopen("book.bin", "rb");
    if(file == NULL){
        printf("Error opening file\n");
        return;
    }
    struct Book book;
    while(fread(&book, sizeof(struct Book), 1, file)){
        printf("Alpha ID: %s, Title: %s, Author: %s, ISBN: %s, Rack: %c, Genre: %s \n",book.alpha_id, book.title, book.author, book.isbn, book.rack, book.genre);
    }
    fclose(file);
}




