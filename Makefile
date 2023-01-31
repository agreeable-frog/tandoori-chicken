MKDIR    := mkdir
RMDIR    := rm -r
INCLUDE  := src
INCLUDEL := libs
BIN      := .
OBJ      := obj
SRC      := src
CC       := g++
CFLAGS   := -std=c++17 -O2 -I$(INCLUDE) -isystem libs -Wall
LDLIBS   := -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
SRCS     := $(wildcard $(SRC)/*.cc)
HHS      := $(wildcard $(SRC)/*.hh)
OBJS     := $(patsubst $(SRC)/%.cc,$(OBJ)/%.o,$(SRCS))
EXE      := $(BIN)/vkapp

.PHONY: all run clean

all: $(EXE)

$(EXE): $(OBJS) | $(BIN)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OBJ)/%.o: $(SRC)/%.cc | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN) $(OBJ):
	$(MKDIR) $@

run: $(EXE)
	./$<

clean:
	$(RMDIR) $(OBJ) $(EXE)