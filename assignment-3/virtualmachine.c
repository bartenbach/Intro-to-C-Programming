#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "virtualmachine.h"


int main() {
    VirtualMachine vm = compile();
    execute(&vm);
    return 0;
}

void printVmState(VirtualMachine *vm) {
    int i, j;
    printf("REGISTERS:\n");
    printf("%-25s%+05i\n", "accumulator", vm->accumulator);
    printf("%-27s %02d\n", "instructionCounter", vm->instructionCounter);
    printf("%-25s+%04d\n", "instructionRegister", vm->instructionRegister);
    printf("%-27s %02d\n", "operationCode", vm->operationCode);
    printf("%-27s %02d\n", "operand", vm->operand);
    printf("MEMORY:\n");
    printf("%8d%6d%6d%6d%6d%6d%6d%6d%6d%6d\n", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    for (i = 0; i < 100; i++) {
        printf("%2d ", i);
        for (j = 0; j < 10; j++) {
            printf("%+d%d%d%d ", getFormattedDigit(vm->memory[i][0]), getFormattedDigit(vm->memory[i][1]),
                   getFormattedDigit(vm->memory[i][2]), getFormattedDigit(vm->memory[i][3]));
            i++;
        }
        i -= 1;
        printf("\n");
    }
}

int getFormattedDigit(char c) {
    if (c != '\0') {
        return c - '0';
    }
    return 0;
}

void execute(VirtualMachine *vm) {
    int i;
    char instruction[3];
    char address[3];
    int intAddress;
    int newAddress;
    int jump;

    /* handoff stdin to the vm */
    stdin = fopen("/dev/tty", "r");
    for (i = 0; i < 100; ++i) {
        /* store the current instruction in the instruction register in ASCII format */
        sprintf(instruction, "%d%d", vm->memory[i][0], vm->memory[i][1]);
        vm->instructionRegister = stringToInt(instruction);

        sprintf(instruction, "%d%d", vm->memory[i][0] - '0', vm->memory[i][1] - '0');
        /* set the opcode and operand registers */
        vm->operationCode = stringToInt(instruction);

        sprintf(address, "%d%d", vm->memory[i][2] - '0', vm->memory[i][3] - '0');
        vm->instructionCounter = i;
        intAddress = stringToInt(address);
        vm->operand = intAddress;
        if (strcmp(instruction, "00") == 0) {
            /* assuming there is a halt somewhere down the road... */
            continue;
        }
        /*printf("Instruction is: %s, Address is: %d\n", intToInstruction(stringToInt(instruction)), intAddress);*/
        jump = executeInstruction(vm, instruction, intAddress, i);
        if (jump == 1) {
            newAddress = intAddress - 1;
            if (intAddress < 0 || intAddress > 99) {
                printf("ERROR: Illegal memory access attempted using address '%d' from address [%d]\n", intAddress, i);
                vmHalt(vm, 1);
            }
            i = newAddress;
        }
    }
}


char *instructionToCharArray(char *instruction, char* index) {
    if (strcmp("READ", instruction) == 0) {
        return "10";
    } else if (strcmp("WRIT", instruction) == 0) {
        return "11";
    } else if (strcmp("PRNT", instruction) == 0) {
        return "12";
    } else if (strcmp("LOAD", instruction) == 0) {
        return "20";
    } else if (strcmp("STOR", instruction) == 0) {
        return "21";
    } else if (strcmp("SET", instruction) == 0) {
        return "22";
    } else if (strcmp("ADD", instruction) == 0) {
        return "30";
    } else if (strcmp("SUB", instruction) == 0) {
        return "31";
    } else if (strcmp("DIV", instruction) == 0) {
        return "32";
    } else if (strcmp("MULT", instruction) == 0) {
        return "33";
    } else if (strcmp("MOD", instruction) == 0) {
        return "34";
    } else if (strcmp("BRAN", instruction) == 0) {
        return "40";
    } else if (strcmp("BRNG", instruction) == 0) {
        return "41";
    } else if (strcmp("BRZR", instruction) == 0) {
        return "42";
    } else if (strcmp("HALT", instruction) == 0) {
        return "99";
    } else {
        /* if anything reaches this point, it's a bogus instruction */
        printf("ERROR: Unrecognized instruction '%s' at program index %s\n", instruction, index);
        exit(1);
    }
}

int executeInstruction(VirtualMachine *vm, char *instruction, int address, int currentAddress) {
    if (strcmp("10", instruction) == 0) {
        vmRead(vm, address);
    } else if (strcmp("11", instruction) == 0) {
        vmWrite(vm, address);
    } else if (strcmp("12", instruction) == 0) {
        vmPrint(vm, address);
    } else if (strcmp("20", instruction) == 0) {
        vmLoad(vm, address);
    } else if (strcmp("21", instruction) == 0) {
        vmStore(vm, address);
    } else if (strcmp("30", instruction) == 0) {
        vmMath(vm, address, 0, currentAddress);
    } else if (strcmp("31", instruction) == 0) {
        vmMath(vm, address, 1, currentAddress);
    } else if (strcmp("32", instruction) == 0) {
        vmMath(vm, address, 3, currentAddress);
    } else if (strcmp("33", instruction) == 0) {
        vmMath(vm, address, 2, currentAddress);
    } else if (strcmp("34", instruction) == 0) {
        vmMath(vm, address, 4, currentAddress);
    } else if (strcmp("40", instruction) == 0) {
        return 1;
    } else if (strcmp("41", instruction) == 0) {
        return vmBranchNegative(vm);
    } else if (strcmp("42", instruction) == 0) {
        return vmBranchZero(vm);
    } else if (strcmp("99", instruction) == 0) {
        vmHalt(vm, 0);
    } else {
        /* if anything reaches this point, it's a bogus instruction */
        printf("ERROR: Unrecognized instruction '%s' at address [%d]\n", instruction, currentAddress);
        vmHalt(vm, 1);
    }
    return 0;
}

void vmLoad(VirtualMachine *vm, int address) {
    char value[4];
    int intValue;
    value[0] = vm->memory[address][0];
    value[1] = vm->memory[address][1];
    value[2] = vm->memory[address][2];
    value[3] = vm->memory[address][3];
    intValue = stringToInt(value);
    vm->accumulator = intValue;
}

void vmStore(VirtualMachine *vm, int address) {
    char array[5];
    int i;
    sprintf(array, "%04d", vm->accumulator);
    for (i = 0; i < 4; i++) {
        vm->memory[address][i] = array[i];
    }
}

void vmMath(VirtualMachine *vm, int address, int operation, int currentAddress) {
    int realValue = 0;
    realValue = (vm->memory[address][0] - '0') * 1000;
    realValue += (vm->memory[address][1] - '0') * 100;
    realValue += (vm->memory[address][2] - '0') * 10;
    realValue += (vm->memory[address][3] - '0') * 1;
    switch (operation) {
        case 0:
            vm->accumulator += realValue;
            checkForOverflow(vm, vm->accumulator, currentAddress);
            break;
        case 1:
            vm->accumulator -= realValue;
            checkForOverflow(vm, vm->accumulator, currentAddress);
            break;
        case 2:
            vm->accumulator *= realValue;
            checkForOverflow(vm, vm->accumulator, currentAddress);
            break;
        case 3:
            if (realValue == 0) {
                printf("ERROR: Attempted to divide by zero at address [%d]\n", currentAddress);
                vmHalt(vm, 1);
            }
            vm->accumulator /= realValue;
            checkForOverflow(vm, vm->accumulator, currentAddress);
            break;
        case 4:
            vm->accumulator %= realValue;
            checkForOverflow(vm, vm->accumulator, currentAddress);
            break;
        default:
            printf("FATAL: Reached unrecognized math operation!\n");
            exit(1);
    }
}

void checkForOverflow(VirtualMachine *vm ,int value, int currentAddress) {
    if (value > 9999 || value < -9999) {
        printf("ERROR: Word overflow! Value larger than supported '%d' at address [%d]\n", value, currentAddress);
        vmHalt(vm, 1);
    }
}

int vmBranchNegative(VirtualMachine *vm) {
    if (vm->accumulator < 0) {
        return 1;
    }
    return 0;
}

int vmBranchZero(VirtualMachine *vm) {
    if (vm->accumulator == 0) {
        return 1;
    }
    return 0;
}

void vmRead(VirtualMachine *vm, int address) {
    char *value = malloc(4);
    int i;
    char input[5];
    memset(value, '0', sizeof(char) * 4);
    printf("Input data: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\r\n")] = 0;
    for (i = 0; i < strlen(input); i++) {
        value[3 - i] = input[strlen(input) - i - 1];
    }
    vm->memory[address][0] = (char) (int) value[0];
    vm->memory[address][1] = (char) (int) value[1];
    vm->memory[address][2] = (char) (int) value[2];
    vm->memory[address][3] = (char) (int) value[3];
}

