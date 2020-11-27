
# Radar

Arduino library for a pan tilt radar based upon 2 servo's.

## Warning
**WARNING: not extensively tested**
There are stil a lot of things to be tested. 
The example code is now working to show the concept.

## Description

radar is a concept library not elaborated yet that implements a Ping))) based Radar
with the use of two pan/tilt servo's. It was written after a question on the forum but 
never finished or tested it. Still, it has some interesting concepts wrt determine 
the position of pan/tilt while in progress. 

The idea is that one knows how fast the pan and tilt servos are working in degrees per second.
From that number and the start moment one can determine approximately its position. 

Given its position while moving is interesting for radar purposes as one can determine e.g.
in which direction a ping is given and which distance belongs to which pair of angles.

## Interface

TODO - see radar.h file

- **RADAR(pan, tilt)** define pan / tilt pins of the radar. These should be PWM pins.




RADAR_POSITIONS

## Operation

See examples






