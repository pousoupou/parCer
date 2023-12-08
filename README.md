# parCer
A simple txt parser written in C

# under construction
*name is subject to change (hopefully to something more clever)*

# Usage:
./parcer [DELIMITER] [OPTIONS] [FILE]

## Delimiter
An ASCII character to delimit the text, enclosed in either "" or ''
_if delimiter is not SPACE (ASCII code: 32), you can skip the marks_

## Options
-t : trim every token of any non-alphanumeric character (if any) at its start and end
