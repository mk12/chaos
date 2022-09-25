# Copyright 2022 Mitchell Kember. Subject to the MIT License.

define usage
Targets:
	all    Build eva
	help   Show this help message
	clean  Remove build output

Variables:
	DEBUG  If nonempty, build in debug mode
endef

.PHONY: all help clean

CFLAGS := $(shell cat compile_flags.txt) $(if $(DEBUG),-O0 -g,-O3 -DNDEBUG)
DEPFLAGS = -MMD -MP -MF $(@:.o=.d)
LDFLAGS := $(if $(DEBUG),,-O3)
LDLIBS := -lpthread

src := $(wildcard src/*.c)
obj := $(src:src/%.c=out/obj/%.o)
dep := $(obj:.o=.d)
bin := out/chaos

.SUFFIXES:

all: $(bin)

help:
	$(info $(usage))
	@:

clean:
	rm -rf out

out out/obj:
	mkdir -p $@

$(obj): out/obj/%.o: src/%.c | out/obj
	$(CC) $(CFLAGS) $(DEPFLAGS) -c -o $@ $<

$(bin): $(obj) | out
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

-include $(dep)
