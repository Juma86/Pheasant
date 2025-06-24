.PHONY: default log run build prepare clean

INCLUDES := gtk4

CC       := gcc
CFLAGS   := `pkg-config --cflags $(INCLUDES)` -O3 -Os -s -Ofast -march=native
LDFLAGS  := `pkg-config --libs $(INCLUDES)`

SRC_DIR  := Source/
OUT_DIR  := Bin/
TMP_DIR  := Temp/
OBJ_DIR  := $(TMP_DIR)Object/

TARGET   := main

SRCS     := $(shell ls $(SRC_DIR)*.c)
OBJS     := $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.c.o)

CPY      := cp -r
MKD      := mkdir -p
DEL      := rm -fr

default: run

log:
	@echo INCLUDES "= $(INCLUDES)"
	@echo CC "      = $(CC)"
	@echo CFLAGS "  = $(CFLAGS)"
	@echo LDFLAGS " = $(LDFLAGS)"
	@echo SRC_DIR " = $(SRC_DIR)"
	@echo OUT_DIR " = $(OUT_DIR)"
	@echo TMP_DIR " = $(TMP_DIR)"
	@echo OBJ_DIR " = $(OBJ_DIR)"
	@echo TARGET "  = $(TARGET)"
	@echo SRCS "    = $(SRCS)"
	@echo OBJS "    = $(OBJS)"
	@echo CPY "     = $(CPY)"
	@echo MKD "     = $(MKD)"
	@echo DEL "     = $(DEL)"

run: build
	$(OUT_DIR)$(TARGET)

build: prepare $(OUT_DIR)$(TARGET)
	$(CPY) $(TMP_DIR)$(OUT_DIR) .

prepare:
	$(MKD) $(TMP_DIR)
	$(MKD) $(OBJ_DIR)
	$(MKD) $(TMP_DIR)$(OUT_DIR)
	$(MKD) $(OUT_DIR)

clean:
	$(DEL) $(TMP_DIR) $(OBJ_DIR) $(OUT_DIR)

$(OUT_DIR)$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TMP_DIR)$(OUT_DIR)$(TARGET) $(LDFLAGS)

$(OBJ_DIR)%.c.o: $(SRC_DIR)%.c
	$(CC) -c -o $@ $< $(CFLAGS)