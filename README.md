# Linked list

a simple implementation to linked list data structure

## features

- `void add(T)` adds an element to the end of the list
- `void deleteAt(int index)` removes element at `index`
- `void forEach(void (*callback)(T))` loop through the list
- `void forEach(void (*callback)(T, int))` loop through the list (with index)
- `int length()` loop through the list (with index)
- `LinkedList& reverse();` loop through the list (with index)

### integral only

- `void insertAfter(int data, int after);` insert `data` after position of
  `after`
- `void insertBefore(int data, int before);` insert `data` after position of
  `before`
