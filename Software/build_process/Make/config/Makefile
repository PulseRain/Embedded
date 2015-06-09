
HOST_CC ?= gcc
HOST_CXX ?= g++

ifndef TOPDIR
	TOPDIR := $(shell pwd)/..
endif


menuconfig config gconfig xconfig:
	@make -f scripts/Makefile.build obj=scripts/basic HOSTCC=$(HOST_CC) HOSTCXX=$(HOST_CXX) srctree=$(shell pwd)
	@make -f scripts/Makefile.build obj=scripts/kconfig $@ HOSTCC=$(HOST_CC) HOSTCXX=$(HOST_CXX) srctree=$(shell pwd) Kconfig=$(TOPDIR)/Config.in

clean:
	-@rm -vf scripts/basic/fixdep
	-@rm -vf scripts/kconfig/mconf
	-@rm -vf scripts/kconfig/conf
	-@rm -vf scripts/kconfig/gconf
	-@rm -vf scripts/kconfig/qconf
	-@rm -vf scripts/kconfig/.tmp_qtcheck
	-@rm -vf scripts/kconfig/.tmp_gtkcheck
	-@find . -type f \( -name "*.d" -o -name "*.o" -o -name "*.cmd" -o -name "*.moc" \) -exec rm -vf {} \;

.PHONY : menuconfig config gconfig xconfig clean
