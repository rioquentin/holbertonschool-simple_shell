#include "main.h"

#define MAX_INPUT_SIZE 1024

/**
 * execute_command - Execute a command
 * @command: The command to execute
 * @program_name: The name of the program
 */

void execute_command(char *command, char *program_name) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
    } else if (pid == 0) {
        char **args = (char **)malloc(2 * sizeof(char *));
        if (args == NULL) {
            perror("malloc");
            _exit(EXIT_FAILURE);
        }
        args[0] = command;
        args[1] = NULL;

        execve(command, args, NULL);
        fprintf(stderr, "%s: No such file or directory\n", program_name);
        free(args);
        _exit(EXIT_FAILURE);
    } else {
        waitpid(pid, NULL, 0);
    }
}

/**
 * main - Entry point
 * @argc: The number of command line arguments
 * @argv: The command line arguments
 * 
 * Return: 0 on success, 1 on failure
 */

int main(int argc, char *argv[]) {
    char input[MAX_INPUT_SIZE];

    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("$ ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            if (feof(stdin)) {
                printf("\n");
                break;
            }
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        execute_command(input, argv[0]);
    }

    return 0;
}