# Description

1. display: prompt in red, file names in white, directories in blue, executibles in green

2. functionalities: 
    a. commands like warp, seek, peek, proclore, pastevents are implemented from scratch
    b. system commands are also implemented using execvp
    c. piping and i/o redirection is implemented for both system and user defined commands
    d. iMan is implemented using man.he.net
    e. activities ping and fg bg are implemented along with interrupts CTRL+C CTRL+D CTRL+Z
    f. neonate is implemented 

# Assumptions

1. in case of warp into invalid directory, the path with invalid address is printed but you stay in the same directory: this was corrected and now an error message is printed

2. invalid commands in normal execution i.e. without piping prints Exec failed and this happens during piping also i.e. the invalid command isnt ignored eg: sleep 5 | echo hello | grhgeb | wc gives Exec failed

3. time of the foreground process is not printed along with prompt instead it's printed before the prompt

4. in case invalid command in typed, error handling is done 

5. all background processes get killed with CTRL+C and they exit abnormally

6. neonate prints latest pids along with a newline 