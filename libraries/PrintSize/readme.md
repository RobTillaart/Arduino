# PrintSize

Arduino library to determine the length of print statements

# Description

PrintSize is a minimal library to determine the length of a variable when printed.
This includes printing of floats, integers in decimal or hex notation.

Works for  **print()**, **println()** and if supported **printf()** e.g. ESP32.

Finally since **0.2.0** it has a total counter to add up the characters "printed" since
the last **reset()** call. (see example)

# Operational

Example shows the right alignment of 10 random numbers

Example shows (elementary) line fitting

Can be used to calculate the needed space.
 - to properly do a right alignment e.g. for numbers or variable text
 - do left alignement and overwrite previous output with just enough spaces.
 - centering of numbers
 - see if output will fit into a line / display
