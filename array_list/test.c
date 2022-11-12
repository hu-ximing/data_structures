// tests array_list
#include <stdio.h>
#include "array_list.h"

void print_size_and_capacity(ArrayList *list) {
    printf("size = %d\tcapacity = %d\n", list->size, list->capacity);
}

void follow_capacity(ArrayList *list, int range) {
    print_size_and_capacity(list);
    int capacity = list->capacity;
    for (int i = 0; i < range; i++) {
        push_back(list, i);
        if (capacity != list->capacity) {
            print_size_and_capacity(list);
            capacity = list->capacity;
        }
    }
}

int main() {
    ArrayList *list = new_array_list();
    // push_back
    puts("Testing push_back:");
    follow_capacity(list, 50);
    out_string(list);
    puts("");

    // pop_back
    puts("Testing pop_back:");
    while (list->size > 10)
        pop_back(list);
    print_size_and_capacity(list);
    out_string(list);
    puts("");

    // insert to list
    puts("Testing insert:");

    puts("insert 100 to front:");
    insert(list, 0, 100);
    out_string(list);
    print_size_and_capacity(list);

    puts("insert 200 to back:");
    insert(list, list->size, 200);
    out_string(list);
    print_size_and_capacity(list);

    puts("insert 300 to index 1:");
    insert(list, 1, 300);
    out_string(list);
    print_size_and_capacity(list);
    puts("");

    // erase from list
    puts("Testing erase:");

    puts("erase index 1:");
    erase(list, 1);
    out_string(list);

    puts("erase front:");
    erase(list, 0);
    out_string(list);

    puts("erase back:");
    erase(list, list->size - 1);
    out_string(list);

    print_size_and_capacity(list);
    puts("");

    // trim array capacity to size
    puts("Testing shrink_to_fit:");

    shrink_to_fit(list);
    print_size_and_capacity(list);

    list->size = 0;
    shrink_to_fit(list);
    print_size_and_capacity(list);

    puts("");

    // clear the list
    puts("Testing clear:");
    puts("before clear:");
    for (int i = 0; i < 20; i++)
        insert(list, list->size, 0);
    print_size_and_capacity(list);
    puts("clearing...");
    clear(list);
    print_size_and_capacity(list);
    out_string(list);
    destruct_array_list(list);
    return 0;
}