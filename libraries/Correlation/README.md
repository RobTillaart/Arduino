# Correlation

Arduino Library to determine linear correlation between X and Y dataset

# Description

This library calculates the coefficients of the linear correlation 
between two (relative small) datasets. The size of these datasets is 
20 by default, but this can be set in the .h file.

The formula of the correlation is expressed as **Y = A + B \* X**,
Use with care.

### Interface

The main functions of the class are 

**add(x, y)** adds a pair of **floats** to the internal storage. 
In the future the constructor should get a TYPE parameter, as this
allows smaller datatypes to be analyzed taking less memory.

**count()** returns the amount of items in the internal arrays.

**clear()** resets the datastructure to clean condition.

**setRunningCorrelation(true | false)** sets the internal variable 
runningMode which allows **add()** to overwrite old elements in the
internal arrays. This way the correlation will be calculated over
the last N elements.

**calculate()** does the math to calculate the correlation parameters
A B and R

**getA()** returns the A parameter of formula **Y = A + B \* X**

**getB()** returns the B parameter of formula **Y = A + B \* X**

**getR()** returns the correlation coefficient R. The closer to 0 the less
correlation there is between X and Y. Correlation can be positive
or negative. Most often the **sqr(R)** is used 

**getRsquare()** returns the **sqr(R)** which is always between 0.. 1.

** getEsquare()** returns the error squared to get an indication of the
quality of the relation

**getEstimateX(y)** and **getEstimateY(x)** are used to calculate the
estimated values for a certain y or x value.

# Operation 

See example
