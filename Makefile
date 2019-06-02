CC = g++

RMDIR = rm -rf

RM = rm -f

DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$*.d

DIRECTIVES = -std=c++14 -c -I $(HEADER_PATH)
#-Wall -Wextra
LIBS = -lm -lpthread

HEADER_PATH = include
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep
BUILD_PATH = build
CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES = $(wildcard $(DEP_PATH)/*.d)

EXEC = ANAO

ifeq ($(OS),Windows_NT)
	RMDIR = rd /s /q
	RM = del
	PTHREAD_PATH = C:\Pthread
	DIRECTIVES += -I $(PTHREAD_PATH)\include -DHAVE_STRUCT_TIMESPEC
	LIBS = -L $(PTHREAD_PATH)\lib -lmingw32 -lpthreadVC2 -lm
	EXEC := $(EXEC).exe
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Darwin)
		LIBS = -lm
	endif
endif

all: $(BUILD_PATH)/$(EXEC)

$(BUILD_PATH)/$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS)
$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp

ifeq ($(OS),Windows_NT)
	@if not exist $(BUILD_PATH) @mkdir $(BUILD_PATH)
	@if not exist $(DEP_PATH) @mkdir $(DEP_PATH)
	@if not exist $(BIN_PATH) @mkdir $(BIN_PATH)
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH) $(BUILD_PATH)
endif

	$(CC) $(DEP_FLAGS) -c -o $@ $< $(DIRECTIVES)

print-% : ;@echo $* = $($*)

debug: DIRECTIVES += -ggdb -O0
debug: all

release: DIRECTIVES += -Ofast -mtune=native
release: all

clean:
	$(RMDIR) $(BIN_PATH) $(DEP_PATH)
	$(RM) $(BUILD_PATH)/$(EXEC)

.PRECIOUS: $(DEP_PATH)/%.d
.PHONY: debug clean release

-include $(DEP_FILES)
