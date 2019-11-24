#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// save every command executed
void appendHistory(char **command);

// add a built-in command history n which prints the last n commands
// if n is not specified it should default to 10
void history(int last);

// count the number of lines in $HOME/.cowrie_history
static int lineCount(void);