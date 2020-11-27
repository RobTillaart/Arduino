# RunningAverage

Arduino library to calculate the running average by means of a circular buffer.

## Description
The RunningAverage object gives a running average of the last N numbers, giving them
all equal weight. This is doen by adding new data to an internal circular buffer, 
removing the oldest and replace it by the newest. The size of the internal buffer 

By keeping track of the **_sum** the runningAverage can be calculated fast (only 1 division).
This is done with **getFastAverage()**. 
However the constant adding/subtracting when adding new elements introduces an accumulating error. 
In tests adding up to 1500000 numbers this error was always small. But that is no proof.
In version 0.2.16 there is a fix added that uses the calculation of the sum in **getAverage()** to 
update the internal **_sum**.

## Operation

See examples
