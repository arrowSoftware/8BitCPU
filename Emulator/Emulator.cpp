#include "InstructionDecoder.hpp"

int main(int argc, char **argv) {
    DataBus<uint8_t> dataBus;
    Register<uint8_t> aRegister(&dataBus);
    Register<uint8_t> bRegister(&dataBus);
    Register<uint8_t> memRegister(&dataBus);
    Register<uint8_t> pcRegister(&dataBus);
    Register<uint8_t> outRegister(&dataBus);
    Register<uint8_t> flagsRegister(&dataBus);
    CounterRegister<uint8_t> instructionRegister(&dataBus);
    ALU<uint8_t> alu(&dataBus, &aRegister, &bRegister);
    ROM<uint8_t> rom;
    RAM<uint8_t> ram(&dataBus, &memRegister);
    InstructionDecoder<uint8_t> decoder(&dataBus, &aRegister, &bRegister, &memRegister, &pcRegister, &outRegister, &flagsRegister, &instructionRegister, &alu, &ram, &rom);
    decoder.loadInstructionMap();
    return 0;
}