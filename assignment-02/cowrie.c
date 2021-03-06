// cowrie.c a simple shell


// PUT YOUR HEADER COMMENT HERE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

// PUT EXTRA `#include'S HERE
#include <spawn.h>
#include "cowrie.h"
#include "subset2.h"

// PUT EXTRA FUNCTION PROTOTYPES HERE
static void runPosix(char *path, char **words, char **env);

int main(void) {
    //ensure stdout is line-buffered during autotesting
    setlinebuf(stdout);

    // Environment variables are pointed to by `environ', an array of
    // strings terminated by a NULL value -- something like:
    //     { "VAR1=value", "VAR2=value", NULL }
    extern char **environ;

    // grab the `PATH' environment variable;
    // if it isn't set, use the default path defined above
    char *pathp;
    if ((pathp = getenv("PATH")) == NULL) {
        pathp = DEFAULT_PATH;
    }
    char **path = tokenize(pathp, ":", "");

    char *prompt = NULL;
    // if stdout is a terminal, print a prompt before reading a line of input
    if (isatty(1)) {
        prompt = INTERACTIVE_PROMPT;
    }

    // main loop: print prompt, read line, execute command
    while (1) {
        if (prompt) {
            fputs(prompt, stdout);
        }

        char line[MAX_LINE_CHARS];
        if (fgets(line, MAX_LINE_CHARS, stdin) == NULL) {
            break;
        }

        char **command_words = tokenize(line, WORD_SEPARATORS, SPECIAL_CHARS);
        execute_command(command_words, path, environ);
        free_tokens(command_words);

    }

    free_tokens(path);
    return 0;
}


