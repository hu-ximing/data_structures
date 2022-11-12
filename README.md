# Data structures

C implementation of some data structures.  
Can only store primitive types.

## array_list

C implementation of _C++ vector_ or _Java ArrayList_.

[_C++ vector_](https://www.cplusplus.com/reference/vector/vector/)

> Internally, vectors use a dynamically allocated array to store their elements. This array may need to be reallocated in order to grow in size when new elements are inserted, which implies allocating a new array and moving all elements to it. This is a relatively expensive task in terms of processing time, and thus, vectors do not reallocate each time an element is added to the container.

## linked_list

C implementation of LinkedList

The LinkedList stores its items in "containers." The list has a link to the first container and each container has a link to the next and previous container in the list. To add an element to the list, the element is placed into a new container and that container is linked to two other containers in the list.
