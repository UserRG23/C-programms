The task is to develop a program that converts color from RGB format into hexadecimal format.

The input describes a color in the format rgb ( x, y, z ) where x, yr, and z are integers in range from 0 to 255. These numbers represent color values. The program converts this format into the hexadecimal format which starts with char # followed by 3 hexadecimal bytes (i.e., there is a total 6 hexadecimal digits, e.g., 200 -> C8). The input and output format is obvious from sample program runs (see below).

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below), and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output). The input is considered invalid, if:

* input does not start with string rgb,
* there is missing a comma or parenthesis,
* a color value is missing,
* a color value is not a valid number,
* a color value is not in range from 0 to 255.
