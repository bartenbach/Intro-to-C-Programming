#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "virtualmachine.h"



int main() {
    CommandLine commandLines[100];
    CommandLine *commandLine = compile(commandLines);
    /*printCommands(commandLine);*/
    VirtualMachine vm = loadVm(commandLine);
    printVmState(vm);
    return 0;
}

void printVmState(VirtualMachine vm) {
    int i;
    printf("REGISTERS:\n");
    printf("%-25s+%04d\n", "accumulator", vm.accumulator);
    printf("%-27s %02d\n", "instructionCounter", vm.instructionCounter);
    printf("%-25s+%04d\n", "instructionRegister", vm.instructionRegister);
    printf("%-27s %02d\n", "operationCode", vm.operationCode);
    printf("%-27s %02d\n", "operand", vm.operand);
    printf("MEMORY:\n");
    for (i = 0; i < 100; i++) {

    }
}

void execute() {

}

VirtualMachine loadVm(CommandLine* commandLine) {
    VirtualMachine vm = { 0 };
    int i;
    int instruction;
    int address;
    char* ptr;
    char string1[4];
    char string2[4];
    for (i = 0; i < 100; i++) {
        if (commandLine[i].index == -1) {
            break;
        }
        instruction = instructionToInt(commandLine[i].instruction);
        address = (int) commandLine[i].address;
        sprintf(string1,"%d",instruction);
        sprintf(string2,"%d",address);
        strcat(string1,string2);
        /*printf("%d\n", atoi(string1));*/
        vm.memory[i] = (int) strtol(string1, &ptr, 10);
    }
    return vm;
}

int instructionToInt(const char instruction[10]) {
    if (strcmp("READ",instruction) == 0) {
        return 10;
    } else if (strcmp("WRIT",instruction) == 0) {
        return 11;
    } else if (strcmp("PRNT", instruction) == 0) {
        return 12;
    } else if (strcmp("LOAD", instruction) == 0) {
        return 20;
    } else if (strcmp("STOR", instruction) == 0) {
        return 21;
    } else if (strcmp("SET", instruction) == 0) {
        return 22;
    } else if (strcmp("ADD", instruction) == 0) {
        return 30;
    } else if (strcmp("SUB", instruction) == 0) {
        return 31;
    } else if (strcmp("DIV", instruction) == 0) {
        return 32;
    } else if (strcmp("MULT", instruction) == 0) {
        return 33;
    } else if (strcmp("MOD", instruction) == 0) {
        return 34;
    } else if (strcmp("BRAN", instruction) == 0) {
        return 40;
    } else if (strcmp("BRNG", instruction) == 0) {
        return 41;
    } else if (strcmp("BRZR", instruction) == 0) {
        return 42;
    } else if (strcmp("HALT", instruction) == 0) {
        return 99;
    } else {
        printf("Unrecognized instruction: %s\n", instruction);
    }
    /* if anything reaches this point, it's a bogus instruction */
    exit(1);
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