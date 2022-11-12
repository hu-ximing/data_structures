#include "array_list.h"

#define ERROR_INDEX_OUT_OF_BOUNDS 1
#define ERROR_MEMORY_ERROR 2

// private

_Bool is_element_index(ArrayList *list, int index) {
    return index >= 0 && index < list->size;
}

_Bool is_position_index(ArrayList *list, int index) {
    return index >= 0 && index <= list->size;
}

void handle_index_out_of_range() {
    puts("ERROR: ArrayList: Index out of range.");
    exit(ERROR_INDEX_OUT_OF_BOUNDS);
}

void handle_memory_error() {
    puts("ERROR: ArrayList: Cannot (re)allocate memory.");
    exit(ERROR_MEMORY_ERROR);
}

// use before inserting
void auto_expand(ArrayList *list) {
    if (list->size == list->capacity) {
        int new_capacity = __max(DEFAULT_CAPACITY,
                                 list->capacity + (list->capacity >> 1));
        set_list_capacity(list, new_capacity);
    }
}

// public

/**
 * @brief Constructs an empty list with an initial capacity of ten.
 *
 * @return ArrayList*
 */
ArrayList *new_array_list() {
    ArrayList *list = malloc(sizeof(ArrayList));
    if (!list)
        return NULL;
    list->capacity = DEFAULT_CAPACITY;
    list->size = 0;
    list->arr = malloc(sizeof *list->arr * list->capacity);
    return list;
}

/**
 * @brief Change the container capacity to n elements.
 *
 * @param list
 * @param n New container capacity, expressed in number of elements.
 */
void set_list_capacity(ArrayList *list, int n) {
    if (n == 0) {
        free(list->arr);
        list->arr = NULL;
        list->capacity = 0;
        list->size = 0;
    } else {
        TYPE *new_arr = realloc(list->arr, sizeof *new_arr * n);
        if (new_arr) {
            list->arr = new_arr;
            list->capacity = n;
            list->size = __min(list->capacity, list->size);
        } else {
            free(list->arr);
            free(list);
            handle_memory_error();
        }
    }
}

/**
 * @brief Trims the capacity of this ArrayList instance to be the list's current size.
 *
 * @param list
 */
void shrink_to_fit(ArrayList *list) {
    set_list_capacity(list, list->size);
}

/**
 * @brief Add element at the end
 *
 * Adds a new element at the end of the vector, after its current last element.
 * The content of val is copied (or moved) to the new element.
 *
 * This effectively increases the container size by one,
 * which causes an automatic reallocation of the allocated storage space
 * if -and only if- the new vector size surpasses the current vector capacity.
 *
 * @param list
 * @param value Value to be copied (or moved) to the new element.
 */
void push_back(ArrayList *list, TYPE value) {
    auto_expand(list);
    list->arr[list->size++] = value;
}

/**
 * @brief Delete last element
 *
 * Removes the last element in the vector, effectively reducing the container size by one.
 * This destroys the removed element.
 *
 * @param list
 */
void pop_back(ArrayList *list) {
    if (list->size == 0)
        return;
    list->arr[--list->size] = 0;
}

/**
 * @brief Inserts the specified element at the specified position in this list.
 *
 * @param list
 * @param index
 * @param value
 */
void insert(ArrayList *list, int index, TYPE value) {
    if (!is_position_index(list, index))
        handle_index_out_of_range();
    auto_expand(list);
    memmove(list->arr + index + 1,
            list->arr + index,
            sizeof(TYPE) * (list->size - index));
    list->arr[index] = value;
    list->size++;
}

/**
 * @brief Removes the element at the specified position in this list.
 *
 * @param list
 * @param index
 * @return TYPE
 */
TYPE erase(ArrayList *list, int index) {
    if (!is_element_index(list, index))
        handle_index_out_of_range();
    TYPE old_val = list->arr[index];
    memmove(list->arr + index,
            list->arr + index + 1,
            sizeof(TYPE) * (list->size - index - 1));
    list->size--;
    return old_val;
}

/**
 * @brief Replaces the element at the specified position in this list with the specified element.
 *
 * @param list
 * @param index
 * @param value
 * @return TYPE
 */
TYPE set(ArrayList *list, int index, TYPE value) {
    if (!is_element_index(list, index))
        handle_index_out_of_range();
    TYPE old_val = list->arr[index];
    list->arr[index] = value;
    return old_val;
}

/**
 * @brief Returns the element at the specified position in this list.
 *
 * @param list
 * @param index
 * @return TYPE
 */
TYPE get(ArrayList *list, int index) {
    if (!is_element_index(list, index))
        handle_index_out_of_range();
    return list->arr[index];
}

/**
 * @brief Returns the index of the first occurrence of the specified element in this list,
 * or -1 if this list does not contain the element.
 *
 * @param list
 * @param value
 * @return int
 */
int index_of(ArrayList *list, TYPE value) {
    for (int i = 0; i < list->size; ++i)
        if (list->arr[i] == value)
            return i;
    return -1;
}

/**
 * @brief Returns the index of the last occurrence of the specified element in this list,
 * or -1 if this list does not contain the element.
 *
 * @param list
 * @param value
 * @return int
 */
int last_index_of(ArrayList *list, TYPE value) {
    for (int i = list->size - 1; i >= 0; --i)
        if (list->arr[i] == value)
            return i;
    return -1;
}

/**
 * @brief Removes all of the elements from this list.
 *
 * @param list
 */
void clear(ArrayList *list) {
    memset(list->arr, 0, sizeof *list->arr * list->size);
    list->size = 0;
}

/**
 * @brief Vector destructor
 *
 * Destroys the container object.
 *
 * @param list
 */
void destruct_array_list(ArrayList *list) {
    free(list->arr);
    free(list);
}

/**
 * @brief Print a string representing values in the list's array.
 *
 * @param list
 */
void out_string(ArrayList *list) {
    printf("[");
    if (list->size) {
        printf("%d", list->arr[0]);
        for (int i = 1; i < list->size; ++i)
            printf(", %d", list->arr[i]);
    }
    printf("]\n");
}