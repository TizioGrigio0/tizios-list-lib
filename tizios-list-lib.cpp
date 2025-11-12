#include "tizios-list-lib.h"

// ----------------------------------------- List management functions ----------------------------------------- //

// Push an element at the last index
void list_push_last(list_node*& root, double data) {
    list_push_at_index(root, data, (unsigned int)(-1));
}

// Push an element at the first index
void list_push_first(list_node*& root, double data) {
        list_push_at_index(root, data, 0);
}

// Places the element at the given index.
// If the given index is unreachable, places at the end of the list
void list_push_at_index(list_node*& root, double data, unsigned int index) {

    // If there is no element at the root of the list
    if (!root) {
        // Make root the first element
        root = new list_node;
        root->data = data;
        root->next = nullptr;
        return;
    }

    // If we want to place it at the front of the list
    if (index == 0) {
        list_node* new_node = new list_node;
        new_node->next = root;
        new_node->data = data;
        root = new_node;
        return;
    }

    // Find the wanted index, or the last available index if the list ends before reached the wanted index
    list_node* node = root;
    for (unsigned int i=0; i<index && node->next; i++) {
        node = node->next;
    }

    // Start initializing the wanted node
    list_node* new_node = new list_node;
    new_node->data = data;
    // Make the node after the new node the old next node (Put it in between cur and next)
    new_node->next = node->next; // If next is nullptr, then new_node->next is nullptr
    node->next = new_node; // Connect the current node to the new node
}

// Returns the length of the specified list, from the given root to the last index.
unsigned int list_length(const list_node* root) {
    unsigned int length = 0;
    const list_node* node = root;
    while (node) { length++; node = node->next; }
    return length;
}

// Returns the length of the specified list, from the given root to the last index.
// Uses the recursive approach to achieve that.
unsigned int recursive_list_length(const list_node* root) {
    if (!root) return 0;
    return recursive_list_length(root->next) + 1;
}

// Pops the last element
// Use bool* success to check if it succeeded
double list_pop_last(list_node*& root, bool* success) {
    return list_pop_at_index(root, (unsigned int)(-1), success);
}

// Pops the first element
// Use bool* success to check if it succeeded
double list_pop_first(list_node*& root, bool* success) {
    return list_pop_at_index(root, 0, success);
}

// Pops the specified index.
// If index isn't found, it pops the last valid element
// Use bool* success to check if it found an element to pop
double list_pop_at_index(list_node*& root, unsigned int index, bool* success) {
    double data = 0.0;
    if (success) *success = false;

    // If there is no element at the root
    if (!root) {
        return data; // Return 0 without success
    }

    // If the user wants the first element
    if (index == 0) {
        // Move the next element in place of the root and return the original root's data.
        data = root->data;
        list_node* node_to_delete = root;
        root = root->next;
        delete node_to_delete;
        if (success) *success = true;
        return data; // Return the data of the old root with success
    }

    // Find the wanted index, or the last available index if the list ends before reached the wanted index
    list_node* node = root;
    list_node* prev = nullptr;
    for (unsigned int i=0; i<index && node->next; i++) {
        prev = node;
        node = node->next;
    }

    if (!prev) { // If there is only one node, pop it
        root = node->next; // Unlink the root from the list
    } else { // If there is more than one node
        prev->next = node->next; // link the previous node to the next
    }

    // Get the data from the selected node, then pop it.
    data = node->data;
    delete node;

    // Successfully reached the end of the pop function
    if (success) *success = true;
    return data;
}

// Returns the value at the last available index
// Use bool* success to check if it succeeded
double list_get_last_value(list_node*& root, bool* success) {
    return list_get_value_at_index(root, (unsigned int)-1, success);
}

// Returns the value at the first available index (usually root->data)
// Use bool* success to check if it succeeded
double list_get_first_value(list_node*& root, bool* success) {
    return list_get_value_at_index(root, 0, success);
}

// Returns the value at the specified index.
// If index isn't found, it returns the last valid element
// Use bool* success to check if it found a valid element
double list_get_value_at_index(const list_node*& root, unsigned int index, bool* success) {
    if (success) *success = false;

    // If there is no element at the root
    if (!root) {
        return 0.0; // Return 0 without success
    }

    // Find the wanted index, or the last available index if the list ends before reached the wanted index
    const list_node* node = root;
    for (unsigned int i=0; i<index && node->next; i++) {
        node = node->next;
    }

    if (!node) return 0.0;

    // Get the data from the selected node.
    if (success) *success = true;
    return node->data;
}

void delete_list(list_node*& root) {
    list_node* cur = root;

    // If there is no root, then the list is already empty
    if (!root) return;

    // Keep going until we processed every node
    while (cur) {
        list_node* next = cur->next; // Get the next node
        delete cur; // Delete the current node
        cur = next; // Make the next node the current node
    }
    root = nullptr; // Nullify root
}

void recursive_delete_list(list_node*& root) {
    if (!root) return;
    // Process the values in reverse order through stack abuse.
    recursive_delete_list(root->next);
    delete root;
    root = nullptr;

}