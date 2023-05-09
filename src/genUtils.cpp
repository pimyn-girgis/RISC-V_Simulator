#include "genUtils.h"

// TH: returns the bits from start to end (inclusive) of num
int genUtils::get_bits(int num, int start, int end)
{
	int mask = (1 << (end - start + 1)) - 1;
	return (num >> start) & mask;
}

// TH: sets the bits from start to end (inclusive) of num to value
int genUtils::set_bits(int num, int start, int end, int value)
{
	value &= (1 << (end - start + 1)) - 1;
	int mask = (1 << (end - start + 1)) - 1;
	return (num & ~(mask << start)) | (value << start);
}
