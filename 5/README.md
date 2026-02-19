Your task is to develop a program that calculates fair distribution of maintenance of road system.

Assume there is a bypass road around a city. The bypass is divided into n sections, there is a maintenance cost known for each such section. The maintenance is assigned to two companies A and B. Each company is assigned a continuous part of the bypass. For example, if the bypass consists of 5 sections, then the sections may be divided as 0-2 + 3-4, 0-0 + 1-4, or 1-3 + 4-0. (A company may be assigned just one section, thus 0-0 is correct. The bypass is circular, thus sections 4-0 are continuous.) On the other hand, we cannot assign sections 0, 2, and 4 to the first company and sections 1 and 3 to the second company (the sections are not continuous). The goal is to assign the sections such that the sum of maintenance costs for the sections assigned to the first company is as close as possible to the sum of maintenance costs for the sections assigned to the second company.

The computation is slightly more complicated - the maintenance cost varies in time. For example, section 0 may have maintenance cost 20 per day, but starting from a certain date (e.g., 2025-01-01), the cost may increase to say 30 per day. The maintenance cost may be changed arbitrary number of times for each section. Thus, the sum of maintenance cost for given section in a given time interval must be aggregated from the daily maintenance cost over the given time interval.

The input of the program consists of two parts. First, there is a list of positive integers in curly braces, the integers are separated by commas. The list defines the daily maintenance cost for individual sections of the bypass, the costs are valid from 1900-01-01. Moreover, the length of this list defines the number of sections in our bypass (at least 2 sections, at most 10000 sections).

Following the list, there are commands to process. A command is either an update of the maintenance cost, or a request to compute the assignment of sections to the companies:

* `= date section: cost`

    sets the daily maintenance cost for the given section starting from date. The date is provided in the ISO format e.g., 2000-12-31. The dates in the update commands must form an increasing sequence. Integer section must fit the range from 0 to the last section in our bypass. Finally, cost is a positive integer (greater than 0). There is at most 300000 updates in the input.

* `? from to`

    a request to compute the assignment of sections to the companies such that the total cost paid to the first company is as close as possible to the total cost paid to the second company. There are two dates in the command, these dates define the time interval where the maintenance cost is computed. Both dates are given in the ISO format, moreover, date to must be greater or equal to date from. The time interval is closed, i.e., both boundary dates are included into the interval. The interval may be rather long, the maintenance cost for individual sections must be aggregated with respect to the cost changes in the interval.

The program displays output only for the assignment commands. The output is the difference in cost paid to the two companies and a total number of options to divide the segments such that the difference is the smallest possible. Following the two results, there is a list of options to assign the road sections. The list format is:

`* s1 - e1, s2 - e2`

where s1 - e1 are the sections assigned to the first company and s2 - e2 are the sections assigned to the second company. There may exist one, two, or even more such assignments, the program prints them all. The order of the possible assignments in the list is not defined (may be arbitrary). Moreover, assignments s1 - e1, s2 - e2 and s2 - e2, s1 - e1 are treated as identical, thus only one of them is printed in the list (any choice is fine).

If the input is invalid, the program detects the problem and prints an error message. The format of the error message is shown below. The following is considered invalid input:

* missing curly braces or commas in the list of daily maintenance cost,
* invalid daily maintenance cost (positive integer required),
* less than 2 sections in the bypass,
* more than 10000 sections in the bypass,
* invalid format of the maintenance update (missing equality sign or colon),
* invalid date format (ISO format required),
* invalid date (valid Gregorian date required),
* dates in maintenance updates must form an increasing sequence,
* invalid section in the maintenance cost update (0 or positive integer required, section number is limited by the bypass length),
* invalid daily maintenance cost (positive integer required),
* invalid format of the assignment command (missing question mark or dates),
* invalid date format (ISO format required),
* invalid date (valid Gregorian date required),
* invalid date interval in the assignment command (start date must be less than or equal to the end date).

If the program detects an error, it immediately stops asking for further input data, it prints out the error message and terminates. Thus, the program must validate input data as it reads it. Do not postpone the checks until the entire input is read. The error message shall be printed to the standard output (do not send it to the standard error output).

Your program will be tested in a restricted environment. The testing environment limits running time and available memory. The exact time and memory limits are shown in the reference solution testing log. There are various ways to solve the problem. A reasonable implementation of the naive algorithm passes all mandatory tests, yet it does not pass the optional and bonus tests. More efficient algorithms are needed to pass the optional / bonus tests:

* mandatory tests input few sections (tens) and few updates (tens),
* optional test inputs a bit more sections (hundreds) and significantly more updates (thousands or more),
* the first bonus test inputs many sections (thousands) and few changes (hundreds to thousand),
* the second bonus test inputs hundreds of sections and huge number of changes (hundreds of thousands).

