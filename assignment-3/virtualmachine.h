#ifndef UNTITLED_VIRTUALMACHINE_H
#define UNTITLED_VIRTUALMACHINE_H
typedef struct VirtualMachine {
    int memory[100];
    int accumulator;
    int instructionCounter;
    int instructionRegister;
    int operationCode;
    int operand;
}VirtualMachine;
typedef struct CommandLine {
    long index;
    char instruction[10];
    long address;
}CommandLine;
CommandLine* compile(CommandLine[100]);
CommandLine getCommand(char[100]);
VirtualMachine loadVm(CommandLine*);
void printCommands(CommandLine*);
int instructionToInt(const char instruction[10]);
void printVmState(VirtualMachine vm);
void execute();
#endif
