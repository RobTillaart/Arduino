# Fraction

Arduino library to implement a Fraction datatype (experimental)

## Description

The fraction library implements fractional numbers a.k.a. Q, 
(integers are Z and floats/doubles are R),
and the conversion to floats.

The code is working with a number of limitations among others:
- denominator is max 4 digits to keep code for multiply and divide simple
- Fractions are not exact (even floats are not exact)
- the range of numbers supported is limited.
- code is experimental still.

That said, the library is useful e.g. to display float numbers as a fraction.
From programming point of view the fractionize function, converting a double
into a fraction is a nice programming problem, fast with a minimal error.

In short, use fractions with care otherwise your sketch might get broken ;)

## Operations

See examples

## Use with care

The library is reasonably tested, and if problems arise please let me know.

