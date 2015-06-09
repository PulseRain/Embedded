ifndef TOPDIR
    TOPDIR := ..
endif


config_targets ?= menuconfig config xconfig gconfig
config_folder_name ?= config

#check to see if we need to include ".config"
ifneq ($(strip $(CONFIG_HAVE_DOT_CONFIG)),y)
   
    ifeq (,$(filter $(config_targets), "$(MAKECMDGOALS)"))
        -include $(TOPDIR)/$(config_folder_name)/.config
    endif
   
endif

ifeq ($(strip $(CONFIG_HAVE_DOT_CONFIG)),y)
    config_file := $(TOPDIR)/$(config_folder_name)/.config
else
    config_file :=
endif


HOST_CC ?= gcc


CROSS ?= $(strip $(subst ",, $(CONFIG_CROSS_COMPILER_PREFIX)))

CROSS_CC ?= $(CROSS)gcc
CROSS_AS ?= $(CROSS)as
CROSS_AR ?= $(CROSS)ar
CROSS_LD ?= $(CROSS)ld
CROSS_NM ?= $(CROSS)nm
CROSS_STRIP ?= $(CROSS)strip

VMAJOR ?= $(strip $(subst ",, $(CONFIG_VMAJOR_STR)))
VMINOR ?= $(strip $(subst ",, $(CONFIG_VMINOR_STR)))
PRODUCT_NAME ?= $(strip $(CONFIG_PRODUCT_NAME))


CFLAGS += -I. -I$(TOPDIR)/common/include
CFLAGS += -g -W -DDEBUG -DCONSOLE_PRINT=printf

CFLAGS += -DVMAJOR=$(VMAJOR) -DVMINOR=$(VMINOR)
CFLAGS += -DPRODUCT_NAME=$(PRODUCT_NAME)


submodules_default_build_command ?= \
	@$(MAKE) -C $@;\
	echo "============================================================================";\
	echo

submodules_build_command ?= $(submodules_default_build_command)
submodules_sofa_build_command ?= $(submodules_default_build_command)
submodules_carpet_build_command ?= $(submodules_default_build_command)
submodules_floor_build_command ?= $(submodules_default_build_command)

all: $(submodules_floor) $(submodules_carpet) \
     $(submodules_sofa) $(submodules) $(obj)  $(additional_files) \
     $(config_file)
	@if [ -n "$(target)" ] ; then \
		echo "====> Linking $(target)";\
		$(CROSS_LD) $(LDFLAGS) $(obj) $(link_obj) -o $(target); \
    fi

	@if [ -n "$(post_link_action)" ] ; then \
		echo "====> $(post_link_action)"; \
	fi

	@$(post_link_action)


$(submodules) : $(submodules_sofa)
	$(submodules_build_command)
   
$(submodules_sofa) : $(submodules_carpet)
	$(submodules_sofa_build_command)
   
$(submodules_carpet) : $(submodules_floor)
	$(submodules_carpet_build_command)

$(submodules_floor)  :
	$(submodules_floor_build_command)
   
%.o : %.c $(config_file)
	@echo "===> Building $@"
	@echo "============> Building Dependency"
	@$(CROSS_CC) $(CFLAGS) -M $< | sed "s,$(@F)\s*:,$@ :," > $*.d
	@echo "============> Generating OBJ"
	@$(CROSS_CC) $(CFLAGS) -c -o $@ $<; \
	if [ $$? -ge 1 ] ; then \
		exit 1; \
	fi
	@echo "----------------------------------------------------------------------"

   
dependency = $(patsubst %.o,%.d,$(obj))

ifeq (,$(filter "clean" "clean_recursive", "$(MAKECMDGOALS)"))
	-include $(dependency)
endif


clean_recursive :
	-@for dir in $(submodules_floor) $(submodules_carpet) $(submodules_sofa) $(submodules); do \
        $(MAKE) -s -C $$dir clean; \
	done
	-@rm -vf $(target)
	-@rm -vf $(obj)
	-@rm -vf $(patsubst %.o,%.d,$(obj))
   
clean :
	-@rm -vf $(target)
	-@find . -type d -name "$(config_folder_name)" -prune -o \
             -type f \( -name "*.OBJ" -o -name "*.d" -o -name "*.o" -o -name "*.LST" -o -name "*.M51" \
                        -o -name "*.hex" -o -name "*.rsp" \) -exec rm -vf {} \;

.PHONY: clean all clean_recursive $(submodules) $(submodules_sofa) $(submodules_carpet) $(submodules_floor)
