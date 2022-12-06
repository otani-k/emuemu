#include "../cpu/cpu.hpp"
#include "memdump.hpp"
#include <iostream>
#include <vector>

void ppu_dump(vector<u8>& ppu_mem){
  int ppu_size = ppu_mem.size();
  cout << "ppu_dump: " << endl;
  cout << "0000: ";
  for(int i=0; i<ppu_size; i++){
		cout << setfill('0') << right << setw(2) << hex << +ppu_mem.at(i) << " ";
    if((i > 14) && (i % 16) == 15) {
      cout << endl;
      cout << setfill('0') << right << setw(4) << hex << i + 1 << ": ";
    }
  }
}

void cpu_dump(vector<u8>& cpu_mem){
  int cpu_size = cpu_mem.size();
  cout << "cpu_dump: " << endl;
  cout << "0000: ";
    for(int i=0; i<cpu_size; i++){
		  cout << setfill('0') << right << setw(2) << hex << +cpu_mem.at(i) << " ";
      if((i > 14) && (i % 16) == 15) {
        cout << endl;
        cout << setfill('0') << right << setw(4) << hex << i + 1 << ": ";
      }
  }
}