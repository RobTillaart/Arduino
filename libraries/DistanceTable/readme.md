# Distancetable

Arduino library to store a symmetrical distance table in less memory

## Description

The DistanceTable library is a class that stores a symmetrical distance table 
which is typically N x N entries in less memory space. 
It uses (N x (N-1))/2 ("in a triangle") as an eucledian distance table is 
symmetrical around its main diagonal. 
Furthermore as the main diagonal are all zero it does not need to be stored either.

An ATMEL328 (Arduino) can store a 30 x 30 matrix = 900 floats in 1740 bytes, 
where it typically would take 900 x 4 = 3600 bytes. 

Within the 2K RAM of an Arduino one could store normally a 21 x 21 matrix (1764 bytes).

## Operational

See examples.
