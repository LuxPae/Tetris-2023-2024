#include <iostream>
#include <fstream>

using namespace std;

typedef struct node{
    int val;
    node *next;
    node *prev;
}* list;

list head_insert (list l, int el);

list insert_ordered(list head, int el);

void print_reverse(list head, const char *filename);

void print_reverse_helper(list head, ofstream& outputFile);

void delete_list(list head);









