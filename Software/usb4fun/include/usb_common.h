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
*   This is the common head file for various USB structure and definitions. 
*   (Noted by C.Gu on 03/25/2011)
*
* References:
* [1] USB Class Codes (http://www.usb.org/developers/defined_class)
* [2] Universal Serial Bus Specification, Revision 2.0, Compaq, 
*     Hewlett-Packard, Intel, Lucent, Microsoft, NEC, Philips, April 27, 2000
* [3] Universal Serial Bus 3.0 Specification, Revision 1.0, Hewlett-Packard 
*     Company, Intel Corporation, Microsoft Corporation, NEC Corporation, 
*     ST-NXP Wireless, Texas Instruments, Nov 12, 2008
* [4] Universal Serial Bus (USB) Language Identifiers (LANGIDs), Version 1.0
*     USB Implementers¡¯ Forum, 03/29/2000
* [5] USB ECN, Interface Association Descriptors
* [6] USB Interface Association Descriptor Device Class Code and Use Model,
*     Intel Corporation, Rev 1.0, Jul 23, 2003
******************************************************************************/

#ifndef USB_COMMON_H
#define USB_COMMON_H

#include "common_type.h"


#define USB_SPEC_VER_2_0_BCD    0x0002          // USB spec 2.0 in BCD code
#define USB_SPEC_VER_3_0_BCD    0x0003          // USB spec 3.0 in BCD code


//===========================================================================
// USB Class Code (Base, Sub, Protocol, See Ref[1] for detail.)
//===========================================================================

#define USB_BASE_CLASS_DEVICE_USE_INTERFACE_DESCRIPTOR      0x0
    #define USB_SUB_CLASS_DEVICE_USE_INTERFACE_DESCRIPTOR       0x0
    #define USB_PROTOCOL_DEVICE_USE_INTERFACE_DESCRIPTOR        0x0

#define USB_BASE_CLASS_INTERFACE_AUDIO                      0x1

#define USB_BASE_CLASS_DEVICE_COMMUNICATION                 0x2
    #define USB_SUBCLASS_DEVICE_DIRECT_LINE_CONTROL_MODEL       0x01 
    #define USB_SUBCLASS_DEVICE_ABSTRACT_CONTROL_MODEL          0x02
    #define USB_SUBCLASS_DEVICE_TELEPHONE_CONTROL_MODEL         0x03

    #define USB_PROTOCOL_DEVICE_NO_SPECIFIC_PROTOCOL            0x00
    #define USB_PROTOCOL_DEVICE_AT_COMMANDS                     0x01


#define USB_BASE_CLASS_INTERFACE_CDC_CONTROL                0x2
#define USB_BASE_CLASS_INTERFACE_CDC_DATA                   0xA

    #define USB_SUBCLASS_INTERFACE_DIRECT_LINE_CONTROL_MODEL    0x01 
    #define USB_SUBCLASS_INTERFACE_ABSTRACT_CONTROL_MODEL       0x02
    #define USB_SUBCLASS_INTERFACE_TELEPHONE_CONTROL_MODEL      0x03

    #define USB_PROTOCOL_INTERFACE_NO_SPECIFIC_PROTOCOL         0x00
    #define USB_PROTOCOL_INTERFACE_AT_COMMANDS                  0x01


#define USB_BASE_CLASS_INTERFACE_HID                        0x3
#define USB_BASE_CLASS_INTERFACE_PHYSICAL                   0x5
#define USB_BASE_CLASS_INTERFACE_IMAGE                      0x6
#define USB_BASE_CLASS_INTERFACE_PRINTER                    0x7
#define USB_BASE_CLASS_INTERFACE_MASS_STORAGE               0x8

#define USB_BASE_CLASS_DEVICE_HUB                           0x9

#define USB_BASE_CLASS_INTERFACE_SMART_CARD                 0xB
#define USB_BASE_CLASS_INTERFACE_CONTENT_SECURITY           0xD
#define USB_BASE_CLASS_INTERFACE_CONTENT_VIDEO              0xE
#define USB_BASE_CLASS_INTERFACE_PERSONAL_HEALTH_CARE       0xF

#define USB_BASE_CLASS_DEVICE_DIAGNOSTIC_DEVICE             0xDC
#define USB_BASE_CLASS_INTERFACE_DIAGNOSTIC_DEVICE          0xDC

#define USB_BASE_CLASS_INTERFACE_WIRELESS_CONTROL           0xE0

#define USB_BASE_CLASS_DEVICE_MISC                          0xEF
	#define USB_SUBCLASS_COMMON										0x02
	#define USB_PROTOCOL_INTERFACE_ASSOCIATION_DESCRIPTOR			0x01

#define USB_BASE_CLASS_INTERFACE_MISC                       0xEF

#define USB_BASE_CLASS_INTERFACE_APP_SPECIFIC               0xFE
    

#define USB_BASE_CLASS_DEVICE_VENDOR_SPECIFIC               0xFF
#define USB_BASE_CLASS_INTERFACE_VENDOR_SPECIFIC            0xFF

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB Descriptor Type
//===========================================================================
#define USB_DESCRIPTOR_DEVICE                               1
#define USB_DESCRIPTOR_CONFIGURATION                        2
#define USB_DESCRIPTOR_STRING                               3
#define USB_DESCRIPTOR_INTERFACE                            4
#define USB_DESCRIPTOR_ENDPOINT                             5
#define USB_DESCRIPTOR_DEVICE_QUALIFIER                     6
#define USB_DESCRIPTOR_OTHER_SPEED_CONFIGURATION            7
#define USB_DESCRIPTOR_INTERFACE_POWER                      8
#define USB_DESCRIPTOR_OTG                                  9
#define USB_DESCRIPTOR_DEBUG                                10
#define USB_DESCRIPTOR_INTERFACE_ASSOCIATION                11
#define USB_DESCRIPTOR_BOS                                  15
#define USB_DESCRIPTOR_DEVICE_CAPABILITY                    16
#define USB_DESCRIPTOR_SUPERSPEED_USB_ENDPOINT_COMPANION    48

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB Endpoint Direction
//===========================================================================
#define USB_ENDPOINT_IN                                     1
#define USB_ENDPOINT_OUT                                    0
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===========================================================================
// USB Endpoint Transfer Type
//===========================================================================
#define USB_ENDPOINT_CONTROL                                0x0
#define USB_ENDPOINT_ISOCHRONOUS                            0x1
#define USB_ENDPOINT_BULK                                   0x2
#define USB_ENDPOINT_INTERRUPT                              0x3
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB bmRequestType Field Definition (See Table 9-2 in Ref[2][3] for detail)
//===========================================================================
#define USB_REQ_DATA_HOST_TO_DEVICE                         0
#define USB_REQ_DATA_DEVICE_TO_HOST                         1
#define USB_REQ_FIELD_DATA_TRANSFER_DIRECTION(x)            ((x) << 7)

#define USB_REQ_TYPE_STANDARD                               0
#define USB_REQ_TYPE_CLASS                                  1
#define USB_REQ_TYPE_VENDOR                                 2
#define USB_REQ_FIELD_TYPE(x)                               ((x) << 5)

#define USB_REQ_RECIPIENT_DEVICE                            0
#define USB_REQ_RECIPIENT_INTERFACE                         1
#define USB_REQ_RECIPIENT_ENDPOINT                          2
#define USB_REQ_RECIPIENT_OTHER                             3
#define USB_REQ_FIELD_RECIPIENT(x)                          ((x))


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB Standard Request Code (See Table 9-4 in Ref[2][3] for detail)
//===========================================================================
#define USB_STD_REQ_GET_STATUS                              0
#define USB_STD_REQ_CLEAR_FEATURE                           1
#define USB_STD_REQ_SET_FEATURE                             3
#define USB_STD_REQ_SET_ADDRESS                             5
#define USB_STD_REQ_GET_DESCRIPTOR                          6
#define USB_STD_REQ_SET_DESCRIPTOR                          7
#define USB_STD_REQ_GET_CONFIGURATION                       8
#define USB_STD_REQ_SET_CONFIGURATION                       9
#define USB_STD_REQ_GET_INTERFACE                           10
#define USB_STD_REQ_SET_INTERFACE                           11
#define USB_STD_REQ_SYNC_FRAME                              12
#define USB_STD_REQ_SET_SEL                                 48
#define USB_STD_REQ_SET_ISOCH_DELAY                         49
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB Language ID (See Ref[4] for detail)
//===========================================================================

#define USB_LANGID_ENGLISH_US                               0x0409
#define USB_LANGID_ENGLISH_UK                               0x0809

#define USB_LANGID_CHINESE_TAIWAN                           0x0404
#define USB_LANGID_CHINESE_PRC                              0x0804
#define USB_LANGID_CHINESE_HONGKONG                         0x0C04
#define USB_LANGID_CHINESE_SINGAPORE                        0x1004
#define USB_LANGID_CHINESE_MACAU                            0x1404

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===========================================================================
// USB Standard Device Descriptor
//===========================================================================

typedef struct {
    
    U8  bLength;                    // Size of this descriptor in bytes
    U8  bDescriptorType;            // DEVICE Descriptor Type
    U16 bcdUSB;                     // USB Spec Release Num in Binary-Coded Decimal
    U8  bDeviceClass;               // Class Code (See Ref[1] for more detail.)
    U8  bDeviceSubClass;            // Sub Class 
    U8  bDeviceProtocol;            // Protocol Code
    U8  bMaxPacketSize0;            // Max packet size for EP0
                                    //
                                    // For USB 2.0, the valid value is
                                    // 8, 16, 32, 64
                                    //
                                    // For USB 3.0, 
                                    // The bMaxPacketSize0 value is used as the 
                                    // exponent for a 2^bMaxPacketeSize0 value.
                                    // valid value can be 3, 4, 5, 6, 9
                                    // 9 is the only valid value for Superspeed mode
   
    U16 idVendor;                   // Vendor ID
    U16 idProduct;                  // Product ID
    
    U16 bcdDevice;                  // Device Release Num in BCD
    U8  iManufacturer;              // Index of string descriptor describing manufacturer
    U8  iProduct;                   // Index of string descriptor describing product
    
    U8  iSerialNumber;              // Index of string descriptor describing the device's serial number
    U8  bNumConfigurations;         // Number of possible configurations

}PACKED USB_STANDARD_DEVICE_DESCRIPTOR, PACKED *PUSB_STANDARD_DEVICE_DESCRIPTOR;

C_ASSERT(sizeof(USB_STANDARD_DEVICE_DESCRIPTOR) == 18);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//===========================================================================
// USB Standard Configuration Descriptor
//===========================================================================
typedef struct {
    U8 bLength;                     // Size of this descriptor in bytes
    U8 bDescriptorType;             // CONFIGURATION Descriptor Type
    U16 wTotalLength;               // Total length of data returned for this configuration
    
    U8 bNumInterfaces;              // Number of interfaces supported by this configuration
    U8 bConfigurationValue;         // value to use as an argument to the SetConfiguration() 
                                    // request to select this configuration
    
    U8 iConfiguration;              // index of string descriptor describing this configuration
    
    union {
        struct {
            U8 zeros        : 5;    // reserved, reset to zero
            U8 remoteWakeup : 1;    
            U8 selfPowered  : 1;    
            U8 one          : 1;    // reserved, set to one for historic reasons
        } bmAttributes;
        U8 bAttributes;
     
    } attributes;
    
    U8 bMaxPower;                   // maximum power consumption from the bus.
                                    // expressed in 2-mA unit for high speed mode
                                    // expressed in 8-mA unit for super speed mode
                                    

}PACKED USB_STANDARD_CONFIGURATION_DESCRIPTOR, PACKED *PUSB_STANDARD_CONFIGURATION_DESCRIPTOR;

C_ASSERT (sizeof(USB_STANDARD_CONFIGURATION_DESCRIPTOR) == 9);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB Standard Interface Descriptor
//===========================================================================
typedef struct {
    U8  bLength;                            // size of the descriptor in bytes
    U8  bDescriptorType;                    // INTERFACE Descriptor Type
    U8  bInterfaceNumber;                   // number of this interface
    U8  bAlternateSetting;                  // alternate setting 
    
    U8  bNumEndpoints;                      // num of endpoints used by this interface
    U8  bInterfaceClass;                    // Class Code
    U8  bInterfaceSubClass;                 // Subclass Code
    U8  bInterfaceProtocol;                 // Protocol Code
    
    U8  iInterface;                         // index of string descriptor describing this interface
   
}PACKED USB_STANDARD_INTERFACE_DESCRIPTOR, PACKED *PUSB_STANDARD_INTERFACE_DESCRIPTOR; 

C_ASSERT(sizeof(USB_STANDARD_INTERFACE_DESCRIPTOR) == 9);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB Standard Endpoint Descriptor
//===========================================================================
typedef struct {
    U8  bLength;                            // size of this descriptor in bytes
    U8  bDescriptor;                        // ENDPOINT Descriptor Type
    
    union {
        struct {
            U8  endpointNumber      : 4;    // endpoint number
            U8  zeros               : 3;    // reserved, reset to zero
            U8  direction           : 1;    // 0 = OUT endpoint, 1 = IN endpoint   
        } bmEndpointAddress;
        U8  bEndpointAddress;
    } endpointAddress;
    
    union {
        struct {
            U8 transferType     : 2;        // transfer type
            U8 zeros            : 6;        // reserved, reset to zero
        } bulk_or_control;
            
        struct {
            U8 transferType     : 2;        // transfer type
            U8 zeros            : 2;        // reserved, reset to zero
            U8 usageType        : 2;        // 00 = period, 01 = notification
            U8 reserved         : 2;        // reserved, reset to zero
        } interrupt_EP;
        
        struct {
            U8 transferType     : 2;        // transfer type
            U8 synchType        : 2;        // Synchronization Type
            U8 usageType        : 2;        // Usage Type;
            U8 reserved         : 2;        // reserved, reset to zero
        } isochronous_EP;
        
        U8  bAttributes;            

    } bmAttributes; 
     
    U16 wMaxPacketSize;                      // Maximum packet size     
    
    U8  bInterval;                           // interval for servicing the EP, in 125 us unit

} PACKED USB_STANDARD_ENDPOINT_DESCRIPTOR, PACKED *PUSB_STANDARD_ENDPOINT_DESCRIPTOR;

C_ASSERT(sizeof(USB_STANDARD_ENDPOINT_DESCRIPTOR) == 7);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB Device Qualifier Descriptor
//===========================================================================
typedef struct {
    U8  bLength;                            // size of descriptor
    U8  bDescriptor;                        // Device Qualifier Type
    U16 bcdUSB;                             // USB Spec Release Num in Binary-Coded Decimal
    U8  bDeviceClass;                       // Class Code
    U8  bDeviceSubClass;                    // SubClass Code
    U8  bDeviceProtocol;                    // Protocol Code
    U8  bMaxPacketSize0;                    // Max Packet size for other speed
    U8  bNumConfigurations;                 // Num of other speed configurations
    U8  bReserved;                          // must be zero

} PACKED USB_DEVICE_QUALIFIER_DESCRIPTOR, PACKED *PUSB_DEVICE_QUALIFIER_DESCRIPTOR;

C_ASSERT(sizeof(USB_DEVICE_QUALIFIER_DESCRIPTOR) == 10);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB Device Request
//===========================================================================
typedef struct {
    union {
        U8 bRequestType;
        struct { // Assume little endian
            U8 recipient             : 5;
            U8 type                  : 2;
            U8 dataTransferDirection : 1;
        }bmRequestType;
    } requestType;                          // See Ref [2][3] for detail
    
    U8 bRequest;                            // See Ref[2][3], Table 9-3         
    
    U16 wValue;                             // field that varies according to request
    union {
        U16 wIndex;                         // field that varies according to request
        struct {    // assume little endian
            U16 EP_Num               : 4;
            U16 reserved_part1       : 3;
            U16 direction            : 1;
            U16 reserved_part2       : 8;
        }bmIndex_EP;
    }index;
    
    U16 wLength;                            // num of bytes to transfer if there is a Data stage

}PACKED USB_DEVICE_REQUEST, PACKED *PUSB_DEVICE_REQUEST;

C_ASSERT(sizeof(USB_DEVICE_REQUEST) == 8);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB String Descriptor, 
//===========================================================================
typedef struct { // This struct only supports one lanauge ID
    U8  bLength;                        // size of this descriptor in bytes
    U8  bDescriptorType;                // STRING Descriptpr type
    U16 wLanguageID;                    // LANGID code zero
} PACKED USB_STRING_DESCRIPTOR_ZERO, PACKED *PUSB_STRING_DESCRIPTOR_ZERO;

C_ASSERT(sizeof(USB_STRING_DESCRIPTOR_ZERO) == 4);

typedef struct {
    U8  bLength;                        // size of this descriptor in bytes
    U8  bDescriptorType;                // STRING Descriptpr type
} PACKED USB_UNICODE_STRING_DESCRIPTOR_HEAD, PACKED *PUSB_UNICODE_STRING_DESCRIPTOR_HEAD;

C_ASSERT(sizeof(USB_UNICODE_STRING_DESCRIPTOR_HEAD) == 2);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//===========================================================================
// USB Interface Association Descriptor
//===========================================================================

typedef struct {
	U8 	bLength;						// Size of this descriptor in bytes
	U8  bDescriptorType;				// INTERFACE ASSOCIATION Descriptor
	U8  bFirstInterface;				// Interface number of the first interface that is associated with this function
	U8  bInterfaceCount;				// Number of contiguous interfaces that are associated with this function
	U8	bFunctionClass;					// Class code
	U8  bFunctionSubClass;				// Subclass code
	U8  bFunctionProtocol;				// Protocol code
	U8  iFunction;						// Index of string descriptor describing this function
} PACKED USB_INTERFACE_ASSOCIATION_DESCRIPTOR, PACKED *PUSB_INTERFACE_ASSOCIATION_DESCRIPTOR;

C_ASSERT(sizeof(USB_INTERFACE_ASSOCIATION_DESCRIPTOR) == 8);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif

