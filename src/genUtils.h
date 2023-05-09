#pragma once

#ifndef GENUTILS_H
#define GENUTILS_H
#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <string>

//AW: general utilities class, encapsulates general functions used in classes, driver code etc
class genUtils
{
public:
	static int get_bits(int num, int start, int end);
	static int set_bits(int num, int start, int end, int value);
};

#endif
