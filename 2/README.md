The task is to develop a program to analyze the mutual position of two circles.

The input of your program are two circles. Each circle is given by its center point (x and y coordinates) and the radius. Thus, the input are 3 decimal numbers x y r for each circle.

The output of the program is the computed position of the circles. There might be a total of 6 answers:

* the two circles are identical,
* one circle is inside the other one,
* internal touch,
* the circles intersect,
* external touch,
* the circles lie outside each other.

The program decides the position and outputs one of the six variants. The exact output format is shown in sample runs below. Moreover, the size of the overlapping area is displayed where applicable. Note: the output line must be terminated by a newline (\n).

The program must test input data. If the input is invalid, the program detects it, it outputs an error message and terminates. If displayed, the error message must be displayed on standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:

* the coordinates are invalid (non-numeric values),
* the radius is invalid (non-numeric value),
* the radius is negative or zero.

