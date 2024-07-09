#pragma once
#include <cstdio>

#define LOG(M, ...) std::printf(M "\n", ##__VA_ARGS__)
