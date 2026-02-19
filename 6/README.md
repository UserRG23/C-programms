The task is to develop a program that analyzes the reports from toll system cameras.

The toll collection system uses toll gates equipped with cameras. When a car passes the toll gate, the cameras take a photograph of the license plate (RZ in Czech). Subsequently, it checks that the car with that RZ paid for the toll. Moreover, secret service is planning to use the system to track cars with suspicious subjects. Your program helps secret services with the tracking.

The input of the program is a list of reports from the toll gate cameras. The list is enclosed in curly braces, individual reports are separated by commas. Each report has the following format: `camera_ID: RZ mon day hour:min where:`

* `camera_ID` is an integer that identifies the camera,
* `RZ` is a string with the car's license plate. The string may be any combination of characters, the only restrictions are length (max. 1000 chars) and spaces (the license plate must not contain any spaces),
* `mon` is the abbreviation of a month (i.e., one of: Jan, Feb, ..., Dec), first letter uppercase,
* `day` is the day of month (1, 2, ...),
* `hour` is the hour (0, 1, 2, ..., 23),
* `min` is the minute (0, 1, 2, ..., 59).

The order of the reports may be arbitrary. In particular, the reports do not have to be ordered by time. One RZ may be reported by several cameras at the same time. Moreover, there may exist duplicated reports where the same camera reports the same RZ at the same time in multiple reports. We keep all such reports.

Following the reports, there are search commands to process. Each search command has the format: RZ mon day hour:min, the meaning is the same as above. The search commands are not separated by any character, the search commands are processed until EOF is reached.

The output of the program are the results of the searches. There are three possible answers to a search command:

* the RZ is not known, there is no report,
* there is a report of the RZ, moreover, the search time and the report time matches. Then the program reports the cameras that reported the RZ in the given time. In addition to the list of camera IDs, there is the number of reports found. If there are duplicated reports (the same RZ, the same time, the same camera), then the camera ID is included multiple times in the answer. The camera IDs are sorted in an ascending order in the answer.
* there are reports of the given RZ, however, the time does not match. Then the program find the closest previous and the closest next report it knows. The formats of both is the same as the format for the exact match.

The program must test input data. If the input is invalid, the program detects it, it outputs an error message and terminates. If displayed, the error message must be displayed on standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:

* invalid camera ID (not an integer, missing),
* invalid RZ (missing, longer than 1000 characters),
* invalid month,
* invalid month day, only consider non-leap February,
* invalid hour/minute,
* any separator is missing (curly brace, comma, colon),
* no data in the list provided by cameras (empty list).
