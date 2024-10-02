#include "members.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_binary_member() {
    FILE* file = fopen("member.bin", "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    struct member member;
    while (fread(&member, sizeof(struct member), 1, file)) {
        printf("Id: %d, Name: %s, Address: %s \n", member.id, member.name, member.address);
    }
    fclose(file);
}
int get_last_member_id() {
    FILE* file = fopen("members.txt", "r");
    if (file == NULL) {
        return 0;
    }

    char buffer[300];
    int last_id = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        struct member member;
        sscanf(buffer, "%5d %100s %200s\n", &member.id, member.name, member.address);
        if (member.id > last_id) {
            last_id = member.id;
        }
    }

    fclose(file);
    return last_id;
}

void append_member_in_file(struct member member) {
    FILE* file = fopen("members.txt", "a");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    int last_id = get_last_member_id();
    member.id = last_id + 1;

    fprintf(file, "%-5d %-100s %-200s\n", member.id, member.name, member.address);
    fclose(file);
}

int get_last_id_binary() {
    FILE* file = fopen("member.bin", "rb");
    if (file == NULL) {
        return 0;
    }

    struct member member;
    int last_id = 0;

    while (fread(&member, sizeof(struct member), 1, file)) {
        if (member.id > last_id) {
            last_id = member.id;
        }
    }

    fclose(file);
    return last_id;
}

void append_to_binary(struct member member) {
    FILE* file = fopen("member.bin", "ab");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int last_id = get_last_id_binary();
    member.id = last_id + 1;

    if (fwrite(&member, sizeof(struct member), 1, file) != 1) {
        printf("Failed to write to file.\n");
    } else {
        printf("Successfully added member.\n");
    }

    fclose(file);
}


void search_members_binary(int id, const char name[], struct member* result, int* found) {
    FILE* file = fopen("member.bin", "rb");
    if (file == NULL) {
        printf("Failed to open member.bin file.\n");
        *found = 0;
        return;
    }

    struct member member;
    *found = 0;

    while (fread(&member, sizeof(struct member), 1, file)) {
        if ((id != 0 && id == member.id) || (strcmp(name, "") != 0 && strcmp(name, member.name) == 0)) {
            *result = member;
            *found = 1;
            break;
        }
    }
    fclose(file);

    if (!(*found)) {
        printf("Member not found.\n");
    }
}

struct member ask_member_data() {
    struct member new_member;
    printf("Member Name: ");
    // scanf("%s", new_member.name);
    scanf("%[^\n]%*c", new_member.name);
    printf("Address: ");
    // scanf("%s", new_member.address);
    scanf("%[^\n]%*c", new_member.address);

    return new_member;
}