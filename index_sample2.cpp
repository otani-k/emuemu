#include <iostream> 
//#include <iostrem.h>
#include <fstream>
//#include <fstream.h>
#include <string>
#include <sstream>
#include <iterator>

using namespace std;

int main(){
	int cnt;
	char outfile[] = "helloworld_cversion/sample2/sample2.nes";
		ifstream fin(outfile, ios::in | ios::binary);
		//ファイルを開く
		//ios::は読み込み専用を示す
		//ios::binaryはバイナリ形式であることを示す
	
	if (!fin){
		cout << "ファイルsample2.nesが開けません";
		return 1;
	}
	//ファイルが開けなかったときのエラー処理
	
	char d;//文字列でないデータ（double型である理由はよくわからん）

	while(!fin.eof()){ //ファイルの最後まで続ける
		fin.read(&d, sizeof(char));
		//文字列でないデータを読み込む
		cout << hex << int(d) << " ";
		cnt++;
		if(cnt % 16 == 0) cout << endl;
	}


	fin.close(); //ファイルを閉じる

	return 0;
}

