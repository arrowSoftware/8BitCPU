# 8BitCPU
8-Bit CPU


## Instruction set (CISC)
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

| Instruction | OpCode |CF |ZF |VF |NF |Step  |FI |HL |AI |AO |SEL  |EO |CI |BI |BO |MI |RW |RR |II |IR |CE |CO |JP |OI |OpCode  |Control Flags  |
|:------------|:------:|:-:|:-:|:-:|:-:|:----:|:-:|:-:|:-:|:-:|:---:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:------:|:-------------:|
|FETCH INSTR  |XXXXX   | X | X | X | X |0     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | XX     | 00104         |
|             |XXXXX   | X | X | X | X |1     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 1 | 0 | 0 | 0 | XX     | 00068         |
|FIN INSTR    |XXXXX   | X | X | X | X |X     | X | X | X | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | XX     | 00010         |
|             |        |   |   |   |   |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   |        |               |
|NOP          |00000   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 00     | 00010         |
|HALT         |00001   | X | X | X | X |2     | 0 | 1 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 01     | 40000         |
|LDA [NUM]    |00010   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 02     | 0010C         |
|             |00010   | X | X | X | X |3     | 0 | 0 | 1 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 02     | 20040         |
|LDA [ADDR]   |00011   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 03     | 0010C         |
|             |00011   | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 03     | 00140         |
|             |00011   | X | X | X | X |4     | 0 | 0 | 1 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 03     | 20040         |
|STA [ADDR]   |00100   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 04     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 04     | 00140         |
|             |        | X | X | X | X |4     | 0 | 0 | 0 | 1 | 000 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 04     | 10080         |
|LDB [NUM]    |00101   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 05     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 05     | 00440         |
|LDB [ADDR]   |00110   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 06     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 06     | 00140         |
|             |        | X | X | X | X |4     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 06     | 00440         |
|STB [ADDR]   |00111   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 07     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 07     | 00140         |
|             |        | X | X | X | X |4     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 07     | 00280         |
|ADD [NUM]    |01000   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 08     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 08     | 00440         |
|             |        | X | X | X | X |4     | 1 | 0 | 1 | 0 | 000 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 08     | A1000         |
|ADD [ADDR]   |01001   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 09     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 09     | 00140         |
|             |        | X | X | X | X |4     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 09     | 00440         |
|             |        | X | X | X | X |5     | 1 | 0 | 1 | 0 | 000 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 09     | A1000         |
|SUB [NUM]    |01010   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 0A     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 1 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0A     | 00C40         |
|             |        | X | X | X | X |4     | 1 | 0 | 1 | 0 | 000 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0A     | A1800         |
|SUB [ADDR]   |01011   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 0B     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0B     | 00140         |
|             |        | X | X | X | X |4     | 0 | 0 | 0 | 0 | 000 | 0 | 1 | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0B     | 00C40         |
|             |        | X | X | X | X |5     | 1 | 0 | 1 | 0 | 000 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0B     | A1800         |
|AND [NUM]    |01100   | 1 | 1 | X | X |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 0C     | 00000         |
|AND [ADDR]   |01101   | 1 | 1 | X | X |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 0D     | 00000         |
|OR [NUM]     |01110   | 1 | 1 | X | X |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 0E     | 00000         |
|OR [ADDR]    |01111   | 1 | 1 | X | X |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 0F     | 00000         |
|XOR [NUM]    |10000   | 1 | 1 | X | X |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 10     | 00000         |
|XOR [ADDR]   |10001   | 1 | 1 | X | X |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 11     | 00000         |
|NOT [A]      |10010   | X | 1 | X | X |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   | 12     | 00000         |
|NOT [ADDR]   |10011   | X | 1 | X | X |      | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 13     | 00000         |
|OUT [A]      |10100   | X | X | X | X |2     | 0 | 0 | 0 | 1 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 14     | 10001         |
|OUT [B]      |10101   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 15     | 00201         |
|OUT [NUM]    |10110   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 16     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 16     | 00041         |
|OUT [ADDR]   |10111   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 17     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 17     | 00140         |
|             |        | X | X | X | X |4     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 17     | 00041         |
|JP [ADDR]    |11000   | X | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 18     | 0010C         |
|             |        | X | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 18     | 00042         |
|JPZ [ADDR]   |11001   | X | 0 | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 19     | 00008         |
|JPZ [ADDR]   |11001   | X | 1 | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 1A     | 0010C         |
|             |        | X | 1 | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 1A     | 00042         |
|JPZ [ADDR]   |11001   | 0 | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 1B     | 00008         |
|JPC [ADDR]   |11010   | 1 | X | X | X |2     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 1B     | 0010C         |
|             |11011   | 1 | X | X | X |3     | 0 | 0 | 0 | 0 | 000 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 1B     | 00042         |
|UNUSED       |11100   |   |   |   |   |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   |        | 00000         |
|UNUSED       |11101   |   |   |   |   |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   |        | 00000         |
|UNUSED       |11110   |   |   |   |   |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   |        | 00000         |
|RST          |11111   |   |   |   |   |      |   |   |   |   |     |   |   |   |   |   |   |   |   |   |   |   |   |   |        | 00000         |


## Registers
### D-Flip Flop
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