# Minishell

## Overview
Minishell is a simplified shell implementation project developed as part of the 42 Network curriculum. This project aims to recreate basic functionalities of a Unix shell, providing a command-line interface for users to interact with the operating system.

<p align="center">
  <img src="https://github.com/Serghini04/minishell/blob/master/intro.png" alt="Image Description" style="width: 80%;">
</p>

Minishell is more than just a project; it's a deep dive into the world of operating systems and command-line interfaces. This implementation challenges us to understand the intricacies of how shells work, from parsing user input to executing complex commands.

## Project Structure
- `builtins/`: Implementation of built-in shell commands
- `lib/`: Custom library functions
- `parser/`: Command parsing and tokenization
- `utils/`: Utility functions
- `wildcard/`: Wildcard expansion functionality
- `minishell.c`: Main program file
- `minishell.h`: Header file with function prototypes and structures
- `Makefile`: Build automation script

## Features
- Display a prompt when waiting for a new command.
- Working history functionality.
- Search and launch the right executable (based on the **PATH** variable or using a relative or absolute path).
- No more than one global variable.
- No interpretation of unclosed quotes or unnecessary special characters.
- Handling of single quotes **(')**, preventing interpretation of metacharacters in the quoted sequence.
- Handling of double quotes **(")** except for **$** (dollar sign) metacharacter.
- Redirections:
  - `<` redirects input.
  - `>` redirects output.
  - `<<` reads input until a line containing the delimiter is seen.
  - `>>` redirects output in append mode.
- Pipes `|` for command pipelines.
- Handling of environment variables (`$` followed by a sequence of characters) for expansion.
- Handling of `$?` for expanding the exit status of the most recently executed foreground pipeline.
- Handling of **ctrl-C**, **ctrl-D**, and **"ctrl-\\"** signals.
- Interactive mode behavior:
  - **ctrl-C**, displays a new prompt on a new line.
  - **ctrl-D** exits the shell.
  - **"ctrl-\\"** does nothing.
- Built-in commands:
  - `echo`: Display a line of text
  - `cd`: Change the current directory
  - `pwd`: Print working directory
  - `export`: Set environment variables
  - `unset`: Unset environment variables
  - `env`: Display environment variables
  - `exit`: Exit the shell
- Wildcard expansion (*).

## Collaboration
This project was developed collaboratively:
- Parsing, Wildcard expansion, and Variable expansion: [Mehdi Serghini](https://github.com/Serghini04)
- Command execution and Signal handling: [Hicham Driouch](https://github.com/paybat)

## Prerequisites
- GCC compiler
- Make
- readline library

## Building and Running
To build the project, use the provided Makefile:
```
make
```
To run the shell:
```
./minishell
```
<p align="center">
  <img src="https://github.com/Serghini04/minishell/blob/master/imgs/ScreenShot.png" alt="Image Description" style="width: 80%;">
</p>

## Usage
Once running, you can use the shell like any other command-line interface. Some examples:
```
$ ls -l
$ echo $HOME
$ cd /path/to/directory
$ ./custom_script.sh
```

## Theory

### What is a shell?

**Simple definition:** A shell is a way to talk to the computer using text commands instead of clicking on icons or menus. It's like a window into the computer's brain. There are different types of shells, but they all let to do things like open programs, move files, and change settings by typing in simple commands.

A shell refers to a command-line interface that allows users to interact with an operating system. It provides a way to access and control the various functions of an operating system using text commands rather than a graphical user interface.

<p align="center">
  <img src="https://github.com/Serghini04/minishell/blob/master/imgs/sh.png" alt="Image Description" style="width: 60%;">
</p>


### What is a GNU shell?

GNU shell, also known as Bash (short for "Bourne-again shell"), is a widely used command-line interface and scripting language for Unix-based operating systems. It is the default shell on most Linux distributions and is available on many other Unix-like systems.

### What are the steps to make the our Minishell?

<p align="center">
  <img src="https://github.com/Serghini04/minishell/blob/master/imgs/parsing.png" alt="Image Description" style="width: 80%;">
</p>

1. **Parser:**
The parser is responsible for breaking down the user input into individual tokens. It takes the raw command line and separates it into distinct components like commands, arguments, operators, and redirections. The parsed tokens are then used to construct the command structure for further processing and execution.
2. **Syntax Errors:**
We handled syntax errors in Minishell to provide informative feedback to the user when they enter an invalid command or have incorrect syntax. Proper error handling helps users identify and correct mistakes, making the shell more user-friendly.
3. **Expander:**
The expander module processes certain special characters and expansions in the command, such as environment variable expansion (e.g., **`$VAR`**) and command substitution (e.g., **`$(command)`**). It ensures that these expansions are resolved correctly before executing the command.
4. **Here Doc:**
Here documents (Here doc) are a type of input redirection in which data is provided directly into the standard input of a command from the script itself, using a delimiter to mark the end of the input. We implemented support for here documents, allowing users to provide input inline within the script or command line.
5. **Redirections:**
Redirections in our Minishell allow users to manipulate standard input, output, and error streams for commands. We implemented input redirection (**`<`**), output redirection (**`>`** and **`>>`**). These redirections enable users to work with files and customize command behavior.
6. **Signals:**
Signal handling is essential for maintaining the shell's responsiveness and user experience. We managed signals like **`SIGINT`** (usually triggered by pressing Ctrl+C) and  **`SIGQUIT`** (usually triggered by pressing Ctrl+D). Handling these signals allows users to interrupt or terminate running processes gracefully.
7. **Built-ins:**
Built-in commands are commands that are directly handled by the shell itself rather than invoking external executables. In Minishell, you implemented several built-in commands like **`cd`** for changing directories, **`echo`** with the **`n`** option to suppress newlines, **`pwd`** to print the current working directory, **`export`** to set environment variables, **`unset`** to remove environment variables, **`env`** to display environment variables, and **`exit`** to exit the shell.

### What is the function fork() ?

In C programming, the **`fork()`** function is used to create a new process by duplicating the calling process. The new process is referred to as the child process, while the original process is referred to as the parent process.

When **`fork()`** is called, a new process is created that is a copy of the calling process. Both processes then continue executing from the point where the **`fork()`** function was called. The new process gets its own unique process ID (PID), while the parent process retains its original PID.
<div align="center">
    <table >
     <!-- <tr>
        <td><b>Latest Tweets</b></td>
        <td><b>daily.dev</b></td>
     </tr> -->
     <tr>
       <td><img src="https://github.com/Serghini04/minishell/blob/master/imgs/fork1.png" width="300" alt="sunil sapkota twitter" > </img></td>
        <td><img src="https://github.com/Serghini04/minishell/blob/master/imgs/fork2.png" width="300" alt="sunil sapkota's Dev Card"/></td>
     </tr>
    </table>
    </div>

The child process and parent process run independently of each other and have their own memory space, CPU registers, and file descriptors. The child process can modify its own memory space, but any changes made by the child process do not affect the parent process.

### What is a pipe?

<div align="center">
        <td> <img src="https://github.com/Serghini04/minishell/blob/master/imgs/pipe.png" width="400" alt="sunil sapkota's Dev Card"/></td>
     </tr>
</div>

**Definition:** A pipe is a method for </ins>interprocess communication (IPC)</ins> that allows one process to send data to another process. A pipe consists of two ends, a read end and a write end. The write end is used to send data to the pipe, and the read end is used to receive data from the pipe.

**Simple Definition:** A pipe is like a tube that connects two processes or programs. One end of the pipe is used to send data and the other end is used to receive it.

### What is the function readline() ?

**Simple definition:** It is a library function in C that reads input from the user via the command line interface. It allows for more advanced user input handling, including features such as line editing and command history.

```c
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
int main() 
{
    char* input;
    while ((input = readline("Enter a command: ")) != NULL) {
        add_history(input);
        printf("You entered: %s\n", input);
        free(input);
    }
    return 0;
}
```

This program will repeatedly prompt the user to enter a command, read the input using **`readline`**, add the input to the command history using **`add_history`**, and then print the input to the console using **`printf`**. Finally, it frees the memory used by the input string with **`free`**.

**Readline library**

The readline library is a set of functions for command-line editing, history, and tab completion in a program.

- The **`readline`** function allows a program to read input from the user with advanced editing features.
- The **`rl_clear_history`** function **clears** the command **history**.
- The **`rl_on_new_line`** function informs readline that the **prompt has moved to a new line**.
- The **`rl_replace_line`** function replaces the current line with a new one.
- The **`rl_redisplay`** function redisplay the current line.
- The **`add_history`** function adds a line to the command history.

## Signals

### What is a sigaction?

**`struct sigaction`** is a data structure in C that represents a set of actions to be taken when a particular signal is delivered to a process. It is used with the **`sigaction()`** function to install a new signal handler or modify an existing handler for a specific signal.

The **`struct sigaction`** type contains the following fields:

- **`sa_handler`**: a pointer to the signal handler function, or one of two special values: **`SIG_DFL`** to set the default action for the signal or **`SIG_IGN`** to ignore the signal.
- **`sa_sigaction`**: an alternative signal handler function that provides additional information about the signal and its context.
- **`sa_flags`**: a set of flags that modify the behavior of the signal handler, such as **`SA_RESTART`** to ensure that system calls are automatically restarted after the signal is handled.
- **`sa_mask`**: a set of signals that are blocked while the signal handler is executing.
- **`sa_restorer`**: a pointer to an optional function that is called after the signal handler returns.

The **`sigaction()`** function takes a pointer to a **`struct sigaction`** object and installs or modifies the signal handler for the specified signal.

**Example:** When the program is executed, it installs the **`sigintHandler()`** as the signal handler for **`SIGINT`** (Ctrl+C).

```c
#include <stdio.h>
#include <signal.h>

// Signal handler function for SIGINT
void sigintHandler(int signum) {
    printf("Received SIGINT signal (Ctrl+C). Exiting...\n");
    // Perform cleanup or other necessary tasks before exiting
    // For this example, we'll simply terminate the program.
    exit(0);
}

int main() {
    struct sigaction sa;

    // Set the signal handler function
    sa.sa_handler = sigintHandler;
    // Clear sa_mask (no additional signals will be blocked during the signal handler execution)
    sigemptyset(&sa.sa_mask);
    // Set SA_RESTART flag to automatically restart system calls after the signal handler returns
    sa.sa_flags = SA_RESTART;
    // Install the signal handler for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }
    printf("Press Ctrl+C to trigger SIGINT...\n");
    // Infinite loop to keep the program running until Ctrl+C is pressed
    while (1) {
        // Do some work or wait for the signal
    }
    return 0;
}
```

When its pressed Ctrl+C in the terminal, the **`sigintHandler()`** function will be called, and it will print the message "Received SIGINT signal (Ctrl+C). Exiting..." before terminating the program gracefully.

Alternatively:

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler function for SIGINT
void handle_sign(int signum) {
    printf("Received SIGINT signal (Ctrl+C). Exiting...\n");
    // Perform cleanup or other necessary tasks before exiting
    // For this example, we'll simply terminate the program.
    exit(0);
}

int main() {
    // Install the signal handler for SIGINT using signal()
    signal(SIGINT, handle_sign);
    printf("Press Ctrl+C to trigger SIGINT...\n");
    // Infinite loop to keep the program running until Ctrl+C is pressed
    while (1) {
        // Do some work or wait for the signal
    }
    return 0;
}
```

## Documentation

[Short introduction to signals in C](https://www.youtube.com/watch?v=5We_HtLlAbs&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=16&pp=iAQB)

[minishell](https://harm-smits.github.io/42docs/projects/minishell#getting-started)

https://github.com/maiadegraaf/minishell

[https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

## Contributing
While this project is primarily an academic exercise, we welcome feedback and suggestions. Please open an issue if you encounter any bugs or have ideas for improvements.

## License
This project is part of the 42 Network curriculum and is subject to their academic policies.

## Acknowledgments
- 42 Network for the project subject and resources
- The developers of Bash and other Unix shells for inspiration
- [Hicham Driouch](https://github.com/paybat) for their work on command execution and signal handling
