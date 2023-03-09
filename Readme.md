**Assembler and Emulator**

There are 3 subdirectories
a) Assembler - Contains all cpp codes for Assembler
b) Emulator - Contain emu.c file for Emulator
c) Assembly_Codes - Contains asm test files

Along with these, it contain 2 txt files
a) instructions.txt - Assembly Language Mnemonic, Opcode and OperandType
b) opcode.txt - Assembly Language Mnemonic and Opcode

Running an Assembler (2 Step process)
**cd Assembler**
**g++ asm.cpp -o asm**
**./asm filename.asm**

Here filename.asm denotes a assembly code to be assembled.
Default directory for filename is **"../Assembly_Codes/"**

It is a two pass assembler. It reports **errors** and **warnings** in **filename.log** file

If their are no errors while assembling it generates 2 files
**filename.l** - Listing the memory location and opcode generated  for each line of assembly code
**filename.o** - Object file to be executed by emulator

Note - All files generated are in present in subdirectory **Assembly_Codes**

Running an emulator

**cd Emulator** 
**gcc emu.c -o emu**
**./emu -[operation] [filename.o]**

**operation** denotes operation to be performed. It supports four operations
1. trace - It shows memory and register information after executing each line
2. before - It shows memory dump before execution of object file
3. after - It shows memory dump after execution of object file
4. isa - It prints the instructions set in terminal - Same as instructions.txt

**filename.o** 
Object file to be executed - Execution terminates when HALT is encountered or number of lines executed equals instructions read from object file. 

