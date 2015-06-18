/******************************************************************************
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*
* Remarks:
*   header file for various debug macros
*   (Noted by C.Gu on 03/25/2011)
*
* References:
******************************************************************************/

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
        

//#define TYPE_ALIGNMENT( t ) \
//        FIELD_OFFSET( struct { char x; t test; }, test )

#define TYPE_ALIGNMENT( t ) \
        ((long)(sizeof(struct { char x; t test; }) - sizeof(t)))
