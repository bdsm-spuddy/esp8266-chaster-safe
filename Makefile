ifndef PORT
PORT=/dev/ttyUSB0
endif
BOARD=esp8266:esp8266:nodemcuv2
XTAL=:xtal=160
EESZ=,eesz=4M1M
FSLOAD=0x300000
BSIZE=8192
PSIZE=256
FSIZE=1024000

ESPTOOL=$(wildcard $(HOME)/.arduino15/packages/esp8266/hardware/esp8266/*/tools/esptool/esptool.py)
MKFS=$(wildcard $(HOME)/.arduino15/packages/esp8266/tools/mklittlefs/*/mklittlefs)

SRC = $(wildcard *.ino) $(wildcard *.h)
PROJECT = $(notdir $(CURDIR))
TARGET=$(PROJECT).ino.bin
FS_SRC=$(wildcard data/*)
HTML=$(wildcard html/*)

$(TARGET): $(SRC) data.img Makefile html.h
	@rm -rf tmp
	@mkdir -p tmp
	TMPDIR=$(PWD)/tmp arduino-cli compile --fqbn=$(BOARD)$(XTAL)$(EESZ) --output-dir $(PWD)
	@rm -rf tmp

data.img: $(FS_SRC) Makefile
	$(MKFS) -c data -p $(PSIZE) -b $(BSIZE) -s $(FSIZE) data.img

html.h: $(HTML)
	./gen_html > html.h

recompile: $(TARGET)

netupload: $(TARGET)
ifdef host
	curl -F "image=@$(TARGET)" ${host}:8266/update
else
	@echo Need host=target to be set - eg make $@ host=testesp
endif

upload:
	python3 $(ESPTOOL) --port=$(PORT) write_flash 0x0 $(TARGET) $(FSLOAD) data.img

serial:
	@kermit -l $(PORT) -b 115200 -c

clean:
	rm -rf *.elf tmp *.bin *.map html.h
