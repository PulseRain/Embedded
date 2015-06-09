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
* Remarks:
*   This is the C file for RS232 USB device (ACM)
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

#pragma NOIV
#include "fx2.h"
#include "fx2regs.h"
#include "syncdly.h"            // SYNCDELAY macro


#include "RS232_Loop_usb_config.h"



//===========================================================================
// USB CDC RS232 Line Coding Structure (Table 17, Ref[2])
//===========================================================================
RS232_LINE_CODING_STRUCTURE data gRS232_Line_Coding = {
    KEIL_32BIT (115200),                            // dwDTERate
    RS232_LINE_CODING_1_STOP_BIT,                   // Stop Bit
    RS232_LINE_CODING_NONE_PARITY,                  // Parity Bit
    8                                               // Data Bit
};


//===========================================================================
// flag for setting Line Code
//===========================================================================
volatile BOOL bWaitForLineCodeStructure;


//===========================================================================
// USB Standard Device Descriptor
//===========================================================================


const USB_STANDARD_DEVICE_DESCRIPTOR code DeviceDscr = {
    sizeof(USB_STANDARD_DEVICE_DESCRIPTOR),         // bLength
    USB_DESCRIPTOR_DEVICE,                          // bDescriptorType
    KEIL_16BIT(USB_SPEC_VER_2_0_BCD),               // bcdUSB
    USB_BASE_CLASS_DEVICE_COMMUNICATION,            // bDeviceClass
    USB_SUB_CLASS_DEVICE_USE_INTERFACE_DESCRIPTOR,  // bDeviceSubClass
    USB_PROTOCOL_DEVICE_USE_INTERFACE_DESCRIPTOR,   // bDeviceProtocol,
    64,                                             // bMaxPacketSize0,
    KEIL_16BIT(0x04B4),                             // idVendor,
    KEIL_16BIT(0x7094),                             // idProduct
//  KEIL_16BIT(0x1004),                             // idProduct

    KEIL_16BIT(0x0000),                             // bcdDevice
    0x1,                                            // iManufacturer
    0x2,                                            // iProduct
    0x0,                                            // iSerialNumber
    0x1                                             // bNumConfigurations
};

//===========================================================================
// USB Device Qualifier Descriptor
//===========================================================================

const USB_DEVICE_QUALIFIER_DESCRIPTOR code DeviceQualDscr = {
    sizeof(USB_DEVICE_QUALIFIER_DESCRIPTOR),        	// bLength
    USB_DESCRIPTOR_DEVICE_QUALIFIER,                	// bDescriptor
    KEIL_16BIT(USB_SPEC_VER_2_0_BCD),               	// bcdUSB
    USB_BASE_CLASS_DEVICE_COMMUNICATION,            	// bDeviceClass
    USB_SUB_CLASS_DEVICE_USE_INTERFACE_DESCRIPTOR,  	// bDeviceSubClass
    USB_PROTOCOL_DEVICE_USE_INTERFACE_DESCRIPTOR,   	// bDeviceProtocol,
    64,                                             	// bMaxPacketSize0,
    0x1,                                            	// bNumConfigurations
    0                                               	// bReserved, must be zero  
};


