#pragma warning(disable : 4996)
#include <string>
#include <sstream>
#include <fstream>
#include "../OS13_HTCOM_LIB/pch.h"
#include "../OS13_HTCOM_LIB/OS14_HTCOM_LIB.h"
using namespace std;

#ifdef _WIN64
#pragma comment(lib, "C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab6/SP_Lab5/x64/Debug/OS14_HTCOM_LIB.lib")
#else
#pragma comment(lib, "../Debug/OS14_HTCOM_LIB.lib")
#endif

string intToString(int number);
wchar_t* getWC(const char* c);
wchar_t* getFileName(const char* c);
int main(int argc, char* argv[])
{
	try
	{
		const char* path = "C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab6/table/HT3.ht";
		ofstream logFile("application.log", ios::app);
		OS14_HTCOM_HANDEL h = OS13_HTCOM::Init();
		ht::HtHandle* ht ;
		if (argc == 4) {
			cout << "зашли и "<< argv[1];
			path = argv[1];
			ht = OS13_HTCOM::HT::open(h,getWC(argv[1]), getWC(argv[2]), getWC(argv[3]), true);
			//ht = OS13_HTCOM::HT::open(h,getWC(argv[1]), true);
		}
		else {
			cout << "зашли и " << argv[1];
			path = argv[1];
			ht = OS13_HTCOM::HT::open(h, getWC(argv[1]), true);
			//ht = OS13_HTCOM::HT::open(h,getWC(argv[1]), true);
		}
		//else {
		//	path = "C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab6/table/tableHTUser01.ht";
		//	ht = OS13_HTCOM::HT::open(h, L"C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab6/table/tableHTUser01.ht", L"HTUser01", L"1122", true);
		//	//ht = OS13_HTCOM::HT::open(h, getWC(argv[1]), true);
		//}
		if (ht) {
			cout << "-- open: success" << endl;
			logFile << "-- open: success" << endl;
		}
		else
			throw "-- open: error";
		HANDLE event = CreateEvent(NULL, TRUE, FALSE, getFileName(path));

		while (WaitForSingleObject(event, 0) == WAIT_TIMEOUT) {
			int numberKey = rand() % 50;
			string key = intToString(numberKey);
			cout << key << endl;
			logFile << key << endl;

			ht::Element* element = OS13_HTCOM::Element::createInsertElement(h,key.c_str(), key.length() + 1, "0", 2);
			if (OS13_HTCOM::HT::insert(h,ht, element)) {
				cout << "-- insert: success" << endl;
				logFile << "-- insert: success" << endl;
			}
			else {
				cout << "-- insert: error" << endl;
				logFile << "-- insert: error" << endl;
			}
			delete element;

			Sleep(1000);
		}
		OS13_HTCOM::HT::close(h, ht);
		OS13_HTCOM::Dispose(h);
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}

wchar_t* getWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 1];
	mbstowcs(wc, c, strlen(c) + 1);

	return wc;
}
wchar_t* getFileName(const char* c)
{
	const char* lastSlash = strrchr(c, '/');
	const char* filename = (lastSlash != NULL) ? lastSlash + 1 : c;
	return getWC(filename);
}

string intToString(int number)
{
	stringstream convert;
	convert << number;

	return convert.str();
}
