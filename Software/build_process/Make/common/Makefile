
obj =  about.o CRC32.o

additional_files = include/about_CRC32.h 

target = common.o

ifndef TOPDIR
	TOPDIR := ..
endif


LDFLAGS += -r

## post_link_action = objdump -s about.o | perl about_sig_CRC32.pl > include/about_CRC32.h
include $(TOPDIR)/Rules.mak

include/about_CRC32.h : about.o  
	objdump -s about.o | perl about_sig_CRC32.pl > include/about_CRC32.h
	@echo "----------------------------------------------------------------------"
	
