#ifndef UNTITLED_VIRTUALMACHINE_H
#define UNTITLED_VIRTUALMACHINE_H
typedef struct VirtualMachine {
    char memory[10][10];
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
VirtualMachine loadVm();
void printCommands(CommandLine*);
void executeInstruction(VirtualMachine*, CommandLine);
void vmHalt(VirtualMachine*);
void vmRead(VirtualMachine*, CommandLine);
void vmWrite(VirtualMachine*, CommandLine);
void vmLoad(VirtualMachine*, CommandLine);
void vmPrint(VirtualMachine, CommandLine);
void vmStore(VirtualMachine*, CommandLine);
void vmSet(VirtualMachine, CommandLine);
void vmAdd(VirtualMachine, CommandLine);
void vmSubtract(VirtualMachine, CommandLine);
void vmDivide(VirtualMachine, CommandLine);
void vmMultiply(VirtualMachine, CommandLine);
void vmModulus(VirtualMachine, CommandLine);
void vmBranch(VirtualMachine, CommandLine);
void vmBranchNegative(VirtualMachine, CommandLine);
void vmBranchZero(VirtualMachine, CommandLine);
void printVmState(VirtualMachine*);
void execute(VirtualMachine*, CommandLine*);
void getBinary(int num, char *str);
#endif
