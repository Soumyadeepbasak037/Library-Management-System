#ifndef MEMBERS_H
#define MEMBERS_H

struct member {
    int id;
    char name[100];
    char address[100];
};

struct member ask_member_data();
void search_members_binary(int id, const char name[], struct member* result, int* found);
void append_member_in_file(struct member member);
void append_to_binary(struct member member);
void read_binary_member();

#endif /* MEMBERS_H */