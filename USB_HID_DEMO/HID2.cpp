#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <windowsx.h>
#include <setupapi.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
WNDCLASSEX wndclass={sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, NULL, NULL, NULL, NULL, "Menu1", "Window Class", NULL};


typedef struct _HIDD_ATTRIBUTES {
        ULONG  Size;
        USHORT VendorID;
        USHORT ProductID;
        USHORT VersionNumber;
} HIDD_ATTRIBUTES, *PHIDD_ATTRIBUTES;

typedef void (WINAPI* t_HidD_GetHidGuid)(LPGUID);
typedef BOOLEAN (WINAPI* t_HidD_SetFeature)(HANDLE, PVOID, ULONG);
typedef BOOLEAN (WINAPI* t_HidD_GetFeature)(HANDLE, PVOID, ULONG);
typedef BOOLEAN (WINAPI* t_HidD_SetOutputReport)(HANDLE, PVOID, ULONG);
typedef BOOLEAN (WINAPI* t_HidD_GetInputReport)(HANDLE, PVOID, ULONG);
typedef BOOLEAN (WINAPI* t_HidD_GetAttributes)(HANDLE, PHIDD_ATTRIBUTES);
typedef BOOLEAN (WINAPI* t_HidD_GetProductString)(HANDLE, PVOID, ULONG);

t_HidD_GetHidGuid HidD_GetHidGuid;
t_HidD_SetFeature HidD_SetFeature;
t_HidD_GetFeature HidD_GetFeature;
t_HidD_SetOutputReport HidD_SetOutputReport;
t_HidD_GetInputReport HidD_GetInputReport;
t_HidD_GetAttributes HidD_GetAttributes;
t_HidD_GetProductString HidD_GetProductString;

int m, n;

HANDLE hHid[16];

SP_DEVICE_INTERFACE_DATA DevData;
HDEVINFO hDev;


int k=0, e=0;
int l;

HMENU hMenu1;
int led_state=0;



void GetHidHandle(void){

	DWORD BufLen;
	SP_DEVICE_INTERFACE_DETAIL_DATA* DetailData;
	HANDLE hFile;
	HIDD_ATTRIBUTES HIDAttributes;
		m++;
		if(SetupDiGetDeviceInterfaceDetail(hDev, &DevData, NULL, 0, &BufLen, NULL)){
//			MessageBox(NULL, "Ошибка получения размера буфера для имени устройства", "Ошибка", MB_OK);
			return;
		}

		DetailData=(SP_DEVICE_INTERFACE_DETAIL_DATA*)malloc(BufLen);
		
		DetailData->cbSize=5;   //sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA) Этот размер равен 8. Почему-то работает только 5
		if(!SetupDiGetDeviceInterfaceDetail(hDev, &DevData, DetailData, BufLen, NULL, NULL)){
//			MessageBox(NULL, "Не могу получить имя устройства", "Ошибка", MB_OK);
			free(DetailData);
			return;
		}
		hFile=CreateFile(DetailData->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile==INVALID_HANDLE_VALUE){
//			MessageBox(NULL, "Не могу открыть устройство", "Ошибка", MB_OK);
			free(DetailData);
			return;
		}
		if(!HidD_GetAttributes(hFile, &HIDAttributes)){
//			MessageBox(NULL, "Не могу получить атрибуты HID устройства", "Ошибка", MB_OK);
			CloseHandle(hFile);
			free(DetailData);
			return;
		}

		if((HIDAttributes.VendorID==0x0483)&&(HIDAttributes.ProductID==0x5711)){
			hHid[n]=hFile;
			n++;
		}else{
			CloseHandle(hFile);
		}
		free(DetailData);

}







