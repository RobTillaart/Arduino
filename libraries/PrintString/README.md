# PrintString

Arduino library to print to a String

# Description


PrintString is a class that buffers a number of print statements in a String.
This String can be requested to process later.

- buffer slowly generated data, and send it with minimum time between bytes
  e.g. to maximize packets for ethernet
- print to buffer to see how many chars the output is;
  use to prevent "display line overflow"
  (e.g. floats)
  
# Operational

See examples
