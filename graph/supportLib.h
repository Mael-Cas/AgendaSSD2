//
// Created by maelc on 22/11/2023.
//

#ifndef AGENDASSD2_SUPPORTLIB_H
#define AGENDASSD2_SUPPORTLIB_H
#include <stdlib.h>
#include <stdio.h>

unsigned char *DoubleArrayToByteArray(double *data, size_t length);
void WriteToFile(ByteArray *data, char *filename);
double *ByteArrayToDoubleArray(unsigned char *data, size_t length);
#endif //AGENDASSD2_SUPPORTLIB_H