//
// Execute a command, and wait until it finishes.
//
//  * `words': a NULL-terminated array of words from the input command line
//  * `path': a NULL-terminated array of directories to search in;
//  * `environment': a NULL-terminated array of environment variables.
//
void execute_command(char **words, char **path, char **environment) {
    assert(words != NULL);
    assert(path != NULL);
    assert(environment != NULL);

    char *program = words[0];

    if (program == NULL) {
        // nothing to do
        return;
    }

    if (strcmp(program, "exit") == 0) {
        do_exit(words);
        // do_exit will only return if there is an error
        return;
    }


    // from COMP1521 - week 09 lab
    // get HOME value
    char *homeEnv = getenv("HOME");
    if (homeEnv == NULL) {
        perror("HOME");
        return;
    }
    
    // set value of /.cowrie_history
    char *hist = ".cowrie_history";
    
    // construct complete pathname $HOME/.cowrie_history
    int pnLen = strlen(homeEnv) + strlen(hist) + 2;
    char pn[pnLen];
    snprintf(pn, pnLen, "%s/%s", homeEnv, hist);
    
    if (strcmp(program, "!") != 0) {
        appendHistory(words, pn);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //                                SUBSET 0                                //
    ////////////////////////////////////////////////////////////////////////////
    
    // cd (change directory)
    // if no argument is given, change to HOME environment
    if (strcmp(program, "cd") == 0) {
        char *newPath = words[1];
        char *home = getenv("HOME");
        if (newPath == NULL) {
            newPath = home;
        }
        if (chdir(newPath) != 0) {
            fprintf(stderr, "cd: %s: No such file or directory\n", newPath);
            return;
        }
        return;
    }
    
    // pwd (print current directory)
    if (strcmp(program, "pwd") == 0) {
        // code from COMP1521 - getcwd.c
        char pathname[MAX_PATH];
        if (getcwd(pathname, sizeof pathname) == NULL) {
            perror("getcwd");
            return;
        }
        printf("current directory is '%s'\n", pathname);
        return;
    }


    ////////////////////////////////////////////////////////////////////////////
    //                                SUBSET 2                                //
    ////////////////////////////////////////////////////////////////////////////
    
    if (strcmp(program, "history") == 0) {
        int num = 0;
        if (words[1] != NULL) {
            char *endptr;
            num = (int)strtol(words[1], &endptr, 10);
            if (*endptr != '\0') {
                fprintf(stderr, "%s: nonnumber: numeric argument required\n", program);
                return;
            }
            if (words[2] != NULL) {
                fprintf(stderr, "%s: too many arguments\n", program);
                return;
            }
        } else {
            num = 10;
        }
        history(num, pn);
        return;
    }
    
    if (strcmp(program, "!") == 0) {
        int line = 0;
        
        if (words[1] != NULL) {
            char *ptr;
            line = (int)strtol(words[1], &ptr, 10);
            if (*ptr != '\0') {
                fprintf(stderr, "!: %s: numeric argument required\n", words[1]);
                return;
            }
            if (words[2] != NULL) {
                fprintf(stderr, "!: too many arguments\n");
                return;
            }
        } else {
            line = lineCount(pn);
        }
        
        printExe(line, pn, path, environment);
        return;
    }

    ////////////////////////////////////////////////////////////////////////////
    //                                SUBSET 1                                //
    ////////////////////////////////////////////////////////////////////////////

    // search for command in path directories
    if (strrchr(program, '/') == NULL) {
        int i = 0;
        int exe = 0;
        while (path[i] != NULL) {
            int len = strlen(path[i]) + strlen(program) + 2;
            char exeProgram[len];
            snprintf(exeProgram, len, "%s/%s", path[i], program);
            exe = is_executable(exeProgram);
            
            if (exe == 1) {
                // posix_spawn
                runPosix(exeProgram, words, environment);
                break;
            }
            ++i;
        }
        if (exe == 0) {
            fprintf(stderr, "%s: command not found\n", program);
            return;
        }
    } else { // directly run the program
        // posix_spawn
        int exe = is_executable(program);
        if (exe == 1) {
            runPosix(program, words, environment);
        } else {
            fprintf(stderr, "%s: command not found\n", program);
            return;
        }
        return;
    }
}


// PUT EXTRA FUNCTIONS HERE
void runPosix(char *prog, char **words, char **env) {
    pid_t pid;
    
    if (posix_spawn(&pid, prog, NULL, NULL, words, env) != 0) {
        perror("spawn");
        return;
    }
    
    int exitStatus;
    if (waitpid(pid, &exitStatus, 0) == -1) {
        perror("waitpid");
        return;
    }
    printf("%s exit status = %d\n", prog, WEXITSTATUS(exitStatus));
    return;
}

//
// Implement the `exit' shell built-in, which exits the shell.
//
// Synopsis: exit [exit-status]
// Examples:
//     % exit
//     % exit 1
//
void do_exit(char **words) {
    int exit_status = 0;

    if (words[1] != NULL) {
        if (words[2] != NULL) {
            fprintf(stderr, "exit: too many arguments\n");
        } else {
            char *endptr;
            exit_status = (int)strtol(words[1], &endptr, 10);
            if (*endptr != '\0') {
                fprintf(stderr, "exit: %s: numeric argument required\n",
                        words[1]);
            }
        }
    }

    exit(exit_status);
}


//
// Check whether this process can execute a file.
// Use this function when searching through the directories
// in the path for an executable file
//
int is_executable(char *pathname) {
    struct stat s;
    return
        // does the file exist?
        stat(pathname, &s) == 0 &&
        // is the file a regular file?
        S_ISREG(s.st_mode) &&
        // can we execute it?
        faccessat(AT_FDCWD, pathname, X_OK, AT_EACCESS) == 0;
}


//
// Split a string 's' into pieces by any one of a set of separators.
//
// Returns an array of strings, with the last element being `NULL';
// The array itself, and the strings, are allocated with `malloc(3)';
// the provided `free_token' function can deallocate this.
//
char **tokenize(char *s, char *separators, char *special_chars) {
    size_t n_tokens = 0;
    // malloc array guaranteed to be big enough
    char **tokens = malloc((strlen(s) + 1) * sizeof *tokens);


    while (*s != '\0') {
        // We are pointing at zero or more of any of the separators.
        // Skip leading instances of the separators.
        s += strspn(s, separators);

        // Now, `s' points at one or more characters we want to keep.
        // The number of non-separator characters is the token length.
        //
        // Trailing separators after the last token mean that, at this
        // point, we are looking at the end of the string, so:
        if (*s == '\0') {
            break;
        }

        size_t token_length = strcspn(s, separators);
        size_t token_length_without_special_chars = strcspn(s, special_chars);
        if (token_length_without_special_chars == 0) {
            token_length_without_special_chars = 1;
        }
        if (token_length_without_special_chars < token_length) {
            token_length = token_length_without_special_chars;
        }
        char *token = strndup(s, token_length);
        assert(token != NULL);
        s += token_length;

        // Add this token.
        tokens[n_tokens] = token;
        n_tokens++;
    }

    tokens[n_tokens] = NULL;
    // shrink array to correct size
    tokens = realloc(tokens, (n_tokens + 1) * sizeof *tokens);

    return tokens;
}


//
// Free an array of strings as returned by `tokenize'.
//
void free_tokens(char **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}