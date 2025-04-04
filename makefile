MCU = atmega32u4
ARCH = AVR8
BOARD = LEONARDO
F_CPU = 16000000
F_USB = $(F_CPU)
OPTIMIZATION = s
TARGET = MultiTouch
SRC = Descriptors.c MultiTouch.c

LUFA_PATH = ./LUFA
CC_FLAGS = -DUSE_LUFA_CONFIG_HEADER -I. -I$(LUFA_PATH)/Drivers
LD_FLAGS =

include $(LUFA_PATH)/Build/lufa_core.mk
