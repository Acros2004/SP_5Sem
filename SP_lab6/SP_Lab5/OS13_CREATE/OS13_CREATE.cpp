#pragma warning(disable : 4996)
#include <iostream>
#include <windows.h>
#include <typeinfo>
#include "../OS13_HTCOM_LIB/pch.h"
#include "../OS13_HTCOM_LIB/OS14_HTCOM_LIB.h"
using namespace std;

#ifdef _WIN64
#pragma comment(lib, "C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab6/SP_Lab5/x64/Debug/OS14_HTCOM_LIB.lib")
#else
#pragma comment(lib, "../Debug/OS14_HTCOM_LIB.lib")
#endif
//snapshotinterval=3,    
//capacity = 2000, maxkeylength = 4, 
//maxdatalength = 4
//OS13_CREATE 2000 3 4 4 C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab5/table/table.ht
//OS14_CREATE.exe 2000 4 4 3 HT C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab6/table/table.ht
wchar_t* getWC(const char* c);
int main(int argc, char* argv[])
{
	cout << atoi(argv[1]) << atoi(argv[2]) << atoi(argv[3]) << atoi(argv[4]) << (argv[5]) << endl;
	try {
		OS14_HTCOM_HANDEL h = OS13_HTCOM::Init();
		ht::HtHandle* ht = OS13_HTCOM::HT::create(h, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), getWC(argv[5]), getWC(argv[6]));
		if (ht)
		{
			cout << "HT-Storage Created" << endl;
			wcout << "filename: " << ht->fileName << endl;
			cout << "secSnapshotInterval: " << ht->secSnapshotInterval << endl;
			cout << "capacity: " << ht->capacity << endl;
			cout << "maxKeyLength: " << ht->maxKeyLength << endl;
			cout << "maxDataLength: " << ht->maxPayloadLength << endl;

			OS13_HTCOM::HT::close(h,ht);
		}
		else
			cout << "-- create: error" << endl;
		OS13_HTCOM::Dispose(h);
	}
	catch (exception e) {
		cout << "error";
	}

}
wchar_t* getWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 1];
	mbstowcs(wc, c, strlen(c) + 1);

	return wc;
}

