#pragma once
#ifdef _WIN64
#pragma comment(lib, "../x64/debug/OS10_HTAPI.lib")
#else
#pragma comment(lib, "../debug/OS10_HTAPI.lib")
#endif

#include "../OS10_HTAPI/pch.h"
#include "../OS10_HTAPI/HT.h"

namespace tests
{
	BOOL TestGetNonExistentElement(ht::HtHandle* htHandle);
	BOOL TestUpdateRemovedElement(ht::HtHandle* htHandle);
	BOOL TestInsertElementWithCollision(ht::HtHandle* htHandle);
	BOOL TestDoubleInsert(ht::HtHandle* htHandle);
	BOOL TestRemoveNonExistentElement(ht::HtHandle* htHandle);
}
