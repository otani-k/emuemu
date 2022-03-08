#include "parse/parse.hpp"
#include "cpu/cpu.hpp"
#include "ppu/ppu.hpp"
#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <ios>
#include <iomanip>
#include <vector>

int cnt;
int prom_size;
int crom_size;
char outfile[]="sample1.nes";
vector<u8> pROM;
vector<u8> cROM;
vector<u8> cpu_mem(0xffff + 1, 0);
vector<u8> ppu_mem(0x3fff + 1, 0);

int main(){
    int result=0;
    struct Register reg;
    struct cpu cpu;
    cout << "start" << endl;
    result = parse(cnt, prom_size, crom_size, outfile, pROM, cROM, cpu_mem, ppu_mem);
    if(result==1) cout << "どんまい" << endl;
//    cout << "pROM: " << endl;
//    cnt = 0;
//    for(int i=0; i<static_cast<int>(pROM.size()); i++){
//		cnt = cnt + 1;
//		cout << setfill('0') << right << setw(2) << hex << +pROM.at(i) << " ";
//		if((cnt > 14) && (cnt % 16) == 0) cout << endl;
//	}

    cout << "ppu_mem: " << endl;
    cout << "name_table0: " << endl;
/*     for(int j=0x2000; j<static_cast<int>(ppu_mem.size()); j++){
		cnt = cnt + 1;
		cout << setfill('0') << right << setw(2) << hex << +ppu_mem.at(j) << " ";
		if((cnt > 14) && (cnt % 16) == 0) cout << endl;
        if(j==0x23BF) cout << "type_table0" << endl;
        if(j==0x23ff) cout << "name_table1" << endl;
        if(j==0x27bf) cout << "type_table1" << endl;
        if(j==0x27ff) cout << "name_table2" << endl;
        if(j==0x2bbf) cout << "type_table2" << endl;
	} */
    //reg.regreset()
    //cout << "aaa" << endl;
    cout <<  "before: " << hex << reg.PC << endl;
    reg.regreset();
    cout << "after: " << hex << reg.PC << endl;
    cpu.run(reg, cpu_mem, ppu_mem);
    //cout << +reg.PC << endl;
    //cpu.exec();
    //for(int i=0; i<)
    
    cout << "cpu_mem: " << endl;
    cnt = 0;
    cout << "00: ";
    for(int i=0; i<static_cast<int>(cpu_mem.size()); i++){
		cnt = cnt + 1;
		cout << setfill('0') << right << setw(2) << hex << +cpu_mem.at(i) << " ";
		if((cnt > 14) && (cnt % 16) == 0) {
            cout << endl;
            cout << setfill('0') << right << setw(2) << hex << +cnt << ": ";
        }
	}

    cout << "ppu_mem: " << endl;
    cnt = 0;
    for(int j=0; j<static_cast<int>(ppu_mem.size()); j++){
		cnt = cnt + 1;
		cout << setfill('0') << right << setw(2) << hex << +ppu_mem.at(j) << " ";
		if((cnt > 14) && (cnt % 16) == 0) {
            cout << endl;
            cout << setfill('0') << right << setw(2) << hex << +cnt << ": ";
        }
	}





    


    return 0;
};