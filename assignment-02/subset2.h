// save every command executed
void appendHistory(char **command, char *pathname);

// count the number of lines in $HOME/.cowrie_history
int lineCount(char *pathname);

// add a built-in command history n which prints the last n commands
// if n is not specified it should default to 10
void history(int last, char *pathname);

// add a built-in command ! n which prints command n and then executes it
// if n is not specified the last command should be executed and printed
void printExe(int command, char *pathname, char **path, char **environ);