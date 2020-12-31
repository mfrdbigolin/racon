# Racon Makefile -- make directives for Racon
# Copyright (C) 2020 Matheus Fernandes Bigolin
# Contact e-mail: <mfrdrbigolin@disroot.org>

# This file is part of Racon.
#   Racon is free software (libre); you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 3 of the License, or (at your
# option) any later version.
#   Racon is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.
#   See the GNU General Public License for more details, you should have
# received a copy of it along with Racon; otherwise, see
# <https://www.gnu.org/licenses/gpl.html>.

BUILD_DIR = build
BIN_DIR = bin
SRC_DIR = src
INCL_DIR = include
TST_DIR = test
TST_INCL_DIR = $(TST_DIR)/test_include
TST_CASES_DIR = $(TST_DIR)/test_cases
OBJ =                           \
  $(BUILD_DIR)/converter.o      \
  $(BUILD_DIR)/str_utils.o      \
  $(BUILD_DIR)/error_handling.o \
  $(BUILD_DIR)/math_utils.o     \
  $(BUILD_DIR)/parser.o         \
  $(BUILD_DIR)/form_utils.o     \
  $(BUILD_DIR)/mem_utils.o      \
  $(BUILD_DIR)/debug.o

CC_OPT = -Wall -pedantic -std=c99
.PHONY: clean debug

racon: racon.o converter.o str_utils.o error_handling.o math_utils.o \
       parser.o form_utils.o mem_utils.o debug.o
	cc -o $(BIN_DIR)/racon $(BUILD_DIR)/racon.o $(OBJ) -lmpfr -lgmp
racon: CC_OPT += -Ofast

debug: converter.o str_utils.o error_handling.o math_utils.o form_utils.o \
       parser.o mem_utils.o tst_converter.o debug.o
	cc -g -o $(BIN_DIR)/debug $(BUILD_DIR)/tst_converter.o $(OBJ) \
        -lmpfr -lgmp
debug: CC_OPT += -g -O0 -D DEBUG

clean:
	rm $(BUILD_DIR)/* $(BIN_DIR)/*

racon.o: $(SRC_DIR)/racon.c $(INCL_DIR)/racon.h
	cc -c $(SRC_DIR)/racon.c $(CC_OPT) -o $(BUILD_DIR)/racon.o \
        -I$(INCL_DIR)

converter.o: $(SRC_DIR)/converter.c $(INCL_DIR)/converter.h
	cc -c $(SRC_DIR)/converter.c $(CC_OPT) -o \
        $(BUILD_DIR)/converter.o -I$(INCL_DIR)

str_utils.o: $(SRC_DIR)/str_utils.c $(INCL_DIR)/str_utils.h
	cc -c $(SRC_DIR)/str_utils.c $(CC_OPT) -o \
        $(BUILD_DIR)/str_utils.o -I$(INCL_DIR)

error_handling.o: $(SRC_DIR)/error_handling.c $(INCL_DIR)/error_handling.h
	cc -c $(SRC_DIR)/error_handling.c $(CC_OPT) -o \
        $(BUILD_DIR)/error_handling.o -I$(INCL_DIR)

math_utils.o: $(SRC_DIR)/math_utils.c $(INCL_DIR)/math_utils.h
	cc -c $(SRC_DIR)/math_utils.c $(CC_OPT) -o \
        $(BUILD_DIR)/math_utils.o -I$(INCL_DIR)

parser.o: $(SRC_DIR)/parser.c $(INCL_DIR)/parser.h
	cc -c $(SRC_DIR)/parser.c $(CC_OPT) -o \
        $(BUILD_DIR)/parser.o -I$(INCL_DIR)

form_utils.o: $(SRC_DIR)/form_utils.c $(INCL_DIR)/form_utils.h
	cc -c $(SRC_DIR)/form_utils.c $(CC_OPT) -o \
        $(BUILD_DIR)/form_utils.o -I$(INCL_DIR)

mem_utils.o: $(SRC_DIR)/mem_utils.c $(INCL_DIR)/mem_utils.h
	cc -c $(SRC_DIR)/mem_utils.c $(CC_OPT) -o \
        $(BUILD_DIR)/mem_utils.o -I$(INCL_DIR)

debug.o: $(SRC_DIR)/debug.c $(INCL_DIR)/debug.h
	cc -c $(SRC_DIR)/debug.c $(CC_OPT) -o \
        $(BUILD_DIR)/debug.o -I$(INCL_DIR)

tst_converter.o: $(TST_DIR)/tst_converter.c $(TST_CASES_DIR)/cases_converter.h \
                 $(TST_INCL_DIR)/tst_converter.h
	cc -c $(TST_DIR)/tst_converter.c $(CC_OPT) -o                          \
        $(BUILD_DIR)/tst_converter.o -I$(INCL_DIR) -I$(TST_INCL_DIR)           \
        -I$(TST_CASES_DIR)
