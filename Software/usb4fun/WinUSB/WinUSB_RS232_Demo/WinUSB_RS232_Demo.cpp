/******************************************************************************
* WinUSB USB-RS232 Demo
*
* Remarks:
*	The following code is trying to use WinUSB to access the IN/OUT bulk 
*   endpoints of a USB-CDC device. The code is based on the sample provided 
*   in Ref[1]. Thus it falls under MICROSOFT LIMITED PUBLIC LICENSE. (A copy of
*   which can be found at the end of this file.). 
*
*   (Noted by C.Gu on 08/09/2011)
*
* References:
* [1] How to Access a USB Device by Using WinUSB Functions, MSDN, 02/01/2011,
*    (http://msdn.microsoft.com/en-us/library/ff540174%28v=vs.85%29.aspx)
******************************************************************************/

// Include Windows headers
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <strsafe.h>

// Include WinUSB headers
#include <winusb.h>
#include <Setupapi.h>

//=============================================================================
// constant and structure definition
//=============================================================================

// constant for {25a72792-746e-4c40-8e78-d81b4a032f31}
static const GUID USB_RS232_DEVICE_INTERFACE = 
{0x25a72792, 0x746e, 0x4c40, {0x8e, 0x78, 0xd8, 0x1b, 0x4a, 0x03, 0x2f, 0x31}};


// parameters to be passed onto the read thread 
struct THREAD_PARAM
{
    WINUSB_INTERFACE_HANDLE hWinUSBHandle;
	UCHAR  PipeInId;
};

// PIPE ID struct
struct PIPE_ID
{
    UCHAR  PipeInId;
    UCHAR  PipeOutId;
};

//=============================================================================


/*
//-----------------------------------------------------------------------------
// GetDeviceHandle()
//
// Parameters:
//        guidDeviceInterface: DEVICE GUID defined in WinUSB inf file
//        hDeviceHandle		 : device handle returned 
//
// Return Values:
//        true : success
//        false: fail
//
// Remarks:
//        Function to create file handle for USB device
//-----------------------------------------------------------------------------
*/

BOOL GetDeviceHandle (GUID guidDeviceInterface, PHANDLE hDeviceHandle)
{
   
    BOOL bResult = TRUE;
    HDEVINFO hDeviceInfo;
    SP_DEVINFO_DATA DeviceInfoData;

    SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
    PSP_DEVICE_INTERFACE_DETAIL_DATA pInterfaceDetailData = NULL;

    ULONG requiredLength=0;

    LPTSTR lpDevicePath = NULL;

    DWORD index = 0;


	 if (guidDeviceInterface == GUID_NULL) {
        return FALSE;
    }


    // Get information about all the installed devices for the specified
    // device interface class.
    hDeviceInfo = SetupDiGetClassDevs( 
        &guidDeviceInterface,
        NULL, 
        NULL,
		DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    if (hDeviceInfo == INVALID_HANDLE_VALUE) { 
        // ERROR 
        printf("Error SetupDiGetClassDevs: %d.\n", GetLastError());
        goto done;
    }

    //Enumerate all the device interfaces in the device information set.
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	

    for (index = 0; SetupDiEnumDeviceInfo(hDeviceInfo, index, &DeviceInfoData); index++) {
        //Reset for this iteration
        if (lpDevicePath) {
            LocalFree(lpDevicePath);
        }

        if (pInterfaceDetailData) {
            LocalFree(pInterfaceDetailData);
        }

        deviceInterfaceData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);

        //Get information about the device interface.
        bResult = SetupDiEnumDeviceInterfaces( 
           hDeviceInfo,
           &DeviceInfoData,
           &guidDeviceInterface,
           index, 
           &deviceInterfaceData);

        // Check if last item
        if (GetLastError () == ERROR_NO_MORE_ITEMS) {
            break;
        }


		bResult = SetupDiEnumDeviceInterfaces( 
           hDeviceInfo,
           &DeviceInfoData,
           &guidDeviceInterface,
           index , 
           &deviceInterfaceData);



		 // Check if last item
        if (GetLastError () == ERROR_NO_MORE_ITEMS) {
            break;
        }



        //Check for some other error
        if (!bResult) {
            printf("Error SetupDiEnumDeviceInterfaces: %d.\n", GetLastError());
            goto done;
        }

        //Interface data is returned in SP_DEVICE_INTERFACE_DETAIL_DATA
        //which we need to allocate, so we have to call this function twice.
        //First to get the size so that we know how much to allocate
        //Second, the actual call with the allocated buffer
        
        bResult = SetupDiGetDeviceInterfaceDetail(
            hDeviceInfo,
            &deviceInterfaceData,
            NULL, 0,
            &requiredLength,
            NULL);


        //Check for some other error
        if (!bResult) {
            if ((ERROR_INSUFFICIENT_BUFFER==GetLastError()) && (requiredLength>0)) {
                //we got the size, allocate buffer
                pInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, requiredLength);
                
                if (!pInterfaceDetailData) { 
                    // ERROR 
                    printf("Error allocating memory for the device detail buffer.\n");
                    goto done;
                }
            } else {
                printf("Error SetupDiEnumDeviceInterfaces: %d.\n", GetLastError());
                goto done;
            }
        }

        //get the interface detailed data
        pInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        //Now call it with the correct size and allocated buffer
        bResult = SetupDiGetDeviceInterfaceDetail(
                hDeviceInfo,
                &deviceInterfaceData,
                pInterfaceDetailData,
                requiredLength,
                NULL,
                &DeviceInfoData);
        
        //Check for some other error
        if (!bResult) {
            printf("Error SetupDiGetDeviceInterfaceDetail: %d.\n", GetLastError());
            goto done;
        }

        //copy device path
                
        size_t nLength = wcslen (pInterfaceDetailData->DevicePath) + 1;  
        lpDevicePath = (TCHAR *) LocalAlloc (LPTR, nLength * sizeof(TCHAR));
        StringCchCopy(lpDevicePath, nLength, pInterfaceDetailData->DevicePath);
        lpDevicePath[nLength-1] = 0;
                        
        printf("Device path:  %s\n", lpDevicePath);

    }

    if (!lpDevicePath) {
        //Error.
        printf("Error %d.", GetLastError());
        goto done;
    }

    //Open the device
    *hDeviceHandle = CreateFile (
        lpDevicePath,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,
        NULL);

    if (*hDeviceHandle == INVALID_HANDLE_VALUE) {
        //Error.
        printf("Error %d.", GetLastError());
        goto done;
    }