void vmWrite(VirtualMachine *vm, int address) {
    char value[4];
    int intValue;
    value[0] = vm->memory[address][0];
    value[1] = vm->memory[address][1];
    value[2] = vm->memory[address][2];
    value[3] = vm->memory[address][3];
    intValue = stringToInt(value);
    printf("%d", intValue);
}


void vmPrint(VirtualMachine *vm, int address) {
    int i;
    int char1, char2;
    char character1[3] = {'0'};
    char character2[3] = {'0'};
    for (i = address; i < 100; i++) {
        character1[0] = vm->memory[i][0];
        character1[1] = vm->memory[i][1];
        character2[0] = vm->memory[i][2];
        character2[1] = vm->memory[i][3];
        char1 = stringToInt(character1);
        char2 = stringToInt(character2);
        checkForIllegalCharacter(vm, char1, i);
        checkForIllegalCharacter(vm, char2, i);
        if (char1 != '\0') {
            printf("%c", char1);
        } else {
            break;
        }
        if (char2 != '\0') {
            printf("%c", char2);
        } else {
            break;
        }
    }
}

void checkForIllegalCharacter(VirtualMachine *vm, int value, int address) {
    if (value == 0 || value == 10) {
        return;
    }
    if (value > 90 || value < 65) {
        printf("\nERROR: Illegal ASCII character reached '%d' at address [%d]\n", value, address);
        printf("ERROR: Only A-Z, NULL, and newline are supported.\n");
        vmHalt(vm, 1);
    }
}

