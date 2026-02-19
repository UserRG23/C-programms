The task is to develop a program to compute the number of required railroad tracks to build a railroad of given length.

We assume that our railroad track supplier produces railroad tracks of two different lengths. The task is to compute the required number of railroad tracks (for both lengths) to build a railroad track of given length. The problem is a bit more complicated since railroad tracks must be used unmodified, i.e. they cannot be cut.

The input of the program are the two lengths of the railroad tracks. The lengths are actually different. Then there follows the length of the railroad to build. Moreover, the input may be of two kinds:

* `- length` in this case the program computes the total number of different ways to combine the railroad tracks,
* `+ length` in this case the program computes the total number of different ways to combine the railroad tracks and it shall list them.

The output of the program is the total number of combinations how to combine the railroad tracks, and (in the case of + length input) the list of all such combinations. The exact output format is shown in the sample runs below. There may be input where the railroad tracks cannot be combined such that the sum result in the required length. In such case the program shall provide the special output (see below). Anyway, the answer is printed with a newline character (\n) at the end.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below) and terminate. If displayed, the error message must be displayed on the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:

* the lengths of the railroad tracks are invalid (not numbers, negative, zero, or both the same),
* the length of the railroad is specified without the +/- indicators, or the indicator was not +/-,
* the length of the railroad is not a number or is negative.

Mandatory tests use small lengths, thus the problem can be solved using naive algorithm that just checks all possible combinations. If the program displays the complete list of combinations (the + mode), the algorithm cannot be significantly optimized. On the other hand, if the complete list is not displayed (the - mode), the computation may be optimized to work significantly faster. There is abonus test that checks the speed of your implementation in the - mode. An improved algorithm must be used to pass the bonus test. Since big numbers are used in the bonus test, the naive algorithm is very slow.
