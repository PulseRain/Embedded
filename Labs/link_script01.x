MEMORY 
{
    ROM  : org = 0x200,  len = 0x1000
    SRAM : org = 0x1300, len = 0x300
    DDR  : org = 0x1900, len = 0x200
}

SECTIONS
{

  my_code : 

  {*(.text);} >SRAM

  my_data : 
    {*(.data);*(.rodata);} >SRAM
  
  .bss :
    {*(.bss);} >DDR

  other :
    {*(.*);} >SRAM 

}
