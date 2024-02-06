#include <string>
#include <sstream>
#include <fstream>
#include "../OS11_HTAPI/pch.h"
#include "../OS11_HTAPI/HT.h"

using namespace std;

string intToString(int number);
int charToInt(char* str);
string incrementPayload(char* str);

int main(int argc, char* argv[])
{
	try 
	{
#ifdef _WIN64
		HMODULE hmdll = LoadLibrary(L"C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_Lab4/x64/Debug/OS11_HTAPI.dll");
#else
		HMODULE hmdll = LoadLibrary(L"../Debug/OS11_HTAPI.dll");
#endif
		ofstream logFile("application3.log", ios::app);
		auto open = (ht::HtHandle * (*)(const wchar_t*, bool)) GetProcAddress(hmdll, "open");
		auto get = (ht::Element * (*)(ht::HtHandle*, const ht::Element*)) GetProcAddress(hmdll, "get");
		auto update = (BOOL(*)(ht::HtHandle*, const ht::Element*,const void*, int)) GetProcAddress(hmdll, "update");
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

			ht::Element* element = get(ht, new ht::Element(key.c_str(), key.length() + 1));
			if (element)
			{
				cout << "-- get: success" << endl;
				logFile << "-- get: success" << endl;
				string newPayload = incrementPayload((char*)element->payload);

				if (update(ht, element, newPayload.c_str(), newPayload.length() + 1)) {
					cout << "-- update: success" << endl;
					logFile << "-- update: success" << endl;
				}
				else {
					cout << "-- update: error" << endl;
					logFile << "-- update: error" << endl;
				}	
			}
			else {
				cout << "-- get: error" << endl;
				logFile << "-- get: error" << endl;
			}

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

int charToInt(char* str)
{
	stringstream convert;
	convert << str;
	int num;
	convert >> num;

	return num;
}

string incrementPayload(char* str)
{
	int oldNumberPayload = charToInt(str);
	int newNumberPayload = oldNumberPayload + 1;
	string newPayload = intToString(newNumberPayload);

	return newPayload;
}
