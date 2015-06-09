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

/******************************************************************************
*
* Remarks:
*   This is the head file for USB Communication Devices
*   (Noted by C.Gu on 04/12/2011)
*
* References:
*
* [1] Universal Serial Bus Class Definition for Communication Devices, Rev 1.2
*     Nov 3, 2010
*
* [2] Universal Serial Bus Communication Class Subclass Specification for 
*     PSTN Devices, Rev 1.2, Feb 9, 2007
******************************************************************************/


#ifndef USB_CDC_H
#define USB_CDC_H

#include "common_type.h"

#define CDC_SPEC_VER_1_2_BCD    0x0120          // USB CDC spec 1.2 in BCD code


//===========================================================================
// Communication Class Function Descriptor Type (See Ref[1] for detail.)
//===========================================================================
#define CDC_TYPE_CS_INTERFACE                                       0x24
#define CDC_TYPE_CS_ENDPOINT                                        0x25


//===========================================================================
// Communication Class Function Descriptor Subtype (See Ref[1] for detail.)
//===========================================================================

#define CDC_SUBTYPE_HEADER                                          0x00
#define CDC_SUBTYPE_CALL_MANAGEMENT                                 0x01
#define CDC_SUBTYPE_ABSTRACT_CONTROL_MANAGEMENT                     0x02
#define CDC_SUBTYPE_DIRECT_LINE_MANAGEMENT                          0x03
#define CDC_SUBTYPE_TELEPHONE_RINGER                                0x04
#define CDC_SUBTYPE_TELEPHONE_CALL_LINE_STATE                       0x05
#define CDC_SUBTYPE_UNION                                           0x06
#define CDC_SUBTYPE_COUNTRY_SELECTION                               0x07
#define CDC_SUBTYPE_TELEPHONE_OPERATIONAL_MODES                     0x08
#define CDC_SUBTYPE_USB_TERMINALEVICE_MANAGEMENT                    0x09
#define CDC_SUBTYPE_NETWORK_CHANNEL_TERMINAL                        0x0A
#define CDC_SUBTYPE_PROTOCOL_UNIT                                   0x0B
#define CDC_SUBTYPE_EXTENSION_UNIT                                  0x0C
#define CDC_SUBTYPE_MULTI_CHANNEL_MANAGEMENT                        0x0D
#define CDC_SUBTYPE_CAPI_CONTROL_MANAGEMENT                         0x0E
#define CDC_SUBTYPE_ETHERNET_NETWORKING                             0x0F
#define CDC_SUBTYPE_ATM_NETWORKING                                  0x10
#define CDC_SUBTYPE_WIRELESS_HANDSET_CONTROL                        0x11

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// Setup Command, 
// USB Communication Class Specific Request Code (Table 19 of Ref [1])
//===========================================================================

#define SC_SEND_ENCAPSULATED_CMD                                    0x00
#define SC_GET_ENCAPSULATED_CMD                                     0x01
#define SC_SET_COMM_FEATURE                                         0x02
#define SC_GET_COMM_FEATURE                                         0x03
#define SC_CLEAR_COMM_FEATURE                                       0x04
#define SC_SET_LINE_CODING                                          0x20
#define SC_GET_LINE_CODING                                          0x21
#define SC_SET_CONTROL_LINE_STATE                                   0x22
#define SC_SEND_BREAK                                               0x23

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//===========================================================================
// USB CDC Header Functional Descriptor
//===========================================================================

typedef struct {
    U8  bFunctionLength;                                // size of the descriptor in bytes
    U8  bDescriptorType;                                // CS_INTERFACE 
    U8  bDescriptorSubtype;                             // CDC_SUBTYPE_HEADER
    U16 bcdCDC;                                         // CDC spec release number
} PACKED CDC_HEADER_FUNCTIONAL_DESCRIPTOR, PACKED *PCDC_HEADER_FUNCTIONAL_DESCRIPTOR;

C_ASSERT(sizeof(CDC_HEADER_FUNCTIONAL_DESCRIPTOR) == 5);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB CDC Union Functional Descriptor
//===========================================================================

