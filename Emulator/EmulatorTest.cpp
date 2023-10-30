#include "Register.hpp"
#include "CounterRegister.hpp"
#include "ProgramLoader.hpp"
#include "RAM.hpp"
#include "ALU.hpp"

#include <stdio.h>
#include <gtest/gtest.h>

TEST(DataBusTest, LoadAndRead) {
    DataBus<uint8_t> dataBus;
    dataBus.load(0xFF);
    ASSERT_EQ(0xFF, dataBus.read());
}

TEST(DataBusTest, Size) {
    DataBus<uint8_t> dataBus;
    ASSERT_EQ(8, dataBus.size());
}

TEST(RegisterTest, LoadWithoutClock) {
    DataBus<uint8_t> dataBus;
    Register<uint8_t> registerA(&dataBus);
    dataBus.load(0xFF);
    registerA.load();
    ASSERT_EQ(0, registerA.peak());
}

TEST(RegisterTest, LoadWithClock) {
    DataBus<uint8_t> dataBus;
    Register<uint8_t> registerA(&dataBus);
    dataBus.load(0xFF);
    registerA.clock(true);
    registerA.load();
    ASSERT_EQ(0xFF, registerA.peak());
}

TEST(RegisterTest, Output) {
    DataBus<uint8_t> dataBus;
    Register<uint8_t> registerA(&dataBus);
    dataBus.load(0xFF);
    registerA.clock(true);
    registerA.load();
    dataBus.load(0x55);
    registerA.output();
    ASSERT_EQ(0xFF, dataBus.read());
}

TEST(CounterRegisterTest, CountWithoutClock) {
    DataBus<uint8_t> dataBus;
    CounterRegister<uint8_t> pc(&dataBus);
    pc.enable();
    ASSERT_EQ(0, pc.peak());
}

TEST(CounterRegisterTest, CountWithClock) {
    DataBus<uint8_t> dataBus;
    CounterRegister<uint8_t> pc(&dataBus);
    pc.clock(true);
    pc.enable();
    ASSERT_EQ(1, pc.peak());
}

TEST(CounterRegisterTest, output) {
    DataBus<uint8_t> dataBus;
    CounterRegister<uint8_t> pc(&dataBus);
    pc.clock(true);
    for (int i = 0; i < 20; i++) {
        pc.enable();
    }
    dataBus.load(0xFF);
    pc.output();
    ASSERT_EQ(20, dataBus.read());
}

TEST(CounterRegisterTest, reset) {
    DataBus<uint8_t> dataBus;
    CounterRegister<uint8_t> pc(&dataBus);
    pc.clock(true);
    for (int i = 0; i < 20; i++) {
        pc.enable();
    }
    pc.reset();
    dataBus.load(0xFF);
    pc.output();
    ASSERT_EQ(0, dataBus.read());
}

TEST(CounterRegisterTest, load) {
    DataBus<uint8_t> dataBus;
    CounterRegister<uint8_t> pc(&dataBus);
    dataBus.load(20);
    pc.clock(true);
    pc.load();
    for (int i = 0; i < 20; i++) {
        pc.enable();
    }
    dataBus.load(0xFF);
    pc.output();
    ASSERT_EQ(40, dataBus.read());
}

TEST(ProgramLoaderTest, Operate) {
    DataBus<uint8_t> dataBus;
    ROM<uint8_t> rom;
    uint8_t programData[3] = {0xFF, 0x55, 0x11};
    rom.program(programData, 3);

    ProgramLoader<uint8_t> pl(&dataBus, &rom);

    dataBus.load(0xAA);
    ASSERT_EQ(0xAA, dataBus.read());

    pl.enable();
    ASSERT_EQ(0, dataBus.read());

    pl.clock(true);
    ASSERT_EQ(0xFF, dataBus.read());

    pl.clock(true);
    ASSERT_EQ(1, dataBus.read());

    pl.clock(true);
    ASSERT_EQ(0x55, dataBus.read());

    pl.clock(true);
    ASSERT_EQ(2, dataBus.read());

    pl.clock(true);
    ASSERT_EQ(0x11, dataBus.read());

    pl.clock(false);
    ASSERT_EQ(0x11, dataBus.read());
}

