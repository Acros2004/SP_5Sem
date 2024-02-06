#include "tests.h"

using namespace std;

int main()
{
	ht::HtHandle* ht = ht::create(1000, 3, 10, 256, L"./files/HTspace.ht");
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
			cout << "-- close: error";
}