//===========================================================================
// USB customized String Descriptor
//===========================================================================
const USB_STRING_DESCRIPTOR code StringDscr = {
    {
        sizeof (USB_STRING_DESCRIPTOR_ZERO),                // bLength
        USB_DESCRIPTOR_STRING,                              // bDescriptorType
        KEIL_16BIT (USB_LANGID_ENGLISH_US),                 // wLanguageID
    },
    //=========================== String 1 ====================================
    { 
        sizeof(USB_UNICODE_STRING_DESCRIPTOR_HEAD) + 8 * 2,     // bLength
        USB_DESCRIPTOR_STRING                                   // bDescriptorType
    },
    {
        KEIL_16BIT('S'),
        KEIL_16BIT('u'),
        KEIL_16BIT('p'),
        KEIL_16BIT('e'),
        KEIL_16BIT('r'),
        KEIL_16BIT('M'),
        KEIL_16BIT('a'),
        KEIL_16BIT('n')
    },
    //=========================== String 2 ====================================
    { 
        sizeof(USB_UNICODE_STRING_DESCRIPTOR_HEAD) + 14 * 2,    // bLength
        USB_DESCRIPTOR_STRING                                   // bDescriptorType
    },
    {
        KEIL_16BIT('U'),
        KEIL_16BIT('S'),
        KEIL_16BIT('B'),
        KEIL_16BIT('_'),	
        KEIL_16BIT('R'),
        KEIL_16BIT('S'),
        KEIL_16BIT('2'),
        KEIL_16BIT('3'),
        KEIL_16BIT('2'),
        KEIL_16BIT('_'),
        KEIL_16BIT('D'),
        KEIL_16BIT('e'),
        KEIL_16BIT('m'),
        KEIL_16BIT('o')
    }   
};


//===========================================================================
// USB CDC ACM High Speed Configuration Descriptor
//===========================================================================

