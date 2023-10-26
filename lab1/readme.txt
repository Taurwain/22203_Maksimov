-- FlatMap --

A FlatMap is an associative container that supports
unique keys (contains at most one of each key value)
and provides for fast retrieval of values
of other type based on the keys.

This FlatMap-implementation uses a String type as keys
and a Value type which consists of two unsigned integers.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

-- FlatMap::swap --  is used from the standard library
since the move-constructor and move-operator
are implemented for FlatMap.

-- FlatVap::clear -- requires no arguments and
clears the container (i.e. it puts an empty string
in the Key and sets the Value fields to zero)

-- FlatMap::resize -- takes the newСapacity as one argument
and increases the container by this value.

-- FlatMap::binarySearch -- binary takes the Key as one argument
and implements Binary search algorithm for finding
insertion/erasing space container element by the given Key.
Depending on the success of the search, it returns either
an index where Value corresponding to the given Key
is located, or the exact insertion location which is
increased by one and taken with a minus sign
(this is done in order to handle the case where for a given
the Key value was not found and the exact insertion location is zero).

-- FlatMap::erase -- takes the Key as one argument
and deletes the corresponding Value. BinarySearch is used
to search for placeToErase. The erasing occurs by shifting
everything behind placeToErase one to the left.
Depending on success returns either true if found
by the given Key Value or false otherwise. If the container is empty,
immediately returns false which is logical.

-- FlatMap::insert -- takes Key and Value as two arguments
and adds a new element containing the given Key and Value
into the container. BinarySearch is used
to search for placeToInsert. To make sure there is enough
in the container place to insert, compares map_size and
map_capacity and in case of equality calls resize
(adding one to the argument for case where
the container is empty). The insertion occurs by shifting everything
behind placeToInsert one to the right and direct assignment
given Key and Value on placeToInsert. Depending on success
returns true if there is no element with the given Key
in container or false otherwise.

-- FlatMap::contains -- takes the Key as one argument
and depending on success returns true if for the given Key
exists Value and false otherwise. If the container is empty,
immediately returns false which is logical.

-- FlatMap::operator[] -- takes the Key as one argument
and depending on success or returns Value by a given Key,
if it is exists, or inserts the given Key
with the default Value and returns it.

-- FlatMap::at -- takes the Key as one argument and
depending on success or returns Value by a given Key,
if it is exists, or throws an exception
"The value you asked for doesn't exist!" otherwise.
There is also a constness overload for this method.

-- FlatMap::size -- requires no arguments and
returns the value of map_size.

-- FlatMap::empty -- requires no arguments and
returns true if container is empty or false otherwise.

-- FlatMap::operator== -- takes two FlatMap references
as two arguments and returns true if they are equal
or false otherwise. Has the opposite effect to the != operator.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

There are also some helper methods.

-- FlatMap::firstKey -- requires no arguments and
returns the first Key in the container.

-- FlatMap::lastKey -- requires no arguments and
returns the last Key in the container.
