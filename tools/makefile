SUBDIRS := $(wildcard */.)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all clean $(SUBDIRS)