done:
    LocalFree(lpDevicePath);
    LocalFree(pInterfaceDetailData);    
    bResult = SetupDiDestroyDeviceInfoList(hDeviceInfo);
    
    return bResult;

} // End of GetDeviceHandle()


/*
//-----------------------------------------------------------------------------
// GetWinUSBHandle()
//
// Parameters:
//        hDeviceHandle  : device handle created for the USB device
//        phWinUSBHandle : WinUSB Interface handle returned 
//
// Return Values:
//        true : success
//        false: fail
//
// Remarks:
//        Function to get WinUSB Interface Handle for the device
//-----------------------------------------------------------------------------
*/

BOOL GetWinUSBHandle(HANDLE hDeviceHandle, PWINUSB_INTERFACE_HANDLE phWinUSBHandle)
{
    if (hDeviceHandle == INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    BOOL bResult = WinUsb_Initialize(hDeviceHandle, phWinUSBHandle);

    if(!bResult) {
        //Error.
        printf("WinUsb_Initialize Error %d.", GetLastError());
        return FALSE;
    }

    return bResult;
} // End of GetWinUSBHandle()



/*
//-----------------------------------------------------------------------------
// GetUSBDeviceSpeed()
//
// Parameters:
//        hDeviceHandle  : WinUSB Interface Handle
//        pDeviceSpeed   : Device Speed returned
//
// Return Values:
//        true : success
//        false: fail
//
// Remarks:
//        Function to get device speed
//-----------------------------------------------------------------------------
*/

BOOL GetUSBDeviceSpeed(WINUSB_INTERFACE_HANDLE hDeviceHandle, UCHAR* pDeviceSpeed)
{
    if (!pDeviceSpeed || hDeviceHandle==INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    BOOL bResult = TRUE;

    ULONG length = sizeof(UCHAR);

    bResult = WinUsb_QueryDeviceInformation(hDeviceHandle, DEVICE_SPEED, &length, pDeviceSpeed);
    if(!bResult) {
        printf("Error getting device speed: %d.\n", GetLastError());
        goto done;
    }

    if(*pDeviceSpeed == LowSpeed) {
        printf("Device speed: %d (Low speed).\n", *pDeviceSpeed);
        goto done;
    }

    if(*pDeviceSpeed == FullSpeed) {
        printf("Device speed: %d (Full speed).\n", *pDeviceSpeed);
        goto done;
    }

    if(*pDeviceSpeed == HighSpeed) {
        printf("Device speed: %d (High speed).\n", *pDeviceSpeed);
        goto done;
    }

done:
    return bResult;
} // End of GetUSBDeviceSpeed()


/*
//-----------------------------------------------------------------------------
// QueryDeviceEndpoints()
//
// Parameters:
//        hDeviceHandle  : WinUSB Interface Handle
//        pipeid		 : Pipe ID returned
//
// Return Values:
//        true : success
//        false: fail
//
// Remarks:
//        Function to check end points and get pipe ID
//-----------------------------------------------------------------------------
*/

BOOL QueryDeviceEndpoints (WINUSB_INTERFACE_HANDLE hDeviceHandle, PIPE_ID* pipeid)
{
    if (hDeviceHandle==INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    BOOL bResult = TRUE;

    USB_INTERFACE_DESCRIPTOR InterfaceDescriptor;
    ZeroMemory(&InterfaceDescriptor, sizeof(USB_INTERFACE_DESCRIPTOR));

    WINUSB_PIPE_INFORMATION  Pipe;
    ZeroMemory(&Pipe, sizeof(WINUSB_PIPE_INFORMATION));

    
    bResult = WinUsb_QueryInterfaceSettings(hDeviceHandle, 0, &InterfaceDescriptor);

    if (bResult) {
        for (int index = 0; index < InterfaceDescriptor.bNumEndpoints; index++) {
            bResult = WinUsb_QueryPipe(hDeviceHandle, 0, index, &Pipe);

            if (bResult) {
                if (Pipe.PipeType == UsbdPipeTypeControl) {
                    printf("Endpoint index: %d Pipe type: Control Pipe ID: %d.\n", index, Pipe.PipeType, Pipe.PipeId);
                }
                
				if (Pipe.PipeType == UsbdPipeTypeIsochronous) {
                    printf("Endpoint index: %d Pipe type: Isochronous Pipe ID: %d.\n", index, Pipe.PipeType, Pipe.PipeId);
                }

                if (Pipe.PipeType == UsbdPipeTypeBulk) {

                    if (USB_ENDPOINT_DIRECTION_IN(Pipe.PipeId)) {
                        printf("Endpoint index: %d Pipe type: Bulk IN Pipe ID: %d.\n", index, Pipe.PipeType, Pipe.PipeId);
                        pipeid->PipeInId = Pipe.PipeId;
                    }

                    if (USB_ENDPOINT_DIRECTION_OUT(Pipe.PipeId)) {
                        printf("Endpoint index: %d Pipe type: Bulk OUT Pipe ID: %d.\n", index, Pipe.PipeType, Pipe.PipeId);
                        pipeid->PipeOutId = Pipe.PipeId;
                    }

                }

                if (Pipe.PipeType == UsbdPipeTypeInterrupt) {
                    printf("Endpoint index: %d Pipe type: Interrupt Pipe ID: %d.\n", index, Pipe.PipeType, Pipe.PipeId);
                }
            } else {
                continue;
            }
        }
    }

//done:
    return bResult;
} // End of QueryDeviceEndpoints()


/*
//-----------------------------------------------------------------------------
// WriteToBulkEndpoint()
//
// Parameters:
//        hDeviceHandle  : WinUSB Interface Handle
//        pID			 : pointer to Pipe ID
//		  pcbWritten     : number of bytes actually written to the OUT endpoint
//		  szBuffer       : data buffer to be written
//		  cbSize         : size of the data buffer to be written
//
// Return Values:
//        true : success
//        false: fail
//
// Remarks:
//        Function to write data to OUT bulk endpoint
//-----------------------------------------------------------------------------
*/

BOOL WriteToBulkEndpoint(WINUSB_INTERFACE_HANDLE hDeviceHandle, UCHAR* pID, ULONG* pcbWritten, UCHAR *szBuffer, ULONG cbSize)
{
    if (hDeviceHandle==INVALID_HANDLE_VALUE || !pID || !pcbWritten) {
        return FALSE;
    }

    BOOL bResult = TRUE;

//    UCHAR szBuffer[] = "Hello World";
//    ULONG cbSize = strlen((char*)szBuffer);
    ULONG cbSent = 0;

    bResult = WinUsb_WritePipe(hDeviceHandle, *pID, szBuffer, cbSize, &cbSent, 0);
    if(!bResult) {
        goto done;
    }

 //==   printf("Wrote to pipe %d: %s \nActual data transferred: %d.\n", *pID, szBuffer, cbSent);
    *pcbWritten = cbSent;


done:
    return bResult;

} // End of WriteToBulkEndpoint()


/*
//-----------------------------------------------------------------------------
// ReadFromBulkEndpoint()
//
// Parameters:
//        hDeviceHandle  : WinUSB Interface Handle
//        pID			 : pointer to Pipe ID
//		  szBuffer       : data buffer to be filled
//		  cbSize         : size of the data buffer to be filled
//
// Return Values:
//        true : success
//        false: fail
//
// Remarks:
//        Function to read data from IN bulk endpoint
//-----------------------------------------------------------------------------
*/


BOOL ReadFromBulkEndpoint(WINUSB_INTERFACE_HANDLE hDeviceHandle, UCHAR* pID, UCHAR* szBuffer, ULONG cbSize)
{
    if (hDeviceHandle==INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    BOOL bResult = TRUE;

  //  UCHAR* szBuffer = (UCHAR*)LocalAlloc(LPTR, sizeof(UCHAR)*cbSize);
    
    ULONG cbRead = 0;

    bResult = WinUsb_ReadPipe(hDeviceHandle, *pID, szBuffer, cbSize, &cbRead, 0);
    
	if (!bResult) {
        goto done;
    }

 //===   printf("Read from pipe %d: %s \nActual data read: %d.\n", *pID, szBuffer, cbRead);


done:
    //LocalFree(szBuffer);
    return bResult;

} // End of ReadFromBulkEndpoint()




/*
//-----------------------------------------------------------------------------
// comReadThread()
//
// Parameters:
//        lpdwThreadParam  : pointer to struct THREAD_PARAM
//        pID			   : pointer to Pipe ID
//		  szBuffer         : data buffer to be filled
//		  cbSize           : size of the data buffer to be filled
//
// Return Values:
//        true : success
//        false: fail
//
// Remarks:
//        Function to be used for read thread
//-----------------------------------------------------------------------------
*/

DWORD comReadThread (LPVOID lpdwThreadParam )
{


	THREAD_PARAM* pthread_param;
	
	pthread_param = (THREAD_PARAM*)lpdwThreadParam;

	ULONG cbSize = 2;
	
	UCHAR* szBuffer = (UCHAR*)LocalAlloc(LPTR, sizeof(UCHAR)*cbSize);



	/*==
	hComPort = CreateFile (TEXT("COM1"), GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 
		FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED,//FILE_ATTRIBUTE_NORMAL, 
		NULL);
	*/
	
	 
	while(1) {
	
		ReadFromBulkEndpoint(pthread_param->hWinUSBHandle, &(pthread_param->PipeInId), szBuffer, cbSize);

		printf("%c",szBuffer[0]);
	

	} // End of while();

	return 0;

} // End of comReadThread()


/*
//-----------------------------------------------------------------------------
// main()
//
// Parameters:
//
// Return Values:
//		  None
//
// Remarks:
//       main function. WinUSB initialization and Bulk Endpoint Write
//-----------------------------------------------------------------------------
*/

void main()
{ 

	UCHAR buf[2];

	THREAD_PARAM thread_param;

	DWORD dwThreadId;

    GUID guidDeviceInterface = USB_RS232_DEVICE_INTERFACE; //in the INF file

    BOOL bResult = TRUE;

    PIPE_ID PipeID;

    HANDLE hDeviceHandle = INVALID_HANDLE_VALUE;
    WINUSB_INTERFACE_HANDLE hWinUSBHandle = INVALID_HANDLE_VALUE;
    
    UCHAR DeviceSpeed;
    ULONG cbSize = 0;


    bResult = GetDeviceHandle(guidDeviceInterface, &hDeviceHandle);
    if(!bResult) {
        goto done;
    }

    bResult = GetWinUSBHandle(hDeviceHandle, &hWinUSBHandle);
    if(!bResult) {
        goto done;
    }

    bResult = GetUSBDeviceSpeed(hWinUSBHandle, &DeviceSpeed);
    if(!bResult) {
        goto done;
    }

    bResult = QueryDeviceEndpoints(hWinUSBHandle, &PipeID);
    if(!bResult) {
        goto done;
    }

//    bResult = SendDatatoDefaultEndpoint(hWinUSBHandle);
//    if(!bResult) {
//        goto done;
//    }



	thread_param.hWinUSBHandle = hWinUSBHandle;
	thread_param.PipeInId = PipeID.PipeInId;


	if (!CreateThread (NULL, 
		0, 
		(LPTHREAD_START_ROUTINE)&comReadThread,
		(LPVOID)&thread_param,
		0,
		&dwThreadId)) {
	
		printf ("Fail to Create Read Thread\n");
		goto done;
	}


	printf ("\n===============================================================\n");


	buf[1] = '\n';

	while(1) {
		buf[0] = _getch();
		
		if (buf[0] == 27) { // Escape key
			goto done;
		}


		if (buf[0] == '\r') {
			WriteToBulkEndpoint(hWinUSBHandle, &PipeID.PipeOutId, &cbSize, buf, 2);
		} else {
			WriteToBulkEndpoint(hWinUSBHandle, &PipeID.PipeOutId, &cbSize, buf, 1);
		}
		
		
	} // End of while loop
    

done:
    CloseHandle(hDeviceHandle);
    WinUsb_Free(hWinUSBHandle);

    
} // End of main()

/**********************************************************************************************
// Appendix I : MICROSOFT LIMITED PUBLIC LICENSE
//     ( http://msdn.microsoft.com/en-us/cc300389.aspx) 
//
// MICROSOFT LIMITED PUBLIC LICENSE
//
// This license governs use of code marked as “sample” or “example” available on 
// this web site without a license agreement, as provided under the section above 
// titled “NOTICE SPECIFIC TO SOFTWARE AVAILABLE ON THIS WEB SITE.” If you use 
// such code (the “software”), you accept this license. If you do not accept the
// license, do not use the software.
//
// 1. Definitions
//
// The terms “reproduce,” “reproduction,” “derivative works,” and “distribution” 
// have the same meaning here as under U.S. copyright law.
// 
// A “contribution” is the original software, or any additions or changes to the software.
//
// A “contributor” is any person that distributes its contribution under this license.
// 
// “Licensed patents” are a contributor’s patent claims that read directly on its contribution.
//
// 2. Grant of Rights
//
// (A) Copyright Grant - Subject to the terms of this license, including the license conditions
// and limitations in section 3, each contributor grants you a non-exclusive, worldwide, 
// royalty-free copyright license to reproduce its contribution, prepare derivative works of 
// its contribution, and distribute its contribution or any derivative works that you create.
//
// (B) Patent Grant - Subject to the terms of this license, including the license conditions
// and limitations in section 3, each contributor grants you a non-exclusive, worldwide, 
// royalty-free license under its licensed patents to make, have made, use, sell, offer for sale, 
// import, and/or otherwise dispose of its contribution in the software or derivative works of 
// the contribution in the software.
//
// 3. Conditions and Limitations
//
// (A) No Trademark License- This license does not grant you rights to use any contributors’ 
// name, logo, or trademarks.
//
// (B) If you bring a patent claim against any contributor over patents that you claim are 
// infringed by the software, your patent license from such contributor to the software ends 
// automatically.
// 
// (C) If you distribute any portion of the software, you must retain all copyright, patent, 
// trademark, and attribution notices that are present in the software.
//
// (D) If you distribute any portion of the software in source code form, you may do so only 
// under this license by including a complete copy of this license with your distribution. If 
// you distribute any portion of the software in compiled or object code form, you may only do
// so under a license that complies with this license.
//
// (E) The software is licensed “as-is.” You bear the risk of using it. The contributors give
// no express warranties, guarantees or conditions. You may have additional consumer rights 
// under your local laws which this license cannot change. To the extent permitted under your 
// local laws, the contributors exclude the implied warranties of merchantability, fitness for
// a particular purpose and non-infringement.
//
// (F) Platform Limitation - The licenses granted in sections 2(A) and 2(B) extend only to the
// software or derivative works that you create that run on a Microsoft Windows operating system
// product.
**********************************************************************************************/
