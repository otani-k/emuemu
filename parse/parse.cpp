#include "parse.hpp"
#include <iostream> 
//#include <iostrem.h>
#include <fstream>
//#include <fstream.h>
#include <string>
#include <sstream>
#include <iterator>
#include <ios>
#include <iomanip>
#include <vector>


int myparse(char outfile[], vector<u8>& cpu_mem, vector<u8>& ppu_mem){
	u8 d;//文字列でないデータ（double型である理由はよくわからん）→  結局charにした
	//u8 v = 0;
	int cnt=0, prom_size=0, crom_size=0;
	vector<u8> pROM;
	vector<u8> cROM;
	ifstream fin(outfile, ios::in | ios::binary);
		//ファイルを開く
		//ios::は読み込み専用を示す
		//ios::binaryはバイナリ形式であることを示す	
	if (!fin){
		cout << "ファイルsample1.nesが開けません" << endl;
		return 1;
	}
	//ファイルが開けなかったときのエラー処理

	//cout << "00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F" << endl;
	//cout << "-------------------------------------------------"  << endl;
	//cout << setfill('0') << right << setw(8) << hex << cnt << ": ";	
	while(!fin.eof()){ //ファイルの最後まで続ける
		fin.read((char*)&d, sizeof(char));
		//データを読み込む
		//cout << setfill('0') << right << setw(2) << hex << +d << " ";
		if(cnt==4) {
			prom_size = static_cast<int>(d);
			prom_size = 16 * 1024 * prom_size;
		}
		else if(cnt==5) {
			crom_size = static_cast<int>(d);
			crom_size = 8 * 1024 * crom_size;
		}
		else if(cnt>=16 && (cnt-15)<=prom_size) {
			pROM.push_back(d);
		}
		else if(cnt>=16 && (cnt-15-prom_size)<=crom_size) {
			cROM.push_back(d);
		}
		cnt++;
		//if(cnt % 16 == 0) {
		//	cout << endl;
	//		cout << setfill('0') << right <<setw(8) << hex << cnt + 1;
		//}	
	}
	fin.close(); //ファイルを閉じる
	//cout << pROM.size() << endl;
	cnt = 0;


	for(int i=0; i<static_cast<int>(pROM.size()); i++){
		//cout << i << endl;
		//cnt = cnt + 1;
		cpu_mem.at(0x8000 + i) = pROM.at(i);
		//v = pROM.at(i);
		//cpu_mem.at(0x8000 + i) = v;
		//cout << setfill('0') << right << setw(2) << hex << +cpu_mem.at(0x8000 + i) << " ";
		//if((cnt > 14) && (cnt % 16) == 0) cout << endl;
	}
	cout << "AAA" << endl;
	cout << (0x3fff + 1) - 0x3f00 << endl;
	cout << 0x3fff + 1  - 0x2000<< endl;
	cout << cROM.size() << endl;
	for(int j=0; j<static_cast<int>(cROM.size()); j++){
		//cnt = cnt + 1;
		//cout << j << endl;
		ppu_mem.at(j) = cROM.at(j);
		//	cout << (0x3fff + 1) - 0x3f00 << endl;cout << j << endl;
	}
	return 0;
}

/*  int main(){
	int result;
	ifstream fin(outfile, ios::in | ios::binary);
		//ファイルを開く
		//ios::は読み込み専用を示す
		//ios::binaryはバイナリ形式であることを示す
	
	if (!fin){
		cout << "ファイルsample1.nesが開けません";
		return 1;
	}
	//ファイルが開けなかったときのエラー処理
	
	u8 d;//文字列でないデータ（double型である理由はよくわからん）→  結局charにした
	//cout << "00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F" << endl;
	//cout << "-------------------------------------------------"  << endl;
	//cout << setfill('0') << right << setw(8) << hex << cnt << ": ";	
	while(!fin.eof()){ //ファイルの最後まで続ける
		fin.read((char*)&d, sizeof(char));
		//データを読み込む
		//cout << setfill('0') << right << setw(2) << hex << +d << " ";
		if(cnt==4) {
			prom_size = static_cast<int>(d);
			prom_size = 16 * 1024 * prom_size;
		}
		else if(cnt==5) {
			crom_size = static_cast<int>(d);
			crom_size = 8 * 1024 * crom_size;
		}
		else if(cnt>=16 && (cnt-15)<=prom_size) {
			pROM.push_back(d);
		}
		else if(cnt>=16 && (cnt-15-prom_size)<=crom_size) {
			cROM.push_back(d);
		}
		cnt++;
		//if(cnt % 16 == 0) {
		//	cout << endl;
	//		cout << setfill('0') << right <<setw(8) << hex << cnt + 1;
		//}	
	}


	fin.close(); //ファイルを閉じる 
	result = parse(cnt, prom_size, crom_size, outfile, pROM, cROM);

	cout << "prom_size: " << prom_size << endl;
	cout << "pROM_size: " << pROM.size() << endl;
	cout << "crom_size: " << crom_size << endl;
	cout << "cROM_size: " << cROM.size() << endl;

	cout << "prom: " << endl;
	cnt=0;
	for(int i=0; i<prom_size; i++){
		cnt = cnt + 1;
		cout << setfill('0') << right << setw(2) << hex << +pROM.at(i) << " ";
		if((cnt > 14) && (cnt % 16) == 0) cout << endl;
	}
	cout << endl;
	cout << "crom: " << endl;
	cnt = 0;
	for(int j=0; j<crom_size; j++){
		cnt = cnt + 1;
		cout << setfill('0') << right << setw(2) << hex << +cROM.at(j) << " ";
		if( (cnt > 14) && (cnt % 16) == 0) cout << endl;
	}

	return 0;
} */