// only 1 subordinate interface

typedef struct {
    U8  bFunctionLength;                                // size of the descriptor in bytes
    U8  bDescriptorType;                                // CS_INTERFACE 
    U8  bDescriptorSubtype;                             // CDC_SUBTYPE_UNION
    U8  bControlInterface;                              // interface number of the controlling interface
    U8  bSubordinateInterface;                          // first subordinate interface
} PACKED CDC_UNION_FUNCTIONAL_DESCRIPTOR, PACKED *PCDC_UNION_FUNCTIONAL_DESCRIPTOR;

C_ASSERT(sizeof(CDC_UNION_FUNCTIONAL_DESCRIPTOR) == 5);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===========================================================================
// USB CDC Call Management Functional Descriptor
//===========================================================================


#define PSTN_DEVICE_HANDLE_CALL                         1
#define PSTN_DEVICE_NOT_HANDLE_CALL                     0

#define PSTN_CALL_MANAGEMENT_OVER_DATA_CLASS_INTERFACE  1
#define PSTN_CALL_MANAGEMENT_OVER_COMM_CLASS_INTERFACE  0

typedef struct {

    U8  bFunctionLength;                                // size of the descriptor in bytes
    U8  bDescriptorType;                                // CS_INTERFACE 
    U8  bDescriptorSubtype;                             // CDC_SUBTYPE_CALL_MANAGEMENT
    union {

        struct {
            U8  call_handle             : 1;            // 1 - device handle call ; 0 - device not handle call

            U8  inband_call_management  : 1;            // 1 - call management over data class interface
                                                        // 0 - call management over comm class interface

            U8  zeros                   : 6;            // reserved, reset to zero                                          

        } capabilities;
                
        U8 bCacabilities;
    } bmCapabilities;

    U8 bDataInterface;                                  // interface num of data class interface optionally used
                                                        // for call management

}PACKED CDC_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR, PACKED *PCDC_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR;

C_ASSERT(sizeof(CDC_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR) == 5);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB CDC Abstract Control Management Functional Descriptor
//===========================================================================

typedef struct {

    U8  bFunctionLength;                                // size of the descriptor in bytes
    U8  bDescriptorType;                                // CS_INTERFACE 
    U8  bDescriptorSubtype;                             // CDC_SUBTYPE_ABSTRACT_CONTROL_MANAGEMENT
    union {

        struct {
            U8  comm_feature            : 1;            // whether support set_comm_feature, clear_comm_feature etc

            U8  line_coding_line_state  : 1;            // whether support set_line_coding etc

            U8  send_break              : 1;            // whether support send_break

            U8  network_connection      : 1;            // whether support network connection

            U8  zeros                   : 4;            // reserved, reset to zero                                          

        } capabilities;
                
        U8 bCacabilities;
        
    } bmCapabilities;


} PACKED ABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR,
  PACKED *PABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR;

C_ASSERT(sizeof(ABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR) == 4);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB CDC RS232 Line Coding Structure (Table 17, Ref[2])
//===========================================================================

#define RS232_LINE_CODING_1_STOP_BIT                0x0
#define RS232_LINE_CODING_1_AND_HALF_STOP_BIT       0x1
#define RS232_LINE_CODING_2_STOP_BIT                0x2

#define RS232_LINE_CODING_NONE_PARITY               0x0
#define RS232_LINE_CODING_ODD_PARITY                0x1
#define RS232_LINE_CODING_EVEN_PARITY               0x2
#define RS232_LINE_CODING_MARK_PARITY               0x3
#define RS232_LINE_CODING_SPACE_PARITY              0x4


typedef struct {
    U32 dwDTERate;                                      // in Bits per Second
    U8  bCharFormat;                                    // Stop Bit
    U8  bParityType;                                    // Parity Bit
    U8  bDataBits;                                      // Data Bit (5, 6, 7, 8 or 16)
} PACKED RS232_LINE_CODING_STRUCTURE,
  PACKED *PRS232_LINE_CODING_STRUCTURE;

C_ASSERT(sizeof(RS232_LINE_CODING_STRUCTURE) == 7);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif

