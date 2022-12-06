#pragma once
#include <iostream>
#include <iomanip>
#include <bitset>
#include <string>
#include <vector>
#include "../ppu/ppu.hpp"

using namespace std;

//オペコード一覧（記法：命令_アドレッシングモード）
#define BRK_impl  0x00
#define ORA_Xind  0x01
#define ORA_zpg   0x05
#define ASL_zpg   0x06
#define PHP_impl  0x08
#define ORA_imm   0x09
#define ORA_abs   0x0D
#define ASL_abs   0x0E

#define BPL_rel   0x10
#define ORA_indY  0x11
#define ORA_zpgX  0x15
#define ASL_zpgX  0x16
#define CLC_impl  0x18
#define ORA_absY  0x19
#define ORA_absX  0x1D
#define ASL_absX  0x1E

#define JSR_abs   0x20
#define AND_Xind  0x21
#define BIT_zpg   0x24
#define AND_zpg   0x25
#define ROL_zpg   0x26
#define PLP_impl  0x28
#define AND_imm   0x29
#define ROL_A     0x2A
#define BIT_abs   0x2C
#define AND_abs   0x2D
#define ROL_abs   0x2E

#define BMI_rel   0x30
#define AND_indY  0x31
#define AND_zpgX  0x35
#define ROL_zpgX  0x36
#define SEC_impl  0x38
#define AND_absY  0x39
#define AND_absX  0x3D
#define ROL_absX  0x3E

#define RTI_impl  0x40
#define EOR_Xind  0x41
#define EOR_zpg   0x45
#define LSR_zpg   0x46
#define PHA_impl  0x48
#define EOR_imm   0x49
#define LSR_A     0x4A
#define JMP_abs   0x4C
#define EOR_abs   0x4D
#define LSR_abs   0x4E

#define BVC_rel   0x50
#define EOR_indY  0x51
#define EOR_zpgX  0x55
#define LSR_zpgX  0x56
#define CLI_impl  0x58
#define EOR_absY  0x59
#define EOR_absX  0x5D
#define LSR_absX  0x5E

#define RTS_impl  0x60
#define ADC_Xind  0x61
#define ADC_zpg   0x65
#define ROR_zpg   0x66
#define PLA_impl  0x68
#define ADC_imm   0x69
#define ROR_A     0x6A
#define JMP_ind   0x6C
#define ADC_abs   0x6D
#define ROR_abs   0x6E

#define BVS_rel   0x70
#define ADC_indY  0x71
#define ADC_zpgX  0x75
#define ROR_zpgX  0x76
#define SEI_impl  0x78
#define ADC_absY  0x79
#define ADC_absX  0x7D
#define ROR_absX  0x7E

#define STA_Xind  0x81
#define STY_zpg   0x84
#define STA_zpg   0x85
#define STX_zpg   0x86
#define DEY_impl  0x88
#define TXA_impl  0x8A
#define STY_abs   0x8C
#define STA_abs   0x8D
#define STX_abs   0x8E

#define BCC_rel   0x90
#define STA_indY  0x91
#define STY_zpgX  0x94
#define STA_zpgX  0x95
#define STX_zpgY  0x96
#define TYA_impl  0x98
#define STA_absY  0x99
#define TXS_impl  0x9A
#define STA_absX  0x9D

#define LDY_imm   0xA0
#define LDA_Xind  0xA1
#define LDX_imm   0xA2
#define LDY_zpg   0xA4
#define LDA_zpg   0xA5
#define LDX_zpg   0xA6
#define TAY_impl  0xA8
#define LDA_imm   0xA9
#define TAX_impl  0xAA
#define LDY_abs   0xAC
#define LDA_abs   0xAD
#define LDX_abs   0xAE

#define BCS_rel   0xB0
#define LDA_indY  0xB1
#define LDY_zpgX  0xB4
#define LDA_zpgX  0xB5
#define LDX_zpgY  0xB6
#define CLV_impl  0xB8
#define LDA_absY  0xB9
#define TSX_impl  0xBA
#define LDY_absX  0xBC
#define LDA_absX  0xBD
#define LDX_absY  0xBE

#define CPY_imm   0xC0
#define CMP_Xind  0xC1
#define CPY_zpg   0xC4
#define CMP_zpg   0xC5
#define DEC_zpg   0xC6
#define INY_impl  0xC8
#define CMP_imm   0xC9
#define DEX_impl  0xCA
#define CPY_abs   0xCC
#define CMP_abs   0xCD
#define DEC_abs   0xCE

#define BNE_rel   0xD0
#define CMP_indY  0xD1
#define CMP_zpgX  0xD5
#define DEC_zpgX  0xD6
#define CLD_impl  0xD8
#define CMP_absY  0xD9
#define CMP_absX  0xDD
#define DEC_absX  0xDE

#define CPX_imm   0xE0
#define SBC_Xind  0xE1
#define CPX_zpg   0xE4
#define SBC_zpg   0xE5
#define INC_zpg   0xE6
#define INX_impl  0xE8
#define SBC_imm   0xE9
#define NOP_impl  0xEA
#define CPX_abs   0xEC
#define SBC_abs   0xED
#define INC_abs   0xEE

#define BEQ_rel   0xF0
#define SBC_indY  0xF1
#define SBC_zpgX  0xF5
#define INC_zpgX  0xF6
#define SED_impl  0xF8
#define SBC_absY  0xF9
#define SBC_absX  0xFD
#define INC_absX  0xFE

// ステータスレジスタの各フラグ
#define NEGATIVE_FLAG  0b10000000
#define OVERFLAW_FLAG  0b01000000
#define BREAK_FLAG     0b00010000
#define DECIMAL_FLAG   0b00001000
#define INTERRUPT_FLAG 0b00000100
#define ZERO_FLAG      0b00000010
#define CARRY_FLAG     0b00000001

// ADC命令かSBC命令かのフラグ
#define ADC_FLAG 0
#define SBC_FLAG 1

typedef unsigned char u8;
//typedef signed char s8;
//typedef signed short int s16;