const USB_CDC_ACM_HIGH_SPEED_CONFIG_DESCRIPTOR code HighSpeedConfigDscr = {

    {//================== USB_STANDARD_CONFIGURATION_DESCRIPTOR ================
        sizeof (USB_STANDARD_CONFIGURATION_DESCRIPTOR),                     // bLength
        USB_DESCRIPTOR_CONFIGURATION,                                       // bDescriptorType
        KEIL_16BIT(sizeof(USB_CDC_ACM_HIGH_SPEED_CONFIG_DESCRIPTOR)),       // wTotalLength
        2,                                                                  // Number of interfaces supported by this configuration

        1,                                                                  // value to use as an argument to the SetConfiguration() 
                                                                            // request to select this configuration
        0,                                                                  // index of string descriptor describing this configuration

        {
            0,                                                              // reserved, reset to zero
            0,                                                              // remoteWakeup
            0,                                                              // selfPowered
            1,                                                              // reserved, set to one for historic reasons
        },

        100                                                                 // maximum power consumption from the bus.
                                                                            // expressed in 2-mA unit for high speed mode
                                                                            // expressed in 8-mA unit for super speed mode
    },

    {//================ USB_CDC_ACM_HIGH_SPEED_INTERFACE_DESCRIPTOR ============

        {//============ USB_STANDARD_INTERFACE_DESCRIPTOR,   Data    ===========
            sizeof (USB_STANDARD_INTERFACE_DESCRIPTOR),                     // bLength
            USB_DESCRIPTOR_INTERFACE,                                       // bDescriptorType
            0,                                                              // bInterfaceNumber
            0,                                                              // bAlternateSetting
            2,                                                              // bNumEndpoints
            USB_BASE_CLASS_INTERFACE_CDC_DATA,                              // bInterfaceClass
            0,                                                              // bInterfaceSubClass
            USB_PROTOCOL_INTERFACE_NO_SPECIFIC_PROTOCOL,                    // bInterfaceProtocol
            0                                                               // iInterface
        },      

        {//=========================== EP4 =====================================
            sizeof(USB_STANDARD_ENDPOINT_DESCRIPTOR),                       // bLength
            USB_DESCRIPTOR_ENDPOINT,                                        // bDescriptor
            {
                { // == bmEndpointAddress
                    4,                                                      // endpointNumber
                    0,                                                      // reserved, reset to zero
                    USB_ENDPOINT_OUT                                        // direction
                } 
            },

            { //== bmAttributes
                { 
                    USB_ENDPOINT_BULK,
                    0
                }
            },

            KEIL_16BIT(128),                                                // Maximum packet size
            0                                                               // bInterval
        },

        {//=========================== EP8 =====================================
            sizeof(USB_STANDARD_ENDPOINT_DESCRIPTOR),                       // bLength
            USB_DESCRIPTOR_ENDPOINT,                                        // bDescriptor
            {
                { // == bmEndpointAddress
                    8,                                                      // endpointNumber
                    0,                                                      // reserved, reset to zero
                    USB_ENDPOINT_IN                                         // direction
                } 
            },

            { //== bmAttributes
                { 
                    USB_ENDPOINT_BULK,
                    0
                }
            },

            KEIL_16BIT(128),                                                // Maximum packet size
            0                                                               // bInterval
        },

        {//============ CDC_HEADER_FUNCTIONAL_DESCRIPTOR =======================
            sizeof(CDC_HEADER_FUNCTIONAL_DESCRIPTOR),                       // bFunctionLength
            CDC_TYPE_CS_INTERFACE,                                          // bDescriptorType
            CDC_SUBTYPE_HEADER,                                             // bDescriptorSubtype
            KEIL_16BIT(CDC_SPEC_VER_1_2_BCD)                                // bcdCDC, CDC spec release number
        },

        {//=========== CDC_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR ===============
            sizeof(CDC_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR),              // bFunctionLength
            CDC_TYPE_CS_INTERFACE,                                          // bDescriptorType
            CDC_SUBTYPE_CALL_MANAGEMENT,                                    // bDescriptorSubtype
            {//== union, bmCapabilities
                {//== struct , capabilities
                        1,                                                  // 1 - device handle call ; 0 - device not handle call
                        1,                                                  // 1 - call management over data class interface
                                                                            // 0 - call management over comm class interface
                        0                                                   // zeros                                                    
                }
            },

            1                                                               // bDataInterface 
        },

        {//=========== ABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR =======
            sizeof(ABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR),      // bFunctionLength
            CDC_TYPE_CS_INTERFACE,                                          // bDescriptorType
            CDC_SUBTYPE_ABSTRACT_CONTROL_MANAGEMENT,                        // bDescriptorSubtype
            {//== union bmCapabilities

                {//== struct capabilities
                        0,                                                  // whether support set_comm_feature, clear_comm_feature etc
                        1,                                                  // whether support set_line_coding etc
                        1,                                                  // whether support send_break
                        0,                                                  // whether support network connection
                        0                                                   // reserved, reset to zero                                          

                }
            }
        },

        
        {//============== CDC_UNION_FUNCTIONAL_DESCRIPTOR ======================
            sizeof(CDC_UNION_FUNCTIONAL_DESCRIPTOR),                        // bFunctionLength
            CDC_TYPE_CS_INTERFACE,                                          // bDescriptorType
            CDC_SUBTYPE_UNION,                                              // bDescriptorSubtype
            0,                                                              // bControlInterface
            1                                                               // bSubordinateInterface, first subordinate interface
        },

		{//============ USB_STANDARD_INTERFACE_DESCRIPTOR, Notification ========
            sizeof (USB_STANDARD_INTERFACE_DESCRIPTOR),                     // bLength
            USB_DESCRIPTOR_INTERFACE,                                       // bDescriptorType
            1,                                                              // bInterfaceNumber
            0,                                                              // bAlternateSetting
            1,                                                              // bNumEndpoints
            USB_BASE_CLASS_INTERFACE_CDC_CONTROL,                           // bInterfaceClass
            USB_SUBCLASS_INTERFACE_ABSTRACT_CONTROL_MODEL,                  // bInterfaceSubClass
            USB_PROTOCOL_INTERFACE_AT_COMMANDS,                             // bInterfaceProtocol
            0                                                               // iInterface
        },

        {//========================== EP6 ======================================
            sizeof(USB_STANDARD_ENDPOINT_DESCRIPTOR),                       // bLength
            USB_DESCRIPTOR_ENDPOINT,                                        // bDescriptor
            {
                { // == bmEndpointAddress
                    6,                                                      // endpointNumber
                    0,                                                      // reserved, reset to zero
                    USB_ENDPOINT_IN                                         // direction
                } 
            },

            { //== bmAttributes
                { 
                    USB_ENDPOINT_INTERRUPT,
                    0
                }
            },

            KEIL_16BIT(128),                                                // Maximum packet size
            255                                                             // bInterval
        }

    }

};


