#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned char u8;
typedef unsigned short int u16;

void ppu_addr(vector<u8>& cpu_mem, struct Register& reg, u8& num);

u16 ppu_addr_create(vector<u8>& cpu_mem, vector<u8>& ppu_mem);

void ppu_addr_incl(u16& ppu_mem_addr, vector<u8>& cpu_mem);

void ppu_read(vector<u8>& cpu_mem, vector<u8>& ppu_mem, u8& num);

void ppu_write(vector<u8>& cpu_mem, vector<u8>& ppu_mem, u8& num);



