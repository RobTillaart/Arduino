# SET

Arduino library to implement simple SET data structure.

# Description

The set library implements the set data structure for integers 0..255.
This limit is chosen because of the memory limitations of an Arduino UNO, 
however these numbers can be used as indices to a table of strings or other
datatypes.

Set level
- **clr()** empty the set
- **invert()** flip all elements in the set.
- **count()** returns number of elements
- **isEmpty()** idem
- **isFull()** idem

Element level
- **add(n)** add element to the Set
- **sub(n)** emove element from Set
- **invert(n)** flip element in Set
- **has(n)** element is in Set
- **add(n)**

Operators
- union + +=
- diff - -=
- intersection * *=

Equality
- equal ==
- not equal !=
- is subSet <=

A superSet B is not implemented as one could say B subSet A (B <= A)

Iterators - all returns value or -1 if not exist
- **first()** find first element
- **next()** find next element
- **prev()** find previous element
- **last()** find last element

# Operational

See examples
