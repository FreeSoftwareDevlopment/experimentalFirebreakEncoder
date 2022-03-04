#include "pch.h"
#include "framework.h"
#include "firebreak.h"

Cfirebreak::Cfirebreak()
{
	return;
}

firebreakLoc Cfirebreak::AddBool(bool* b)
{
	//! BOOL
	//! (TRUE)  = 0b00000001
	//! (FALSE) = 0b00000000
	return AddData((void*)b, 1);
}

firebreakLoc Cfirebreak::AddData(void* b, BIT bits)
{
	br1.push_back(firebreakstruct(bits, b));
	bitcounter += bits;
	return (br1.size() - 1);
}

firebreakLoc Cfirebreak::AddInt(int* b)
{
	return AddDataSiz((void*)b, sizeof(int));
}

firebreakLoc Cfirebreak::AddDataSiz(void* b, size_t size)
{
	return AddData(b, size * 8);
}

firebreakstruct::firebreakstruct(BIT bits, void* datar) :bit(bits), data(datar) {}

firebreakstruct::firebreakstruct() : bit(0), data(nullptr) {}

