//#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include "ppu.hpp"
#include "../cpu/cpu.hpp"

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
