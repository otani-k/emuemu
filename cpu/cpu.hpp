#pragma once
#include <iostream>
#include <iomanip>
#include <bitset>
#include <string>
#include <vector>
#include "../ppu/ppu.hpp"

using namespace std;

//オペコード一覧（記法：命令_アドレッシングモード）
#define SEI_impl  0x78

#define LDX_imm   0xA2
#define LDX_zpg   0xA6
#define LDX_abs   0xAE

#define TXS_impl  0x9A

#define LDA_Xind  0xA1
#define LDA_zpg   0xA5
#define LDA_imm   0xA9
#define LDA_abs   0xAD
#define LDA_indY  0xB1
#define LDA_zpgX  0xB5
#define LDA_absY  0xB9
#define LDA_absX  0xBD

#define STA_Xind  0x81
#define STA_zpg   0x85
#define STA_abs   0x8D
#define STA_indY  0x91
#define STA_zpgX  0x95
#define STA_absY  0x99
#define STA_absX  0x9D

#define LDY_imm   0xA0
#define LDY_zpg   0xA4
#define LDY_absX  0xAC

#define INX_impl  0xE8

#define DEY_impl  0x88

#define BNE_rel   0xD0

#define JMP_abs   0x4C
#define JMP_ind   0x6C


typedef unsigned char u8;
//typedef signed char s8;
//typedef signed short int s16;

typedef unsigned short int u16;

	struct Register { //レジスタ（ステータスレジスタの内訳は今度やる）
		u8 A;// アキュムレータ（演算を行うとき使う？）
		u8 X;// インデックスレジスタ
		u8 Y;// インデックスレジスタ
		u8 S;// スタックポインタ
		u8 P;// ステータスレジスタ
		
		// ステータスレジスタの各フラグ
		// 7 6 5 4 3 2 1 0
		// N V 1 B D I Z C
		// N (Negative flag): 演算結果のビット7をストア．BIT命令ではメモリ値のビット7をストア
		// V (oVerflow flag): 演算によって$7F-$80をまたぐときにセット，そうでないなら0をセット
		//                    BIT命令でメモリ値のビット6をストアし，CLV命令でクリア
		// B (Break flag): BRK命令による割り込みが発生したときにセット，NMIやIRQの場合はクリア
		// D (Decimal flag): NESでは10進数演算は削除されているため基本無視．ただし，SED，CLD命令
		//                   で操作可能
		// I (Interrupt flag): 割り込みが発生するとセット．CLI命令でクリア，SEI命令でセット
		// Z (Zero flag): 演算結果が0の場合セット，それ以外の場合クリア
		// C (Carry flag): ADC命令によってビット7からの桁上げが発生した場合セット
		//                 SBC，CMP，CPX命令によってビット7からの桁上げが発生しなかった場合セット
	    //                 ASL，POL命令では，Aのビット7をストア
		//                 LSR，ROR命令ではAのビット0をストア
		//                 CLC命令でクリア，SEC命令でセット
		u16 PC;//プログラムカウンタ

//		u8 readcpu_mem(vector<char> cpu_mem, u16 addr){
//			u16 w;
//			w = cpu_mem.at(addr);
//			w = w << 4;
//			cpu_mem = w | cpu_mem.at(addr+1);
//		      return w;	
//		}

        void flag_z(u8& ans){
			if(ans == 0) P = P | 0b00000010;
			else P = P & 0b11111101;

			cout << "P flag: " << bitset<8>(P) << endl;
		}

		void regreset() {
			A = 0x00;
			X = 0x00;
			Y = 0x00;
			P = 0b00110100;
			S = 0xFD;
			PC = 0x8000;
		}
	};

	//各命令のクロックサイクル数
