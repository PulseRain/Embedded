#include "common_type.h"
#include "debug.h"
#include "about.h"

C_ASSERT(sizeof(U8) == 1);

void main()
{
	about();
	
	DEBUG_PRINT ("debug print\n");
	
}
