#ifndef __INPUT_H__
#define __INPUT_H__

// char* store_input(char* input);
int which_task(char* token);
char* check_correctness(char* token);
char* make_good(char* token);
int contains_io_pipe(char* input);

#endif