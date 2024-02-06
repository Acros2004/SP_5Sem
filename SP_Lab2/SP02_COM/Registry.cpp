//#define _CRT_SECURE_NO_WARNINGS
#include "REGISTRY.h"
//#include <iostream>
//#include "SEQLOG.h"

BOOL setKeyAndValue(const WCHAR* szKey,
	const WCHAR* szSubkey,
	const WCHAR* szValue);

void CLSIDtochar(const CLSID& clsid,
	WCHAR* szCLSID,
	int length);

LONG recursiveDeleteKey(HKEY hKeyParent, const WCHAR* szKeyChild); // Delete szKeyChild and all of its descendents.

const int CLSID_STRING_SIZE = 39;//состоит из 38 + символов /0

HRESULT RegisterServer(HMODULE hModule,            // дискриптор DLL в котором находится COM-компанент
	const CLSID& clsid,         // Class ID глобальный индетификатор
	const WCHAR* szFriendlyName, // Friendly Name просто имя COM-комп
	const WCHAR* szVerIndProgID, // Programmatic ProgId версия
	const WCHAR* szProgID)       //   IDs ProgId идентификатор
{

	WCHAR szModule[512]; //для пути
	DWORD dwResult = GetModuleFileName(hModule, szModule, sizeof(szModule) / sizeof(WCHAR));//получаем путь через дискриптор
	assert(dwResult != 0);//проверяем, что всё ок

	WCHAR szCLSID[CLSID_STRING_SIZE];//CLSID в строку
	CLSIDtochar(clsid, szCLSID, sizeof(szCLSID));//преобразуем

	WCHAR szKey[264];      //smw szKey[64] для записи ключа(CLSID) в реестр
	wcscpy_s(szKey, L"CLSID\\");
	wcscat_s(szKey, szCLSID);

	setKeyAndValue(szKey, NULL, szFriendlyName);//null - это подключ
	setKeyAndValue(szKey, L"InprocServer32", szModule);
	setKeyAndValue(szKey, L"ProgID", szProgID);
	setKeyAndValue(szKey, L"VersionIndependentProgID", szVerIndProgID);
	setKeyAndValue(szVerIndProgID, NULL, szFriendlyName);
	setKeyAndValue(szVerIndProgID, L"CLSID", szCLSID);
	setKeyAndValue(szVerIndProgID, L"CurVer", szProgID);
	setKeyAndValue(szProgID, NULL, szFriendlyName);
	setKeyAndValue(szProgID, L"CLSID", szCLSID);

	return S_OK;
}

HRESULT UnregisterServer(const CLSID& clsid,
	const WCHAR* szVerIndProgID,
	const WCHAR* szProgID)

{
	WCHAR szCLSID[CLSID_STRING_SIZE];
	CLSIDtochar(clsid, szCLSID, sizeof(szCLSID));

	WCHAR szKey[64];
	wcscpy_s(szKey, L"CLSID\\");
	wcscat_s(szKey, szCLSID);

	LONG lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szKey);//удаляем ключ и его подключи рекурсивно
	assert((lResult == ERROR_SUCCESS) || (lResult == ERROR_FILE_NOT_FOUND)); // Subkey may not exist.
	lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szVerIndProgID);
	assert((lResult == ERROR_SUCCESS) || (lResult == ERROR_FILE_NOT_FOUND)); // Subkey may not exist.
	lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szProgID);
	assert((lResult == ERROR_SUCCESS) || (lResult == ERROR_FILE_NOT_FOUND)); // Subkey may not exist.

	return S_OK;
}


void CLSIDtochar(const CLSID& clsid,      // Преобразуем  CLSID в строку
	WCHAR* szCLSID,          // smw:char* szCLSID,
	int length)
{
	assert(length >= CLSID_STRING_SIZE);

	LPOLESTR wszCLSID = NULL;//специфичный формат строки(промежуточный)
	HRESULT hr = StringFromCLSID(clsid, &wszCLSID);
	assert(SUCCEEDED(hr));
	wcscpy_s(szCLSID, CLSID_STRING_SIZE, wszCLSID);
	CoTaskMemFree(wszCLSID);//высвобождение памяти из-за StringFromCLSID

}


LONG recursiveDeleteKey(HKEY hKeyParent,           // Parent of key to delete
	const WCHAR* lpszKeyChild)  // Key to delete
{

	HKEY hKeyChild;
	LONG lRes = RegOpenKeyEx(hKeyParent, lpszKeyChild, 0,
		KEY_ALL_ACCESS, &hKeyChild);//вообще мы получаем доступ к дочернему ключу из родительского,0 - никакие специфичные флаги
	if (lRes != ERROR_SUCCESS)
	{
		return lRes;
	}

	FILETIME time;//инфа о времени, но она какбы для нас бесполезна 
	WCHAR szBuffer[256];//под ключ
	DWORD dwSize = 256;
	while (RegEnumKeyEx(hKeyChild, 0, szBuffer, &dwSize, NULL,
		NULL, NULL, &time) == S_OK)//пробегаем по всем подключам
	{
		lRes = recursiveDeleteKey(hKeyChild, szBuffer);
		if (lRes != ERROR_SUCCESS)
		{
			RegCloseKey(hKeyChild);//закрываем дискриптор ключа
			return lRes;
		}
		dwSize = 256;
	}

	RegCloseKey(hKeyChild);
	return RegDeleteKey(hKeyParent, lpszKeyChild);
}

BOOL setKeyAndValue(const WCHAR* szKey,         // smw:const char* szKey
	const WCHAR* szSubkey,						// smw:const char* szSubkey,
	const WCHAR* szValue)						// smw: const char* szValue
{
	HKEY hKey;//дискриптор ключа
	WCHAR szKeyBuf[1024];

	wcscpy_s(szKeyBuf, szKey);

	if (szSubkey != NULL)
	{
		wcscat_s(szKeyBuf, L"\\");
		wcscat_s(szKeyBuf, szSubkey);
	}
	long lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT,
		szKeyBuf,
		0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL,
		&hKey, NULL);//0 - без флагов, null - безопастность, reg_option..- постоянный ключ,null - получение инфы о классе ключа
	if (lResult != ERROR_SUCCESS)
	{
		return FALSE;
	}

	if (szValue != NULL)
	{
		RegSetValueEx(hKey, NULL, 0, REG_SZ,
			(BYTE*)szValue,
			2 * wcslen(szValue) + 1);//*2 из-за wchar +1 из-за /0
	}

	RegCloseKey(hKey);
	return TRUE;
}
