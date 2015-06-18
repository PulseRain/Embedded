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
#include "stdlib.h"
#include "time.h"
#include "about.h"
#include "about_CRC32.h"

enum FSM_State {
    STATE_INIT,
    STATE_PLAN,
    STATE_CONTROL,
    STATE_EXECUTE,
    STATE_CLOSE
};


char *state_name_string[] = {
    "STATE_INIT",
    "STATE_PLAN",
    "STATE_CONTROL",
    "STATE_EXECUTE",
    "STATE_CLOSE"
};


enum FSM_State FSM(int input)
{
    static enum FSM_State state = STATE_INIT;
    enum FSM_State prev_state;
   
    printf ("current state = %s\n", state_name_string[state]);
   
    prev_state = state;
   
    switch (state) {
        case STATE_INIT:
		    	  logo_print();
            
            if (input == 0) {
                state = STATE_PLAN;
            } 
           
            break;
           
        case STATE_PLAN:    
            if (input == 0) {
            	  printf ("proceed to execute\n");
                state = STATE_EXECUTE;
            }
           
            break;
           
        case STATE_EXECUTE:
				
            if (input > 0) {
            	  printf ("about to close\n");
                state = STATE_CLOSE;
            } else if (input < 0) {
                state = STATE_CONTROL;
            }
           
            break;
           
        case STATE_CONTROL:
            if (input > 0) {
                state = STATE_EXECUTE;
            } else if (input < 0) {
                state = STATE_PLAN;
            }
           
            break;
   
        case STATE_CLOSE:
            printf ("Game Over!\n");
            printf ("ABOUT_CRC32 = 0x%x\n", ABOUT_CRC32);
            break;
           
        default:
            printf (" unknown state, index = %d\n", state);
            break;
    } // End of switch
   
    return prev_state;
} // End of FSM()


void FSM_Test()
{
    int FSM_input;
    unsigned int temp;
    srand(time(0));

    do {
        temp = rand() % 100;
       
        if (temp < 5) {
            FSM_input = 1;
        } else if (temp < 10) {
            FSM_input = -1;
        } else {
            FSM_input = 0;
        }
   
    } while (FSM(FSM_input) != STATE_CLOSE); 
 

} // End of FSM_Test()


