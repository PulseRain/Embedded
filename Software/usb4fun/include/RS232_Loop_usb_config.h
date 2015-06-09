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
*   This is the head file for RS232 USB device (ACM)
*   (Noted by C.Gu on 07/10/2011)
*
* References:
*
* [1] Universal Serial Bus Class Definition for Communication Devices, Rev 1.2
*     Nov 3, 2010
*
* [2] Universal Serial Bus Communication Class Subclass Specification for 
*     PSTN Devices, Rev 1.2, Feb 9, 2007
******************************************************************************/
#ifndef RS232_LOOP_USB_CONFIG_H
#define RS232_LOOP_USB_CONFIG_H

#include "usb_common.h"
#include "USB_CDC.h"


//===========================================================================
// USB High Speed Interface Descriptor
//===========================================================================

typedef struct {
    USB_STANDARD_INTERFACE_DESCRIPTOR stdInterface;
    USB_STANDARD_ENDPOINT_DESCRIPTOR EP2;
    USB_STANDARD_ENDPOINT_DESCRIPTOR EP4;
    USB_STANDARD_ENDPOINT_DESCRIPTOR EP6;
    USB_STANDARD_ENDPOINT_DESCRIPTOR EP8;
} PACKED USB_HIGH_SPEED_INTERFACE_DESCRIPTOR, PACKED *PUSB_HIGH_SPEED_INTERFACE_DESCRIPTOR;

C_ASSERT(sizeof(USB_HIGH_SPEED_INTERFACE_DESCRIPTOR) == \
    (sizeof(USB_STANDARD_INTERFACE_DESCRIPTOR) + sizeof(USB_STANDARD_ENDPOINT_DESCRIPTOR) * 4));
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===========================================================================
// USB Full Speed Interface Descriptor
//===========================================================================

typedef USB_HIGH_SPEED_INTERFACE_DESCRIPTOR USB_FULL_SPEED_INTERFACE_DESCRIPTOR;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB CDC ACM High Speed Interface Descriptor
//===========================================================================

typedef struct {
    USB_STANDARD_INTERFACE_DESCRIPTOR                   dataInterface;
    USB_STANDARD_ENDPOINT_DESCRIPTOR                    EP4;
    USB_STANDARD_ENDPOINT_DESCRIPTOR                    EP8;

    CDC_HEADER_FUNCTIONAL_DESCRIPTOR                    headerFunctionalDescriptor;
    CDC_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR           callManagementFunctionalDescriptor;
    ABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR   acmFunctionalDescriptor;
    CDC_UNION_FUNCTIONAL_DESCRIPTOR                     unionFunctionalDescriptor;

    USB_STANDARD_INTERFACE_DESCRIPTOR                   notificationInterface;
    USB_STANDARD_ENDPOINT_DESCRIPTOR                    EP6;    // Endpoint for notification

} PACKED USB_CDC_ACM_HIGH_SPEED_INTERFACE_DESCRIPTOR, 
  PACKED *PUSB_CDC_ACM_HIGH_SPEED_INTERFACE_DESCRIPTOR;

C_ASSERT(sizeof(USB_CDC_ACM_HIGH_SPEED_INTERFACE_DESCRIPTOR) == \
        (sizeof(USB_STANDARD_INTERFACE_DESCRIPTOR) * 2 + \
         sizeof(USB_STANDARD_ENDPOINT_DESCRIPTOR) * 3 + \ 
         sizeof(CDC_HEADER_FUNCTIONAL_DESCRIPTOR) + \
         sizeof(CDC_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR) + \
         sizeof(ABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR) + \
         sizeof(CDC_UNION_FUNCTIONAL_DESCRIPTOR)));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    
//===========================================================================
// USB CDC ACM Full Speed Interface Descriptor
//===========================================================================

