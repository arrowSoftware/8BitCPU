class Flags(object):
    def __init__(self, FI=0, HLT=0, AI=0, AO=0, SEL3=0, SEL2=0, SEL1=0, EO=0, CI=0, BI=0, BO=0, MI=0, RW=0, RR=0, II=0, IR=0, CE=0, CO=0, JP=0, OI=0):
        self.FI = FI     # LOAD FLAGS REGISTER
        self.HLT = HLT   # HALT THE CPU
        self.AI = AI     # LOAD A REGISTER
        self.AO = AO     # ENABLE A REGISTER OUTPUT
        self.SEL3 = SEL3 # ALU SELECT BIT 3
        self.SEL2 = SEL2 # ALU SELECT BIT 2
        self.SEL1 = SEL1 # ALU SELECT BIT 1
        self.EO = EO     # ENABLE ALU
        self.CI = CI     # CARRY IN BIT FOR ALU (1 = SUBTRACT)
        self.BI = BI     # LOAD B REGISTER
        self.BO = BO     # ENABLE B REGISTER OUTPUT
        self.MI = MI     # LOAD MEMORY REGISTER
        self.RW = RW     # ENABLE RAM WRITE
        self.RR = RR     # ENABLE RAM READ
        self.II = II     # LOAD INSTRUCTION REGISTER
        self.IR = IR     # RESET INSTRUCTION REGISTER
        self.CE = CE     # ENABLE PROGRAM COUNTER
        self.CO = CO     # ENABLE PROGRAM COUNTER OUTPUT
        self.JP = JP     # LOAD PROGRAM COUNTER
        self.OI = OI     # LOAD OUTPUT REGISTER

    def val(self):
        return (self.FI * 524288 + \
        self.HLT * 262144 + \
        self.AI * 131072 + \
        self.AO * 65536 + \
        self.SEL3 * 32768 + \
        self.SEL2 * 16384 + \
        self.SEL1 * 8192 + \
        self.EO * 4096 + \
        self.CI * 2048 + \
        self.BI * 1024 + \
        self.BO * 512 + \
        self.MI * 256 + \
        self.RW * 128 + \
        self.RR * 64 + \
        self.II * 32 + \
        self.IR * 16 + \
        self.CE * 8 + \
        self.CO * 4 + \
        self.JP * 2 + \
        self.OI * 1)

    def __repr__(self):
        return str(self.val())

FETCH_INSTR = {"name": "FETCH", "OpCode": 0x00,"steps": 2, "flags": [Flags(MI=1, CO=1)] + [Flags(RR=1, II=1, CE=1)]}
FIN_INSTR =   {"name": "FIN",   "OpCode": 0x00,"steps": 1, "flags": [Flags(IR=1)]}

