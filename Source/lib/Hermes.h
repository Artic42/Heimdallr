/*
File Name:   Hermes.h
//
Compiler:    gcc
Author:      Artic42
Description: Header file of Hermes library
Testd on:    Raspberry Pi OS
*/

#ifndef HERMES_H
#define HERMES_H

/****************************************
*	Include                             *
****************************************/

#include "Artic42.h"

/****************************************
*	Public macros                       *
****************************************/

/****************************************
*	Public Function Prototype           * 
****************************************/

void createFile (string path);
void deleteFile (string path);
void bool2file (string  path, bool value);
bool file2bool (string  path);
void int2file (string  path, int value);
int file2int (string  path);
void float2file (string path, float value);
float file2float (string path);
void string2file (string path, string value);
string file2string (string path);

/****************************************
*	Public Constants                    * 
****************************************/

#endif