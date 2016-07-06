# Makefile for sample.out

TARGET 	= sample.out
SRCS 	= ./sample.cpp

# 基本コマンド
RM 		:= rm
CXX 	:= g++
CC 		:= gcc

# デバッグ時とリリース時の微調整
CXX_DEBUG_FLAGS		=	-g -O0 -Wall -Wextra
CXX_RELEASE_FLAGS	=	-O2 -Wall -Wextra

# 基本オプション
CPPFLAGS = -std=c++11

# make
# debug
.PHONY: Debug
Debug: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
Debug: all
# release
.PHONY: Release
Release: CXXFLAGS+=$(CXX_RELEASE_FLAGS)
Release: all

all: $(TARGET)
$(TARGET): $(SRCS)
	$(CXX) $^ -o $@ $(CXXFLAGS) $(CPPFLAGS)

# make clean
.PHONY: clean
clean:
	$(RM) -f *.out

# make install
.PHONY: install
install:
	mkdir bin && cp $(TARGET) bin/$(TARGET)