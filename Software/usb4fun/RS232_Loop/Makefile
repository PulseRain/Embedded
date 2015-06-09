CYPRESS_USB_DIR := /cygdrive/e/Cypress/USB
KEIL_DIR := /cygdrive/c/Keil

PATH := $(PATH):$(KEIL_DIR)/C51/BIN:$(CYPRESS_USB_DIR)/bin;$(CYPRESS_USB_DIR)/Target/Lib/LP
export PATH


CC = C51
AS = A51
LD = LX51
GCC = gcc

C51_FLAGS = INCDIR\(E:\\Cypress\\USB\\Target\\Inc\;..\\include\; \
                 ..\\..\\common\\include\) DEFINE\(KEIL_C51\) DEBUG OBJECTEXTEND

GCC_FLAGS = -I/cygdrive/e/Cypress/USB/Target/Inc -I../include -I../../common/include -I$(KEIL_DIR)/C51/INC -DKEIL_C51 -DALLOCATE_EXTERN
 
ASFLAGS += -g 

#LDFLAGS += -g


#pattern rule

   

#== Put all the object files here
obj = fw.OBJ delay.OBJ discon.OBJ RS232_Loop.OBJ

#== replace space with comma in the $obj for Keil C51 linker
comma = ,
empty =
space = $(empty) $(empty)

additional_link_obj = E:\\Cypress\\USB\\Target\\Lib\\LP\\EZUSB.LIB, E:\\Cypress\\USB\\Target\\Lib\\LP\\USBJmpTb.OBJ
link_obj = $(additional_link_obj), $(subst $(space),$(comma),$(obj))



     
target = rs232_loop

all: $(obj)
	@echo "====> Linking"
	@$(LD) $(LDFLAGS) $(link_obj) TO $(target)
	@echo "====> HEX File Creating"
	@OHX51 $(target)
	@echo "====> Copying"	
	cp -f $(target) /cygdrive/e/temp/rs232_loop
	cp -f $(target).hex /cygdrive/e/temp/rs232_loop
	cp -f $(target).LST /cygdrive/e/temp/rs232_loop
	cp -f $(target).MAP /cygdrive/e/temp/rs232_loop
   
   
   
%.OBJ : %.c
	@echo "===> Building $@"
	@echo "============> Building Dependency"
	@$(GCC) $(GCC_FLAGS) -M $< | sed "s,[a-zA-Z0-9_-]*\.o\s*:,$*\.OBJ :," > $*.d
	@echo "============> Generating OBJ"
	@$(CC) $< $(C51_FLAGS); \
	if [ $$? -ge 2 ] ; then \
		exit 1; \
	fi
	@echo "----------------------------------------------------------------------------"




dependency = $(patsubst %.OBJ,%.d,$(obj)) 

ifneq "$(MAKECMDGOALS)" "clean"
	-include $(dependency)
endif

clean :
	-@rm -vf $(target)
	-@find . -type f \( -name "*.OBJ" -o -name "*.d" -o -name "*.o" -o -name "*.LST" -o -name "*.M51" \
	                    -o -name "*.hex" -o -name "*.rsp" \) -exec rm -vf {} \;



.PHONY: clean all
