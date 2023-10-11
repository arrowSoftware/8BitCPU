# 8BitCPU
8-Bit CPU


## Instruction set
  * CF = Carry Flag
  * ZF = Zero flag.
  * NF = Negative flag.
  * VF = Overflow flag.

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
  * HLT = Halt clock.
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


| Instruction | OpCode |CF|ZF| STEP |FI|HL|AI|AO|EO|SU|BI|BO|MI|RW|RR|II|IR|CE|CO|JP|OI| OpCode | Control Flags |
|-------------|--------|--|--|------|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--------|---------------|
| FETCH INSTR | XXXX   |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| FIN INST    | XXXX   |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| NOP         | 00000       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| HALT        | 00001       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| LDA NUM     | 00010       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| LDA [ADDR]  | 00011       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| STR [ADDR]  | 00100       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| LDB NUM     | 00101       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| LDB [ADDR]  | 00110       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| STB [ADDR]  | 00111       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| ADD NUM     | 01000       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| ADD [ADDR]  | 01001       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| SUB NUM     | 01010       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| SUB [ADDR]  | 01011       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| AND NUM     | ?????       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| AND [ADDR]  | ?????       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| OR NUM      | ?????       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| OR [ADDR]   | ?????       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| XOR NUM     | ?????       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| XOR [ADDR]  | ?????       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| NOT A       | ?????       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| NOT [ADDR]  | ?????       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| OUT A       | ?????       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| OUT B       | ?????       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| OUT NUM     | ?       |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| OUT [ADDR]  |        |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| JP [ADDR]   |        |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| JPZ0 [ADDR] |        |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| JPZ1 [ADDR] |        |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| JPC0 [ADDR] |        |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| JPC1 [ADDR] |        |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |
| RST         |        |  |  |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        |               |

## Registers
### D-Flip Flop
![D-FLip FLop with set and reset](/Images/D-FlipFlop.png)

![D-FLip FLop with set and reset](/Images/D-FlipFlop.gif)

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

### 1-Bit register
![1-Bit register](/Images/1-BitRegister.png)

![1-Bit register](/Images/1-BitRegister.gif)

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

### 4-Bit register
Identical to the 8-Bit register but with 4 input and output pins instead of 8

### 8-Bit register
![8-Bit register](/Images/8-BitRegister.png)

![8-Bit regsiter](/Images/8-BitRegister.gif)

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


Available registers in this project.

- Program counter register (PC)
  - The program counter is a register that contains the address
  of the instruction being executed at the current time. As each instruction gets fetched, the program counter increases its stored value by 1. After each instruction is fetched, the program counter points to the next instruction in the sequence. The program counter register is built using 8 J-K Flip Flops linked together.

  https://www.daniellowengrub.com/blog/2021/02/08/binary-counter

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