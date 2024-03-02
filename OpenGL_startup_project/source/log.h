#pragma once
#include <iostream>

#define SEDEN_ERROR(Message,...) printf("ERROR : " Message "\n", ##__VA_ARGS__);
#define SEDEN_WARNING(Message,...) printf("WARNING : " Message "\n", ##__VA_ARGS__);
#define SEDEN_INFO(Message,...) printf("INFO : " Message "\n", ##__VA_ARGS__);