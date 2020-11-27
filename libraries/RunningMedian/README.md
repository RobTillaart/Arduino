# RunningMedian
Arduino library to determine the running median by means of a circular buffer.

## Description

Running Median looks like a running average with a small but important twist.
Running average averages the last N samples while the running median takes 
the last N samples, sort them and take the middle one, or the average of the middle two.

Important differences between running average and running median:
- Running median will return real data (e.g. a real sample from a sensor) 
if one uses an odd size of the buffer (preferred).
Running average may return a value that is never sampled.
- Running median will give zero weight to outliers, and 100% to the middle sample, 
whereas running average gives the same weight to all samples.
- Running median will give often constant values for some time.
- As one knows the values in the buffer one can predict to some extend how much 
the next samples will change the running median. 
- Running median is a bit harder as one needs to keep the values in order 
to remove the oldest and keep them sorted to be able to select the median.

## Operation

See examples
