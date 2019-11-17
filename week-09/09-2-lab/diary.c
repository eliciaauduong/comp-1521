////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  diary.c                                                                   //
//  -----                                                                     //
//  Write a C program, diary.c, which appends 1 line to $HOME/.diary.         //
//  The line should be its command-line arguments separated by a space        //
//  followed by a '\n'.                                                       //
//  diary.c should print nothing on stdout. It should only append to          // 
//  $HOME/.diary.                                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {

    // get HOME value
    char *homeEnv = getenv("HOME");
    if (homeEnv == NULL) {
        perror("HOME");
        return 1;
    }
    
    // set value of /.diary
    char *diary = ".diary";
    
    // construct complete pathname $HOME/.diary
    int len = strlen(homeEnv) + strlen(diary) + 2;
    char pathname[len];
    snprintf(pathname, len, "%s/%s", homeEnv, diary);

    // open file to append
    FILE *f = fopen(pathname, "a");
    
    // add each argument to $HOME./diary
    for (int i = 1; i < argc; ++i) {
        fprintf(f, "%s ", argv[i]);    
    }
    
    // add newline
    fprintf(f, "\n"); 
    
    // close file
    fclose(f);

    return 0;
}