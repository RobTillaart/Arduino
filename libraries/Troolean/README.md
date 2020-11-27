# Troolean

Arduino Library for a three state logic datatype supporting {True False Unknown}

# Description

Troolean is a datatype that implements three state logic with the values 
{True False Unknown }

Logic operators are similar to boolean and behave the same for the familiar boolean values.

Trooleans can be used e.g. to indicate a value is valid, invald or unknown to be valid or not.
Imagine a monitoring application which has different sensors e.g. temperature. If the sensor 
is sampled less than 1 minute ago one could say the value is valid, if the last sample is taken 
more than an hour ago it could be changed (a lot) or not. So one does not know if the temperature
has become invalid or not. Boolean logic would make it invalid, but troolean allows to state we
just don't know. As long as there is no urgency ( a customer that needs a valid value) 
one does not need to resample yet.

See also https://en.wikipedia.org/wiki/Three-valued_logic

# Operation

See examples

