#ifndef __InstructionDecoder_H__
#define __InstructionDecoder_H__

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "DataBus.hpp"
#include "Register.hpp"
#include "ALU.hpp"
#include "RAM.hpp"
#include "ROM.hpp"
#include "CounterRegister.hpp"

template <class T>
class InstructionDecoder
{
    public:
        InstructionDecoder(DataBus<T> *dataBus,
            Register<T> *aRegister,
            Register<T> *bRegister,
            Register<T> *memRegister,
            Register<T> *pcRegister,
            Register<T> *outRegister,
            Register<T> *flagsRegister,
            CounterRegister<T> *instructionRegister,
            ALU<T> *alu,
            RAM<T> *ram,
            ROM<T> *rom
        ) :
        _dataBus(dataBus),
        _aRegister(aRegister),
        _bRegister(bRegister),
        _memRegister(memRegister),
        _pcRegister(pcRegister),
        _outRegister(outRegister),
        _flagsRegister(flagsRegister),
        _instructionRegister(instructionRegister),
        _alu(alu),
        _ram(ram),
        _rom(rom) {}

        ~InstructionDecoder(void) {}

        void loadInstructionMap(void) {
            std::ifstream infile("../istructionDecoderMicrowords.rom");
            std::string value;
            std::string line;

            while (std::getline(infile, line)) {
                // Skip first line.
                if (line.find("raw") != std::string::npos) {
                    continue;
                }

                std::istringstream iss(line);

                while (iss >> value) {
                    _instructionMicrocodeMap.push_back(stoi(value, 0, 16));
                }
            }
        }

        void clock(bool high) {
            _clock = high;

            // on the low pulse the address is incremented.
            if (high == false) {
                int zf = 1, cf = 0,  cp0 = 0,  cp1 = 0,  cp2 = 0,  cp3 = 0,  cp4 = 0;

                uint16_t addressSelect = _addressCounter;
                addressSelect |= zf << 3;
                addressSelect |= cf << 4;
                addressSelect |= cp0 << 5;
                addressSelect |= cp1 << 6;
                addressSelect |= cp2 << 7;
                addressSelect |= cp3 << 8;
                addressSelect |= cp4 << 9;
                printf("0x%x\n",addressSelect);
                _addressCounter++;
            }

            if (_addressCounter >= 8) {
                _addressCounter = 0;
            }
        }

        void reset(void) {
            _addressCounter = 0;

        }

        void OI(void) {
            _outRegister->load();
        }
        void JP(void) {
            _pcRegister->load();
        }
        void CO(void) {
            _pcRegister->output();
        }
        void CE(void) {
            _pcRegister->enable();
        }
        void IR(void) {
            _addressCounter = 0;
        }
        void II(void) {
            _instructionRegister->load();
        }
        void RR(void) {
            _ram->read();
        }
        void RW(void) {
            _ram->write();
        }
        void MI(void) {
            _memRegister->load();
        }
        void BO(void) {
            _bRegister->output();
        }
        void BI(void) {
            _bRegister->load();
        }
        void CI(void) {
            _pcRegister->load();
        }
        void EO(void) {
            _alu->output();
        }
        void SEL1(int en) {
            _alu->SEL1(en);
        }
        void SEL2(int en) {
            _alu->SEL2(en);
        }
        void SEL3(int en) {
            _alu->SEL3(en);
        }
        void AO(void) {
            _aRegister->output();
        }
        void AI(void) {
            _aRegister->load();
        }
        void HLT(void) {
            // TODO
        }
        void FI(void) {
            _flagsRegister->load();
        }

    protected:
    private:
        DataBus<T> *_dataBus;
        Register<T> *_aRegister;
        Register<T> *_bRegister;
        Register<T> *_memRegister;
        Register<T> *_pcRegister;
        Register<T> *_outRegister;
        Register<T> *_flagsRegister;
        CounterRegister<T> *_instructionRegister;
        ALU<T> *_alu;
        RAM<T> *_ram;
        ROM<T> *_rom;

        std::vector<uint32_t> _instructionMicrocodeMap;

        int _addressCounter = 0;

        bool _clock;
        // inputs
        bool _VF;
        bool _ZF;
        bool _CF;
        bool _OP0;
        bool _OP1;
        bool _OP2;
        bool _OP3;
        bool _OP4;
        bool _PM;
};

#endif // __InstructionDecoder_H__