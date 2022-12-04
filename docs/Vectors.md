# Some quick documentation for our version of `std::vector`

- `T &operator[](int index)` - gets the `index`-th object starting at zero
- `void push(T obj)` - pushes `obj` end of the vector
- `T pop()` - pops the last element off the vector
- `void rm(int index)` - removes the `index`-th object starting at zero
- `void insert(int index, T obj)` - inserts `obj` at `index` starting at zero, pushing everything after it back by one
- `int getCount()` - gets the number of objects in the vector
- `T &getLast()` - gets the last object in the vector
- `T &getFirst()` - gets the first object in the vector