//===========================================================================
// USB CDC ACM Full Speed Configuration Descriptor
//===========================================================================

const USB_CDC_ACM_FULL_SPEED_CONFIG_DESCRIPTOR code FullSpeedConfigDscr = {

    {//================== USB_STANDARD_CONFIGURATION_DESCRIPTOR ================
        sizeof (USB_STANDARD_CONFIGURATION_DESCRIPTOR),                     // bLength
        USB_DESCRIPTOR_CONFIGURATION,                                       // bDescriptorType
        KEIL_16BIT(sizeof(USB_CDC_ACM_HIGH_SPEED_CONFIG_DESCRIPTOR)),       // wTotalLength
        2,                                                                  // Number of interfaces supported by this configuration

        1,                                                                  // value to use as an argument to the SetConfiguration() 
                                                                            // request to select this configuration
        0,                                                                  // index of string descriptor describing this configuration

        {
            0,                                                              // reserved, reset to zero
            0,                                                              // remoteWakeup
            0,                                                              // selfPowered
            1,                                                              // reserved, set to one for historic reasons
        },

        100                                                                 // maximum power consumption from the bus.
                                                                            // expressed in 2-mA unit for high speed mode
                                                                            // expressed in 8-mA unit for super speed mode
    },

    {//================ USB_CDC_ACM_HIGH_SPEED_INTERFACE_DESCRIPTOR ============

        {//============ USB_STANDARD_INTERFACE_DESCRIPTOR, Notification ========
            sizeof (USB_STANDARD_INTERFACE_DESCRIPTOR),                     // bLength
            USB_DESCRIPTOR_INTERFACE,                                       // bDescriptorType
            0,                                                              // bInterfaceNumber
            0,                                                              // bAlternateSetting
            2,                                                              // bNumEndpoints
            USB_BASE_CLASS_INTERFACE_CDC_DATA,                              // bInterfaceClass
            0,                                                              // bInterfaceSubClass
            USB_PROTOCOL_INTERFACE_NO_SPECIFIC_PROTOCOL,                    // bInterfaceProtocol
            0                                                               // iInterface
        },      

        {//=========================== EP4 =====================================
            sizeof(USB_STANDARD_ENDPOINT_DESCRIPTOR),                       // bLength
            USB_DESCRIPTOR_ENDPOINT,                                        // bDescriptor
            {
                { // == bmEndpointAddress
                    4,                                                      // endpointNumber
                    0,                                                      // reserved, reset to zero
                    USB_ENDPOINT_OUT                                        // direction
                } 
            },

            { //== bmAttributes
                { 
                    USB_ENDPOINT_BULK,
                    0
                }
            },

            KEIL_16BIT(128),                                                // Maximum packet size
            0                                                               // bInterval
        },

        {//=========================== EP8 =====================================
            sizeof(USB_STANDARD_ENDPOINT_DESCRIPTOR),                       // bLength
            USB_DESCRIPTOR_ENDPOINT,                                        // bDescriptor
            {
                { // == bmEndpointAddress
                    8,                                                      // endpointNumber
                    0,                                                      // reserved, reset to zero
                    USB_ENDPOINT_IN                                         // direction
                } 
            },

            { //== bmAttributes
                { 
                    USB_ENDPOINT_BULK,
                    0
                }
            },

            KEIL_16BIT(128),                                                // Maximum packet size
            0                                                               // bInterval
        },

        {//============ CDC_HEADER_FUNCTIONAL_DESCRIPTOR =======================
            sizeof(CDC_HEADER_FUNCTIONAL_DESCRIPTOR),                       // bFunctionLength
            CDC_TYPE_CS_INTERFACE,                                          // bDescriptorType
            CDC_SUBTYPE_HEADER,                                             // bDescriptorSubtype
            KEIL_16BIT(CDC_SPEC_VER_1_2_BCD)                                // bcdCDC, CDC spec release number
        },

        {//=========== CDC_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR ===============
            sizeof(CDC_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR),              // bFunctionLength
            CDC_TYPE_CS_INTERFACE,                                          // bDescriptorType
            CDC_SUBTYPE_CALL_MANAGEMENT,                                    // bDescriptorSubtype
            {//== union, bmCapabilities
                {//== struct , capabilities
                        1,                                                  // 1 - device handle call ; 0 - device not handle call
                        1,                                                  // 1 - call management over data class interface
                                                                            // 0 - call management over comm class interface
                        0                                                   // zeros                                                    
                }
            },

            1                                                               // bDataInterface 
        },

        {//=========== ABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR =======
            sizeof(ABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR),      // bFunctionLength
            CDC_TYPE_CS_INTERFACE,                                          // bDescriptorType
            CDC_SUBTYPE_ABSTRACT_CONTROL_MANAGEMENT,                        // bDescriptorSubtype
            {//== union bmCapabilities

                {//== struct capabilities
                        0,                                                  // whether support set_comm_feature, clear_comm_feature etc
                        1,                                                  // whether support set_line_coding etc
                        1,                                                  // whether support send_break
                        0,                                                  // whether support network connection
                        0                                                   // reserved, reset to zero                                          

                }
            }
        },
        
        {//============== CDC_UNION_FUNCTIONAL_DESCRIPTOR ======================
            sizeof(CDC_UNION_FUNCTIONAL_DESCRIPTOR),                        // bFunctionLength
            CDC_TYPE_CS_INTERFACE,                                          // bDescriptorType
            CDC_SUBTYPE_UNION,                                              // bDescriptorSubtype
            0,                                                              // bControlInterface
            1                                                               // bSubordinateInterface, first subordinate interface
        },

        {//============ USB_STANDARD_INTERFACE_DESCRIPTOR, Notification ========
            sizeof (USB_STANDARD_INTERFACE_DESCRIPTOR),                     // bLength
            USB_DESCRIPTOR_INTERFACE,                                       // bDescriptorType
            1,                                                              // bInterfaceNumber
            0,                                                              // bAlternateSetting
            1,                                                              // bNumEndpoints
            USB_BASE_CLASS_INTERFACE_CDC_CONTROL,                           // bInterfaceClass
            USB_SUBCLASS_INTERFACE_ABSTRACT_CONTROL_MODEL,                  // bInterfaceSubClass
            USB_PROTOCOL_INTERFACE_AT_COMMANDS,                             // bInterfaceProtocol
            0                                                               // iInterface
        },

        {//========================== EP6 ======================================
            sizeof(USB_STANDARD_ENDPOINT_DESCRIPTOR),                       // bLength
            USB_DESCRIPTOR_ENDPOINT,                                        // bDescriptor
            {
                { // == bmEndpointAddress
                    6,                                                      // endpointNumber
                    0,                                                      // reserved, reset to zero
                    USB_ENDPOINT_IN                                         // direction
                } 
            },

            { //== bmAttributes
                { 
                    USB_ENDPOINT_INTERRUPT,
                    0
                }
            },

            KEIL_16BIT(128),                                                // Maximum packet size
            255                                                             // bInterval
        }

    }

};

