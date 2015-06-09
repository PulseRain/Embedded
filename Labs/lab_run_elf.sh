gcc -fno-exceptions -m32 -c lost.c 
objcopy --remove-section=.comment lost.o
ld -o my_output01.elf -T link_script01.x lost.o 
ld -o my_output02.elf -T link_script02.x lost.o 
objdump -h my_output01.elf
objdump -h my_output02.elf
objcopy -O binary my_output02.elf my_output02.bin
echo "Hex Dump"
hexdump -C my_output02.bin
