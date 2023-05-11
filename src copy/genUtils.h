#pragma once

#ifndef GENUTILS_H
#define GENUTILS_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string>

// AW: general utilities class, encapsulates general functions used in classes,
// driver code etc
class genUtils {
public:
  static int get_bits(int num, int start, int end);
  static int set_bits(int num, int start, int end, int value);
  static int sign_extend(int num, int bits);
};

#endif