typedef USB_CDC_ACM_HIGH_SPEED_INTERFACE_DESCRIPTOR USB_CDC_ACM_FULL_SPEED_INTERFACE_DESCRIPTOR;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//===========================================================================
// USB High Speed Configuration Descriptor
//===========================================================================

typedef struct {
    USB_STANDARD_CONFIGURATION_DESCRIPTOR stdConfig;
    USB_HIGH_SPEED_INTERFACE_DESCRIPTOR highSpeedInterface;
}PACKED USB_HIGH_SPEED_CONFIG_DESCRIPTOR, PACKED *PUSB_HIGH_SPEED_CONFIG_DESCRIPTOR;

C_ASSERT(sizeof(USB_HIGH_SPEED_CONFIG_DESCRIPTOR) == \
    sizeof(USB_STANDARD_CONFIGURATION_DESCRIPTOR) + sizeof(USB_HIGH_SPEED_INTERFACE_DESCRIPTOR));


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB Full Speed Configuration Descriptor
//===========================================================================

typedef struct {
    USB_STANDARD_CONFIGURATION_DESCRIPTOR stdConfig;
    USB_FULL_SPEED_INTERFACE_DESCRIPTOR fullSpeedInterface;
}PACKED USB_FULL_SPEED_CONFIG_DESCRIPTOR, PACKED *PUSB_FULL_SPEED_CONFIG_DESCRIPTOR;

C_ASSERT(sizeof(USB_FULL_SPEED_CONFIG_DESCRIPTOR) == \
    sizeof(USB_STANDARD_CONFIGURATION_DESCRIPTOR) + sizeof(USB_FULL_SPEED_INTERFACE_DESCRIPTOR));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB CDC ACM High Speed Configuration Descriptor
//===========================================================================

typedef struct {
    USB_STANDARD_CONFIGURATION_DESCRIPTOR stdConfig;
    USB_CDC_ACM_HIGH_SPEED_INTERFACE_DESCRIPTOR highSpeedInterface;
}PACKED USB_CDC_ACM_HIGH_SPEED_CONFIG_DESCRIPTOR, PACKED *PUSB_CDC_ACM_HIGH_SPEED_CONFIG_DESCRIPTOR;

C_ASSERT(sizeof(USB_CDC_ACM_HIGH_SPEED_CONFIG_DESCRIPTOR) == \
    sizeof(USB_STANDARD_CONFIGURATION_DESCRIPTOR) + sizeof(USB_CDC_ACM_HIGH_SPEED_INTERFACE_DESCRIPTOR));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//===========================================================================
// USB CDC ACM Full Speed Configuration Descriptor
//===========================================================================

typedef struct {
    USB_STANDARD_CONFIGURATION_DESCRIPTOR stdConfig;
    USB_CDC_ACM_FULL_SPEED_INTERFACE_DESCRIPTOR fullSpeedInterface;
}PACKED USB_CDC_ACM_FULL_SPEED_CONFIG_DESCRIPTOR, PACKED *PUSB_CDC_ACM_FULL_SPEED_CONFIG_DESCRIPTOR;

C_ASSERT(sizeof(USB_CDC_ACM_FULL_SPEED_CONFIG_DESCRIPTOR) == \
    sizeof(USB_STANDARD_CONFIGURATION_DESCRIPTOR) + sizeof(USB_CDC_ACM_FULL_SPEED_INTERFACE_DESCRIPTOR));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===========================================================================
// USB customized String Descriptor
//===========================================================================
typedef struct {
    USB_STRING_DESCRIPTOR_ZERO descritptorZero;
    USB_UNICODE_STRING_DESCRIPTOR_HEAD manufacturer;
    U16 manufacturerName[8];
    USB_UNICODE_STRING_DESCRIPTOR_HEAD product;
    U16 productName[14];
}PACKED USB_STRING_DESCRIPTOR, PACKED *PUSB_STRING_DESCRIPTOR;

C_ASSERT(sizeof(USB_STRING_DESCRIPTOR) == 52);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif

