#include <string>
#include <sstream>
#include <fstream>
#include "../OS11_HTAPI/pch.h"
#include "../OS11_HTAPI/HT.h"

using namespace std;

string intToString(int number);

int main(int argc, char* argv[])
{
	try 
	{
#ifdef _WIN64
		HMODULE hmdll = LoadLibrary(L"C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_Lab4/x64/Debug/OS11_HTAPI.dll");
#else
		HMODULE hmdll = LoadLibrary(L"../Debug/OS11_HTAPI.dll");
#endif
		ofstream logFile("application.log", ios::app);
		if (!hmdll)
			throw "-- LoadLibrary failed";
		cout << "-- LoadLibrary success" << endl;
		logFile << "-- LoadLibrary success" << endl;

		auto open = (ht::HtHandle * (*)(const wchar_t*, bool)) GetProcAddress(hmdll, "open");
		auto insert = (BOOL(*)(ht::HtHandle*, const ht::Element*)) GetProcAddress(hmdll, "insert");
		auto createInsertElement = (ht::Element * (*)(const void*, int, const void*, int)) GetProcAddress(hmdll, "createInsertElement");

		ht::HtHandle* ht = open(L"C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_Lab4/storage/HTspace2.ht", true);
		if (ht) {
			cout << "-- open: success" << endl;
			logFile << "-- open: success" << endl;
		}
		else
			throw "-- open: error";

		while (true) {
			int numberKey = rand() % 50;
			string key = intToString(numberKey);
			cout << key << endl;
			logFile << key << endl;

			ht::Element* element = createInsertElement(key.c_str(), key.length() + 1, "0", 2);
			if (insert(ht, element)) {
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
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}

string intToString(int number)
{
	stringstream convert;
	convert << number;

	return convert.str();
}