TEST(ProgramLoaderTest, Reset) {
    DataBus<uint8_t> dataBus;
    ROM<uint8_t> rom;
    uint8_t programData[3] = {0xFF, 0x55, 0x11};
    rom.program(programData, 3);

    ProgramLoader<uint8_t> pl(&dataBus, &rom);

    dataBus.load(0xAA);
    ASSERT_EQ(0xAA, dataBus.read());

    pl.enable();
    ASSERT_EQ(0, dataBus.read());

    pl.clock(true);
    ASSERT_EQ(0xFF, dataBus.read());

    pl.clock(true);
    ASSERT_EQ(1, dataBus.read());

    pl.clock(true);
    ASSERT_EQ(0x55, dataBus.read());

    pl.reset();
    pl.clock(true);
    ASSERT_EQ(0, dataBus.read());

    pl.clock(true);
    ASSERT_EQ(0xFF, dataBus.read());

    pl.clock(true);
    ASSERT_EQ(1, dataBus.read());

    pl.clock(true);
    ASSERT_EQ(0x55, dataBus.read());
}

TEST(RAMTest, readWrite) {
    DataBus<uint8_t> dataBus;
    Register<uint8_t> memoryRegister(&dataBus);
    RAM<uint8_t> ram(&dataBus, &memoryRegister);

    // Load the bus with an address
    dataBus.load(10);

    // store the address in the register
    memoryRegister.clock(true);
    memoryRegister.load();

    // Load the bus with data
    dataBus.load(0xFF);

    // store the data on the bus in RAM
    ram.write();

    // reset the databus
    dataBus.load(0);

    // load the bus with an address
    dataBus.load(10);

    // store the address in the memory register
    memoryRegister.clock(true);
    memoryRegister.load();

    // reset the data bus
    dataBus.load(0);

    // read the data from the RAM
    ram.read();

    // check result
    ASSERT_EQ(0xFF, dataBus.read());

    // Attempt to read RAM without data
    dataBus.load(5);
    memoryRegister.clock(true);
    memoryRegister.load();
    dataBus.load(0x55);
    ram.read();
    ASSERT_EQ(0, dataBus.read());
}

TEST(LoadProgramToRAMFromROM, loading) {
    DataBus<uint8_t> dataBus;
    Register<uint8_t> memoryRegister(&dataBus);
    ROM<uint8_t> rom;
    uint8_t programData[7] = {0xFF, 0x55, 0x11, 0x21, 0x34, 0x54, 0x54};
    rom.program(programData, 7);
    ProgramLoader<uint8_t> pl(&dataBus, &rom);
    RAM<uint8_t> ram(&dataBus, &memoryRegister);

    pl.enable(); // load bus with first rom address
    for (int i = 0; i < 7; i++) {
        memoryRegister.clock(true);
        memoryRegister.load(); // load memory register with address from bus
        pl.clock(true); // load the data at address 0 from ROM to the bus
        ram.write(); // write the data on the bus to the address stored in the memory address.
        ASSERT_EQ(programData[i], ram.peak(i));
        pl.clock(true);
    }
}

TEST(LoadProgramToRAMFromROM, FullLoad) {
    DataBus<uint8_t> dataBus;
    Register<uint8_t> memoryRegister(&dataBus);
    ROM<uint8_t> rom;
    uint8_t programData[256] = {0};
    for (int i = 0; i < 256; i++) {
        programData[i] = i;
    }

    rom.program(programData, 256);
    ProgramLoader<uint8_t> pl(&dataBus, &rom);
    RAM<uint8_t> ram(&dataBus, &memoryRegister);

    pl.enable(); // load bus with first rom address
    for (int i = 0; i < 256; i++) {
        memoryRegister.clock(true);
        memoryRegister.load(); // load memory register with address from bus
        pl.clock(true); // load the data at address 0 from ROM to the bus
        ram.write(); // write the data on the bus to the address stored in the memory address.
        ASSERT_EQ(programData[i], ram.peak(i));
        pl.clock(true);
    }
}

TEST(ALUTest, FullLoad) {
    DataBus<uint8_t> dataBus;
    Register<uint8_t> aRegister(&dataBus);
    Register<uint8_t> bRegister(&dataBus);
    ALU<uint8_t> alu(&dataBus, &aRegister, &bRegister);
    dataBus.load(0x05);
    aRegister.clock(true);
    aRegister.load();
    dataBus.load(0x04);
    bRegister.clock(true);
    bRegister.load();
    alu.enable();
    ASSERT_EQ(9, alu.peak());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}