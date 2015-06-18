/*
//===========================================================================
// Copyright (c) : Pulserain Technology, LLC. 2015
//===========================================================================
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
*/


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