instruction_set = [
    {"name": "NOP",          "OpCode": 0x00,"steps": 3, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + FIN_INSTR["flags"]},
    {"name": "HLT",          "OpCode": 0x01,"steps": 3, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(HLT=1)] + FIN_INSTR["flags"]},
    {"name": "LDA_NUM",      "OpCode": 0x02,"steps": 4, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(AI=1, RR=1, )] + FIN_INSTR["flags"]},
    {"name": "LDA_ADDR",     "OpCode": 0x03,"steps": 5, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(MI=1, RR=1)] + [Flags(AI=1, RR=1)] + FIN_INSTR["flags"]},
    {"name": "STA_ADDR",     "OpCode": 0x04,"steps": 4, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(MI=1, RR=1)] + [Flags(AO=1, RW=1)] + FIN_INSTR["flags"]},
    {"name": "LDB_NUM",      "OpCode": 0x05,"steps": 4, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(BI=1, RR=1)] + FIN_INSTR["flags"]},
    {"name": "LDB_ADDR",     "OpCode": 0x06,"steps": 5, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(MI=1, RR=1)] + [Flags(BI=1, RR=1)] + FIN_INSTR["flags"]},
    {"name": "STB_ADDR",     "OpCode": 0x07,"steps": 5, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(MI=1, RR=1)] + [Flags(BO=1, RW=1)] + FIN_INSTR["flags"]},
    {"name": "ADD_NUM",      "OpCode": 0x08,"steps": 5, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(BI=1, RR=1)] + [Flags(FI=1, AI=1, EO=1, SEL1=1, SEL2=1)] + FIN_INSTR["flags"]},
    {"name": "ADD_ADDR",     "OpCode": 0x09,"steps": 6, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(MI=1, RR=1)] + [Flags(BI=1, RR=1)] + [Flags(FI=1, AI=1, EO=1, SEL1=1, SEL2=1)] + FIN_INSTR["flags"]},
    {"name": "SUB_NUM",      "OpCode": 0x0A,"steps": 5, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(CI=1, BI=1, RR=1)] + [Flags(FI=1, AI=1, EO=1, CI=1, SEL1=1, SEL2=1)] + FIN_INSTR["flags"]},
    {"name": "SUB_ADDR",     "OpCode": 0x0B,"steps": 6, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(MI=1, RR=1)] + [Flags(CI=1, BI=1, RR=1)] + [Flags(FI=1, AI=1, EO=1, CI=1, SEL1=1, SEL2=1)] + FIN_INSTR["flags"]},
    {"name": "AND_NUM",      "OpCode": 0x0C,"steps": 3, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(IR=1)] + FIN_INSTR["flags"]}, # TODO
    {"name": "AND_ADDR",     "OpCode": 0x0D,"steps": 3, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(IR=1)] + FIN_INSTR["flags"]}, # TODO
    {"name": "OR_NUM",       "OpCode": 0x0E,"steps": 3, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(IR=1)] + FIN_INSTR["flags"]}, # TODO
    {"name": "OR_ADDR",      "OpCode": 0x0F,"steps": 3, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(IR=1)] + FIN_INSTR["flags"]}, # TODO
    {"name": "XOR_NUM",      "OpCode": 0x10,"steps": 3, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(IR=1)] + FIN_INSTR["flags"]}, # TODO
    {"name": "XOR_ADDR",     "OpCode": 0x11,"steps": 3, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(IR=1)] + FIN_INSTR["flags"]}, # TODO
    {"name": "NOT_A",        "OpCode": 0x12,"steps": 3, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(IR=1)] + FIN_INSTR["flags"]}, # TODO
    {"name": "NOT_ADDR",     "OpCode": 0x13,"steps": 3, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(IR=1)] + FIN_INSTR["flags"]}, # TODO
    {"name": "OUT_A",        "OpCode": 0x14,"steps": 3, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(AO=1, OI=1)] + FIN_INSTR["flags"]},
    {"name": "OUT_B",        "OpCode": 0x15,"steps": 3, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(BO=1, OI=1)] + FIN_INSTR["flags"]},
    {"name": "OUT_NUM",      "OpCode": 0x16,"steps": 4, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(RR=1, OI=1)] + FIN_INSTR["flags"]},
    {"name": "OUT_ADDR",     "OpCode": 0x17,"steps": 5, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(MI=1, RR=1)] + [Flags(RR=1, OI=1)] + FIN_INSTR["flags"]},
    {"name": "JMP_ADDR",     "OpCode": 0x18,"steps": 4, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(RR=1, JP=1)] + FIN_INSTR["flags"]},
    {"name": "JPZ_ADDR_ZF0", "OpCode": 0x19,"steps": 3, "CF": [0,1], "ZF": [0],   "flags": FETCH_INSTR["flags"] + [Flags(CE=1)] + FIN_INSTR["flags"]},
    {"name": "JPZ_ADDR_ZF1", "OpCode": 0x19,"steps": 3, "CF": [0,1], "ZF": [1],   "flags": FETCH_INSTR["flags"] + [Flags(CE=1)] + FIN_INSTR["flags"]},
    {"name": "JPC_ADDR_CF0", "OpCode": 0x1A,"steps": 4, "CF": [0],   "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(RR=1, JP=1)] + FIN_INSTR["flags"]},
    {"name": "JPC_ADDR_CF1", "OpCode": 0x1A,"steps": 4, "CF": [1],   "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(MI=1, CE=1, CO=1)] + [Flags(RR=1, JP=1)] + FIN_INSTR["flags"]},
    {"name": "RST",          "OpCode": 0x1B,"steps": 3, "CF": [0,1], "ZF": [0,1], "flags": FETCH_INSTR["flags"] + [Flags(IR=1)] + FIN_INSTR["flags"]}, # TODO
]

def cast_array(value):
    return value if isinstance(value, list) else [value]

def flat_array(data):
    return [value for internal_data in data for value in internal_data]

def createInstructionMicrocode(instruction, cf, zf):
    step = 0
    instruction_steps = list()

    for flag in cast_array(instruction["flags"]):
        address = instruction["OpCode"] << 5 | cf << 4 | zf << 3 | step
        instruction_microcode = {
            "name" : instruction["name"],
            "address" : address,
            "flag" : flag.val()
        }
        instruction_steps.append(instruction_microcode)
        step += 1
    return instruction_steps

def createMicrocode(instruction_set):
    microcode = list()

    for instruction in instruction_set:
        instruction_steps = [createInstructionMicrocode(instruction, cf, zf) for cf in cast_array(instruction["CF"]) for zf in cast_array(instruction["ZF"])]
        microcode += flat_array(instruction_steps)

    return microcode

def fillMicrocodeNops(microcode):
    address = 0
    filled_microcode = list()
    microcode = sorted(
        microcode, key = lambda item: item["address"], reverse=False
    )
    for instruction_step in microcode:
        while address < instruction_step["address"]:
            filled_microcode.append({
                "name" : "NOP",
                "address" : address,
                "flag" : 0
            })
            address += 1
        filled_microcode.append(instruction_step)
        address += 1

    return filled_microcode

def printMicrocode(microcode):
    for instruction in microcode:
        op_code = instruction["address"] >> 5
        cf = (instruction["address"] & 0x10) >> 4
        zf = (instruction["address"] & 0x08) >> 3
        step = instruction["address"] & 0x07
        print("{} - 0x{:04x} - {:05b} {:01b} {:01b} {:03b} - 0x{:05x}".format(
            instruction["name"].ljust(13),
            instruction["address"],
            op_code, cf, zf, step,
            instruction["flag"]))

def createROM(file_name, codes_table, instruction_size, cols = 8):
    file = open(file_name, "w+", encoding="utf-8")
    file.write("v2.0 raw\n")
    col = 0
    instruction_size = int(instruction_size / 4)
    for code in codes_table:
        col += 1
        instruction = "{:0x}".format(code).rjust(instruction_size, "0")
        file.write("{} ".format(instruction))
        if(col > cols - 1):
            col = 0
            file.write("\n")
    file.close()

microcode = createMicrocode(instruction_set)
microcode = fillMicrocodeNops(microcode)
printMicrocode(microcode)
createROM("istructionDecoderMicrowords.rom", [instruction_step["flag"] for instruction_step in microcode], 20)
