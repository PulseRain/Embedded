#include "stdio.h"
#include "about.h"
#include "align.h"
#include "state_machine.h"
#include "about_CRC32.h"

int main (void)
{

#if defined (CONFIG_CHECK_ABOUT_SIGNATURE)
 	about(ABOUT_CRC32);
#endif

#if defined (CONFIG_ENABLE_ALIGNMENT_MODULE)
    DEBUG_PRINT ("========== align test ===============\n\n");
    alignment_test();	
#endif

#if defined (CONFIG_ENABLE_STATE_MACHINE_MODULE)
    DEBUG_PRINT ("==========  FSM test  ===============\n\n");
    FSM_Test();
#endif	
	  return 0;
} // End of main()

