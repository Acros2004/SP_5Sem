#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <string>
#include "sddl.h"



#include "C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab7/SP_lab6/OS15_HTCOM_LIB/pch.h"
#include "C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab7/SP_lab6/OS15_HTCOM_LIB/OS15_HTCOM_LIB.h"

#define SERVICENAME L"NIKLAD"
#define HTPATH L"C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab7/SP_lab6/storage/HT20.ht"

#define USERNAME L"HTUser01"
#define PASSWORD L"1122"

#define TRACEPATH L"C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab7/SP_lab6/storage/servise.trace"

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
VOID WINAPI ServiceHandler(DWORD fdwControl);

SECURITY_ATTRIBUTES getSecurityAttributes();
HANDLE createStopEvent(const wchar_t* stopEventName);
void startService();
void trace(const char* msg, int r = std::ofstream::app);
