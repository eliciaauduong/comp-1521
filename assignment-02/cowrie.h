#define MAX_LINE_CHARS 1024
#define INTERACTIVE_PROMPT "cowrie> "
#define DEFAULT_PATH "/bin:/usr/bin"
#define WORD_SEPARATORS " \t\r\n"
#define DEFAULT_HISTORY_SHOWN 10

// These characters are always returned as single words
#define SPECIAL_CHARS "!><|"


// PUT EXTRA `#define'S HERE
#define MAX_PATH 10000
#define MAX_BUFF 100

void execute_command(char **words, char **path, char **environment);
void do_exit(char **words);
int is_executable(char *pathname);
char **tokenize(char *s, char *separators, char *special_chars);
void free_tokens(char **tokens);