//	vector<char> cycles = {
//	        /*0x00*/ 7, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 4, 4, 6, 6,
//          /*0x10*/ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 6, 7,
//          /*0x20*/ 6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 4, 4, 6, 6,
//          /*0x30*/ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 6, 7,
//          /*0x40*/ 6, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 3, 4, 6, 6,
//          /*0x50*/ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 6, 7,
//          /*0x60*/ 6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 5, 4, 6, 6,
//          /*0x70*/ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 6, 7,
//          /*0x80*/ 2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
//          /*0x90*/ 2, 6, 2, 6, 4, 4, 4, 4, 2, 4, 2, 5, 5, 4, 5, 5,
//          /*0xA0*/ 2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
//          /*0xB0*/ 2, 5, 2, 5, 4, 4, 4, 4, 2, 4, 2, 4, 4, 4, 4, 4,
//          /*0xC0*/ 2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
//          /*0xD0*/ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
//          /*0xE0*/ 2, 6, 3, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
//          /*0xF0*/ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
//	};

	struct cpu {

		u16 u16_a;// 適当な変数

		// read:メモリから値を読み込み
		// 引数：読み込みたいアドレス
		// 返り値：読み込んだ値
		u8 read(u16 addr, vector<u8>& cpu_mem) { 
			return cpu_mem.at(addr);
		}
		// write:メモリに値を書き込み
		// 引数：書き込むアドレス，書き込む値
		void write(u16& addr, u8& data, vector<u8>& cpu_mem) {
			cpu_mem.at(addr) = data;			
		}
		
		// fetch:メモリから命令を読み込み
		// 
		u8 fetch(struct Register& reg, vector<u8>& cpu_mem) {
			u8 w;

			w = read(reg.PC, cpu_mem);
			if(reg.PC != 0xffff) reg.PC++;
			return w;
		}

		//アドレッシングモードに対応した処理
		// sharp: オペコードの次の番地に格納されている値を演算対象とする．
		u8 sharp(struct Register& reg, vector<u8>& cpu_mem){
			u8 u8_1;
			u8_1 = read(reg.PC, cpu_mem);
			reg.PC++;
			return u8_1;
		}

		// zpg: 0x00を上位アドレス，オペコードの次の番地に格納された値を下位アドレスとした番地を演算対象とする．
		u16 zpg(struct Register& reg, vector<u8>& cpu_mem){
			u8 u8_1;
			u16 u16_1;

			u8_1 = read(reg.PC, cpu_mem);
			reg.PC++;
			u16_1 = static_cast<u16>(u8_1);
			return u16_1;
		}

		//zpgX: 0x00を上位アドレス，オペコードの次の番地に格納された値にXレジスタを加算した値を下位アドレスとした
		//      番地を演算対象とする．
		u16 zpgX(struct Register& reg, vector<u8>& cpu_mem){
			u8 u8_1;
			u16 u16_1;

			u8_1 = read(reg.PC, cpu_mem);
			reg.PC++;
			u8_1 = u8_1 + reg.X;
			u16_1 = static_cast<u16>(u8_1);
			return u16_1;
		}
		
		//zpgY: 0x00を上位アドレス，オペコードの次の番地に格納された値にYレジスタを加算した値を下位アドレスとした
		//      番地を演算対象とする．
		u16 zpgY(struct Register& reg, vector<u8>& cpu_mem){
			u8 u8_1;
			u16 u16_1;

			u8_1 = read(reg.PC, cpu_mem);
			reg.PC++;
			u8_1 = u8_1 + reg.Y;
			u16_1 = static_cast<u16>(u16_1);
			return u16_1;
		}

		//abs: オペコードの次の番地に格納されている値を下位アドレス，その次の番地に格納されている値を上位アドレスとした
		//     値を上位アドレスとした番地を演算対象とする．
		u16 abs(struct Register& reg, vector<u8>& cpu_mem){
			u8 u8_1, u8_2;
			u16 u16_1;

			u8_1 = read(reg.PC, cpu_mem);
			reg.PC++;
			u8_2 = read(reg.PC, cpu_mem);
			reg.PC++;
			u16_1 = static_cast<u16>(u8_2);
			u16_1 = u16_1 << 8;
			u16_1 = u16_1 | static_cast<u16>(u8_1);
			return u16_1;
		}

		//absX: absによって得られた値にXレジスタの値を加算した番地を演算対象とする．
		u16 absX(struct Register& reg, vector<u8>& cpu_mem){
			u16 u16_1;

			u16_1 = abs(reg, cpu_mem);
			u16_1 = u16_1 + static_cast<u16>(reg.X);
			return u16_1;
		}

		//absY: absによって得られた値にYレジスタの値を加算した番地を演算対象とする．
		u16 absY(struct Register& reg, vector<u8>& cpu_mem){
			u16 u16_1;

			u16_1 = abs(reg, cpu_mem);
			u16_1 = u16_1 + static_cast<u16>(reg.Y);
			return u16_1;
		}

		//rel: オペコードの次の番地に格納されている値にその次の番地を加算した番地を演算対象とする．
		u16 rel(struct Register& reg, vector<u8>& cpu_mem){
			u8 u8_1;
			u16 u16_1;
		    int i;

			u8_1 = read(reg.PC, cpu_mem);
			reg.PC++;
			if((u8_1 & 0b10000000) != 0){
				u8_1 = ~u8_1 + 1;
				u16_1 = static_cast<u16>(u8_1);
				//cout << "u16_1(before): " << bitset<16>(u16_1) << endl;
				u16_1 = ~u16_1 + 1;
				//cout << "reg.PC: " << bitset<16>(reg.PC) << endl;
				//u16_1 = reg.PC;
				//cout << "u16_1: " << bitset<16>(u16_1) << endl;
				//u16_1 = static_cast<int>(reg.PC) + static_cast<int>(u16_1);
				//i = static_cast<int>(reg.PC) + static_cast<int>(u16_1);
				i = static_cast<int>(reg.PC) + static_cast<int>(u16_1);
				//cout << "i: " << bitset<17>(i) << endl;
				//if((1<<16) & i)  {
				//	i = i << 16;
				//	i = i >> 16;
				//}
				//cout << "i: " << bitset<17>(i) << endl;
				u16_1 = static_cast<u16>(i);
				//cout << "u16_1(ans): " << bitset<16>(u16_1) << endl;
			}
			else {
				u16_1 = reg.PC + static_cast<u16>(u8_1);

			}


			//cout << "u8_1: " << bitset<8>(u8_1) << endl; 
			//	cout << "u8_1: " << bitset<16>(u8_1) << endl;
			//	cout << "reg.PC: " << bitset<16>(reg.PC) << endl; 
			//	u16_1 = reg.PC + u8_1;
				//if(reg.PC > static_cast<u16>(u8_1)) u16_1 = reg.PC - static_cast<u16>(u8_1);
				//else cout << "error" << endl;   
			//cout << bitset<16>(reg.PC) << endl;
			//cout << bitset<16>(static_cast<u16>(u8_1)) << endl;
			//cout << hex << +u16_1 << endl;

			return u16_1;
		}

		//XInd: (1) 0x00を上位アドレス，オペコードの次の番地に格納されている値を下位アドレスとした番地にXレジスタの値を加算
		//      (2) (1) の値を下位アドレス，その次の番地の値を上位アドレスとした番地を演算対象とする．
		u16 XInd(struct Register& reg, vector<u8>& cpu_mem){
			u8 u8_1, u8_2, u8_3;
			u16 u16_1, u16_2;

			u8_1 = read(reg.PC, cpu_mem);
			reg.PC++;
			u8_1 = u8_1 + reg.X;
			u16_1 = static_cast<u16>(u8_1);
			u8_2 = read(u16_1, cpu_mem);
			u16_1++;
			u8_3 = read(u16_1, cpu_mem);
			u16_2 = static_cast<u16>(u8_3);
			u16_2 = u16_2 << 8;
			u16_2 = u16_2 | static_cast<u16>(u8_2);
			return u16_2;
		}

		//IndY: 0x00を上位アドレス，オペコードの次の番地に格納されている値を下位アドレスとした番地に格納されている値を下位アドレス，
		//      その次の番地の値を上位アドレスとした番地にYレジスタの値を加算した番地を演算対象とする．
		u16 IndY(struct Register& reg, vector<u8>& cpu_mem){
			u8 u8_1, u8_2, u8_3;
			u16 u16_1, u16_2;

			u8_1 = read(reg.PC, cpu_mem);
			reg.PC++;
			u16_1 = static_cast<u16>(u8_1);
			u8_2 = read(u16_1, cpu_mem);
			u16_1++;
			u8_3 = read(u16_1, cpu_mem);
			u16_2 = static_cast<u16>(u8_3);
			u16_2 = u16_2 << 8;
			u16_2 = u16_2 | static_cast<u16>(u8_2);
			u16_2 = u16_2 + static_cast<u16>(reg.Y);
			return u16_2;
		}

		//Ind: absで得られた番地に格納されている値を下位アドレス，その次に格納されている値を上位アドレスとした番地を演算対象とする．
		u16 Ind(struct Register& reg, vector<u8>& cpu_mem){
			u8 u8_1, u8_2;
			u16 u16_1, u16_2;

			u16_1 = abs(reg, cpu_mem);
			u8_1 = read(u16_1, cpu_mem);
			u16_1++;
			u8_2 = read(u16_1, cpu_mem);
			u16_2 = static_cast<u16>(u8_2);
			u16_2 = u16_2 << 8;
			u16_2 = u16_2 | u8_1;
			return u16_2;
		}

		//命令に対応した処理
		//sei: ステータスレジスタのビット2 (I) に1をセット
		void sei(struct Register& reg){
			reg.P = reg.P | 0b00000100;
		}

		//ldx: 指定したアドレスに格納されている値をXレジスタにロード
		void ldx(struct Register& reg, u16& addr, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			if(addr == 0x2007) ppu_read(cpu_mem, ppu_mem, reg.X);
			else reg.X = read(addr, cpu_mem);
		}

		//txs: Xレジスタの値をSレジスタの下位アドレスにロード
		void txs(struct Register& reg){
			reg.S = reg.X;
		}

		// lda: 指定したアドレスに格納されている値をAレジスタにロード
		void lda(struct Register& reg, u16& addr, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			if(addr == 0x2007) ppu_read(cpu_mem, ppu_mem, reg.A);
			else {
				reg.A = read(addr, cpu_mem);
				cout << setfill('0') << right << setw(2) << "reg.A = " << hex << +reg.A << endl;;
			}
		}

		// sta: 指定したアドレスにAレジスタの値を格納
		void sta(struct Register& reg, u16& addr, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			if(addr == 0x2006) ppu_addr(cpu_mem, reg, reg.A);
			else if(addr == 0x2007) ppu_write(cpu_mem, ppu_mem, reg.A);
			else write(addr, reg.A, cpu_mem);
		}

		// ldy: 指定したアドレスに格納されている値をYレジスタにロード
		void ldy(struct Register& reg, u16& addr, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			if(addr == 0x2007) ppu_read(cpu_mem, ppu_mem, reg.Y);
			else reg.Y = read(addr, cpu_mem);
		}

		// inx: Xレジスタに1を加算
		void inx(struct Register& reg){
			reg.X = reg.X + 1;
			cout << "reg.X: " << hex << +reg.X << endl;
			reg.flag_z(reg.X);
		}

		// dey: Yレジスタを1減算
		void dey(struct Register& reg){
			u16 u16_1;

			cout << "before reg.Y: " << hex << +reg.Y << endl;
			u16_1 = static_cast<u16>(reg.Y) + static_cast<u16>(0b11111111);
			reg.Y  = static_cast<u8>(u16_1);
			//if(reg.Y == 0) reg.P = reg.P | 0b00000010;
			reg.flag_z(reg.Y);
			cout << "after reg.Y: " << hex << +reg.Y << endl;
		}

		// bne: Zフラグがクリアされている場合，アドレッシングモードrelにより指定される分岐先のアドレスをPCレジスタに格納
		//      そうでない場合，次の命令のアドレスをPCレジスタに格納
		void bne(struct Register& reg, vector<u8>& cpu_mem){
			if((reg.P & 0b00000010) != 0){
				reg.PC++;
			}
			else {
				reg.PC = rel(reg, cpu_mem);
			}
		}

		// jmp: 指定したアドレスをPCレジスタに格納
		void jmp(struct Register& reg, u16& addr){
			reg.PC = addr;
		}

		void exec(struct Register& reg, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			u8 operand;
			
			operand = fetch(reg, cpu_mem);
			cout << "operand = " << hex << +operand << endl;
			
			switch(operand){
				case SEI_impl:
				sei(reg);
				break;

				case LDX_imm:
				// Load X from M M -> X
				// アドレッシングモード (imm): 次のバイトのデータをXレジスタにロード
				
				//reg.X = read(reg.PC, cpu_mem);
				ldx(reg, reg.PC, cpu_mem, ppu_mem);
				
				reg.PC++;
				break;

				case LDX_zpg:
				// Load X from M M -> X
				// アドレッシングモード (ZPG): 0x00を上位アドレス，オペコードの次の番地に格納された値を下位アドレスとした番地
				// のデータをXレジスタにロード

				u16_a = zpg(reg, cpu_mem);
				ldx(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case LDX_abs:
				// Load X from M M -> X
				// アドレッシングモード（abs）: オペコードの次のアドレスに格納された値を下位アドレス，その次のアドレスに格納された値を上位
				//                            アドレスとした番地のデータをXレジスタにロード

				u16_a = abs(reg, cpu_mem);
				ldx(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case TXS_impl:
				// Xレジスタの値をSレジスタ（スタックレジスタ）に格納
				txs(reg);
				break;

				case LDA_Xind:
				// Load A from M M -> A
				// アドレッシングモード（X, ind）:(1) 0x00を上位アドレス，オペコードの次の番地に格納された値を下位アドレスとした番地にレジスタX
				//                                  の値を加算
				//                               (2) 加算した値の番地に格納された値を下位アドレス，その次の番地に格納された値を上位アドレスとし
				//								    た番地に格納された値をAレジスタにロード

				u16_a = XInd(reg, cpu_mem);
				lda(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case LDA_zpg:
				// Load A from M M -> A
				// アドレッシングモード（zpg）: 0x00を上位アドレス，オペコードの次の番地に格納された値を下位アドレスとした番地に格納された値を
				// Aレジスタにロード

				u16_a = zpg(reg, cpu_mem);
				lda(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case LDA_imm:
				// Load A from M M -> A
				// アドレッシングモード（imm）: オペコードの次のアドレスに格納された値をAレジスタにロード
				//reg.A = read(reg.PC, cpu_mem);
				lda(reg, reg.PC, cpu_mem, ppu_mem);
				reg.PC++;
				break;

				case LDA_abs:
				// Load A from M M -> A
				// アドレッシングモード（abs）: オペコードの次のアドレスに格納された値を下位アドレス，その次に格納された値を上位アドレスとした
				// 番地の値をAレジスタにロード

				u16_a = abs(reg, cpu_mem);
				lda(reg, u16_a, cpu_mem, ppu_mem);
				break;
				
				case LDA_indY:
				// Load A from M M -> A
				// アドレッシングモード（indY）: 0x00を上位アドレス，オペコードの次の番地に格納された値を下位アドレスとした番地の値を下位アドレス
				//                              その次の番地に格納されている値を上位アドレスとした番地にYレジスタを加算した番地に格納されている
				//                              値をAレジスタにロード

				u16_a = IndY(reg, cpu_mem);
				lda(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case LDA_zpgX:
				// Load A from M M -> A
				// アドレッシングモード（zpgX）: 0x00を上位アドレス，オペコードの次の番地に格納された値にXレジスタの値を加算した値を下位アドレスとし
				// た番地に格納されている値をAレジスタにロード

				u16_a = zpgX(reg, cpu_mem);
				lda(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case LDA_absY:
				// Load A from M M -> A
				// アドレッシングモード（absY）: (1) オペコードの次の番地に格納された値を下位アドレス，その次の番地に格納された値を上位アドレスとする．
				//                              (2) (1) の番地にYレジスタの値を加算した番地に格納されている値をAレジスタにロード
				
				u16_a = absY(reg, cpu_mem);
				lda(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case LDA_absX:
				// Load A from M M -> A
				// アドレッシングモード（absX）: (1) オペコードの次の番地に格納された値を下位アドレス，その次の番地に格納された値を上位アドレスとする．
				//                              (2) (1) の番地にXレジスタの値を加算した番地に格納されている値をAレジスタにロード

				u16_a = absX(reg, cpu_mem);
				cout << "lda_absx address: " << hex << +u16_a << endl;
				lda(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case STA_Xind:
				// Store A to M A -> M
				// アドレッシングモード（Xind）: (1) 0x00を上位アドレス，オペコードの次の番地に格納されている値を下位アドレスとした番地にレジスタXの値を加算
				//                                (2) (1) の番地に格納されている値を下位アドレス，その次の番地に格納されている値を上位アドレスとした番地に
				//                                    Aレジスタの値を書き込み

				u16_a = XInd(reg, cpu_mem);
				sta(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case STA_zpg:
				// Store A to M A -> M
				// アドレッシングモード（zpg）: 0x00を上位アドレス，オペコードの次の番地に格納されている値を下位アドレスとした番地にAレジスタの値を書き込み

				u16_a = zpg(reg, cpu_mem);
				sta(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case STA_abs:
				// Store A to M A -> M
				// アドレッシングモード（abs）: オペコードの次の番地に格納された値を下位アドレス，その次の番地に格納された値を上位アドレスとした番地に
				//                             Aレジスタの値を書き込み

				u16_a = abs(reg, cpu_mem);
				sta(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case STA_indY:
				// Store A to M A -> M
				// アドレッシングモード（indY）: 0x00を上位アドレス，オペコードの次の番地に格納された値を下位アドレスとした番地の値を下位アドレス，
				// その次の番地の値を上位アドレスとした番地にYレジスタの値を加算した番地にAレジスタの値を格納


				u16_a = IndY(reg, cpu_mem);
				sta(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case STA_zpgX:

				u16_a = zpgX(reg, cpu_mem);
				sta(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case STA_absY:

				u16_a = absY(reg, cpu_mem);
				sta(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case STA_absX:

				u16_a = absX(reg, cpu_mem);
				sta(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case LDY_imm:
				
				//reg.Y = read(reg.PC, cpu_mem);
				ldy(reg, reg.PC, cpu_mem, ppu_mem);
				reg.PC++;
				break;

				case LDY_zpg:

				u16_a = zpg(reg, cpu_mem);
				ldy(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case LDY_absX:

				u16_a = absX(reg, cpu_mem);
				ldy(reg, u16_a, cpu_mem, ppu_mem);
				break;

				case INX_impl:

				inx(reg);
				break;

				case DEY_impl:

				dey(reg);
				break;

				case BNE_rel:

				bne(reg, cpu_mem);
				break;

				case JMP_abs:

				u16_a = abs(reg, cpu_mem);
				jmp(reg, u16_a);
				break;

				case JMP_ind:
				
				u16_a = Ind(reg, cpu_mem);
				jmp(reg, u16_a);
				break;

				default:
					if(operand != 0) cout << "unknown cpu_mem: " << setfill('0') << right << setw(2) << hex << +operand << " " << "reg.PC: " << reg.PC << endl;

				//
				//	cout << setfill('0') << right << setw(2) << hex << +operand << endl;
			}
		}

		void reset(struct Register& reg, vector<u8>& cpu_mem) {
			u8 u8_1, u8_2;
			reg.regreset();
			//cpu_mem.at(0x2000) = 1;
			u8_1 = read(0xFFFC, cpu_mem);
			//cout << hex << u8_1 << endl;
			u8_2 = read(0xFFFD, cpu_mem);
			//cout << hex << u8_2 << endl;
			u16_a = static_cast<u16>(u8_2);
			u16_a = u16_a << 8;
			u16_a = u16_a | u8_1;
			reg.PC = read(u16_a, cpu_mem);	
		}

		void run(struct Register& reg, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			int cnt=0;
			while(1){
				//cout << hex << +reg.PC << endl;
				if(reg.PC == 0xffff){
					exec(reg, cpu_mem, ppu_mem);
					return;
				}
			if(cnt == 200) return;

				cout << hex << reg.PC << endl;
				exec(reg, cpu_mem, ppu_mem);
				cnt++;
		}
		}
	};