HANDLE ConectToHid(void){


	HINSTANCE hDLL1;
	GUID HidGuid;


	m=0;
	n=0;

	hDLL1=LoadLibrary("hid.dll");   
	if(!hDLL1){
//		MessageBox(NULL, "Не открывается HID.DLL", "Ошибка", MB_OK);
		return INVALID_HANDLE_VALUE;
	}
        
	HidD_GetHidGuid=(t_HidD_GetHidGuid)GetProcAddress(hDLL1, "HidD_GetHidGuid");
	if(!HidD_GetHidGuid){
//		MessageBox(NULL, "Не могу получить адрес функции HidD_GetHidGuid", "Ошибка", MB_OK);
		return INVALID_HANDLE_VALUE;
	}

	HidD_GetAttributes=(t_HidD_GetAttributes)GetProcAddress(hDLL1, "HidD_GetAttributes");
	if(!HidD_GetAttributes){
//		MessageBox(NULL, "Не могу получить адрес функции HidD_GetAttributes", "Ошибка", MB_OK);
		return INVALID_HANDLE_VALUE;
    }
    
    HidD_SetFeature=(t_HidD_SetFeature)GetProcAddress(hDLL1, "HidD_SetFeature");
    if(!HidD_SetFeature){
//    	MessageBox(NULL, "Не могу получить адрес функции HidD_SetFeature", "Ошибка", MB_OK);
    	return INVALID_HANDLE_VALUE;
    }

    HidD_GetFeature=(t_HidD_GetFeature)GetProcAddress(hDLL1, "HidD_GetFeature");
    if(!HidD_GetFeature){
//        MessageBox(NULL, "Не могу получить адрес функции HidD_GetFeature", "Ошибка", MB_OK);
        return INVALID_HANDLE_VALUE;
    }

    HidD_SetOutputReport=(t_HidD_SetOutputReport)GetProcAddress(hDLL1, "HidD_SetOutputReport");
    if(!HidD_SetOutputReport){
//        MessageBox(NULL, "Не могу получить адрес функции HidD_SetOutputReport", "Ошибка", MB_OK);
        return INVALID_HANDLE_VALUE;
    }
        
    HidD_GetInputReport=(t_HidD_GetInputReport)GetProcAddress(hDLL1, "HidD_GetInputReport");
    if(!HidD_GetInputReport){
//        MessageBox(NULL, "Не могу получить адрес функции HidD_GetInputReport", "Ошибка", MB_OK);
        return INVALID_HANDLE_VALUE;
    }
    

	HidD_GetHidGuid(&HidGuid);

	hDev=SetupDiGetClassDevs(&HidGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if(hDev==INVALID_HANDLE_VALUE){
//		MessageBox(NULL, "Не могу получить Device Information Sets", "Ошибка", MB_OK);
		return INVALID_HANDLE_VALUE;
    }


	DevData.cbSize=sizeof(SP_DEVICE_INTERFACE_DATA);

	while(SetupDiEnumDeviceInterfaces(hDev, NULL, &HidGuid, m, &DevData)){
		GetHidHandle();
    }


//Здесь в массиве hHid[] хэндлы устройств HID; n - количество хэндлов





}



void CloseHid(void){

     for(int i=0; i<n; i++)CloseHandle(hHid[i]);


}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
unsigned char OutBuf1[65], InBuf1[65];

char txtbuf1[256];
int i;
HDC hdc1;

	switch(iMsg){
		case WM_CREATE:
    		ConectToHid();
    		//Здесь в массиве hHid[] хэндлы устройств HID; n - количество хэндлов
    		i = sprintf(txtbuf1, "N = %d", n);
        	txtbuf1[i]=0;
        	MessageBox(NULL, txtbuf1, "Количество найденых устройств", MB_OK);
    		
        	SetTimer(hWnd, 1, 100, NULL);
        	
        	hMenu1 = CreateMenu();
        	AppendMenu(hMenu1, MF_STRING, 1000, "On/Off");
        	SetMenu(hWnd, hMenu1);
        	
			break;
		case WM_TIMER:
			hdc1 = GetDC(hWnd);
			l=k;
			OutBuf1[4]=k/16777216; k=k-OutBuf1[4]*16777216; OutBuf1[3]=k/65536; k=k-OutBuf1[3]*65536; OutBuf1[2]=k/256; k=k-OutBuf1[2]*256; OutBuf1[1]=k; OutBuf1[0]=0;
			OutBuf1[5]=led_state;
			OutBuf1[0]=0;
			if(!HidD_SetFeature(hHid[0], OutBuf1, 65)){
				//if(!WriteFile(hHid[0], t, 64, &NRW, NULL)){
				MessageBox(NULL, "Не могу отправить репорт", "Ошибка", MB_OK);
			}
			InBuf1[0]=0;
			if(!HidD_GetFeature(hHid[0], InBuf1, 65)){
				MessageBox(NULL, "Не могу принять репорт", "Ошибка", MB_OK);
			}
			k=InBuf1[1]+InBuf1[2]*256+InBuf1[3]*65536+InBuf1[4]*16777216;
			i = sprintf(txtbuf1, "Total : %d", k);
			TextOut(hdc1, 0, 0, txtbuf1, i);
			if(k!=l+1)e++;
			i = sprintf(txtbuf1, "Errors: %d", e);
			TextOut(hdc1, 0, 16, txtbuf1, i);
			ReleaseDC(hWnd, hdc1);
			break;
			
		case WM_COMMAND:
			if(LOWORD(wParam)==1000){
				if(led_state==0){led_state=1;}else{led_state=0;}
			}
			break;
		
		case WM_DESTROY:
        	CloseHid();
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}
}


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow){
	HWND hWnd;
	MSG msg;
	wndclass.hInstance     = hInstance;
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	if(RegisterClassEx(&wndclass) == 0){
       exit(1);
	}
	hWnd=CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "Window Class", "Create Window Example", WS_OVERLAPPEDWINDOW, 0, 0, 360, 200, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, iCmdShow);


	while(GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}

