# Minishell

Welcome to our **Minishell** project! This project is part of the 42 curriculum and involves creating a minimalistic shell that mimics some of the functionalities of Bash.

## About

The **Minishell** project is designed to deepen your understanding of how shells work by implementing your own version of a basic shell. It includes handling of essential shell features such as command parsing, environment variables, and more.

## Features

- Command execution (e.g., `ls`, `echo`, etc.)
- Built-in commands like `cd`, `pwd`, `export`, `unset`, `env`, and `exit`
- Command line editing with history
- Handling of single and double quotes
- Redirections (`>`, `>>`, `<`, `<<`)
- Pipes (`|`)
- Environment variable management
- Error handling for invalid commands and syntax
- Signal handling (Ctrl-C, Ctrl-D, and Ctrl-\)

## Bonus Features

- Wildcards (e.g., `*.c`)
- Command substitution
- Support for logical operators (`&&`, `||`)

## Installation

To build and run **Minishell** on your local machine, follow these steps:

1. Clone the repository:
    ```
    git clone https://github.com/Geesama02/Minishell.git
    ```
2. Navigate to the project directory:
    ```
    cd minishell
    ```
3. Compile the project:
    ```
    make
    ```

## Usage

Once compiled, you can start the minishell by running:

```
./minishell
```

## Some commands to try:

As this project is made to mimic bash, you can try any commands you normally would try in bash.

If you really can't think of anything try some of the following.  You do have to enter each line separately as the program doesn't handle new lines.
```
ls -la | grep a | tr 'a-z' 'A-Z'
```

```
cat << EOF > file
cat file
rm file
```

```
ls | rev > file
cat file
rev file | cat
rm file
```

*to exit the program:*
```
exit
```

## Credit

This two-person project was done with [maglagal](https://github.com/MAROUAN17).
