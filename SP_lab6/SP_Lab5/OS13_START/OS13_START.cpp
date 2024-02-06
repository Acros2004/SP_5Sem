﻿#pragma warning(disable : 4996)
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "../OS13_HTCOM_LIB/pch.h"
#include "../OS13_HTCOM_LIB/OS14_HTCOM_LIB.h"

#ifdef _WIN64
#pragma comment(lib, "C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab6/SP_Lab5/x64/Debug/OS14_HTCOM_LIB.lib")
#else
#pragma comment(lib, "../Debug/OS14_HTCOM_LIB.lib")
#endif
//OS13_START C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab5/table/table.ht
//OS14_START.exe C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab6/table/tableHTUser01.ht HTUser01 1122
using namespace std;

wchar_t* getWC(const char* c);
wchar_t* getFileName(const char* c);

int main(int argc, char* argv[])
{
	HANDLE event = CreateEvent(NULL,TRUE, FALSE, getFileName(argv[1]));
	OS14_HTCOM_HANDEL h = OS13_HTCOM::Init();
	ht::HtHandle* ht = nullptr;

	wchar_t* fileName = getWC(argv[1]);
	if (argc == 4)
	{
		wchar_t* username = getWC(argv[2]);
		wchar_t* password = getWC(argv[3]);

		ht = OS13_HTCOM::HT::open(h, fileName, username, password);
	}
	else
	{
		ht = OS13_HTCOM::HT::open(h, fileName);
	}

	if (ht)
	{
		cout << "==============  HT-Storage Start  ==============" << endl;
		wcout << "filename:\t\t" << ht->fileName << endl;
		cout << "secSnapshotInterval:\t" << ht->secSnapshotInterval << endl;
		cout << "capacity:\t\t" << ht->capacity << endl;
		cout << "maxKeyLength:\t\t" << ht->maxKeyLength << endl;
		cout << "maxPayloadLength:\t" << ht->maxPayloadLength << endl << endl;

		while (WaitForSingleObject(event, 0) == WAIT_TIMEOUT) {
			SleepEx(0, TRUE);
		}
		OS13_HTCOM::HT::snap(h, ht);
		OS13_HTCOM::HT::close(h, ht);
	}
	else
		cout << "-- open: error" << endl; 
	OS13_HTCOM::Dispose(h);
}
wchar_t* getFileName(const char* c)
{
	const char* lastSlash = strrchr(c, '/');
	const char* filename = (lastSlash != NULL) ? lastSlash + 1 : c;
	return getWC(filename);
}

wchar_t* getWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 1];
	mbstowcs(wc, c, strlen(c) + 1);

	return wc;
}