# PrintCharArray

Arduino library to print to a char array

# Description

PrintCharArray is a class that buffers a number of print statements in a char array.
This char array can be processed later.

- buffer slowly generated data, and send it with minimum time between bytes
- print to buffer to see how many chars the output is;
  use to prevent "display line overflow"
  (e.g. floats)
  
## Operation

See examples
