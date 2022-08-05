#include "parse/parse.hpp"
#include "cpu/cpu.hpp"
#include "ppu/ppu.hpp"
#include "window/window.hpp"
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
char outfile[]="sample/sample1.nes";

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

    reg.regreset();
    cpu.run(reg, cpu_mem, ppu_mem);
    ret = disp(ppu_mem);
    if(ret==1) cout << "描画失敗" << endl;

    return 0;
};