typedef unsigned short int u16;

	struct Register { //レジスタ（ステータスレジスタの内訳は今度やる）
		u8 A;// アキュムレータ（演算を行うとき使う？）
		u8 X;// インデックスレジスタ
		u8 Y;// インデックスレジスタ
		u8 SP;// スタックポインタ
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
	    //                 ASL，ROL命令では，Aのビット7をストア
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

		void regreset() {
			A = 0x00;
			X = 0x00;
			Y = 0x00;
			P = 0b00100100;
			SP = 0xFD;
			PC = 0x8000;
		}
	};

	struct cpu {
		//各命令のクロックサイクル数
		vector<char> cycles = {
		/*0x00*/ 7, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 4, 4, 6, 6,
        /*0x10*/ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 6, 7,
        /*0x20*/ 6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 4, 4, 6, 6,
        /*0x30*/ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 6, 7,
		/*0x40*/ 6, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 3, 4, 6, 6,
		/*0x50*/ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 6, 7,
		/*0x60*/ 6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 5, 4, 6, 6,
		/*0x70*/ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 6, 7,
		/*0x80*/ 2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
		/*0x90*/ 2, 6, 2, 6, 4, 4, 4, 4, 2, 4, 2, 5, 5, 4, 5, 5,
		/*0xA0*/ 2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
		/*0xB0*/ 2, 5, 2, 5, 4, 4, 4, 4, 2, 4, 2, 4, 4, 4, 4, 4,
		/*0xC0*/ 2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
		/*0xD0*/ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
		/*0xE0*/ 2, 6, 3, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
		/*0xF0*/ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
	};
		// read:メモリから値を読み込み
		// 引数：読み込みたいアドレス
		// 返り値：読み込んだ値
		u8 read(u16 addr, vector<u8>& cpu_mem){ 
			return cpu_mem.at(addr);
		}
		// write:メモリに値を書き込み
		// 引数：書き込むアドレス，書き込む値
		void write(u16& addr, u8& data, vector<u8>& cpu_mem){
			cpu_mem.at(addr) = data;			
		}
		
		// fetch:メモリから命令を読み込み
		// 
		u8 fetch(struct Register& reg, vector<u8>& cpu_mem){
			u8 w;
			cout <<  hex << uppercase << setw(4) << setfill('0') << +reg.PC;
			cout << " A:" << hex << uppercase << setw(2) << setfill('0') << +reg.A;
			cout << " X:" << hex << uppercase << setw(2) << setfill('0') << +reg.X;
			cout << " Y:" << hex << uppercase << setw(2) << setfill('0') << +reg.Y;
			cout << " P:" << hex << uppercase << setw(2) << setfill('0') << +reg.P;
			cout << " SP:" << hex << uppercase << setw(2) << setfill('0') << +reg.SP << endl;			
			w = read(reg.PC, cpu_mem);
			if(reg.PC != 0xffff) reg.PC++;
			return w;
		}

		// ステータスレジスタの各フラグのチェックと値の変更
		void check_zero_flag_u8(u8& ans, struct Register& reg){
			if(ans == 0) reg.P = reg.P | 0b00000010;
			else reg.P = reg.P & ~ZERO_FLAG;
		}

		void check_zero_flag_u16(u16& ans, struct Register& reg){
			if(ans == 0) reg.P = reg.P | 0b00000010;
			else reg.P = reg.P & ~ZERO_FLAG;
		}

		void check_carry_flag(u16& ans, struct Register& reg){
			if((ans >> 8) & 1){
				reg.P = reg.P | CARRY_FLAG;
				ans &= ~(1 << 8);
			}else{
				reg.P = reg.P & ~CARRY_FLAG;
			}
		}

		void check_negative_flag_u8(u8& ans, struct Register& reg){
			if((ans >> 7) & 1) reg.P |= NEGATIVE_FLAG;
			else reg.P &= ~NEGATIVE_FLAG;
		}

		void check_negative_flag_u16(u16& ans, struct Register& reg){
			if((ans >> 7) & 1) reg.P |= NEGATIVE_FLAG;
			else reg.P &= ~NEGATIVE_FLAG;
		}

		void check_overflaw_flag(int operand, u8& op1, u16& ans, struct Register& reg){
			if(operand == ADC_FLAG){
				if(((op1 >> 7) & 1) == ((reg.A << 7) & 1)){  
					if(((op1 >> 7) & 1) == 1){
						if(((ans >> 7) & 1) == 0) reg.P |= OVERFLAW_FLAG;
						else reg.P &= ~OVERFLAW_FLAG;
					} else {
						if(((ans >> 7) & 1) == 1) reg.P |= OVERFLAW_FLAG;
						else reg.P &= ~OVERFLAW_FLAG;
					}
				} else {
					reg.P &= ~OVERFLAW_FLAG;
				}
			} 
			else if(operand == SBC_FLAG){
				if(((op1 >> 7) & 1) != ((reg.A >> 7) & 1)){
					if((((op1 >> 7)) & 1) == 1){
						if(((ans >> 7) & 1) == 0) reg.P |= OVERFLAW_FLAG;
						else reg.P &= ~OVERFLAW_FLAG;
					} else {
						if(((ans >> 7) & 1) == 1) reg.P |= OVERFLAW_FLAG;
						else reg.P &= ~OVERFLAW_FLAG;
					}
				} else {
					reg.P &= ~OVERFLAW_FLAG;
				}
			} 
		}

		//スタック操作
		void stack_push(struct Register& reg, u8 addr, vector<u8>& cpu_mem){
			u16 u16_1, u16_2;

			u16_1 = 1;
			u16_1 <<= 8;
			u16_2 = static_cast<u16>(reg.SP);
			u16_1 |= u16_2;
			cpu_mem.at(u16_1) = addr;
			//cout << "u16_1: " << hex << +cpu_mem.at(u16_1) <<  endl;
			reg.SP--;
		}

		void stack_pop(struct Register& reg, u8& addr, vector<u8>& cpu_mem){
			u16 u16_1, u16_2;

			u16_1 = 1;
			u16_1 <<= 8;
			reg.SP++;
			u16_2 = static_cast<u16>(reg.SP);
			u16_1 |= u16_2;
			//cout << "u16_1: " << hex << +u16_1 << endl;
			addr = cpu_mem.at(u16_1);
			//cout << "addr: " << hex << +addr << endl;
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
			u16_1 = static_cast<u16>(u8_1);
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

		// 命令に対応した処理
		// 演算命令
		// adc: 指定したアドレスの値とAレジスタの値を足した結果をAレジスタに格納
		void adc(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1; 
			u16 u16_1;

			u8_1 = read(addr, cpu_mem);
			u16_1 = static_cast<u16>(u8_1);
			if((reg.P | CARRY_FLAG)==1) u16_1 |= (1 << 8);
			check_carry_flag(u16_1, reg);
			check_overflaw_flag(ADC_FLAG, u8_1, u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			check_negative_flag_u16(u16_1, reg);
			reg.A = static_cast<u8>(u16_1);
		}

		// sbc: 指定したアドレスの値からAレジスタの値を引いた結果をAレジスタに格納
		void sbc(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1, u8_2;
			u16 u16_1;

			u8_1 = read(addr, cpu_mem);
			u8_2 = ~reg.A;
			u16_1 = static_cast<u16>(u8_1) + static_cast<u16>(u8_2) + 1;
			check_carry_flag(u16_1, reg);
			check_overflaw_flag(SBC_FLAG, u8_1, u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			check_negative_flag_u16(u16_1, reg);
			reg.A = static_cast<u8>(u16_1);
		}

		// 論理演算
		// and: 指定したアドレスの値とAレジスタをANDした結果をAレジスタに格納
		void and_op(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1;

			u8_1 = read(addr, cpu_mem);
			reg.A &= u8_1;
			check_zero_flag_u8(reg.A, reg);
			check_negative_flag_u8(reg.A, reg);
		}

		// ora: 指定したアドレスの値とAレジスタをORした結果をAレジスタに格納
		void ora(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1;

			u8_1 = read(addr, cpu_mem);
			reg.A |= u8_1;
			check_zero_flag_u8(reg.A, reg);
			check_negative_flag_u8(reg.A, reg);
		}

		// eor: 指定したアドレスの値とAレジスタをXORした結果をAレジスタに格納
		void eor(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1;

			u8_1 = read(addr, cpu_mem);
			reg.A ^= u8_1;
			check_zero_flag_u8(reg.A, reg);
			check_negative_flag_u8(reg.A, reg);
		}

		// シフト，ローテーション
		// asl: Carry flagにAレジスタのビット7を格納
		//      Aレジスタを左に1シフト，ビット0は0
		void asl_a(struct Register& reg){
			u16 u16_1;

			u16_1 = static_cast<u16>(reg.A);
			u16_1 <<= 1;
			check_carry_flag(u16_1, reg);
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			reg.A = static_cast<u8>(u16_1);
		}

		// シフト，ローテーション
		// asl: Carry flagにAレジスタのビット7を格納
		//      指定したアドレスの値を左に1シフト，ビット0は0
		void asl(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1;
			u16 u16_1;

			u8_1 = read(addr, cpu_mem);
			u16_1 = static_cast<u16>(u8_1);
			u16_1 <<= 1;
			check_carry_flag(u16_1, reg);
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			u8_1 = static_cast<u8>(u16_1);
			write(addr, u8_1, cpu_mem);
		}

		// lsr: Carry flagにAレジスタのビット0を格納
		//      Aレジスタを右に1シフト，ビット7には0

		void lsr_a(struct Register& reg){
			u16 u16_1;

			u16_1 = static_cast<u16>(reg.A);
			u16_1 <<= 8;
			check_carry_flag(u16_1, reg);
			u16_1 >>= 9;
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			reg.A = static_cast<u8>(u16_1);
		}

		void lsr(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1;
			u16 u16_1;

			u8_1 = read(addr, cpu_mem);
			u16_1 = static_cast<u16>(u8_1);
			u16_1 <<= 8;
			check_carry_flag(u16_1, reg);
			u16_1 >>= 9;
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			write(addr, u8_1, cpu_mem);
		}
		
		// rol: Carry flagにAレジスタのビット7を格納
		//      Aレジスタを左に1シフト，その後Aレジスタのビット0にCarry flagの値を格納
		void rol_a(struct Register& reg){
			u16 u16_1;

			u16_1 = static_cast<u16>(reg.A);
			u16_1 <<= 1;
			if(reg.P & CARRY_FLAG) u16_1 |= (1 << 0);
			check_carry_flag(u16_1, reg);
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			reg.A = static_cast<u8>(u16_1);
		}

		void rol(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1;
			u16 u16_1;

			u8_1 = read(addr, cpu_mem);
			u16_1 = static_cast<u16>(u8_1);
			u16_1 <<= 1;
			if(reg.P & CARRY_FLAG) u16_1 |= (1 << 0);
			check_carry_flag(u16_1, reg);
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			u8_1 = static_cast<u8>(u16_1);
			write(addr, u8_1, cpu_mem);
		}

		// ror: Carry flagにAレジスタのビット0
		//      Aレジスタを右に1シフト，その後Aレジスタのビット7にCarry flagの値を格納
		void ror_a(struct Register& reg){
			u8 u8_1;
			u16 u16_1;


			u16_1 = static_cast<u16>(reg.A);
			u8_1 = reg.P & CARRY_FLAG;
			u16_1 <<= 8;
			check_carry_flag(u16_1, reg);
			u16_1 >>= 9;
			if(u8_1) u16_1 |= (1 << 7);
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			reg.A = static_cast<u8>(u16_1);
		}

		void ror(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1;
			u16 u16_1;

			u8_1 = read(addr, cpu_mem);
			u16_1 = static_cast<u16>(u8_1);
			u8_1 = reg.P & CARRY_FLAG;
			u16_1 <<= 8;
			check_carry_flag(u16_1, reg);
			u16_1 >>= 9;
			if(u8_1) u16_1 |= (1 << 7);
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			write(addr, u8_1, cpu_mem);
		}

		// 条件分岐: 条件が成立した場合，リラティブ・アドレス指定により，分岐先のアドレスをPCへストア
		//          成立しなかった場合，分岐命令の先頭アドレス+2をPCへストア（次の命令のアドレス）
		
		// bcc: Cフラグがクリアされていれば分岐
		void bcc(struct Register& reg, vector<u8>& cpu_mem){
			if(reg.P & CARRY_FLAG) reg.PC++;
			else reg.PC = rel(reg, cpu_mem);
		}

		// bcs: Cフラグがセットされていれば分岐
		void bcs(struct Register& reg, vector<u8>& cpu_mem){
			if(reg.P & CARRY_FLAG) reg.PC = rel(reg, cpu_mem);
			else reg.PC++;
		}

		// beq: Zフラグがセットされていれば分岐
		void beq(struct Register& reg, vector<u8>& cpu_mem){
			if(reg.P & ZERO_FLAG) reg.PC = rel(reg, cpu_mem);
			else reg.PC++;
		}

		// bne: Zフラグがクリアされている場合，アドレッシングモードrelにより指定される分岐先のアドレスをPCレジスタに格納
		//      そうでない場合，次の命令のアドレスをPCレジスタに格納
		void bne(struct Register& reg, vector<u8>& cpu_mem){
			if(reg.P & ZERO_FLAG) reg.PC++;
			else reg.PC = rel(reg, cpu_mem);
		}

		// bvc: Vフラグがクリアされていれば分岐
		void bvc(struct Register& reg, vector<u8>& cpu_mem){
			if(reg.P & OVERFLAW_FLAG) reg.PC++;
			else reg.PC = rel(reg, cpu_mem);
		}

		// bvs: Vフラグがセットされていれば分岐
		void bvs(struct Register& reg, vector<u8>& cpu_mem){
			if(reg.P & OVERFLAW_FLAG) reg.PC = rel(reg, cpu_mem);
			else reg.PC++;
		}

		//bpl: Nフラグがクリアされていれば分岐
		void bpl(struct Register& reg, vector<u8>& cpu_mem){
			if(reg.P & NEGATIVE_FLAG) reg.PC++;
			else reg.PC = rel(reg, cpu_mem);
		}

		//bmi: Nフラグがセットされていれば分岐
		void bmi(struct Register& reg, vector<u8>& cpu_mem){
			if(reg.P & NEGATIVE_FLAG) reg.PC = rel(reg, cpu_mem);
			else reg.PC++;
		}

		// ビット検査
		// bit: メモリのデータをAレジスタでテスト
	    // A and M の結果でZフラグをセットし，Mのビット7をNへ，ビット6をVフラグへ転送(TODO: ビット6をVフラグへ転送の部分)
		void bit(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1, u8_2;
			
			u8_1 = read(addr, cpu_mem);
			u8_2 = u8_1 & reg.A;
			check_zero_flag_u8(u8_2, reg);
			check_negative_flag_u8(u8_1, reg);
			if(u8_1 & 0b01000000) reg.P |= OVERFLAW_FLAG;
			else reg.P &= ~OVERFLAW_FLAG;
		}

		// ジャンプ
		// jmp: 指定したアドレスをPCレジスタに格納
		void jmp(struct Register& reg, u16& addr){
			reg.PC = addr;
		}

		// jsr: サブルーチンへジャンプ
		//      ジャンプ先のアドレスをアドレス指定によって取得した後，PCを上位バイト，下位バイトの順で
		//      スタックへプッシュ．このときのPCはjsrの最後のバイトアドレス，その後ジャンプ先へジャンプ
		void jsr(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1, u8_2;
			u16 u16_1;

			u16_1 = reg.PC - 1;
			
			u8_1 = static_cast<u8>(u16_1);
			//cout << "u8_1: " << hex << +u8_1 << endl;
			u16_1 >>= 8;
			u8_2 = static_cast<u8>(u16_1);
			//cout << "u8_2: " << hex << +u8_2 << endl;
			stack_push(reg, u8_2, cpu_mem);
			stack_push(reg, u8_1, cpu_mem);
			reg.PC = addr;
		}

		// rts: サブルーチンから復帰
		//      復帰アドレスをスタックから，下位バイト，上位バイトの順にポップしたのちインクリメント
		void rts(struct Register& reg, vector<u8>& cpu_mem){
			u8 u8_1=0, u8_2=0;

			stack_pop(reg, u8_1, cpu_mem);
			stack_pop(reg, u8_2, cpu_mem);
			//cout << "u8_1: " << hex << +u8_1 << endl;
			//cout << "u8_2: " << hex << +u8_2 << endl;
			reg.PC = static_cast<u16>(u8_2);
			reg.PC <<= 8;
			reg.PC |= static_cast<u16>(u8_1);
			reg.PC++;
		}

		// 割り込み
		// brk: ソフトウェア割り込みを発生
		void brk(struct Register& reg, vector<u8>& cpu_mem){
			u8 u8_1;

			if(!(reg.P | INTERRUPT_FLAG)){
				reg.P |= BREAK_FLAG;
				reg.PC++;
				u8_1 = static_cast<u8>(reg.PC);
				stack_push(reg, u8_1, cpu_mem);
				reg.PC >>= 8;
				u8_1 = static_cast<u8>(reg.PC);
				stack_push(reg, u8_1, cpu_mem);
				stack_push(reg, reg.P, cpu_mem);
				reg.P |= INTERRUPT_FLAG;
				u8_1 = read(0xfffe, cpu_mem);
				reg.PC = static_cast<u16>(u8_1);
				reg.PC <<= 8;
				u8_1 = read(0xffff, cpu_mem);
				reg.PC |= static_cast<u16>(u8_1);
			}
		}
		// rti: 割り込みから復帰
		//      スタックから，ステータスレジスタ，PCの下位バイト，上位バイトの順にポップ
		void rti(struct Register& reg, vector<u8>& cpu_mem){
			u8 u8_1=0;

			stack_pop(reg, reg.P, cpu_mem);
			stack_pop(reg, u8_1, cpu_mem);
			reg.PC = static_cast<u16>(u8_1);
			reg.PC <<= 8;
			stack_pop(reg, u8_1, cpu_mem);
			reg.PC |= static_cast<u16>(u8_1);
		}

		// 比較
		// cmp: Aレジスタの値と指定したアドレスの値を比較
		void cmp(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1;
			u16 u16_1;

			u8_1 = read(addr, cpu_mem);
			u8_1 = ~u8_1;
			u16_1 = static_cast<u16>(reg.A) + static_cast<u16>(u8_1) + 1;
			u8_1 = static_cast<u8>(u16_1);
			check_negative_flag_u8(u8_1, reg);
			check_zero_flag_u8(u8_1, reg);
			check_carry_flag(u16_1, reg);
		}

		// cpx: Xレジスタと指定したアドレスの値を比較
		void cpx(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1;
			u16 u16_1;

			u8_1 = read(addr, cpu_mem);
			u8_1 = ~u8_1;
			u16_1 = static_cast<u16>(reg.X) + static_cast<u16>(u8_1) + 1;
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			check_carry_flag(u16_1, reg);
		}
        
		// cpy: Yレジスタと指定したアドレスの値を比較
		void cpy(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1;
			u16 u16_1;
		
			u8_1 = read(addr, cpu_mem);
			u8_1 = ~u8_1;
			u16_1 = static_cast<u16>(reg.Y) + static_cast<u16>(u8_1) + 1;
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			check_carry_flag(u16_1, reg);
		}
		// インクリメント，デクリメント
		// inc: 指定したアドレスの値を1加算
		void inc(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1;

			u8_1 = read(addr, cpu_mem);
			u8_1++;
			write(addr, u8_1, cpu_mem);
			check_negative_flag_u8(u8_1, reg);
			check_zero_flag_u8(u8_1, reg);
		}

		// dec: 指定したアドレスの値を1減算
		void dec(struct Register& reg, u16& addr, vector<u8>& cpu_mem){
			u8 u8_1;
			u16 u16_1;

			u8_1 = read(addr, cpu_mem);
			u8_1 = ~u8_1;
			u16_1 = static_cast<u16>(u8_1) + 1 + 1;
			u8_1 = static_cast<u8>(u16_1);
			check_negative_flag_u8(u8_1, reg);
			check_zero_flag_u8(u8_1, reg);
		}

		// inx: Xレジスタに1を加算
		void inx(struct Register& reg){
			reg.X = reg.X + 1;
			//cout << "reg.X: " << hex << +reg.X << endl;
			check_negative_flag_u8(reg.X, reg);
			check_zero_flag_u8(reg.X, reg);
		}

		// dex: Xレジスタを1減算
		void dex(struct Register& reg){
			u8 u8_1;
			u16 u16_1;

			u8_1 = 0b11111110;
			u16_1 = static_cast<u16>(reg.X) + u8_1 + 1;
			u8_1 = static_cast<u8>(u16_1);
			check_negative_flag_u8(reg.X, reg);
			check_zero_flag_u8(reg.X, reg);
		}

		// iny: Yレジスタに1を加算
		void iny(struct Register& reg){
			reg.Y = reg.Y + 1;
			check_negative_flag_u8(reg.Y, reg);
			check_zero_flag_u8(reg.Y, reg);
		}

		// dey: Yレジスタを1減算
		void dey(struct Register& reg){
			u8 u8_1;
			u16 u16_1;

			u8_1 = 0b11111110;
			u16_1 = static_cast<u16>(reg.Y) + static_cast<u16>(u8_1) + 1;
			reg.Y = static_cast<u8>(u16_1);
			check_negative_flag_u8(reg.Y, reg);
			check_zero_flag_u8(reg.Y, reg);
		}

		// フラグ操作
		// clc: Carryフラグをクリア
		void clc(struct Register& reg){
			reg.P &= ~CARRY_FLAG;
		}

		// sec: Carryフラグをセット
		void sec(struct Register& reg){
			reg.P |= CARRY_FLAG;
		}

		// cli: 割り込みフラグをクリア
		void cli(struct Register& reg){
			reg.P &= ~INTERRUPT_FLAG;
		}

		//sei: ステータスレジスタのビット2 (割り込みフラグ) に1をセット
		void sei(struct Register& reg){
			reg.P = reg.P | INTERRUPT_FLAG;
		}

		// cld: Decimalフラグをクリア
		void cld(struct Register& reg){
			reg.P &= ~DECIMAL_FLAG;
		}

		// sed: Decimalフラグをセット
		void sed(struct Register& reg){
			reg.P |= DECIMAL_FLAG;
		}

		// clv: オーバフローフラグをクリア
		void clv(struct Register& reg){
			reg.P &= ~OVERFLAW_FLAG; 
		}

		// ロード
		// lda: 指定したアドレスに格納されている値をAレジスタにロード
		void lda(struct Register& reg, u16& addr, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			if(addr == 0x2007) ppu_read(cpu_mem, ppu_mem, reg.A);
			else {
				reg.A = read(addr, cpu_mem);
			}
			check_negative_flag_u8(reg.A, reg);
			check_zero_flag_u8(reg.A, reg);
		}

		//ldx: 指定したアドレスに格納されている値をXレジスタにロード
		void ldx(struct Register& reg, u16& addr, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			if(addr == 0x2007) ppu_read(cpu_mem, ppu_mem, reg.X);
			else reg.X = read(addr, cpu_mem);
			check_negative_flag_u8(reg.X, reg);
			check_zero_flag_u8(reg.X, reg);
		}

		// ldy: 指定したアドレスに格納されている値をYレジスタにロード
		void ldy(struct Register& reg, u16& addr, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			if(addr == 0x2007) ppu_read(cpu_mem, ppu_mem, reg.Y);
			else reg.Y = read(addr, cpu_mem);
		    check_negative_flag_u8(reg.Y, reg);
			check_zero_flag_u8(reg.Y, reg);
		} 

		// ストア
	    // sta: 指定したアドレスにAレジスタの値を格納
		void sta(struct Register& reg, u16& addr, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			if(addr == 0x2006) ppu_addr(cpu_mem, reg, reg.A);
			else if(addr == 0x2007) ppu_write(cpu_mem, ppu_mem, reg.A);
			else write(addr, reg.A, cpu_mem);
		}

		//stx: 指定したアドレスにXレジスタの値を格納
		void stx(struct Register& reg, u16& addr, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			if(addr == 0x2006) ppu_addr(cpu_mem, reg, reg.X);
			else if(addr == 0x2007) ppu_write(cpu_mem, ppu_mem, reg.X);
			else write(addr, reg.X, cpu_mem);
		}

		//sty: 指定したアドレスにYレジスタの値を格納
		void sty(struct Register& reg, u16& addr, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			if(addr == 0x2006) ppu_addr(cpu_mem, reg, reg.Y);
			else if(addr == 0x2007) ppu_write(cpu_mem, ppu_mem, reg.Y);
			else write(addr, reg.Y, cpu_mem);
		}

		// レジスタ間転送
		// tax: Aレジスタの値をXレジスタに転送
		void tax(struct Register& reg){
			reg.X = reg.A;
			check_negative_flag_u8(reg.X, reg);
			check_zero_flag_u8(reg.X, reg);
		}

		// txa: Xレジスタの値をAレジスタに転送
		void txa(struct Register& reg){
			reg.A = reg.X;
			check_negative_flag_u8(reg.A, reg);
			check_zero_flag_u8(reg.A, reg);
		}

		// tay: Aレジスタの値をYレジスタに転送
		void tay(struct Register& reg){
			reg.Y = reg.A;
			check_negative_flag_u8(reg.Y, reg);
			check_zero_flag_u8(reg.Y, reg);
		}

		// tya: Yレジスタの値をAレジスタに転送
		void tya(struct Register& reg){
			reg.A = reg.Y;
			check_negative_flag_u8(reg.A, reg);
			check_zero_flag_u8(reg.A, reg);
		}

		// tsx: SPレジスタの値をXレジスタに転送
		void tsx(struct Register& reg){
			reg.X = reg.SP;
			check_negative_flag_u8(reg.X, reg);
			check_zero_flag_u8(reg.X, reg);
		}

		//txs: Xレジスタの値をSPレジスタの下位アドレスにロード
		void txs(struct Register& reg){
			reg.SP = reg.X;
		}


		// スタック
		// pha: Aレジスタの値をスタックへプッシュ
		void pha(struct Register& reg, vector<u8>& cpu_mem){
			stack_push(reg, reg.A, cpu_mem);
		}

		// pla: スタックの値をAレジスタに格納
		void pla(struct Register& reg, vector<u8>& cpu_mem){
			stack_pop(reg, reg.A, cpu_mem);
			reg.A |= BREAK_FLAG;
			check_negative_flag_u8(reg.A, reg);
			check_zero_flag_u8(reg.A, reg);
		}

		// php: ステータスレジスタの値をスタックへプッシュ
		void php(struct Register& reg, vector<u8>& cpu_mem){
			stack_push(reg, reg.P, cpu_mem);
		}

		// plp: スタックの値をステータスレジスタに格納
		void plp(struct Register& reg, vector<u8>& cpu_mem){
			stack_pop(reg, reg.P, cpu_mem);
			reg.P &= ~BREAK_FLAG;
		}


		char exec(struct Register& reg, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			u8 operand;
			u16 u16_1;
			operand = fetch(reg, cpu_mem);
			//cout << "operand = " << hex << +operand << endl;
			
			switch(operand){
				case BRK_impl:
					break;

				case ORA_Xind:
					u16_1 = XInd(reg, cpu_mem);
					ora(reg, u16_1, cpu_mem);
					break;

				case ORA_zpg:
					u16_1 = zpg(reg, cpu_mem);
					ora(reg, u16_1, cpu_mem);
					break;
				
				case ASL_zpg:
					u16_1 = zpg(reg, cpu_mem);
					asl(reg, u16_1, cpu_mem);
					break;
				
				case PHP_impl:
					php(reg, cpu_mem);
					break;

				case ORA_imm:
					u16_1 = reg.PC;
					ora(reg, u16_1, cpu_mem);
					reg.PC++;
					break;

				case ORA_abs:
					u16_1 = abs(reg, cpu_mem);
					ora(reg, u16_1, cpu_mem);
					break;

				case ASL_abs:
					u16_1 = abs(reg, cpu_mem);
					asl(reg, u16_1, cpu_mem);
					break;

				case BPL_rel:
 					bpl(reg, cpu_mem);
					break;

				case ORA_indY:
					u16_1 = IndY(reg, cpu_mem);
					ora(reg, u16_1, cpu_mem);
					break;

				case ORA_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					ora(reg, u16_1, cpu_mem);
					break;

				case ASL_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					asl(reg, u16_1, cpu_mem);
					break;

				case CLC_impl:
					clc(reg);
					break;

				case ORA_absY:
					u16_1 = absY(reg, cpu_mem);
					ora(reg, u16_1, cpu_mem);
					break;

				case ORA_absX:
					u16_1 = absX(reg, cpu_mem);
					ora(reg, u16_1, cpu_mem);
					break;

				case ASL_absX:
					u16_1 = absX(reg, cpu_mem);
					asl(reg, u16_1, cpu_mem);
					break;

				case JSR_abs:
					u16_1 = abs(reg, cpu_mem);
					jsr(reg, u16_1, cpu_mem);
					break;

				case AND_Xind:
					u16_1 = XInd(reg, cpu_mem);
					and_op(reg, u16_1, cpu_mem);
					break;

				case BIT_zpg:
					u16_1 = zpg(reg, cpu_mem);
					bit(reg, u16_1, cpu_mem);
					break;

				case AND_zpg:
					u16_1 = zpg(reg, cpu_mem);
					and_op(reg, u16_1, cpu_mem);
					break;

				case ROL_zpg:
					u16_1 = zpg(reg, cpu_mem);
					rol(reg, u16_1, cpu_mem);
					break;

				case PLP_impl:
					plp(reg, cpu_mem);
					break;

				case AND_imm:
					and_op(reg, reg.PC, cpu_mem);
					reg.PC++;
					break;

				case ROL_A:
					rol_a(reg);
					break;

				case BIT_abs:
					u16_1 = abs(reg, cpu_mem);
					bit(reg, u16_1, cpu_mem);
					break;

				case AND_abs:
					u16_1 = abs(reg, cpu_mem);
					and_op(reg, u16_1, cpu_mem);
					break;

				case ROL_abs:
					u16_1 = abs(reg, cpu_mem);
					rol(reg, u16_1, cpu_mem);
					break;

				case BMI_rel:
					bmi(reg, cpu_mem);
					break;

				case AND_indY:
					u16_1 = IndY(reg, cpu_mem);
					and_op(reg, u16_1, cpu_mem);
					break;

				case AND_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					and_op(reg, u16_1, cpu_mem);
					break;

				case ROL_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					rol(reg, u16_1, cpu_mem);
					break;

				case SEC_impl:
					sec(reg);
					break;

				case AND_absY:
					u16_1 = absY(reg, cpu_mem);
					and_op(reg, u16_1, cpu_mem);
					break;

				case AND_absX:
					u16_1 = absX(reg, cpu_mem);
					and_op(reg, u16_1, cpu_mem);
					break;

				case ROL_absX:
					u16_1 = absX(reg, cpu_mem);
					rol(reg, u16_1, cpu_mem);
					break;

				case RTI_impl:
					rti(reg, cpu_mem);
					break;

				case EOR_Xind:
					u16_1 = XInd(reg, cpu_mem);
					eor(reg, u16_1, cpu_mem);
					break;

				case EOR_zpg:
					u16_1 = zpg(reg, cpu_mem);
					eor(reg, u16_1, cpu_mem);
					break;

				case LSR_zpg:
					u16_1 = zpg(reg, cpu_mem);
					lsr(reg, u16_1, cpu_mem);
					break;

				case PHA_impl:
					pha(reg, cpu_mem);
					break;

				case EOR_imm:
					eor(reg, reg.PC, cpu_mem);
					reg.PC++;
					break;

				case LSR_A:
					lsr_a(reg);
					break;
				case JMP_abs:
					u16_1 = abs(reg, cpu_mem);
					jmp(reg, u16_1);
					break;

				case EOR_abs:
					u16_1 = abs(reg, cpu_mem);
					eor(reg, u16_1, cpu_mem);
					break;

				case LSR_abs:
					u16_1 = abs(reg, cpu_mem);
					lsr(reg, u16_1, cpu_mem);
					break;

				case BVC_rel:
					bvc(reg, cpu_mem);
					break;

				case EOR_indY:
					u16_1 = IndY(reg, cpu_mem);
					eor(reg, u16_1, cpu_mem);
					break;

				case EOR_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					eor(reg, u16_1, cpu_mem);
					break;

				case LSR_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					lsr(reg, u16_1, cpu_mem);
					break;

				case CLI_impl:
					cli(reg);
					break;

				case EOR_absY:
					u16_1 = absY(reg, cpu_mem);
					eor(reg, u16_1, cpu_mem);
					break;

				case EOR_absX:
					u16_1 = absX(reg, cpu_mem);
					eor(reg, u16_1, cpu_mem);
					break;

				case LSR_absX:
					u16_1 = absX(reg, cpu_mem);
					lsr(reg, u16_1, cpu_mem);
					break;

				case RTS_impl:
					rts(reg, cpu_mem);
					break;

				case ADC_Xind:
					u16_1 = XInd(reg, cpu_mem);
					adc(reg, u16_1, cpu_mem);
					break;

				case ADC_zpg:
					u16_1 = zpg(reg, cpu_mem);
					adc(reg, u16_1, cpu_mem);
					break;

				case ROR_zpg:
					u16_1 = zpg(reg, cpu_mem);
					ror(reg, u16_1, cpu_mem);
					break;

				case PLA_impl:
					pla(reg, cpu_mem);
					break;

				case ADC_imm:
					adc(reg, reg.PC, cpu_mem);
					reg.PC++;
					break;

				case ROR_A:
					ror_a(reg);
					break;

				case JMP_ind:
					u16_1 = Ind(reg, cpu_mem);
					jmp(reg, u16_1);
					break;

				case ADC_abs:
					u16_1 = abs(reg, cpu_mem);
					adc(reg, u16_1, cpu_mem);
					break;

				case ROR_abs:
					u16_1 = abs(reg, cpu_mem);
					ror(reg, u16_1, cpu_mem);
					break;

				case BVS_rel:
					bvs(reg, cpu_mem);
					break;

				case ADC_indY:
					u16_1 = IndY(reg, cpu_mem);
					adc(reg, u16_1, cpu_mem);
					break;

				case ADC_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					adc(reg, u16_1, cpu_mem);
					break;

				case ROR_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					ror(reg, u16_1, cpu_mem);
					break;

				case SEI_impl://0x78
					sei(reg);
					break;

				case ADC_absY:
					u16_1 = absY(reg, cpu_mem);
					adc(reg, u16_1, cpu_mem);
					break;

				case ADC_absX:
					u16_1 = absX(reg, cpu_mem);
					adc(reg, u16_1, cpu_mem);
					break;

				case ROR_absX:
					u16_1 = absX(reg, cpu_mem);
					ror(reg, u16_1, cpu_mem);
					break;

				// Store A to M A -> M
				// アドレッシングモード（Xind）: (1) 0x00を上位アドレス，オペコードの次の番地に格納されている値を下位アドレスとした番地にレジスタXの値を加算
				//                                (2) (1) の番地に格納されている値を下位アドレス，その次の番地に格納されている値を上位アドレスとした番地に
				//                                    Aレジスタの値を書き込み
				case STA_Xind://0x81
					u16_1 = XInd(reg, cpu_mem);
					sta(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case STY_zpg:
					u16_1 = zpg(reg, cpu_mem);
					sty(reg, u16_1, cpu_mem, ppu_mem);
					break;

				// Store A to M A -> M
				// アドレッシングモード（zpg）: 0x00を上位アドレス，オペコードの次の番地に格納されている値を下位アドレスとした番地にAレジスタの値を書き込み
				case STA_zpg://0x85
					u16_1 = zpg(reg, cpu_mem);
					sta(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case STX_zpg:
					u16_1 = zpg(reg, cpu_mem);
					stx(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case DEY_impl:
					dey(reg);
					//cout << "reg.Y: " << std::dec << +reg.Y << endl;
					break;
				case TXA_impl:
					txa(reg);
					break;

				case STY_abs:
					u16_1 = abs(reg, cpu_mem);
					sty(reg, u16_1, cpu_mem, ppu_mem);
					break;

				// Store A to M A -> M
				// アドレッシングモード（abs）: オペコードの次の番地に格納された値を下位アドレス，その次の番地に格納された値を上位アドレスとした番地に
				//                             Aレジスタの値を書き込み
				case STA_abs:
					u16_1 = abs(reg, cpu_mem);
					sta(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case STX_abs:
					u16_1 = abs(reg, cpu_mem);
					stx(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case BCC_rel:
					bcc(reg, cpu_mem);
					break;

				// Store A to M A -> M
				// アドレッシングモード（indY）: 0x00を上位アドレス，オペコードの次の番地に格納された値を下位アドレスとした番地の値を下位アドレス，
				// その次の番地の値を上位アドレスとした番地にYレジスタの値を加算した番地にAレジスタの値を格納
				case STA_indY:
					u16_1 = IndY(reg, cpu_mem);
					sta(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case STY_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					sty(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case STA_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					sta(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case STX_zpgY:
				 	u16_1 = zpgY(reg, cpu_mem);
					stx(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case TYA_impl:
					tya(reg);
					break;

				case STA_absY:
					u16_1 = absY(reg, cpu_mem);
					sta(reg, u16_1, cpu_mem, ppu_mem);
					break;
				
				// Xレジスタの値をSレジスタ（スタックレジスタ）に格納
				case TXS_impl://0x9A
					txs(reg);
					break;

				case STA_absX:
					u16_1 = absX(reg, cpu_mem);
					sta(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case LDY_imm:
					//reg.Y = read(reg.PC, cpu_mem);
					ldy(reg, reg.PC, cpu_mem, ppu_mem);
					reg.PC++;
					break;

				// Load A from M M -> A
				// アドレッシングモード（X, ind）:(1) 0x00を上位アドレス，オペコードの次の番地に格納された値を下位アドレスとした番地にレジスタX
				//                                  の値を加算
				//                               (2) 加算した値の番地に格納された値を下位アドレス，その次の番地に格納された値を上位アドレスとし
				//								    た番地に格納された値をAレジスタにロード
				case LDA_Xind://0xA1
					u16_1 = XInd(reg, cpu_mem);
					lda(reg, u16_1, cpu_mem, ppu_mem);
					break;

				// Load X from M M -> X
				// アドレッシングモード (imm): 次のバイトのデータをXレジスタにロード
				case LDX_imm://0xA6
					//reg.X = read(reg.PC, cpu_mem);
					ldx(reg, reg.PC, cpu_mem, ppu_mem);
					reg.PC++;
					break;

				case LDY_zpg:
					u16_1 = zpg(reg, cpu_mem);
					ldy(reg, u16_1, cpu_mem, ppu_mem);
					break;


				// Load A from M M -> A
				// アドレッシングモード（zpg）: 0x00を上位アドレス，オペコードの次の番地に格納された値を下位アドレスとした番地に格納された値を
				// Aレジスタにロード
				case LDA_zpg://0xA5
					u16_1 = zpg(reg, cpu_mem);
					lda(reg, u16_1, cpu_mem, ppu_mem);
					break;

				// Load X from M M -> X
				// アドレッシングモード (ZPG): 0x00を上位アドレス，オペコードの次の番地に格納された値を下位アドレスとした番地
				// のデータをXレジスタにロード
				case LDX_zpg://0xA2
					u16_1 = zpg(reg, cpu_mem);
					ldx(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case TAY_impl:
					tay(reg);
					break;

				// Load A from M M -> A
				// アドレッシングモード（imm）: オペコードの次のアドレスに格納された値をAレジスタにロード
				//reg.A = read(reg.PC, cpu_mem);
				case LDA_imm://0xA9
					lda(reg, reg.PC, cpu_mem, ppu_mem);
					reg.PC++;
					break;

				case TAX_impl:
					tax(reg);
					break;

				case LDY_abs:
					u16_1 = abs(reg, cpu_mem);
					ldy(reg, u16_1, cpu_mem, ppu_mem);
					break;

				// Load A from M M -> A
				// アドレッシングモード（abs）: オペコードの次のアドレスに格納された値を下位アドレス，その次に格納された値を上位アドレスとした
				// 番地の値をAレジスタにロード
				case LDA_abs://0xAD
					u16_1 = abs(reg, cpu_mem);
					lda(reg, u16_1, cpu_mem, ppu_mem);
					break;

				// Load X from M M -> X
				// アドレッシングモード（abs）: オペコードの次のアドレスに格納された値を下位アドレス，その次のアドレスに格納された値を上位
				//                            アドレスとした番地のデータをXレジスタにロード
				case LDX_abs://0xAE
					u16_1 = abs(reg, cpu_mem);
					ldx(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case BCS_rel:
					bcs(reg, cpu_mem);
					break;

				// Load A from M M -> A
				// アドレッシングモード（indY）: 0x00を上位アドレス，オペコードの次の番地に格納された値を下位アドレスとした番地の値を下位アドレス
				//                              その次の番地に格納されている値を上位アドレスとした番地にYレジスタを加算した番地に格納されている
				//                              値をAレジスタにロード
				case LDA_indY://0xB1
					u16_1 = IndY(reg, cpu_mem);
					lda(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case LDY_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					ldy(reg, u16_1, cpu_mem, ppu_mem);
					break;

				// Load A from M M -> A
				// アドレッシングモード（zpgX）: 0x00を上位アドレス，オペコードの次の番地に格納された値にXレジスタの値を加算した値を下位アドレスとし
				// た番地に格納されている値をAレジスタにロード
				case LDA_zpgX://0xB5
					u16_1 = zpgX(reg, cpu_mem);
					lda(reg, u16_1, cpu_mem, ppu_mem);
					break; 

				case LDX_zpgY:
					u16_1 = zpgY(reg, cpu_mem);
					ldx(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case CLV_impl:
					clv(reg);
					break;

				// Load A from M M -> A
				// アドレッシングモード（absY）: (1) オペコードの次の番地に格納された値を下位アドレス，その次の番地に格納された値を上位アドレスとする．
				//                              (2) (1) の番地にYレジスタの値を加算した番地に格納されている値をAレジスタにロード
				case LDA_absY://0xB9
					u16_1 = absY(reg, cpu_mem);
					lda(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case TSX_impl:
					tsx(reg);
					break;

				case LDY_absX:
					u16_1 = absX(reg, cpu_mem);
					ldy(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case LDA_absX://0xBD
					u16_1 = absX(reg, cpu_mem);
					// cout << "lda_absx address: " << hex << +u16_a << endl;
					lda(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case LDX_absY:
					u16_1 = absY(reg, cpu_mem);
					ldx(reg, u16_1, cpu_mem, ppu_mem);
					break;

				case CPY_imm:
					cpy(reg, reg.PC, cpu_mem);
					reg.PC++;
					break;

				case CMP_Xind:
					u16_1 = XInd(reg, cpu_mem);
					cmp(reg, u16_1, cpu_mem);
					break;

				case CPY_zpg:
					u16_1 = zpg(reg, cpu_mem);
					cpy(reg, u16_1, cpu_mem);
					break;

				case CMP_zpg:
					u16_1 = zpg(reg, cpu_mem);
					cmp(reg, u16_1, cpu_mem);
					break;

				case DEC_zpg:
					u16_1 = zpg(reg, cpu_mem);
					dec(reg, u16_1, cpu_mem);
					break;

				case INY_impl:
					iny(reg);
					break;

				case CMP_imm:
					cmp(reg, reg.PC, cpu_mem);
					reg.PC++;
					break;

				case DEX_impl:
					dex(reg);
					break;

				case CPY_abs:
					u16_1 = abs(reg, cpu_mem);
					cpy(reg, u16_1, cpu_mem);
					break;

				case CMP_abs:
					u16_1 = abs(reg, cpu_mem);
					cmp(reg, u16_1, cpu_mem);
					break;

				case DEC_abs:
					u16_1 = abs(reg, cpu_mem);
					dec(reg, u16_1, cpu_mem);
					break;

				case BNE_rel:
					bne(reg, cpu_mem);
					break;

				case CMP_indY:
					u16_1 = IndY(reg, cpu_mem);
					cmp(reg, u16_1, cpu_mem);
					break;

				case CMP_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					cmp(reg, u16_1, cpu_mem);
					break;

				case DEC_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					dec(reg, u16_1, cpu_mem);
					break;

				case CLD_impl:
					cld(reg);
					break;

				case CMP_absY:
					u16_1 = absY(reg, cpu_mem);
					cmp(reg, u16_1, cpu_mem);
					break;

				case CMP_absX:
					u16_1 = absX(reg, cpu_mem);
					cmp(reg, u16_1, cpu_mem);
					break;

				case DEC_absX:
					u16_1 = absX(reg, cpu_mem);
					dec(reg, u16_1, cpu_mem);
					break;

				case CPX_imm:
					cpx(reg, reg.PC, cpu_mem);
					reg.PC++;
					break;

				case SBC_Xind:
					u16_1 = XInd(reg, cpu_mem);
					sbc(reg, u16_1, cpu_mem);
					break;

				case CPX_zpg:
					u16_1 = zpg(reg, cpu_mem);
					cpx(reg, u16_1, cpu_mem);
					break;
				case SBC_zpg:
					u16_1 = zpg(reg, cpu_mem);
					sbc(reg, u16_1, cpu_mem);
					break;

				case INC_zpg:
					u16_1 = zpg(reg, cpu_mem);

					break;
				case INX_impl:
					inx(reg);
					break;

				case SBC_imm:
					sbc(reg, reg.PC, cpu_mem);
					reg.PC++;
					break;

				case NOP_impl:
					break;

				case CPX_abs:
					u16_1 = abs(reg, cpu_mem);
					cpx(reg, u16_1, cpu_mem);
					break;

				case SBC_abs:
					u16_1 = abs(reg, cpu_mem);
					sbc(reg, u16_1, cpu_mem);
					break;

				case INC_abs:
					u16_1 = abs(reg, cpu_mem);
					inc(reg, u16_1, cpu_mem);
					break;

				case BEQ_rel:
					beq(reg, cpu_mem);
					break;

				case SBC_indY:
					u16_1 = IndY(reg, cpu_mem);
					sbc(reg, u16_1, cpu_mem);
					break;

				case SBC_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					sbc(reg, u16_1, cpu_mem);
					break;

				case INC_zpgX:
					u16_1 = zpgX(reg, cpu_mem);
					inc(reg, u16_1, cpu_mem);
					break;

				case SED_impl:
					sed(reg);
					break;

				case SBC_absY:
					u16_1 = absY(reg, cpu_mem);
					sbc(reg, u16_1, cpu_mem);
					break;

				case SBC_absX:
					u16_1 = absX(reg, cpu_mem);
					sbc(reg, u16_1, cpu_mem);
					break;

				case INC_absX:
					u16_1 = absX(reg, cpu_mem);
					inc(reg, u16_1, cpu_mem);
					break;

				default:
					cout << "unknown cpu_mem: " << setfill('0') << right << setw(2) << hex << +operand << " " << "reg.PC: " << reg.PC << endl;
				//
				//	cout << setfill('0') << right << setw(2) << hex << +operand << endl;
			}
			return cycles[operand];
		}

		void reset(struct Register& reg, vector<u8>& cpu_mem) {
			u8 u8_1, u8_2;
			u16 u16_1;
			
			reg.regreset();
			//cpu_mem.at(0x2000) = 1;
			u8_1 = read(0xFFFC, cpu_mem);
			//cout << hex << u8_1 << endl;
			u8_2 = read(0xFFFD, cpu_mem);
			//cout << hex << u8_2 << endl;
			u16_1 = static_cast<u16>(u8_2);
			u16_1 = u16_1 << 8;
			u16_1 = u16_1 | u8_1;
			reg.PC = read(u16_1, cpu_mem);	
		}

		void run(struct Register& reg, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			int cpu_cycle=0;

			while(1){
				if(reg.PC == 0xffff){
					cpu_cycle += exec(reg, cpu_mem, ppu_mem);
					cout << "0xC002: " << hex << +cpu_mem[0xC002] << endl;
					cout << "0xC003: " << hex << +cpu_mem[0xC003] << endl;
					return;
				}
				cpu_cycle += exec(reg, cpu_mem, ppu_mem);
				if(cpu_cycle > 114) return; 
			}	
		}
	};









