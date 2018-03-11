#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "virtualmachine.h"



int main() {
    CommandLine commandLines[100];
    CommandLine *commandLine = compile(commandLines);
    /*printCommands(commandLine);*/
    VirtualMachine vm = loadVm();
    execute(vm, commandLine);
    return 0;
}

void printVmState(VirtualMachine vm) {
    int i,j;
    printf("REGISTERS:\n");
    printf("%-25s+%04d\n", "accumulator", vm.accumulator);
    printf("%-27s %02d\n", "instructionCounter", vm.instructionCounter);
    printf("%-25s+%04d\n", "instructionRegister", vm.instructionRegister);
    printf("%-27s %02d\n", "operationCode", vm.operationCode);
    printf("%-27s %02d\n", "operand", vm.operand);
    printf("MEMORY:\n");
    printf("%8d%6d%6d%6d%6d%6d%6d%6d%6d%6d\n",0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    for (i = 0; i < 10; i++) {
        printf("%2d ", i * 10);
        for (j = 0; j < 10; j++) {
            printf("%+05i ", vm.memory[i][j]);
        }
        printf("\n");
    }
}

void execute(VirtualMachine vm, CommandLine commandLines[100]) {
    int i;
    /* handoff stdin to the vm */
    stdin = fopen("/dev/tty", "r");
    for (i = 0; i < 100; ++i) {
        if (commandLines[i].index == -1) {
            break;
        }
        printf("Command [ Index: %ld, Instruction: %s, Address: %ld ]\n", commandLines[i].index,
               commandLines[i].instruction, commandLines[i].address);
        executeInstruction(vm, commandLines[i]);
    }
}

VirtualMachine loadVm() {
    VirtualMachine vm = { 0 };
    memset(vm.memory, 0, strlen(vm.memory[0]));
    return vm;
}

void executeInstruction(VirtualMachine vm, CommandLine commandLine) {
    char* instruction = commandLine.instruction;
    if (strcmp("READ",instruction) == 0) {
        vmRead(&vm, commandLine);
    } else if (strcmp("WRIT",instruction) == 0) {
        vmWrite(vm, commandLine);
    } else if (strcmp("PRNT", instruction) == 0) {
    } else if (strcmp("LOAD", instruction) == 0) {
    } else if (strcmp("STOR", instruction) == 0) {
    } else if (strcmp("SET", instruction) == 0) {
    } else if (strcmp("ADD", instruction) == 0) {
    } else if (strcmp("SUB", instruction) == 0) {
    } else if (strcmp("DIV", instruction) == 0) {
    } else if (strcmp("MULT", instruction) == 0) {
    } else if (strcmp("MOD", instruction) == 0) {
    } else if (strcmp("BRAN", instruction) == 0) {
    } else if (strcmp("BRNG", instruction) == 0) {
    } else if (strcmp("BRZR", instruction) == 0) {
    } else if (strcmp("HALT", instruction) == 0) {
        vmHalt(vm);
    } else {
        /* if anything reaches this point, it's a bogus instruction */
        printf("Unrecognized instruction: %s\n", instruction);
        exit(1);
    }
}

void vmRead(VirtualMachine *vm, CommandLine commandLine) {
    char input[3];
    int j;
    int y = (int) (commandLine.address % 10);
    commandLine.address /= 10;
    int x = (int) (commandLine.address % 10);
    fgets(input, sizeof(input), stdin);
    /* trim the newline */
    input[strcspn(input, "\n")] = 0;
    printf("Writing %s to %ld\n", input, commandLine.address);
    printf("coords: %d,%d", x, y);
    /*strcpy(vm.memory[x][y], input);*/
    /*vm->memory[x][y] = input;*/

}

void vmWrite(VirtualMachine vm, CommandLine commandLine) {
    printf("%s\n", vm.memory[commandLine.address]);
}

void vmHalt(VirtualMachine vm) {
    printVmState(vm);
    exit(0);
}

CommandLine *compile(CommandLine commandLines[100]) {
    int i = 0;
    char string[100];
    CommandLine marker = {-1, {'\0'}, -1};
    while (fgets(string, sizeof(string), stdin)) {
        CommandLine commandLine = getCommand(string);
        commandLines[i] = commandLine;
        i++;
    }
    commandLines[i] = marker;
    return commandLines;
}

void printCommands(CommandLine commandLines[100]) {
    int i;
    for (i = 0; i < 100; ++i) {
        if (commandLines[i].index == -1) {
            break;
        }
        printf("Command [ Index: %ld, Instruction: %s, Address: %ld ]\n", commandLines[i].index,
               commandLines[i].instruction, commandLines[i].address);
    }
}

CommandLine getCommand(char string[100]) {
    CommandLine commandLine = { '0' };
    int i = 0;
    char *split;
    char *ptr;
    size_t len;
    split = strtok(string, " ");
    for (i = 0; i < 3; ++i) {
        switch (i) {
            case 0:
                commandLine.index = strtol(split, &ptr, 10);
                break;
            case 1:
                /* parse command string */
                strcpy(commandLine.instruction, split);
                break;
            case 2:
                /* remove newline from this entry if exists */
                len = strlen(split);
                if (split[len - 1] == '\n') {
                    split[len - 1] = 0;
                }
                commandLine.address = strtol(split, &ptr, 10);
                break;
            default:
                printf("this should never happen");
                break;
        }
        split = strtok(NULL, " ");
    }
    return commandLine;
}