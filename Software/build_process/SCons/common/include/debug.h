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


#ifndef DEBUG_H
#define DEBUG_H

           

#include "stdio.h"
#define CONSOLE_PRINT printf

//#include <linux/kernel.h>
//#define CONSOLE_PRINT printk
    
#if defined (__GNUC__)  // GNU C defined
    
    #if defined(DEBUG)  
        
        #define DEBUG_PRINT(fmt, args...) CONSOLE_PRINT("DEBUG: " fmt, ##args)

        #define DEBUG_ASSERT_WARNING(val) do{ \
                                            if(!(val)) {\
                                                DEBUG_PRINT ("ASSERTION FAIL at File %s, Line %d\n", __FILE__, __LINE__); \
                                            } \
                                        }while(0)
        
        #define DEBUG_ASSERT_FATAL(val) do { \
                                            DEBUG_ASSERT_WARNING(val); \
                                            if(!(val)) { \
                                                *((int*)0) = 0; \
                                            } \
                                        } while (0)

    #else
        #define DEBUG_PRINT(fmt, args...)
        #define DEBUG_ASSERT_WARNING (val)
        #define DEBUG_ASSERT_FATAL(val)
    #endif

#else   //  GNU C not defined

    #if defined(DEBUG)  
        
        #define DEBUG_PRINT(_x_) \
            do{printf ("DEBUG: "); CONSOLE_PRINT _x_;}while(0)


        #define DEBUG_ASSERT_WARNING(val) do{ \
                                            if(!(val)) {\
                                                DEBUG_PRINT (("ASSERTION FAIL at File %s, Line %d\n", __FILE__, __LINE__)); \
                                            } \
                                        }while(0)
        
        #define DEBUG_ASSERT_FATAL(val) do { \
                                            DEBUG_ASSERT_WARNING(val); \
                                            if(!(val)) { \
                                                *((int*)0) = 0; \
                                            } \
                                        } while (0)

    #else
        #define DEBUG_PRINT(fmt, args)
        #define DEBUG_ASSERT_WARNING (val)
        #define DEBUG_ASSERT_FATAL(val)
    #endif

        
#endif


#define C_ASSERT(cond) \
    extern char compile_time_assertion[(cond) ? 1 : -1]
#endif


#define FIELD_OFFSET(type, field) \
        ((long)(long*)&(((type *)0)->field)) 
        

//#define TYPE_ALIGNMENT( t ) FIELD_OFFSET( struct { char x; t test; }, test )

#define TYPE_ALIGNMENT( t ) \
        ((long)(sizeof(struct { char x; t test; }) - sizeof(t)))