const U16 code UserDscr = 0x0000;

extern BOOL GotSUD;             // Received setup data flag
extern BOOL Sleep;
extern BOOL Rwuen;
extern BOOL Selfpwr;

BYTE Configuration;             // Current configuration
BYTE AlternateSetting;          // Alternate settings



//-----------------------------------------------------------------------------
// Task Dispatcher hooks
//   The following hooks are called by the task dispatcher.
//-----------------------------------------------------------------------------



//=============================================================================
// TD_Init()
//
// Parameters :
//      None
//
// Return Value :
//      None
//
// Remarks:
//      Initialization Function, Called once at startup
//=============================================================================

void TD_Init(void)             
{

   bWaitForLineCodeStructure = FALSE;

   // set the CPU clock to 48MHz
   CPUCS = ((CPUCS & ~bmCLKSPD) | bmCLKSPD1) ;

   // set the slave FIFO interface to 48MHz
   IFCONFIG |= 0x40;

   EP4CFG = 0xA0; // bulk, in buffer, 512 byte  
   SYNCDELAY;                    
  
   EP6CFG = 0xf2; // interrupt, IN BUFFER, 512 byte
   SYNCDELAY;                    

   EP8CFG = 0xE0;
   SYNCDELAY;                    

   EP4BCL = 128;                // arm EP4OUT
   SYNCDELAY;                    
   EP4BCL = 128;

   EPIE |= bmBIT5 | bmBIT7 |  bmBIT0 | bmBIT1;
  
   // enable dual autopointer feature
   AUTOPTRSETUP |= 0x01;

   Rwuen = TRUE;                 // Enable remote-wakeup
} // End of TD_Init()


