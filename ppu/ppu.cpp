//#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include "ppu.hpp"
#include "../cpu/cpu.hpp"

using namespace std;



//パレットの色たち（具体的な実装はまだ）
/*const vector<vector<int>> colors = [
  [0x80, 0x80, 0x80], [0x00, 0x3D, 0xA6], [0x00, 0x12, 0xB0], [0x44, 0x00, 0x96],
  [0xA1, 0x00, 0x5E], [0xC7, 0x00, 0x28], [0xBA, 0x06, 0x00], [0x8C, 0x17, 0x00],
  [0x5C, 0x2F, 0x00], [0x10, 0x45, 0x00], [0x05, 0x4A, 0x00], [0x00, 0x47, 0x2E],
  [0x00, 0x41, 0x66], [0x00, 0x00, 0x00], [0x05, 0x05, 0x05], [0x05, 0x05, 0x05],
  [0xC7, 0xC7, 0xC7], [0x00, 0x77, 0xFF], [0x21, 0x55, 0xFF], [0x82, 0x37, 0xFA],
  [0xEB, 0x2F, 0xB5], [0xFF, 0x29, 0x50], [0xFF, 0x22, 0x00], [0xD6, 0x32, 0x00],
  [0xC4, 0x62, 0x00], [0x35, 0x80, 0x00], [0x05, 0x8F, 0x00], [0x00, 0x8A, 0x55],
  [0x00, 0x99, 0xCC], [0x21, 0x21, 0x21], [0x09, 0x09, 0x09], [0x09, 0x09, 0x09],
  [0xFF, 0xFF, 0xFF], [0x0F, 0xD7, 0xFF], [0x69, 0xA2, 0xFF], [0xD4, 0x80, 0xFF],
  [0xFF, 0x45, 0xF3], [0xFF, 0x61, 0x8B], [0xFF, 0x88, 0x33], [0xFF, 0x9C, 0x12],
  [0xFA, 0xBC, 0x20], [0x9F, 0xE3, 0x0E], [0x2B, 0xF0, 0x35], [0x0C, 0xF0, 0xA4],
  [0x05, 0xFB, 0xFF], [0x5E, 0x5E, 0x5E], [0x0D, 0x0D, 0x0D], [0x0D, 0x0D, 0x0D],
  [0xFF, 0xFF, 0xFF], [0xA6, 0xFC, 0xFF], [0xB3, 0xEC, 0xFF], [0xDA, 0xAB, 0xEB],
  [0xFF, 0xA8, 0xF9], [0xFF, 0xAB, 0xB3], [0xFF, 0xD2, 0xB0], [0xFF, 0xEF, 0xA6],
  [0xFF, 0xF7, 0x9C], [0xD7, 0xE8, 0x95], [0xA6, 0xED, 0xAF], [0xA2, 0xF2, 0xDA],
  [0x99, 0xFF, 0xFC], [0xDD, 0xDD, 0xDD], [0x11, 0x11, 0x11], [0x11, 0x11, 0x11],
];
*/ 

//ppu_addrへの書き込みが何度行われたか（0 or 1）
int ppu_addr_count = 0;

//ppu_addr：ppu_scrollレジスタとppu_addrレジスタへの書き込み
void ppu_addr(vector<u8>& cpu_mem, struct Register& reg, u8& num){
    if(ppu_addr_count == 0){
        cpu_mem.at(0x2005) = num;
        ppu_addr_count++;
        cout << "0x2005 & 0x2006:  " << setfill('0') << right << setw(2) << hex << +cpu_mem.at(0x2005) << " " << +cpu_mem.at(0x2006) << endl;
        
    }
    else if(ppu_addr_count == 1){
        cpu_mem.at(0x2006) = num;
        ppu_addr_count = 0;
        cout << "0x2005 & 0x2006:  " << setfill('0') << right << setw(2) << hex << +cpu_mem.at(0x2005) << " " << +cpu_mem.at(0x2006) << endl;
    }
}

u16 ppu_addr_create(vector<u8>& cpu_mem, vector<u8>& ppu_mem){
    u16 ppu_mem_addr;

    //cout << "0x2005 & 0x2006:  " << setfill('0') << right << setw(2) << hex << +cpu_mem.at(0x2005) << " " << +cpu_mem.at(0x2006) << endl;

    ppu_mem_addr = static_cast<u16>(cpu_mem.at(0x2005));
    //cout << "before bitset" << bitset<16>(ppu_mem_addr) << endl;
    ppu_mem_addr = ppu_mem_addr << 8;
    //cout << "after bitset" << bitset<16>(ppu_mem_addr) << endl;
    ppu_mem_addr = ppu_mem_addr | static_cast<u16>(cpu_mem.at(0x2006));
    
    return ppu_mem_addr; 
}

void ppu_addr_incl(u16& ppu_mem_addr, vector<u8>& cpu_mem){
    if((cpu_mem.at(0x2000) & 0b00000100) == 0){
        ppu_mem_addr++;
        cpu_mem.at(0x2005) = static_cast<u8>(ppu_mem_addr >> 8);
        cpu_mem.at(0x2006) = static_cast<u8>(ppu_mem_addr & 0x00ff);
    //    cout << "0x2005 & 0x2006:  " << setfill('0') << right << setw(2) << hex << +cpu_mem.at(0x2005) << " " << +cpu_mem.at(0x2006) << endl;
    }
    else {
        ppu_mem_addr = ppu_mem_addr + 32;
        cpu_mem.at(0x2005) = static_cast<u8>(ppu_mem_addr & 0x00ff);
        cpu_mem.at(0x2006) = static_cast<u8>(ppu_mem_addr >> 8);
    }
}
//ppu_read: ppuのメモリ領域（cpu_memの0x2006番地）の値をppu_dataレジスタ（cpu_memの0x2007番地）に読み込み（あんま使われんっぽい）
void ppu_read(vector<u8>& cpu_mem, vector<u8>& ppu_mem, u8& num){
    u16 ppu_mem_addr;

    ppu_mem_addr = ppu_addr_create(cpu_mem, ppu_mem);
    cpu_mem.at(0x2007) = ppu_mem.at(ppu_mem_addr);
    num = cpu_mem.at(0x2007);
    ppu_addr_incl(ppu_mem_addr, cpu_mem);
}

//ppu_write: ppuのメモリ領域（cpu_memの0x2006番地）にppu_dataレジスタ（cpu_memの0x2007番地）を書き込み 
void ppu_write(vector<u8>& cpu_mem, vector<u8>& ppu_mem, u8& num){
    u16 ppu_mem_addr;

    ppu_mem_addr = ppu_addr_create(cpu_mem, ppu_mem);
    cpu_mem.at(0x2007) = num;
    //cout << "aaa" << endl;
    //cout << "ppu_mem_addr: " << hex << +ppu_mem_addr << endl;
    //cout << hex << +ppu_mem_addr << endl;
    ppu_mem.at(ppu_mem_addr) = cpu_mem.at(0x2007);
    //cout << "before ppu_addr_incl2" << endl;
    ppu_addr_incl(ppu_mem_addr, cpu_mem);
}
