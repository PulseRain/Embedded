
CFLAGS = -c -Wall -g


.PHONY: all clean

OBJECT = tab.o

target = tab.exe

all:    $(OBJECT)
	gcc -g $(OBJECT) -o tab

clean: 
	-@rm -vf $(target) 
	-@find . -type f \( -name "*.d" -o -name "*.o" \) -exec rm -vf {} \;    
    
.c.o: 
	gcc $(CFLAGS) $<	
