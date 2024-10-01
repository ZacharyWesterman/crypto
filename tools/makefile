SUBDIRS := $(wildcard */.)

all: $(SUBDIRS)
clean:
	$(MAKE) clean -C $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all clean $(SUBDIRS)
