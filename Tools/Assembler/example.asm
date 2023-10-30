INIT:
    LDA 0x0
    STA [N1]
    OUT [N1]
    LDA 01
    STA [N2]

START:
    OUT [N2]
    LDA [N1]
    ADD [N2]
    STB [N1]
    STA [N2]
    JPC [INIT]
    JMP [START]
END:
    HLT

N1: DB 00
N2: DB 00