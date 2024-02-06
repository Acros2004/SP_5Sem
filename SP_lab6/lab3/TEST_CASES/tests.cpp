#include "tests.h"

namespace tests
{
	BOOL TestDoubleInsert(ht::HtHandle* htHandle) {
		ht::Element* element = new ht::Element("t1", 3, "t1", 3);
		const char str[] = "-- found element(insert)";
		ht::insert(htHandle, element);
		ht::insert(htHandle, element);
		if (std::memcmp(ht::getLastError(htHandle), str, sizeof(str)) == 0)
			return true;
		return false;	
	}

	BOOL TestGetNonExistentElement(ht::HtHandle* htHandle) {
		ht::get(htHandle, new ht::Element("nik", 6));
		const char str[] = "-- not found element (GET)";
		if (std::memcmp(ht::getLastError(htHandle), str, sizeof(str)) == 0)
			return true;
		return false;
	}
	BOOL TestUpdateRemovedElement(ht::HtHandle* htHandle) {
		ht::Element* element = new ht::Element("update", 6, "old_data", 8);
		const char str[] = "-- not found element (UPDATE)";
		ht::insert(htHandle, element);
		ht::remove(htHandle,element);

		const char* newPayload = "new_data";
		int newPayloadLength = 8;
		ht::update(htHandle, new ht::Element("update", 6), newPayload, newPayloadLength);
		if (std::memcmp(ht::getLastError(htHandle), str, sizeof(str)) == 0)
			return true;
		return false;
	}
	BOOL TestInsertElementWithCollision(ht::HtHandle* htHandle)
	{
		const char str[] = "-- found element(insert)";
		ht::insert(htHandle, new ht::Element("abc", 4, "payload", 8));
		ht::insert(htHandle, new ht::Element("cab", 4, "payload", 8));
		ht::remove(htHandle, new ht::Element("abc", 4, "payload", 8));
		ht::insert(htHandle, new ht::Element("cab", 4, "payload", 8));
		if (std::memcmp(ht::getLastError(htHandle), str, sizeof(str)) == 0)
			return true;
		return false;
	}

	
	
	BOOL TestRemoveNonExistentElement(ht::HtHandle* htHandle)
	{
		const char str[] = "-- not found element (DELETE)";
		ht::Element* element = new ht::Element("remove", 7, "to_be_deleted", 14);
		ht::insert(htHandle, element);
		ht::remove(htHandle, new ht::Element("nothing", 10));
		if (std::memcmp(ht::getLastError(htHandle), str, sizeof(str)) == 0)
			return true;
		return false;
	}

	
}