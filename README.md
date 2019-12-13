# WIndows SHell (WinShell)
By Jason Wu and Julian Wong

### Features implemented by WISH

* Running singular commands (including cd and exit)
* Running multiple commands separated by one or more semicolons
* Simple redirection using > and <

### Features unsuccessfully implemented

* (Expected as of 11:31pm December 11, subject to change) Pipes

### Bugs present in the shell

* Putting a space in front of and behind semicolons may result in commands not executed properly.
  * `echo 1 ; echo 2` will result in `echo 2` failing, but `echo 1;echo 2` will work.
* Multiple semicolons would also cause errors.
  * `echo 1;;echo 2` would result in an error message between executions of `echo 1` and `echo 2`.

### Function Headers

parse.c

    struct parse_output parse_args()
    Inputs: char * line
    Returns: A struct containing an array of string tokens, 
    as well as a few other useful bits of data.

    The function turns an input line into a series of tokens separated by a specified delimiter.

    -----------

    void run_cmds()
    Inputs: The struct returned from parse_args, as well as a parentPID int.
    Returns: None.

    The function creates a child, which runs execvp(), returns an error message if any, and ends.

main.c

    Handles the command processing and execution.