void vmHalt(VirtualMachine *vm, int exitCode) {
    printVmState(vm);
    exit(exitCode);
}

VirtualMachine compile() {
    CommandLine commandLines[100];
    int i = 0;
    char string[100];
    /* marks the final instruction */
    CommandLine marker = {{'%', '\0', '\0'}};
    while (fgets(string, sizeof(string), stdin)) {
        CommandLine commandLine = getCommand(string);
        commandLines[i] = commandLine;
        i++;
    }
    commandLines[i] = marker;
    return loadVm(commandLines);
}

VirtualMachine loadVm(CommandLine *commandLines) {
    int i;
    int j;
    int index;
    int hasHalt = 0;
    char *instruction;
    char *address;
    char *paddedValue = malloc(4);
    VirtualMachine vm = {{{'0'}}};
    memset(vm.memory, '0', sizeof(vm.memory));
    for (i = 0; i < 100; i++) {
        if (commandLines[i].index[0] == '%') {
            break;
        }
        index = stringToInt(commandLines[i].index);
        instruction = instructionToCharArray(commandLines[i].instruction, commandLines[i].index);
        /* halt check */
        if (strcmp(instruction, "99") == 0) {
            hasHalt = 1;
        }
        address = commandLines[i].address;
        if (strcmp("22", instruction) == 0) {
            /* there is no standard format for the size of SET instructions, so this
             * pads them with zeros so they can easily be stored in a retrievable format */
            if (strlen(address) > 4) {
                printf("ERROR: Word overflow detected using value '%s' at program index %s\n", address, commandLines[i].index);
                printf("ERROR: Values may not be larger than 4 digits.\n");
                exit(1);
            }
            memset(paddedValue, '0', sizeof(char) * 4);
            for (j = 0; j < strlen(address); j++) {
                paddedValue[3 - j] = address[strlen(address) - j - 1];
            }
            vm.memory[index][0] = (char) (int) paddedValue[0];
            vm.memory[index][1] = (char) (int) paddedValue[1];
            vm.memory[index][2] = (char) (int) paddedValue[2];
            vm.memory[index][3] = (char) (int) paddedValue[3];
        } else {
            vm.memory[index][0] = (char) (int) instruction[0];
            vm.memory[index][1] = (char) (int) instruction[1];
            vm.memory[index][2] = (char) (int) address[0];
            vm.memory[index][3] = (char) (int) address[1];
        }
    }
    if (hasHalt == 0) {
        printf("ERROR: No halt instruction detected in program. Programs must contain the halt instruction.\n");
        exit(1);
    }
    return vm;
}

/* convert a base 10 string back to an integer */
int stringToInt(const char *string) {
    int result = 0;
    while (*string) {
        result *= 10;
        result += *string++ - '0';
    }
    return result;
}

CommandLine getCommand(char string[100]) {
    CommandLine commandLine = {{'0'}};
    int i = 0;
    char *split;
    size_t len;
    split = strtok(string, " ");
    for (i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                strcpy(commandLine.index, split);
                break;
            case 1:
                strcpy(commandLine.instruction, split);
                break;
            case 2:
                /* remove newline from this entry if exists */
                len = strlen(split);
                if (split[len - 1] == '\n') {
                    split[len - 1] = 0;
                }
                strcpy(commandLine.address, split);
                break;
            default:
                printf("FATAL: reached impossible case in getCommand()\n");
                exit(1);
        }
        split = strtok(NULL, " ");
    }
    return commandLine;
}