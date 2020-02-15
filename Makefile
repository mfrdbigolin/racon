# racon Makefile -- make directives for racon
# Copyright (C) 2020 Matheus Fernandes Bigolin

# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
# Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <https://www.gnu.org/licenses/>.

# Contact e-mail: mfrdrbigolin@disroot.org

BUILD_DIR = build
BIN_DIR = bin
SRC_DIR = src
INCL_DIR = include
TST_DIR = test
OBJ =                           \
  $(BUILD_DIR)/converter.o      \
  $(BUILD_DIR)/str_utils.o      \
  $(BUILD_DIR)/error_handling.o \
  $(BUILD_DIR)/math_utils.o     \
  $(BUILD_DIR)/parser.o
SRC =                         \
  $(SRC_DIR)/converter.c      \
  $(SRC_DIR)/str_utils.c      \
  $(SRC_DIR)/error_handling.c \
  $(SRC_DIR)/math_utils.c     \
  $(SRC_DIR)/parser.c

CC_OPT = -g -Wall -pedantic -std=c99 -O0

racon: racon.o converter.o str_utils.o error_handling.o math_utils.o parser.o
	cc -o $(BIN_DIR)/racon $(BUILD_DIR)/racon.o $(OBJ) -lmpfr -lgmp

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

tst_converter.o: $(TST_DIR)/tst_converter.c $(TST_DIR)/cases_converter.h \
                 $(TST_DIR)/tst_converter.h
	cc -c $(TST_DIR)/tst_converter.c $(CC_OPT) -o \
        $(BUILD_DIR)/tst_converter.o -I$(INCL_DIR)

.PHONY: clean debug
clean:
	rm $(BUILD_DIR)/* $(BIN_DIR)/*

debug: converter.o str_utils.o error_handling.o math_utils.o parser.o \
       tst_converter.o
	cc -g -o $(BIN_DIR)/debug $(BUILD_DIR)/tst_converter.o $(OBJ) \
        -lmpfr -lgmp
