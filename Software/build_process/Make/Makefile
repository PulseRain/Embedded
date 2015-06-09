TOPDIR := $(shell pwd)

export TOPDIR


config_targets := menuconfig config xconfig gconfig
config_folder_name := config
       
# Pull in the user's configuration
ifeq (,$(filter $(config_targets),$(MAKECMDGOALS)))
	-include $(TOPDIR)/$(config_folder_name)/.config
endif       

#############################################################################
ifeq ($(strip $(CONFIG_HAVE_DOT_CONFIG)),y)

        link_obj += main/main.o
        submodules += main
       
        ifeq ($(strip $(CONFIG_BUILD_WHOLE_IMAGE)),y)
            target := demo
        endif

    #+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        ifeq ($(strip $(CONFIG_ENABLE_ALIGNMENT_MODULE)),y)
            submodules_sofa += align
            link_obj += align/align.o
            CFLAGS += -DCONFIG_ENABLE_ALIGNMENT_MODULE   
        endif
    #+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        ifeq ($(strip $(CONFIG_ENABLE_STATE_MACHINE_MODULE)),y)
            submodules_sofa += state_machine
            link_obj += state_machine/state_machine.o
            CFLAGS += -DCONFIG_ENABLE_STATE_MACHINE_MODULE
        endif
    #+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        ifeq ($(strip $(CONFIG_CHECK_ABOUT_SIGNATURE)),y)
            CFLAGS += -DCONFIG_CHECK_ABOUT_SIGNATURE
        endif
    #+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
       
        submodules_carpet = common
        link_obj += common/common.o

        CROSS :=
        CROSS_LD := gcc
        export CROSS

    #+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        ifeq ($(strip $(CONFIG_REBUILD_COMMON)),y)
            submodules_floor = clean_common
            submodules_floor_build_command = \
                @echo "===> clean common module";\
                make -C common clean;\
                echo "----------------------------------------------------------------------"

        endif
    #+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        export CFLAGS    
        include $(TOPDIR)/Rules.mak

#############################################################################
else # need to be configured

$(config_targets):
	@make -C $(config_folder_name) $(MAKECMDGOALS)
   
.PHONY: $(config_targets)

endif
