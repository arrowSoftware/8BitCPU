# 8BitCPU
8-Bit CPU

# Table of Contents
- [References](#references)
- [TODO](#todo)
- [Instruction set](#instruction-set)
  - [Instructions](#instructions)
  - [Microcodes](#microcodes)
  - [Instruction microcode decriptions](#instruction-microcode-decriptions)
  - [Logisim Instructions Testing](#logisim-instructions-testing)
    - [NOP & HLT](#nop-hlt)
    - [LDA NUM](#lda-num)
    - [LDA [ADDR]](#lda-addr)
    - [STA [ADDR]](#sta-addr)
    - [LDB [NUM]](#ldb-num)
    - [LDB [ADDR]](#ldb-addr)
    - [STB [ADDR]](#stb-addr)
    - [ADD NUM](#add-num)
    - [ADD [ADDR]](#add-addr)
    - [SUB NUM](#sub-num)
    - [SUB [ADDR]](#sub-addr)
    - [AND NUM](#add-num)
    - [AND [ADDR]](#and-addr)
    - [OR NUM](#or-num)
    - [OR [ADDR]](#or-addr)
    - [XOR NUM](#xor-num)
    - [XOR [ADDR]](#xor-addr)
    - [NOTA](#nota)
    - [NOT [ADDR]](#not-addr)
    - [OUTA](#outa)
    - [OUTB](#outb)
    - [OUT NUM](#out-num)
    - [OUT [ADDR]](#out-addr)
    - [JMP [ADDR]](#jmp-addr)
    - [JPZ [ADDR]](#jpz-addr)
    - [JPC [ADDR]](#jpc-addr)
    - [RST](#rst)
    - [Fibinacci test](#fibinacci-test)
    - [Multiplication test](#multiplication-test)
- [CPU Design](#cpu-design)
  - [Register](#register)
    - [D-Flip-Flop](#d-flip-flop)
    - [Available registers in this project](#available-registers-in-this-project)
  - [Half Adder](#half-adder)
  - [Full Adder](#full-adder)
  - [8-Bit Adder](#8-bit-adder)
  - [D-Latch](#d-latch)
  - [4-Bit Binary Decoder](#4-bit-binary-decoder)
  - [Multiplexer](#multiplexer)
    - [1-Bit Multiplexer](#1-bit-multiplexer)
    - [8-Bit Multiplexer](#8-bit-multiplexer)
    - [8-Bit 2x1 Multiplexer](#8-bit-2x1-multiplexer)
    - [8-Bit 4x1 Multiplexer](#8-bit-4x1-multiplexer)
  - [8-Bit Clear](#8-bit-clear)
  - [8-Bit Inverter](#8-bit-inverter)
  - [8-Bit OR](#8-bit-or)
  - [8-Bit AND](#8-bit-and)
  - [8-Bit XOR](#8-bit-xor)
  - [8-Bit ALU](#8-bit-alu)
  - [4-Bit Decoder - 7 Segment](#4-bit-decoder---7-segment)
  - [8-Bit Decoder - 7 Segment](#8-bit-decoder---7-segment)
  - [8-Bit Reverser](#8-bit-reverser)
  - [SRAM](#sram)
    - [16-Byte SRAM](#16-byte-sram)
    - [256-Byte SRAM](#256-byte-sram)
  - [Program Loader](#program-loader)
  - [8-Bit Processor](#8-bit-processor)
- [Compiler](#compiler)
- [Emulator](#emulator)

## References
* https://schweigi.github.io/assembler-simulator/
* https://schweigi.github.io/assembler-simulator/instruction-set.html
* https://users.informatik.haw-hamburg.de/~krabat/FH-Labor/gnupro/5_GNUPro_Utilities/c_Using_LD/ldLinker_scripts.html#example
* https://github.com/leonicolas/computer-8bits
* https://www.daniellowengrub.com/blog/2021/02/08/binary-counter
* https://github.com/hlorenzi/customasm

## TODO

## Instruction set
The instruction set implemented in this project is CISC (Complex Instruction Set Computers) based.

### Instructions
|Instruction | OpCode | Description |
|:-----------|:-------|:------------|
|NOP         |0x00    |No operation. Fetches the next operation.|
|HLT         |0x01    |Stops the clock.|
|LDA NUM     |0x02    |Loads register A with the given value.|
|LDA [ADDR]  |0x03    |Loads register A with the value stored in the given memory address.|
|STA [ADDR]  |0x04    |Stores the register A value in the given memory address.|
|LDB NUM     |0x05    |Loads register B with the given value.|
|LDB [ADDR]  |0x06    |Loads register B with the value stored in the given memory address.|
|STB [ADDR]  |0x07    |Stores the register B value in the given memory address.|
|ADD NUM     |0x08    |Adds the given value with the value stored in register A and stores the sum result in register A. The given number will be stored in register B.|
|ADD [ADDR]  |0x09    |Adds the value stored in the given memory address with the value stored in register A. Stores the sum result in register A.|
|SUB NUM     |0x0A    |Subtracts the given value with the value stored in register A and stores the subtraction result in register A. The given number will be stored in register B.|
|SUB [ADDR]  |0x0B    |Subtracts the value stored in the given memory address with the value stored in register A. Stores the subtraction result in register A.|
|AND NUM     |0x0C    |TODO|
|ADD [ADDR]  |0x0D    |TODO|
|OR NUM      |0x0E    |TODO|
|OR [ADDR]   |0x0F    |TODO|
|XOR NUM     |0x10    |TODO|
|XOR [ADDR]  |0x11    |TODO|
|NOTA        |0x12    |TODO|
|NOT [ADDR]  |0x13    |TODO|
|OUTA        |0x14    |Sets the Output register with the register A value.|
|OUTB        |0x15    |Sets the Output register with the register B value.|
|OUT NUM     |0x16    |Sets the Output register with the given value.|
|OUT [ADDR]  |0x17    |Sets the Output register with the value stored in the given memory address.|
|JMP [ADDR]  |0x18    |Jumps to the given address.|
|JPZ [ADDR]  |0x19    |Jumps to the given address if the zero flag is 1.|
|JPC [ADDR]  |0x1A    |Jumps to the given address if the carry flag is 1.|
|UNUSED      |0x1B    |Spare expansion.|
|UNUSED      |0x1C    |Spare expansion.|
|UNUSED      |0x1D    |Spare expansion.|
|RST         |0x1E    |Reset the cpu (TODO).|

### Microcodes
* FLG = FLAG REGISTER
  * FI = Enable flag register load.
    * Loads the flags register with the value currently on the data bus.
    * Available flags:
    * | Flag | Description   |
      |------|---------------|
      | CF   | Carry Flag    |
      | ZF   | Zero Flag     |
      | NF   | Negative Flag |
      | VF   | Overflow Flag |
* CL = CLOCK
  * HL = Halt clock.
    * Stops the clock.
* AR = A REGISTER
  * AI = Enable A register load.
    * Loads the A register with the value currently on the data bus.
  * AO = Enable A regsiter output.
    * Outputs the current register value to the data bus.
* ALU = ALGORITHMIC AND LOGIC UNIT
  * EO = Enable ALU output.
    * Outputs the current ALU operation result to the data bus.
  * CI = Carry in flag.
    * Carry in flag from Flag register
  * SEL = ALU operation select code
    * 3 bit number for selecting the ALU operation.
    * | code | operation      |
      |------|----------------|
      |000   | A OR B         |
      |001   | NOT A          |
      |010   | A + NOT B + Ci |
      |011   | A + B + Ci     |
      |100   | A XOR B        |
      |101   | A AND B        |
      |110   | A - 1 + Ci     |
* BR = B REGISTER
  * BI = Enable B register load.
    * Loads the A register with the value currently on the data bus.
  * BO = Enable B regsiter output.
    * Outputs the current register value to the data bus.
* MR = MEMORY REGISTER
  * MI = Enable memory register load.
    * Loads the memory register with the value currently on the data bus.
* RAM = RANDOM ACCESS MEMORY
  * RW = Enable RAM write.
    * Writes the value currently on the data bus into the selected memory banks.
  * RR = Enable RAM read.
    * Outputs the value stored in the selected memory bank to the data bus.
* IR = INSTRUCTION REGISTER
  * II = Enable instruction register load.
    * Loads the instruction register with the value currently on the data bus.
  * IR = Reset instruction register.
    * Resets the instruction decoder counter back to 0. (Fetch next instruction set)
* PC = PROGRAM COUNTER REGISTER
  * CE = Enable counter register.
    * Enables the program counter to process the count.
  * CO = Enable counter register output.
    * Ouputs the current register value to the data bus.
  * JP = Enable counter register load.
    * Loads the program counter register with the value currently on the data bus.
* OR = OUTPUT REGISTER
  * OI = Enable output register load.
    * Loads the output register with the value currently on the data bus.

### Instruction microcode decriptions

* Control Flags is a bit mapping of each microword.
* OpCode in column 2 is the assembly opcode value.
* OpCode in second to last column is the microcode opcode value.

| Instruction | OpCode |CF |ZF |VF |NF |Step  |FI |HL |AI |AO |SEL  |EO |CI |BI |BO |MI |RW |RR |II |IR |CE |CO |JP |OI |OpCode  |Control Flags  |
|:------------|:------:|:-:|:-:|:-:|:-:|:----:|:-:|:-:|:-:|:-:|:---:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:------:|:-------------:|
|FETCH INSTR  |XXXXX   | X | X | X | X |0     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | XX     | 00104         |
|             |XXXXX   | X | X | X | X |1     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 1 | 0 | 0 | 0 | XX     | 00068         |
|FIN INSTR    |XXXXX   | X | X | X | X |X     | X | X | X | 0 | XXX | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | XX     | 00010         |
|             |        |   |   |   |   |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   |        |               |
|NOP          |00000   | X | X | X | X |2     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 00     | 00010         |
|HLT          |00001   | X | X | X | X |2     | 0 | 1 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 01     | 40000         |
|LDA NUM      |00010   | X | X | X | X |2     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 02     | 0010C         |
|             |00010   | X | X | X | X |3     | 0 | 0 | 1 | 0 | XXX | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 02     | 20040         |
|LDA [ADDR]   |00011   | X | X | X | X |2     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 03     | 0010C         |
|             |00011   | X | X | X | X |3     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 03     | 00140         |
|             |00011   | X | X | X | X |4     | 0 | 0 | 1 | 0 | XXX | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 03     | 20040         |
|STA [ADDR]   |00100   | X | X | X | X |2     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 04     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 04     | 00140         |
|             |        | X | X | X | X |4     | 0 | 0 | 0 | 1 | XXX | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 04     | 10080         |
|LDB NUM      |00101   | X | X | X | X |2     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 05     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 05     | 00440         |
|LDB [ADDR]   |00110   | X | X | X | X |2     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 06     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 06     | 00140         |
|             |        | X | X | X | X |4     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 06     | 00440         |
|STB [ADDR]   |00111   | X | X | X | X |2     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 07     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 07     | 00140         |
|             |        | X | X | X | X |4     | 0 | 0 | 0 | 0 | XXX | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 07     | 00280         |
|ADD NUM      |01000   | 0 | X | X | X |2     | 0 | 0 | 0 | 0 | 001 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 08     | 0010C         |
|             |        | 0 | X | X | X |3     | 0 | 0 | 0 | 0 | 001 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 08     | 00440         |
|             |        | 0 | X | X | X |4     | 1 | 0 | 1 | 0 | 001 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 08     | A1000         |
|ADD [ADDR]   |01001   | 0 | X | X | X |2     | 0 | 0 | 0 | 0 | 001 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 09     | 0010C         |
|             |        | 0 | X | X | X |3     | 0 | 0 | 0 | 0 | 001 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 09     | 00140         |
|             |        | 0 | X | X | X |4     | 0 | 0 | 0 | 0 | 001 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 09     | 00440         |
|             |        | 0 | X | X | X |5     | 1 | 0 | 1 | 0 | 001 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 09     | A1000         |
|SUB NUM      |01010   | 1 | X | X | X |2     | 0 | 0 | 0 | 0 | 001 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 0A     | 0010C         |
|             |        | 1 | X | X | X |3     | 0 | 0 | 0 | 0 | 001 | 0 | 1 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0A     | 00C40         |
|             |        | 1 | X | X | X |4     | 1 | 0 | 1 | 0 | 001 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0A     | A1800         |
|SUB [ADDR]   |01011   | 1 | X | X | X |2     | 0 | 0 | 0 | 0 | 001 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 0B     | 0010C         |
|             |        | 1 | X | X | X |3     | 0 | 0 | 0 | 0 | 001 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0B     | 00140         |
|             |        | 1 | X | X | X |4     | 0 | 0 | 0 | 0 | 001 | 0 | 1 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0B     | 00C40         |
|             |        | 1 | X | X | X |5     | 1 | 0 | 1 | 0 | 001 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0B     | A1800         |
|AND NUM      |01100   | 1 | 1 | X | X |TODO  |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 0C     | 00000         |
|AND [ADDR]   |01101   | 1 | 1 | X | X |TODO  |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 0D     | 00000         |
|OR NUM       |01110   | 1 | 1 | X | X |TODO  |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 0E     | 00000         |
|OR [ADDR]    |01111   | 1 | 1 | X | X |TODO  |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 0F     | 00000         |
|XOR NUM      |10000   | 1 | 1 | X | X |TODO  |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 10     | 00000         |
|XOR [ADDR]   |10001   | 1 | 1 | X | X |TODO  |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 11     | 00000         |
|NOTA         |10010   | X | 1 | X | X |TODO  |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 12     | 00000         |
|NOT [ADDR]   |10011   | X | 1 | X | X |TODO  |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 13     | 00000         |
|OUTA         |10100   | X | X | X | X |2     | 0 | 0 | 0 | 1 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 14     | 10001         |
|OUTB         |10101   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 15     | 00201         |
|OUT NUM      |10110   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 16     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 16     | 00041         |
|OUT [ADDR]   |10111   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 17     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 17     | 00140         |
|             |        | X | X | X | X |4     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 17     | 00041         |
|JMP [ADDR]   |11000   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 18     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 18     | 00042         |
|JPZ [ADDR]   |11001   | X | 0 | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 19     | 00008         |
|JPZ [ADDR]   |11001   | X | 1 | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 19     | 0010C         |
|             |        | X | 1 | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 19     | 00042         |
|JPC [ADDR]   |11001   | 0 | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 1A     | 00008         |
|JPC [ADDR]   |11010   | 1 | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 1A     | 0010C         |
|             |11011   | 1 | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 1A     | 00042         |
|UNUSED       |11100   |   |   |   |   |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 1B     | 00000         |
|UNUSED       |11101   |   |   |   |   |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 1C     | 00000         |
|UNUSED       |11110   |   |   |   |   |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 1D     | 00000         |
|RST          |11111   |   |   |   |   |TODO  |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 1E     | 00000         |

### Logisim Instructions Testing

<a id="nop-hlt"></a>
#### NOP & HLT
```nasm
00:  NOP # No operation
01:  HLT # Halt the clock
```
```nasm
v2.0 raw
00
01
```
![NOP and HLT test](/Images/Test_NOP_HLT.gif)

#### LDA NUM
```nasm
00:  LDA 0x55 # Load A register with value 0x55
02:  HLT # Halt the clock
```
```nasm
v2.0 raw
02 55
01
```
![LDA NUM test](/Images/Test_LDA_NUM.gif)

#### LDA [ADDR]
```nasm
# 0x04 variable

00:  LDA [variable] # Load A register with value at address [variable]
02:  HLT # Halt the clock
```
```nasm
v2.0 raw
03 04
01 00
aa 00
```
![LDA ADDR test](/Images/Test_LDA_ADDR.gif)

#### STA [ADDR]
```nasm
# 0x05 variablePtr

00: LDA 0xAA # Load A register with value 0xAA
02: STA [variablePtr] # Store value in A register at memory address [variablePtr]
04: HLT # Halt the clock
```
```nasm
v2.0 raw
02 55
04 05
01
```
![STA ADDR test](/Images/Test_STA_ADDR.gif)

#### LDB [NUM]
```nasm
00:  LDB 0x55 # Load B register with value 0x55
02:  HLT # Halt the clock
```
```nasm
v2.0 raw
05 55
01
```
![LDB NUM test](/Images/Test_LDB_NUM.gif)

#### LDB [ADDR]
```nasm
# 0x04 variable

00:  LDB [variable] # Load B register with value at address [variable]
02:  HLT # Halt the clock
```
```nasm
v2.0 raw
06 04
01 00
aa 00
```
![LDB ADDR test](/Images/Test_LDB_ADDR.gif)

#### STB [ADDR]
```nasm
# 0x05 variablePtr

00: LDB 0xAA # Load B register with value 0xAA
02: STB [variablePtr] # Store value in B register at memory address [variablePtr]
04: HLT # Halt the clock
```
```nasm
v2.0 raw
05 55
07 05
01
```
![STB ADDR test](/Images/Test_STB_ADDR.gif)

#### ADD NUM
```nasm
00: LDA 0x02 # Load A register with value 0x02
02: ADD 0x04 # Add 0x04 to the value in A register and store output in A register
04: OUTA # Load output register with the value in the A register
05: HLT # halt the clock
```
```nasm
v2.0 raw
02 02
08 04
14
01
```
![ADD NUM test](/Images/Test_ADD_NUM.gif)

#### ADD [ADDR]
```nasm
# 0x07 variablePtr

00: LDA 0x5
02: ADD [variablePtr] # Add the value in memory address [variablePtr] to the value in the A register and store the output in the A register
04: OUTA # Load output register with the value in the A register
05: HLT # halt the clock
```
```nasm
v2.0 raw
02 05
09 07
14
01
00
05
```
![ADD ADDR test](/Images/Test_ADD_ADDR.gif)

#### SUB NUM
```nasm
00: LDA 0x08
02: SUB 0x02
04: OUTA
05: HLT
```
``` nasm
v2.0 raw
02 08
0A 02
14
01
```
![SUB NUM test](/Images/Test_SUB_NUM.gif)

#### SUB [ADDR]
```nasm
# 0x07 variablePtr

00: LDA 0x08
02: SUB [variablePtr] # Subtract the value in memory address [variablePtr] from the value in the A register and store the output in the A register
04: OUTA
05: HLT
```
``` nasm
v2.0 raw
02 08
0B 07
14
01
00
02
```
![SUB ADDR test](/Images/Test_SUB_ADDR.gif)

#### AND NUM
```nasm
TODO
```
```nasm
v2.0 raw
```
![AND NUM test](/Images/Test_AND_NUM.gif)

#### AND [ADDR]
```nasm
TODO
```
```nasm
v2.0 raw
```
![AND [ADDR] test](/Images/Test_AND_ADDR.gif)

#### OR NUM
```nasm
TODO
```
```nasm
v2.0 raw
```
![OR NUM test](/Images/Test_OR_NUM.gif)

#### OR [ADDR]
```nasm
TODO
```
```nasm
v2.0 raw
```
![OR [ADDR] test](/Images/Test_OR_ADDR.gif)

#### XOR NUM
```nasm
TODO
```
```nasm
v2.0 raw
```
![XOR NUM test](/Images/Test_XOR_NUM.gif)

#### XOR [ADDR]
```nasm
TODO
```
```nasm
v2.0 raw
```
![XOR [ADDR] test](/Images/Test_XOR_ADDR.gif)

#### NOTA
```nasm
TODO
```
```nasm
v2.0 raw
```
![NOTA test](/Images/Test_NOTA.gif)

#### NOT [ADDR]
```nasm
TODO
```
```nasm
v2.0 raw
```
![NOT [ADDR] test](/Images/Test_NOT_ADDR.gif)

#### OUTA
```nasm
00: LDA 0x55 # Load A register with value 0x55
02: OUTA
03: HLT
```
```nasm
v2.0 raw
02 55
14 
01
```
![OUTA test](/Images/Test_OUTA.gif)

#### OUTB
```nasm
00: LDB 0x55 # Load B register with value 0x55
02: OUTB
03: HLT
```
```nasm
v2.0 raw
05 55
15
01
```
![OUTB test](/Images/Test_OUTB.gif)

#### OUT NUM
```nasm
00: OUT 0xAA
02: HLT
```
```nasm
v2.0 raw
16 aa
01
```
![OUT NUM test](/Images/Test_OUT_NUM.gif)

#### OUT [ADDR]
```nasm
# 0x04 variablePtr

00: OUT [variablePtr]
02: HLT

```
```nasm
v2.0 raw
17 04
01
00
55
```
![OUT ADDR test](/Images/Test_OUT_ADDR.gif)

#### JMP [ADDR]
```nasm
JMP 0x20

# address 0x20
LDA 0x55
OUTA
HLT
```
```nasm
v2.0 raw
00: 18 10
...
10: 02 55
12: 14
13: 01
```
![JMP ADDR test](/Images/Test_JMP_ADDR.gif)

#### JPZ [ADDR]
ZF = 1
```nasm
00: LDA 0x04
02: SUB 0x04
04: JPZ 0x10
06: OUT 0xFF
07: HLT
...
10: OUT 0x55
12: HLT
```
```nasm
v2.0 raw
02 04
0a 04
19 10
16 ff
01
00 00
00 00
00 00
00
16 55
01
```
![JPZ ZF = 1 ADDR test](/Images/Test_JPZ_ADDR_ZF1.gif)

ZF = 0
```nasm
00: LDA 0x04
02: ADD 0x04
04: JPZ 0x10
06: OUT 0xFF
07: HLT
...
10: OUT 0x55
12: HLT
```
```nasm
v2.0 raw
02 04
0a 04
19 10
16 ff
01
00 00
00 00
00 00
00
16 55
01
```
![JPZ ZF = 0 ADDR test](/Images/Test_JPZ_ADDR_ZF0.gif)

#### JPC [ADDR]
CF = 0
```nasm
00: LDA 0xFE
02: ADD 0x01
04: JPC 0x10
06: OUT 0xFF
07: HLT
...
10: OUT 0x55
12: HLT
```
```nasm
v2.0 raw
02 FE
08 01
1A 10
16 FF
01
00 00
00 00
00 00
00 
16 55
01
```
![JPC CF = 0 ADDR test](/Images/Test_JPC_ADDR_CF0.gif)

CF = 1
```nasm
00: LDA 0xFE
02: ADD 0x02
04: JPC 0x10
06: OUT 0xFF
07: HLT
...
10: OUT 0x55
12: HLT
```
```nasm
v2.0 raw
02 FE
08 02
1A 10
16 FF
01
00 00
00 00
00 00
00 
16 55
01
```
![JPC CF = 1 ADDR test](/Images/Test_JPC_ADDR_CF1.gif)

#### RST
```nasm
TODO
```
```nasm
v2.0 raw
```
![RST test](/Images/Test_RST.gif)

#### Fibinacci test
```nasm
INIT:
00:  LDA 0X00
02:  STA [N1]
04:  OUT [N1]
06:  LDA 0X01
08:  STA [N2]
START:
0A  OUT [N2]
0C  LDA [N1]
0E  ADD [N2]
10  STB [N1]
12  STA [N2]
14  JPC [INIT]
16  JMP [START]
# 18: [N1]
# 19: [N2]
```
```nasm
v2.0 raw
02 00
04 18
17 18
02 01
04 19
17 19
03 18
09 19
07 18
04 19
1A 00
18 0A
```
![Fibinacci test](/Images/Test_Fibinacci.gif)

#### Multiplication test
Reference code in C
```C
void multiply(uint8_t *result, uint8_t *multiplicand, uint8_t *multiplier) {
  uint8_t temp = 0;
  while (1) {
    if (*multiplier == 0) {
      break;
    }
    temp = *result;
    temp = temp + *multiplicand;
    *result = temp;

    temp = *multiplier;
    temp = temp - 1;
    *multiplier = temp;
  }

  printf("%d\n", *result);
  return;
}

int main(void) {
  uint8_t result = 0, multiplicand = 4, multiplier = 5;
  multiply(&result, &multiplicand, &multiplier);
}

```
```nasm
INIT:
0x00  LDA 4
0x02  STA [MULTIPLIER]
0x04  OUTA
0x05  LDA 0
0x07  STA [RESULT]
0x09  LDA 5
0x0B  STA [MULTIPLICAND]
0x0D  OUTA

START:
0x0E  JPZ [END]

0x10  LDA [RESULT]
0x12  ADD [MULTIPLICAND]
0x14  STA [RESULT]

0x16  LDA [MULTIPLIER]
0x18  SUB 1
0x1C  STA [MULTIPLIER]

0x1E  JP  [START]

END:
0x20  OUT [RESULT]
0x22  HALT

# 0x23  MULTIPLIER
# 0x24  MULTIPLICAND
# 0X25  RESULT
```
![Multiplication test](/Images/Test_Multiplication.gif)

## CPU Design

### Register
#### D-Flip Flop
<p align="center" width="100%">
  <img src="/Images/D-FlipFlop.png" alt="D-FLip Flop with set and reset"/>
</p>
<p align="center" width="100%">
  <img src="/Images/D-FlipFlop.gif" alt="D-FLip Flop with set and reset GIF"/>
</p>

D-Flip Flop will latch (save) whats in the input line (D) when the clock signal is on the rising edge into the output (Q) and it will store the invserse in output (Q').  Setting the set flag (S) to 1 will bypass the clock pulse and latch the output (Q) to 1 and the output (Q') to 0.  Setting the reset flag (R) to 1 will bypass the clock pulse and latch the output (Q) to a 0 and the output (Q') to a 1.

The initial state of the D-Flip Flops output pins (Q) and (Q') are unknown so setting an initial reset (R) is used to initialize the D-FLip Flop to 0(Q) and 1 (Q')

Inputs
- **Clock** - Clock pulse
- **Data** - Data to latch
- **Set** - Hold output Q to 1
- **Reset** - Hold output Q to 0

Outputs
- **Q** - Latched data
- **Q'** - Inverse of latched data

Truth Table
| Clock | D | S | R | Q | Q' |
|-------|---|---|---|---|----|
|0      |X  |0  |0  |Q  |Q'  |
|0      |X  |1  |0  |1  |0   |
|0      |X  |0  |1  |0  |1   |
|1      |0  |0  |0  |0  |1   |
|1      |0  |0  |1  |0  |1   |
|1      |0  |1  |0  |1  |0   |
|1      |1  |0  |1  |0  |1   |
|1      |1  |1  |0  |1  |0   |
|1      |1  |0  |0  |1  |0   |
|1      |X  |1  |1  |1  |ERR |

#### 1-Bit register
<p align="center" width="100%">
  <img src="/Images/1-BitRegister.png" alt="1-Bit register"/>
</p>

<p align="center" width="100%">
  <img src="/Images/1-BitRegister.gif" alt="1-Bit register"/>
</p>

The 1-Bit register is made up of 1 D-Flip Flop. There is extra logic that will load the output (Q) back into the input (D) when a clock pulse comes in. This is to keep the same value latched each pulse of the clock if the load pin is not active.

Inputs
- **Clock** - Clock pulse
- **Load** - Enable pin to load the input data into the circuit
- **Data** - Data to latch
- **Set** - Hold output Q to 1
- **Reset** - Hold output Q to 0

Outputs
- **Q** - Latched data
- **Q'** - Inverse of latched data

#### 4-Bit register
Identical to the 8-Bit register but with 4 input and output pins instead of 8

#### 8-Bit register
<p align="center" width="100%">
  <img src="/Images/1-BitRegister.png" alt="8-Bit register"/>
</p>

<p align="center" width="100%">
  <img src="/Images/1-BitRegister.gif" alt="8-Bit register"/>
</p>

The 8-Bit register is made up of 8 1-Bit registers. There is an aditional enable pin used to enable the output pins Q1:Q7. Q'1:Q'7 are not currently routed to output pins.

Inputs
- **Clock** - Clock pulse
- **Load** - Enable pin to load the input data into the circuit
- **Data A1:A7** - Data to latch
- **Set** - Hold output Q to 1
- **Reset** - Hold output Q to 0
- **Enable** - Enables output pins

Outputs
- **S1:S7** - Imediate data latched.
- **Q1:Q7** - Latched data
- **Q'1:Q'7** - Inverse of latched data (Not routed to output pins)

#### Available registers in this project

- Program counter register (PC)
  - The program counter is a register that contains the address
  of the instruction being executed at the current time. As each instruction gets fetched, the program counter increases its stored value by 1. After each instruction is fetched, the program counter points to the next instruction in the sequence. The program counter register is built using 8 J-K Flip Flops linked together.

  ![8-Bit counter reference](/Images/8-BitCounter.png)

  ![8-Bit counter reference](/Images/8-BitCounter.gif)

  Inputs
  - **Enable Out[EnO]** - Enables the output pins
  - **Enable[En]** - Enables the counter
  - **Reset[R]** - Resets the counter back to 0
  - **Write[L]** - Write the input value A0:A8 to the current count value.
  - **Clock[Clk]** - Clock pulse
  - **A1:A8** - Data input, used to set the current count value.

  Outputs
  - **Q1:Q8** - Data output pins.
  - **S1:S8** - Imediate data outputs.

- Register A connected to the ALU
  - ![A register](/Images/RegisterA.png)
  - General purpose register connected directly to the ALU
- Register B connected to the ALU
  - ![B register](/Images/RegisterB.png)
  - General purpose register connected directly to the ALU
- Instruction register
  - ![Instruction register](/Images/InstructionRegister.png)
  - The instruction register holds a machine instruction that is currently being executed.  It remains in the instruction register until the instruction decoder is finished executing the micro-instructions.
- memory address register
  - ![Memory register](/Images/MemoryRegister.png)
  - This reigster is directly connected to the RAM and stores the address to read/write from.
- output register
  - ![Output register](/Images/OutRegister.png)
  - General purpose register connected to the data bus. Stores the output data from any operation.
- Status flags register
  - ![Flags Register](/Images/FlagsRegister.png)
  - Contains the ALU status flags Z(Zero), V(overflow), N(negative), C(carry)

### Half Adder
### Full Adder
### 8-Bit Adder
### D-Latch
### 4-Bit Binary Decoder
### Multiplexer
#### 1-Bit Multiplexer
#### 8-Bit Multiplexer
#### 8-Bit 2x1 Multiplexer
#### 8-Bit 4x1 Multiplexer
### 8-Bit Clear
### 8-Bit Inverter
### 8-Bit OR
### 8-Bit AND
### 8-Bit XOR
### 8-Bit ALU
### 4-Bit Decoder - 7 Segment 
### 8-Bit Decoder - 7 Segment
### 8-Bit Reverser
### SRAM
#### 16-Byte SRAM
#### 256-Byte SRAM
### Program Loader
### 8-Bit Processor

## Compiler
TODO

# TODO
Example asm program
```asm
          global    _start

          section   .text
_start:   mov       rax, 1                  ; system call for write
          mov       rdi, 1                  ; file handle 1 is stdout
          mov       rsi, message            ; address of string to output
          mov       rdx, 13                 ; number of bytes
          syscall                           ; invoke operating system to do the write
          mov       rax, 60                 ; system call for exit
          xor       rdi, rdi                ; exit code 0
          syscall                           ; invoke operating system to exit

          section   .data
message:  db        "Hello, World", 10      ; note the newline at the end
```
objdump -D
```asm
Disassembly of section .text:

0000000000000000 <_start>:
   0:   b8 01 00 00 00          mov    $0x1,%eax
   5:   bf 01 00 00 00          mov    $0x1,%edi
   a:   48 be 00 00 00 00 00    movabs $0x0,%rsi
  11:   00 00 00
  14:   ba 0d 00 00 00          mov    $0xd,%edx
  19:   0f 05                   syscall
  1b:   b8 3c 00 00 00          mov    $0x3c,%eax
  20:   48 31 ff                xor    %rdi,%rdi
  23:   0f 05                   syscall

Disassembly of section .data:

0000000000000000 <message>:
   0:   48                      rex.W
   1:   65 6c                   gs insb (%dx),%es:(%rdi)
   3:   6c                      insb   (%dx),%es:(%rdi)
   4:   6f                      outsl  %ds:(%rsi),(%dx)
   5:   2c 20                   sub    $0x20,%al
   7:   57                      push   %rdi
   8:   6f                      outsl  %ds:(%rsi),(%dx)
   9:   72 6c                   jb     77 <message+0x77>
   b:   64                      fs
   c:   0a                      .byte 0xa
```
objdump -s
```asm
Contents of section .text:
 0000 b8010000 00bf0100 000048be 00000000  ..........H.....
 0010 00000000 ba0d0000 000f05b8 3c000000  ............<...
 0020 4831ff0f 05                          H1...
Contents of section .data:
 0000 48656c6c 6f2c2057 6f726c64 0a        Hello, World.
```
diff between pre and post linked object file
```asm
asm.o:     file format elf64-x86-64                           | a.out:     file format elf64-x86-64


Disassembly of section .text:                                   Disassembly of section .text:

0000000000000000 <_start>:                                    | 0000000000401000 <_start>:
   0:   b8 01 00 00 00          mov    $0x1,%eax              |   401000:       b8 01 00 00 00          mov    $0x1,%eax
   5:   bf 01 00 00 00          mov    $0x1,%edi              |   401005:       bf 01 00 00 00          mov    $0x1,%edi
   a:   48 be 00 00 00 00 00    movabs $0x0,%rsi              |   40100a:       48 be 00 20 40 00 00    movabs $0x402000,%rsi
  11:   00 00 00                                              |   401011:       00 00 00
  14:   ba 0d 00 00 00          mov    $0xd,%edx              |   401014:       ba 0d 00 00 00          mov    $0xd,%edx
  19:   0f 05                   syscall                       |   401019:       0f 05                   syscall
  1b:   b8 3c 00 00 00          mov    $0x3c,%eax             |   40101b:       b8 3c 00 00 00          mov    $0x3c,%eax
  20:   48 31 ff                xor    %rdi,%rdi              |   401020:       48 31 ff                xor    %rdi,%rdi
  23:   0f 05                   syscall                       |   401023:       0f 05                   syscall
```
elf header dump
```asm
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x401000
  Start of program headers:          64 (bytes into file)
  Start of section headers:          8464 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         3
  Size of section headers:           64 (bytes)
  Number of section headers:         6
  Section header string table index: 5
  ```