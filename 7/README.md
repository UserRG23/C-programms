The task is to develop a program to search DNA samples in a database.

The program maintains a list of DNA samples. Each sample is a sequence of bases coded as characters A, T, C, and G. The sample is provided in the form of a string. The length of the strings is not limited, however, the length must be a multiple of 3 (3 bases form one triplet).

The program can search the DNA samples it knows. The program is given a string to search for (again, a list of bases A, T, C, and G). The result is a list of DNA samples that contain the searched string. Caution: the position in the DNA sample is important. The results list only DNA samples where the searched string is aligned on a triplet boundary.

The input is a list of DNA samples. Each sample is provided on a separate line. The line has the following form:

`frq:list_of_bases`

`frq` is a rational decimal number that denotes the sample frequency, this will be used to sort the results (see below). Following the colon, there is the DNA sample itself. The sample consists of characters A, T, C, and G. The length is not limited, however, the length must be a multiple of 3. There is an empty line that indicates the samples are done.

Following the empty line, the input contains strings to search for. Each string is provided on a separate line, each searched string contains only characters A, T, C, and G. The length is again unlimited, but the length must be a multiple of 3.

The output is the number of matched DNA samples and a list of the matched DNA samples. The searched string may be included in many DNA samples, the matched samples are listed in the descending order of frequency (parameter frq above). If the number of matched DNA samples exceeds 50, then the program lists only 50 DNA samples with the highest frequency (the other are counted, but not displayed).

The position is important when matching the DNA samples and the searched string. The string must start on a triplet boundary, i.e., on a multiple of 3. This is demonstrated in the example run. Searched string CCT is included in 4 DNA samples: ATAAGCCTA, GTACCTATAACA, CCCTATCCTTAG, and CCTCCCCCC. The output lists only samples GTACCTATAACA (position 3), CCTCCCCCC (position 0), and CCCTATCCTTAG (position 6, position 1 is not important). DNA sample ATAAGCCTA (position 5) is not included, 5 is not a multiple of 3.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below) and terminate. If displayed, the error message must be displayed on the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:

* frequency is missing or is invalid for a DNA sample,
* colon is missing in a DNA sample,
* DNA sample is invalid (must consist of characters A, T, C, and G, length must be a multiple of 3),
* no DNA samples were given,
* searched string is invalid (must consist of characters A, T, C, and G, length must be a multiple of 3).

Your program will be tested in a restricted environment. The testing environment limits running time and available memory. The exact time and memory limits are shown in the reference solution testing log. There are small inputs used in the mandatory tests, thus a reasonable implementation of the naive algorithm shall pass the mandatory tests. There are a bonus tests included, the bonus test input many DNA samples, the samples are long, and there are many/long search strings. An improved algorithm and a careful coding is required to pass the bonus test.
