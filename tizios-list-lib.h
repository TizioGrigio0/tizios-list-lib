#ifndef TIZIOS_LIST_LIB_TIZIOS_LIST_LIB_H
#define TIZIOS_LIST_LIB_TIZIOS_LIST_LIB_H

// Declaration of the nodes
struct list_node {
    double data;
    list_node* next;
};

struct double_list_node {
    double data;
    list_node* next;
    list_node* prev;
};

// List management functions
void list_push_last(list_node*& root, double data);
void list_push_first(list_node*& root, double data);
void list_push_at_index(list_node*& root, double data, unsigned int index);

unsigned int list_length(const list_node* root);
unsigned int recursive_list_length(const list_node* root);

double list_pop_last(list_node*& root, bool* success = nullptr);
double list_pop_first(list_node*& root, bool* success = nullptr);
double list_pop_at_index(list_node*& root, unsigned int index, bool* success = nullptr);

double list_get_last_value(list_node*& root, bool* success = nullptr);
double list_get_first_value(list_node*& root, bool* success = nullptr);
double list_get_value_at_index(list_node*& root, unsigned int index, bool* success = nullptr);

void delete_list(list_node*& root);
void recursive_delete_list(list_node*& root);
#endif //TIZIOS_LIST_LIB_TIZIOS_LIST_LIB_H