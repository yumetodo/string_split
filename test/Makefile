# Makefile for test.out

TARGET 	= test.out
SRCS 	= ./test.cpp

# 基本コマンド
RM 		?= rm
CXX 	?= g++
CC		?= gcc
CCOV 	?= gcov

# デバッグ時とリリース時の微調整
CXX_DEBUG_FLAGS		=	-g -O0 -Wall -Wextra
CXX_RELEASE_FLAGS	=	-O2 -Wall -Wextra

# 基本オプション
CPPFLAGS = -std=c++14
ifeq ($(OS),Windows_NT)
CPPFLAGS += -lWs2_32
endif

CONFIGURATION = unknown
PLATFORM = $(shell uname)
COVERAGE_OPTION := -coverage
# make
# debug
.PHONY: Debug
Debug: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
ifdef USE_COVERAGE
Debug: CXXFLAGS+=$(COVERAGE_OPTION)
endif
Debug: CONFIGURATION=Debug
Debug: all
# release
.PHONY: Release
Release: CXXFLAGS+=$(CXX_RELEASE_FLAGS)
Release: CONFIGURATION=Release
Release: all

.PHONY: all
all: $(TARGET)
$(TARGET): $(SRCS)
	$(CXX) --version;
	$(CXX) $^ -o $@ $(CXXFLAGS) $(CPPFLAGS)
	mkdir -p bin/$(CXX)/$(PLATFORM)/$(CONFIGURATION) && cp $(TARGET) bin/$(CXX)/$(PLATFORM)/$(CONFIGURATION)/$(TARGET)

# make clean
.PHONY: clean
clean:
	$(RM) -f *.out

# coverage
.PHONY: coverage
coverage:
	$(CCOV) -v
ifeq ($(USE_COVERAGE),lcov)
	lcov --version
	lcov -c -d . --gcov-tool "$(shell which $(CCOV))" -o coverage.info && lcov -r coverage.info *gcc* -o coverage.info && lcov -r coverage.info *iutest* -o coverage.info && lcov -r coverage.info */usr/include/* -o coverage.info && lcov -r coverage.info *mingw* -o coverage.info;
endif
ifeq ($(USE_COVERAGE),gcov)
ifeq ($(findstring relative-only, $(shell $(CCOV) --help)), relative-only)
	gcov -r *.gcda;
else
	gcov *.gcda;
endif
endif

# send-coveralls
.PHONY: send-coveralls
send-coveralls: coverage
pwd
ifeq ($(USE_COVERAGE),lcov)
	cd ../; lcoveralls --retry-count 3 ./test/coverage.info
endif
ifeq ($(USE_COVERAGE),gcov)
	coveralls -n -r ./ -b ./ $(COVARALLS_EXCLUDE_PATTERN) $(COVARALLS_EXCLUDE)
endif