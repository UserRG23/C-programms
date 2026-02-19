The task is to implement functions (not a whole program, just functions) which help counting Fridays the 13th.

Friday 13 is traditionally perceived as an unhappy day. Of course this is a superstition, but one shall proceed with caution when it is the 13th Friday 13 in his/her life. Or when there is a Progtest homework assigned after Friday 13. Thus we develop functions that help counting Fridays the 13th.

The assignment requires 3 functions. The functions find the previous/next Friday the 13th and count Fridays the 13th in a given time interval. The functions use dates, the dates are implemented as a structure composed of year, month, and day. The interface of the functions is dictated by the testing environment, your implementation must follow it:

* `countFriday13 ( from, to, cnt )`

    he function counts Fridays the 13th in the given time interval. The interval is given by the two dates from and to, both boundaries are included. Each boundary is a date, thus it is defined by a three-tuple year/month/day. The function saves the computed number of Fridays into the output parameter cnt. Return value is true (success) or false (failure). The function fails if:

    - date from is invalid (see notes below),
    - date to is invalid,
    - from and to do not form a valid interval (date to is before date from).

* `prevFriday13 ( x )`

    the function finds the closest Friday the 13th that precedes date x. The date is stored into the input-output parameter x. Return value is true (success) or false (failure). The function fails if date x is invalid or if the computed Friday the 13th falls before 1.1.1900. 

* `nextFriday13 ( x )`

    the function finds the closest Friday the 13th that follows date x. The date is stored into the input-output parameter x. Return value is true (success) or false (failure). The function fails if date x is invalid. 

* `TDATE`

    the structure describes a date, it contains fields year, month, and day. The structure is used in the above functions to pass dates, thus your implementation must use it. The structure is declared in the testing environment and is provided in the attached source. Your implementation must use the declarations as it is.

* `makeDate (y, m, d)`

    an auxiliary function that eases the initialization of structure TDATE. The function is implemented in the testing environment and is included in the attached source. The function is used in the example tests, you may use the function in your implementation it you find it useful.

* `equalDate (d1, d2)`

    an auxiliary function to compare two dates for exact match. The function is implemented in the testing environment and is included in the attached source. The function is used in the example tests, you may use the function in your implementation it you find it useful.

The functions above fail if the parameters define an invalid date. Valid dates are:

* year must be greater or equal to 1900,
* month is valid (1 to 12),
* day is valid (1 to the number of days in the month),
* leap years must be handled correctly.

Submit a source file with the implementation of the required functions. The functions will be called from the testing environment, thus, it is important to adhere to the required interface. Use the attached source as a basis for your development, complete missing function bodies and add your required auxiliary functions. There is an example main with some test in the attached source. These values will be used in the basic test. Please note the header files as well as main is nested in a conditional compile block (#ifdef/#endif). Please keep these conditional compile block in place. They are present to simplify the development. When compiling on your computer, the headers and main will be present as usual. On the other hand, the header and main will "disappear" when compiled by Progtest. Thus, your testing main will not interfere with the testing environment's main.

We assume standard Gregorian calendar when counting days. Thus, there is a fixed number of days (30/31) in a month, with the exception of February. February is either 28 days (non-leap year) or 29 days (a leap year). The leap year rules of Gregorian calendar are:

1. years are not leap years in general,
2. except multiples of 4 which are leap years,
3. except multiples of 100 which are not leap years,
4. except multiples of 400 which are leap years,
5. except multiples of 4000 which are not leap years.

Thus, years 1901, 1902, 1903, 1905, ... are not leap years (rule #1), years 1904, 1908, ..., 1996, 2004, ... are leap years (rule #2), years 1700, 1800, 1900, 2100, ... are not leap years (rule #3), years 1600, 2000, 2400, ..., 3600, 4400, ... are leap years (rule #4), and years 4000, 8000, ... are not leap years (rule #5).

Your function will be executed in a limited environment. There are limits on both time and memory. The exact limits are shown in the test log of the reference. The time limits are set such that a correct implementation of the naive solution passes all mandatory tests. Thus, the solution may be awarded nominal 100% percent. The algorithm must be improved to pass the bonus tests and gain the extra points. There are long intervals tested in the bonus tests (years exceed 4000 several orders of magnitude).

