# DistanceTable Library

## Description

The DistanceTable library is a class that stores a distance table which is typically x * x entries
in less memory space. It uses x * (x-1)/2 ("in a triangle") as an eucledian distance table is 
symmetrical around its main diagonal. Furthermore the main diagonal are all zero.

An ATMEL328 (Arduino) can store a 30x30 matrix = 900 floats in 1740 bytes. Normally this amount 
would approx hold a 21x21 matrix (1764 bytes).

## Operational

Trivial, see examples.


