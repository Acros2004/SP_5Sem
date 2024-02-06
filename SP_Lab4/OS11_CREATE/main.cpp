#include "../OS11_HTAPI/pch.h"
#include "../OS11_HTAPI/HT.h"
#include <typeinfo>
using namespace std;
//.\OS11_CREATE.exe 2000 3 4 4 nikita.ht
wchar_t* getWC(const char* c);
int main(int argc, char* argv[])
{
#ifdef _WIN64
	HMODULE hmdll = LoadLibrary(L"C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_Lab4/x64/Debug/OS11_HTAPI.dll");
#else
	HMODULE hmdll = LoadLibrary(L"../Debug/OS11_HTAPI.dll");
#endif
	auto create = (ht::HtHandle * (*)(int,int,int,int,const wchar_t*)) GetProcAddress(hmdll, "create");
	auto close = (BOOL(*)(ht::HtHandle*)) GetProcAddress(hmdll, "close");
	cout << hmdll << endl;
	cout << create << endl;
	ht::HtHandle* ht = nullptr;
	cout << atoi(argv[1]) << atoi(argv[2]) << atoi(argv[3]) << atoi(argv[4]) << (argv[5]) << endl;
	//ht = create(2000, 3, 4, 4, L"HTspace.ht");
	
	ht = create(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), getWC(argv[5]));
	try {
		if (ht)
		{
			cout << "HT-Storage Created" << endl;
			wcout << "filename: " << ht->fileName << endl;
			cout << "secSnapshotInterval: " << ht->secSnapshotInterval << endl;
			cout << "capacity: " << ht->capacity << endl;
			cout << "maxKeyLength: " << ht->maxKeyLength << endl;
			cout << "maxDataLength: " << ht->maxPayloadLength << endl;

			close(ht);
		}
		else
			cout << "-- create: error" << endl;
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

