-- FlatMap --

A FlatMap is an associative container that supports
unique keys (contains at most one of each key value)
and provides for fast retrieval of values
of other type based on the keys.

This FlatMap-implementation uses a String type as keys
and a Value type which consists of two unsigned integers.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

FlatMap(): Default constructor.
Initializes an empty FlatMap object.

~FlatMap(): Destructor.
Frees up dynamically allocated memory
used by keys and values arrays.

FlatMap(const FlatMap& b): Copy constructor.
Takes another FlatMap b as an argument,
creates a new FlatMap as a copy of b.

FlatMap(FlatMap&& b) noexcept: Move constructor.
Takes another FlatMap b as an argument,
efficiently moves the resources from b
to a newly created FlatMap.

swap(FlatMap& b): Swaps contents of
the FlatMap object with another FlatMap b.

operator=(const FlatMap& b): Copy assignment
operator. Overwrites the FlatMap object
with a copy of another FlatMap b.

operator=(FlatMap&& b) noexcept: Move assignment
operator. Efficiently moves resources
from another FlatMap b to the FlatMap object.

clear(): Empties the FlatMap,
releases all the resources.

resize(size_t newCapacity): Resizes
the capacity of the FlatMap to accommodate
more elements than it can currently hold.

binarySearch(const Key& k) const: Performs
a binary search for a given key k,
returns the position if present,
else returns a negative value.

erase(const Key& k): Removes key-value pair
with key k. Returns true if the pair was
successfully found and erased, false otherwise.

insert(const Key& k, const Value& v): Inserts
the key-value pair (k, v). Returns false
if the key already exists in the FlatMap,
true otherwise.

contains(const Key& k) const:
Checks whether the FlatMap contains a certain key k.

operator[](const Key& k): Returns
reference to the value that
is mapped to a key equivalent to k,
performing an insertion
if such key does not already exist.

at(const Key& k): Accesses the element
with key k, if it exists, otherwise
throws a std::out_of_range exception.

at(const Key& k) const : Similar
to the above but for const object.

size() const: Returns the number
of elements in the FlatMap.

empty() const: Checks if the FlatMap is empty.

operator==(const FlatMap& a, const FlatMap& b):
Checks if the FlatMaps a and b are equal (i.e.,
contain the same keys with the exact
same values in the same order).

operator!=(const FlatMap& a, const FlatMap& b):
Checks if the FlatMaps a and b are not equal.

firstKey() const: Returns
the first key in the FlatMap.

lastKey() const: Returns
the last key in the FlatMap.

