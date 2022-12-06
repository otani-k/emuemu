#pragma once
#include "../cpu/cpu.hpp"
#include <iostream>
#include <vector>

void ppu_dump(vector<u8>& ppu_mem);
void cpu_dump(vector<u8>& cpu_mem);