#include "tests.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
string intToString(int number)
{
	stringstream convert;
	convert << number;

	return convert.str();
}
int main()
{
	ht::HtHandle* ht = ht::open(L"C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab6/table/HT3.ht", L"HTUser01", L"1122", true);
	while (true) {
		int numberKey = rand() % 50;
		string key = intToString(numberKey);
		cout << key << endl;

		ht::Element* element = new ht::Element( key.c_str(), key.length() + 1, "0", 2);
		if (ht::insert(ht, element))
			cout << "-- insert: success" << endl;
		else
			cout << "-- insert: error" << endl;

		delete element;

		Sleep(1000);
	}


	/*ht::HtHandle* ht = ht::create(1000, 3, 10, 256, L"./files/HTspace.ht");
	if (ht)
		cout << "-- create: success" << endl;
	else {
		cout << "-- create: error" << endl;
		cout << ht::getLastError(ht) << endl;
	}
	
	if (tests::TestGetNonExistentElement(ht))
		cout << "-- TestGetNonExistentElement: success" << endl;
	else {
		cout << "-- TestGetNonExistentElement: error" << endl;
	}

	if (tests::TestDoubleInsert(ht))
		cout << "-- TestDoubleInsert: success" << endl;
	else {
		cout << "-- TestDoubleInsert: error" << endl;
	}
	
	if(tests::TestUpdateRemovedElement(ht))
		cout << "-- TestUpdateRemovedElement: success" << endl;
	else {
		cout << "-- TestUpdateRemovedElement: error" << endl;
	}

	if (tests::TestInsertElementWithCollision(ht))
		cout << "-- TestInsertElementWithCollision: success" << endl;
	else {
		cout << "-- TestInsertElementWithCollision: error" << endl;
	}

	if (tests::TestRemoveNonExistentElement(ht))
		cout << "-- TestRemoveNonExistentElement: success" << endl;
	else {
		cout << "-- TestRemoveNonExistentElement: error" << endl;
	}

	if (ht != nullptr)
		if (ht::close(ht))
			cout << "-- close: success" << endl;
		else
			cout << "-- close: error";*/
}