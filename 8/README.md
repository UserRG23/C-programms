The task is to develop a program that solves mathematical puzzles.

Assume a mathematical puzzle. There is a sequence of decimal digits. The problem is to place mathematical operators +, -, and * somewhere into the sequence such that the resulting expression is valid and evaluates to the given value. There may exist more than one way to place the operators to evaluate the given value. We want to find all possibilities in such case.

Example: the input sequence is 1234. The problem is to place the operators such that the result is 10 (the first problem), 5, and 11 (another problems). There are two solutions of the first problem:

> 1+2+3+4 = 10
>
> 1*2*3+4 = 10

there is just one solution to the second problem:

> 12-3+4 = 5

finally, there are 3 solutions of the last problem:

> 1-2+3*4 = 11
>
> 1+2*3+4 = 11
>
> 12+3-4  = 11

Please note that we are not obligated to place operators between each digit pair - we may leave two digits adjacent to form a bigger number (e.g., number 12 in the example). Next, note that the generator/evaluator respects the priorities (addition and subtraction vs. multiplication and division). Finally, note that we may place operators anywhere in the sequence, however, we cannot shuffle the digits in the sequence.

The input consists of the digit sequence and a list of problems to solve. The digit sequence is given first. The sequence must be formed by digits 0-9, the length is limited to 12 digits. Following the sequence, there is a list of problems. The problems are of two kinds:

* `? num`, find all possible ways to place the operators into the digit sequence such that the expression evaluates to result num. The program prints out all such solutions (see the example runs). Finally, the program prints out the total number of such solutions.
* `# num`, the problem is identical, however the program does not print the solutions. The program prints out only the total number of solutions.

The output of the program is the list of possible solutions (problems of kind ?) and the total number of such solutions. Each solution is printed on a separate line and starts with = character. The order of solutions in the output is not given, the testing environment fixes the order before the comparison.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below) and terminate. If displayed, the error message must be displayed on the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:

* the sequence of digits was not given or is invalid (must contain characters 0-9 only),
* the sequence of digits is too long (12 digits maximum),
* the problem kind is not recognized (only ? and # are valid),
* the expected result is not a valid integer.

Your program will be tested in a restricted environment. The testing environment limits running time and available memory. The exact time and memory limits are shown in the reference solution testing log. We expect you to start with the "brute force" solution. That is, try all possible options to place the operators in the digit sequence. This solution is very inefficient (that is the reason for the short digit sequences). Nevertheless, the implementation must be reasonably efficient. For example, the program generates many expressions that must be evaluated. Thus, it may be a good idea to evaluate the expression as you generate it.

The mandatory tests input reasonably small problems (limited digit sequence, few problems to solve). There is a bonus test included, the test includes a bit longer input sequence and really many problems to solve. Thus, some preprocessing may be beneficial here. There is enough memory to save additional data. Next, bonus test only enters problems of kind # (it would take a lot of time to print out all solutions).