void TD_Poll(void)              // Called repeatedly while the device is idle
{
    
}

BOOL TD_Suspend(void)          // Called before the device goes into suspend mode
{
   return(TRUE);
}

BOOL TD_Resume(void)          // Called after the device resumes
{
   return(TRUE);
}

//-----------------------------------------------------------------------------
// Device Request hooks
//   The following hooks are called by the end point 0 device request parser.
//-----------------------------------------------------------------------------

BOOL DR_GetDescriptor(void)
{
   return(TRUE);
}

BOOL DR_SetConfiguration(void)   // Called when a Set Configuration command is received
{
   Configuration = SETUPDAT[2];
   return(TRUE);            // Handled by user code
}

BOOL DR_GetConfiguration(void)   // Called when a Get Configuration command is received
{
   EP0BUF[0] = Configuration;
   EP0BCH = 0;
   EP0BCL = 1;
   return(TRUE);            // Handled by user code
}

BOOL DR_SetInterface(void)       // Called when a Set Interface command is received
{
   AlternateSetting = SETUPDAT[2];
   return(TRUE);            // Handled by user code
}

BOOL DR_GetInterface(void)       // Called when a Set Interface command is received
{
   EP0BUF[0] = AlternateSetting;
   EP0BCH = 0;
   EP0BCL = 1;
   return(TRUE);            // Handled by user code
}

BOOL DR_GetStatus(void)
{
   return(TRUE);
}

BOOL DR_ClearFeature(void)
{
   return(TRUE);
}

BOOL DR_SetFeature(void)
{
   return(TRUE);
}


//=============================================================================
// DR_VendorCmnd()
//
// Parameters :
//      None
//
// Return Value :
//      None
//
// Remarks :
//      Implement the following command for USB/RS232 Device:
//          SET_CONTROL_LINE_STATE
//          SEND_BREAK
//          GET_LINE_CODING
//          SET_LINE_CODING
//
// See Also :
//      Ref [2]
//=============================================================================

BOOL DR_VendorCmnd(void)
{
  WORD i;

  switch (SETUPDAT[1])
  {

     case SC_SET_CONTROL_LINE_STATE:
         break;

        
     case SC_SEND_BREAK: 
         // BREAK can be used as Magic SysRq Key for Linux. 
         // Do nothing for now. 
         // (Noted by C.Gu on 07/05/2011)
         break;

     case SC_GET_LINE_CODING:
        
        AUTOPTRH1 = MSB( &EP0BUF );
        AUTOPTRL1 = LSB( &EP0BUF );
    
        AUTOPTRH2 = MSB( &gRS232_Line_Coding );
        AUTOPTRL2 = LSB( &gRS232_Line_Coding );
    
        for( i = 0; i < sizeof(RS232_LINE_CODING_STRUCTURE); ++i) {
           EXTAUTODAT1= EXTAUTODAT2;
        } // End of for loop i

        EP0BCH = 0;
        EP0BCL = sizeof(RS232_LINE_CODING_STRUCTURE);
        break;

     case SC_SET_LINE_CODING:
        
        bWaitForLineCodeStructure = TRUE;

        // arm EP0, and wait inside EP0 ISR with bWaitForLineCodeStructure flag
        EP0BCH = 0;
        EP0BCL = sizeof(RS232_LINE_CODING_STRUCTURE);
        break;
   
        
     default:
        return(TRUE);
  }

  return(FALSE);
  
} // End of DR_VendorCmnd()

