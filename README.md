# C-Shell: A Custom Unix Shell

C-Shell is a custom Unix shell implemented in C that replicates many of the core functionalities of standard shells like bash or zsh. It provides a custom prompt, supports a range of built-in commands, handles system commands, and includes advanced features like I/O redirection, piping, and process management.

Implemented as part of Operating Systems and Networks course at IIIT Hyderabad (Monsoon 2023).

---

## Features

### 1. Interactive Prompt
The shell displays a dynamic and informative prompt that includes the **username**, **system name**, and the **current working directory**. The prompt is color-coded for better readability. The path is abbreviated with `~` to represent the home directory, making it clean and concise.

### 2. Command Handling
- **User-Defined Commands:** A suite of custom commands implemented from scratch (see list below).
- **System Commands:** Seamlessly executes any system command found in your system's PATH (e.g., `ls`, `cat`, `grep`) using `execvp`.
- **Multiple Commands:** Supports executing multiple commands in a single line, separated by semicolons (`;`).

### 3. Process Management
- **Foreground and Background Processes:** Run processes in the foreground (blocking) or background (non-blocking) by appending an `&` to the command.
- **`fg` and `bg` Commands:** Move background processes to the foreground and resume stopped background processes.
- **`activities` Command:** Lists all currently running and stopped background jobs, sorted alphabetically, with their PIDs and current status.
- **`ping` Command:** Send signals to a specified process using its PID.
- **Signal Handling:**
  - **`Ctrl+C`**: Interrupts the current foreground process.
  - **`Ctrl+Z`**: Stops the current foreground process and moves it to the background.
  - **`Ctrl+D`**: Logs out of the C-Shell.

### 4. I/O Redirection and Piping
- **Input/Output Redirection:** Redirect input (`<`), output (`>`), and append output (`>>`) for any command.
- **Piping:** Chain multiple commands together using pipes (`|`), allowing the output of one command to serve as the input for the next. This is supported for both user-defined and system commands.

### 5. Command History (`pastevents`)
- A robust command history feature that automatically saves the last 15 unique commands to a file.
- `pastevents`: Display the command history.
- `pastevents purge`: Clear the entire command history.
- `pastevents execute <n>`: Execute the *n*th command from the end of the history.

### 6. Additional Utilities
- **`iMan`**: Fetches and displays the man page for any command directly from the internet by making an HTTP request to `man.he.net`.
- **`neonate`**: Periodically prints the PID of the most recently created process on the system until the 'x' key is pressed.

---

## Custom Commands Implemented

| Command | Description |
|---|---|
| `warp <dir>` | A custom `cd` command. Navigates the file system. Supports absolute and relative paths, `~` for home, and `-` for the previous directory. |
| `peek <dir>` | A custom `ls` command. Lists files and directories with color-coded output: **blue for directories**, **green for executables**, and **white for files**. Supports `-l` (long listing) and `-a` (show hidden files) flags. |
| `seek <search> <dir>` | Recursively searches for a file or directory named `<search>` within the specified `<dir>`. Supports flags: `-d` (search for directories only), `-f` (search for files only), and `-e` (if exactly one match is found, execute it or open it). |
| `proclore <pid>` | Displays detailed information about a process, including its PID, status (Running, Stopped, etc.), process group, virtual memory usage, and the path to its executable. If no PID is provided, it shows details for the shell itself. |
| `activities` | Lists all background processes spawned by the shell, displaying their PID, command name, and current state (Running or Stopped). |
| `ping <pid> <signal>` | Sends a specified signal to a process. |
| `fg <pid>` | Brings a background process to the foreground. |
| `bg <pid>` | Resumes a stopped background process. |
| `iMan <command>` | Displays the manual page for a given command. |
| `neonate -n <time>` | Prints the most recent process ID every `<time>` seconds. |

---

## How to Compile and Run

1.  **Clone the repository:**
    ```bash
    git clone <your-repo-link>
    cd c-shell/code
    ```

2.  **Compile the source code using the provided Makefile:**
    ```bash
    make
    ```

3.  **Run the shell:**
    ```bash
    ./a.out
    ```
Now you can start typing commands into your very own C-Shell!

---

#### Assumptions

1. In case of warp into invalid directory, the path with invalid address is printed but you stay in the same directory: this was corrected and now an error message is printed

2. Invalid commands in normal execution i.e. without piping prints Exec failed and this happens during piping also i.e. the invalid command isnt ignored eg: sleep 5 | echo hello | grhgeb | wc gives Exec failed

3. Time of the foreground process is not printed along with prompt instead it's printed before the prompt

4. In case invalid command in typed, error handling is done

5. All background processes get killed with CTRL+C and they exit abnormally

6. Neonate prints latest pids along with a newline