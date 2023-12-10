# parCer
A simple txt parser written in C

# under construction
*name is subject to change (hopefully to something more clever)*

# Usage:
./parcer [DELIMITER] [OPTIONS] [FILE] [FILE]

## Delimiter
An ASCII character to delimit the text
- -d " " _or_ -d ' '
will set the delimiter to SPACE  
_if delimiter is not SPACE (ASCII code: 32), you can skip the marks_

## Options
- -l : print a simple log in the terminal when the file is parsed
- -n : write each token in a new line instead of in the same line
- -t : trim every token of any non-alphanumeric character (if any) at its start and end
 