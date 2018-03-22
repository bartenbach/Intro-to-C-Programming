#ifndef UNTITLED_VIRTUALMACHINE_H
#define UNTITLED_VIRTUALMACHINE_H
typedef struct VirtualMachine {
    char memory[100][4];
    int accumulator;
    int instructionCounter;
    int instructionRegister;
    int operationCode;
    int operand;
}VirtualMachine;
typedef struct CommandLine {
    char index[3];
    char instruction[10];
    char address[6];
}CommandLine;
VirtualMachine compile();
CommandLine getCommand(char[100]);
VirtualMachine loadVm(CommandLine[100]);
int stringToInt(const char *s);
int getFormattedDigit(char c);
char* instructionToCharArray(char* instruction, char* address);
int executeInstruction(VirtualMachine*, char*, int, int);
void vmHalt(VirtualMachine*, int);
void vmRead(VirtualMachine*, int);
void vmWrite(VirtualMachine*, int);
void vmLoad(VirtualMachine*, int);
void vmPrint(VirtualMachine*, int);
void vmStore(VirtualMachine*, int);
void vmMath(VirtualMachine *vm, int address, int operation, int currentAddress);
int vmBranchNegative(VirtualMachine*);
int vmBranchZero(VirtualMachine*);
void printVmState(VirtualMachine*);
void execute(VirtualMachine*);
void checkForIllegalCharacter(VirtualMachine *vm, int value, int address);
void checkForOverflow(VirtualMachine *vm ,int value, int address);
#endif
