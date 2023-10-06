#include "Register.hpp"
#include "CounterRegister.hpp"
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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
