
PrintCharArray is a class that buffers a number of print statements in a char array.
This char array can be processed later.

Typical usecase:
- buffer slow generated of a packet of data
  and send it with minimum time between bytes

- print to buffer an see how long output is;
  use to prevent "display line overflow"
  (e.g. floats)

