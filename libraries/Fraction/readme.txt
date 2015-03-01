
Fraction is an experimental fraction library for the Arduino.
The code is working with a number of limitations among others:
- denominator is max 4 digits to keep code for multiply and divide simple
- therefore not all fractions are exact
- the range of numbers supported is limited.

That said, the library is useful e.g. to display float numbers as a fraction.
From programming point of view the fractionize function, converting a double
into a fraction is a nice programming problem, fast with a minimal error.

In short, use fractions with care otherwise your sketch might get broken ;)