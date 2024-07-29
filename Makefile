ifndef PORT
PORT=/dev/ttyUSB0
endif
BOARD=esp8266:esp8266:nodemcuv2
XTAL=:xtal=160,eesz=4M1M

ESPTOOL=$(wildcard $(HOME)/.arduino15/packages/esp8266/hardware/esp8266/*/tools/esptool/esptool.py)

SRC = $(wildcard *.ino) $(wildcard *.h) html.h
PROJECT = $(notdir $(CURDIR))
TARGET=$(PROJECT).ino.bin
FS_SRC= $(wildcard html/*)

$(TARGET): $(SRC) html.h version.h certs.h Makefile
	@rm -rf tmp
	@mkdir -p tmp
	TMPDIR=$(PWD)/tmp arduino-cli compile --fqbn=$(BOARD)$(XTAL) --output-dir $(PWD)
	@rm -rf tmp

html.h: $(FS_SRC) Makefile
	./gen_html > $@

certs.h: certs.ar Makefile
	./make_certs >$@

recompile: $(TARGET)

netupload: $(TARGET)
ifdef host
	curl -F "image=@$(TARGET)" ${host}:8266/update
else
	@echo Need host=target to be set - eg make $@ host=testesp
endif

upload:
	@mkdir -p tmp
	TMPDIR=$(PWD)/tmp arduino-cli upload --fqbn=$(BOARD) -p $(PORT) --input-dir $(PWD)
	@rm -rf tmp

serial:
	@kermit -l $(PORT) -b 115200 -c

clean:
	rm -rf *.elf tmp *.bin *.map html.h certs.h

reset:
	python3 $(ESPTOOL) --port $(PORT) chip_id