//-----------------------------------------------------------------------------
// USB Interrupt Handlers
//   The following functions are called by the USB interrupt jump table.
//-----------------------------------------------------------------------------

// Setup Data Available Interrupt Handler
void ISR_Sudav(void) interrupt 0
{
   GotSUD = TRUE;            // Set flag
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSUDAV;         // Clear SUDAV IRQ
}

// Setup Token Interrupt Handler
void ISR_Sutok(void) interrupt 0
{
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSUTOK;         // Clear SUTOK IRQ
}

void ISR_Sof(void) interrupt 0
{
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSOF;            // Clear SOF IRQ
}

void ISR_Ures(void) interrupt 0
{
   // whenever we get a USB reset, we should revert to full speed mode
   pConfigDscr = pFullSpeedConfigDscr;
   ((CONFIGDSCR xdata *) pConfigDscr)->type = CONFIG_DSCR;
   pOtherConfigDscr = pHighSpeedConfigDscr;
   ((CONFIGDSCR xdata *) pOtherConfigDscr)->type = OTHERSPEED_DSCR;

   EZUSB_IRQ_CLEAR();
   USBIRQ = bmURES;         // Clear URES IRQ
}

void ISR_Susp(void) interrupt 0
{
   Sleep = TRUE;
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSUSP;
}

void ISR_Highspeed(void) interrupt 0
{
   if (EZUSB_HIGHSPEED())
   {
      pConfigDscr = pHighSpeedConfigDscr;
      ((CONFIGDSCR xdata *) pConfigDscr)->type = CONFIG_DSCR;
      pOtherConfigDscr = pFullSpeedConfigDscr;
      ((CONFIGDSCR xdata *) pOtherConfigDscr)->type = OTHERSPEED_DSCR;
   }

   EZUSB_IRQ_CLEAR();
   USBIRQ = bmHSGRANT;
}
void ISR_Ep0ack(void) interrupt 0
{
}
void ISR_Stub(void) interrupt 0
{
}
void ISR_Ep0in(void) interrupt 0
{
    EZUSB_IRQ_CLEAR();
    EPIRQ = bmBIT0;

}


//=============================================================================
// ISR_Ep0out()
//
// Parameters :
//      None
//
// Return Value :
//      None
//
// Remarks :
//      ISR for EP0 Out, 
//      Use bWaitForLineCodeStructure flag for SET_LINE_CODING command
//
// See Also :
//      Ref [2]
//=============================================================================

void ISR_Ep0out(void) interrupt 0
{
  WORD i;
  U8 *p1, *p2;
  
    if (bWaitForLineCodeStructure) {
        bWaitForLineCodeStructure = FALSE;
        
        p1 = &EP0BUF;
        p2 = (U8*)&gRS232_Line_Coding;
        
        for( i = 0; i < sizeof(RS232_LINE_CODING_STRUCTURE); ++i) {
            
             *p2 = *p1;
             ++p1;
             ++p2;

        } // End of for loop i
    }

    EZUSB_IRQ_CLEAR();
    EPIRQ = bmBIT1;

}
void ISR_Ep1in(void) interrupt 0
{

}

void ISR_Ep1out(void) interrupt 0
{

}
void ISR_Ep2inout(void) interrupt 0
{

}

