ifdef OS
   RM = del /Q
   FixPath = $(subst /,\,$1)
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
      FixPath = $1
   endif
endif

GTEST_DIR = C:/Users/Tyler/Documents/googletest/googletest
#GTEST_DIR = C:/Users/tyler/OneDrive/Documents/googletest/googletest
#GTEST_DIR = /usr/src/gtest

USER_DIR = .

USER_SRCS  = ObjDump.cpp \
			../Instructions.cpp \
			../Helpers.cpp \
			 main.cpp

USER_HEADS = $(USER_DIR)/*.h ../*.h
USER_OBJS = $(USER_SRCS:.cpp=.o)

USER_TEST_SRCS  = ObjDump.cpp \
			../Instructions.cpp \
			../Helpers.cpp \
			 ObjDumpTest.cpp

USER_TEST_OBJS = $(USER_TEST_SRCS:.cpp=.o)

INCLUDES = -I. -I../

# Flags passed to the preprocessor.
CPPFLAGS += --coverage -g -O0 -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread

TARGET = objdump
TEST_TARGET = objdumpTest

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h

.DEFAULT_GOAL := $(TARGET)

all : $(TARGET) $(TEST_TARGET)

clean:
	$(RM) $(call FixPath,*.a *.exe *.o html *.gcda *.gcdo *.gcno *.bin *.hex coverage.run $(TARGET) $(TEST_TARGET))

coverage:
	./$(TEST_TARGET)
	lcov -c -d . -o coverage.run; genhtml -o html/ coverage.run

test : $(TEST_TARGET)

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
			$(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
			$(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

$(TEST_TARGET): $(USER_TEST_OBJS) gtest.a
	$(CXX) -o $@ $(USER_TEST_OBJS) $(CPPFLAGS)  $(CXXFLAGS) gtest.a

$(TARGET): $(USER_OBJS)
	$(CXX) -o $@ $(USER_OBJS) $(CPPFLAGS) $(CXXFLAGS)

$(USER_DIR)/%.o: $(USER_DIR)/%.cpp $(USER_HEADS) $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) -I../ -c -o $@ $< $(CPPFLAGS)
