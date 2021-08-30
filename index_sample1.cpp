#include <iostream> 
//#include <iostrem.h>
#include <fstream>
//#include <fstream.h>
#include <string>
#include <sstream>
#include <iterator>
#include <ios>
#include <iomanip>

using namespace std;

int main(){
	int cnt;
	char outfile[] = "helloworld/sample1/sample1.nes";
		ifstream fin(outfile, ios::in | ios::binary);
		//ファイルを開く
		//ios::は読み込み専用を示す
		//ios::binaryはバイナリ形式であることを示す
	
	if (!fin){
		cout << "ファイルsample1.nesが開けません";
		return 1;
	}
	//ファイルが開けなかったときのエラー処理
	
	int d;//文字列でないデータ（double型である理由はよくわからん）→  結局charにした
	//cout << "00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F" << endl;
	//cout << "-------------------------------------------------"  << endl;
	//cout << setfill('0') << right << setw(8) << hex << cnt << ": ";	
	while(!fin.eof()){ //ファイルの最後まで続ける
		fin.read((char*)&d, sizeof(char));
		//データを読み込む
		cout << setfill('0') << right << setw(2) << hex << d << " ";
		cnt++;
		if(cnt % 16 == 0) {
			cout << endl;
	//		cout << setfill('0') << right <<setw(8) << hex << cnt + 1;
		}	
	}


	fin.close(); //ファイルを閉じる

	return 0;
}