//=============================================================================
// ISR_Ep4inout()
//
// Parameters :
//      None
//
// Return Value :
//      None
//
// Remarks :
//      ISR for EP4 OUT, Get Data from Host, and copy them to EP8 IN
//
// See Also :
//      Ref [2]
//=============================================================================

void ISR_Ep4inout(void) interrupt 0
{

    WORD count;
    WORD  i;

    if(!(EP2468STAT & bmEP4EMPTY)) { 
        // check EP4 EMPTY(busy) bit in EP2468STAT (SFR), core set's this bit when FIFO is empty
         if(!(EP2468STAT & bmEP8FULL)) {
            // check EP8 FULL(busy) bit in EP2468STAT (SFR), core set's this bit when FIFO is full
            AUTOPTRH1 = MSB( &EP4FIFOBUF );
            AUTOPTRL1 = LSB( &EP4FIFOBUF );
    
            AUTOPTRH2 = MSB( &EP8FIFOBUF );
            AUTOPTRL2 = LSB( &EP8FIFOBUF );
    
            count = (EP4BCH << 8) + EP4BCL;

            // loop EP4OUT buffer data to EP8IN
            for( i = 0x0000; i < count; i++ ) {
                EXTAUTODAT2= EXTAUTODAT1+1;
            } // End of for loop i

        
            EP8BCH = EP4BCH;  
            SYNCDELAY;  
            EP8BCL = EP4BCL;        // arm EP8IN
            SYNCDELAY;                    
         }
    }

    EZUSB_IRQ_CLEAR();
    EPIRQ = bmBIT5;
    
} // End of ISR_Ep4inout()

void ISR_Ep6inout(void) interrupt 0
{

}

//=============================================================================
// ISR_Ep8inout()
//
// Parameters :
//      None
//
// Return Value :
//      None
//
// Remarks :
//      ISR for EP8 IN
//
// See Also :
//      Ref [2]
//=============================================================================

void ISR_Ep8inout(void) interrupt 0
{

    EP4BCL = 128;          // re(arm) EP4OUT
    SYNCDELAY;

    EZUSB_IRQ_CLEAR();
    EPIRQ = bmBIT7;
}

void ISR_Ibn(void) interrupt 0
{
}
void ISR_Ep0pingnak(void) interrupt 0
{
}
void ISR_Ep1pingnak(void) interrupt 0
{
}
void ISR_Ep2pingnak(void) interrupt 0
{
}
void ISR_Ep4pingnak(void) interrupt 0
{
}
void ISR_Ep6pingnak(void) interrupt 0
{
}
void ISR_Ep8pingnak(void) interrupt 0
{
}
void ISR_Errorlimit(void) interrupt 0
{
}
void ISR_Ep2piderror(void) interrupt 0
{
}
void ISR_Ep4piderror(void) interrupt 0
{
}
void ISR_Ep6piderror(void) interrupt 0
{
}
void ISR_Ep8piderror(void) interrupt 0
{
}
void ISR_Ep2pflag(void) interrupt 0
{
}
void ISR_Ep4pflag(void) interrupt 0
{
}
void ISR_Ep6pflag(void) interrupt 0
{
}
void ISR_Ep8pflag(void) interrupt 0
{
}
void ISR_Ep2eflag(void) interrupt 0
{
}
void ISR_Ep4eflag(void) interrupt 0
{
}
void ISR_Ep6eflag(void) interrupt 0
{
}
void ISR_Ep8eflag(void) interrupt 0
{
}
void ISR_Ep2fflag(void) interrupt 0
{
}
void ISR_Ep4fflag(void) interrupt 0
{
}
void ISR_Ep6fflag(void) interrupt 0
{
}
void ISR_Ep8fflag(void) interrupt 0
{
}
void ISR_GpifComplete(void) interrupt 0
{
}
void ISR_GpifWaveform(void) interrupt 0
{
}

