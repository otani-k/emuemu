#include "parse/parse.hpp"
#include "cpu/cpu.hpp"
#include "ppu/ppu.hpp"
#include "window/window.hpp"
#include "debug/memdump.hpp"
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <ios>
#include <iomanip>
#include <vector>
#include <GLFW/glfw3.h>

// 読み込むプログラム
char outfile[]="sample/nestest.nes";

// cpuメモリ
vector<u8> cpu_mem(0xffff + 1, 0);

// ppuメモリ
vector<u8> ppu_mem(0x3fff + 1, 0);

int main(){
    int ret=0;
    struct Register reg;
    struct cpu cpu;
    
    ret = myparse(outfile, cpu_mem, ppu_mem);
    if(ret==1) cout << "どんまい" << endl;
    //cpu_dump(cpu_mem);
    //ppu_dump(ppu_mem);
    reg.regreset();
    reg.PC = 0xC000;
    ret = disp(reg, cpu, cpu_mem, ppu_mem);
    if(ret==1) cout << "描画失敗" << endl;
    //cpu_dump(cpu_mem);
    //ppu_dump(ppu_mem);
//    cout << "cpu_mem[0xC002]: " << hex << +cpu_mem[0xC002] << endl;
//    cout << "cpu_mem[0xC003]: " << hex << +cpu_mem[0xC003] << endl;
//    cout << "reg.PC: " << reg.PC << endl;

    return 0;
};
