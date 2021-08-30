#include <iostream>

//オペコード一覧（記法：命令_アドレッシングモード）
#define SEI_impl  0x78

#define LDX_sharp 0xA2
#define LDX_zpg   0xA6
#define LDX_abs   0xAE

#define TXS_impl  0x9A

#define LDA_Xind  0xA1
#define LDA_zpg   0xA5
#define LDA_sharp 0xA9
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

#define LDY_sharp 0xA0
#define LDY_zpg   0xA4
#define LDY_absX  0xAC

#define INX_impl  0xE8

#define DEY_impl  0x88

#define BNE_rel   0xD0

#define JMP_abs   0x4C
#define JMP_ind   0x6C


typedef unsigned char u8;
typedef short int u16;

	struct Register { //レジスタ（ステータスレジスタの内訳は今度やる）
		u8 A;//アキュムレータ（演算を行うとき使う？）
		u8 X;//インデックスレジスタ
		u8 Y;//インデックスレジスタ
		u16 S;//スタックポインタ
		u8 P;//ステータスレジスタ
		u16 PC;//プログラムカウンタ

		u8 readword(u16 addr){
			u16 w;
			w = word.at(addr);
			w = w << 4;
			word = w | word.at(addr+1);
		      return w;	
		}

		void regreset () {
			A = 0x00;
			X = 0x00;
			Y = 0x00;
			P = 0b00110100;
			S = 0x01FD;
			PC = 0x0000;
		}
	};

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
	}

	struct Cpu {

		u8 read(u16 addr) { 
			return word.at(addr);
		}
		
		u8 fetch() {
			return read(reg.PC++);
		}

		u8 exec() {
			u8 operand;
			
			operand = fetch();
			switch(operand){
				case SEI_imple:

				case LDX_sharp:
				case LDX_zpg:
				case LDX_abs:

				case TXS_impl:

				case LDA_Xind:
				case LDA_zpg:
				case LDA_sharp:
				case LDA_abs:
				case LDA_indY:
				case LDA_zpgX:
				case LDA_absY:
				case LDA_absX:

				case STA_Xind:
				case STA_zpg:
				case STA_abs:
				case STA_indY:
				case STA_zpg:
				case STA_abs:
				case STA_indY:
				case STA_zpgX:
				case STA_absY:
				case STA_absX:

				case LDY_sharp:
				case LDY_zpg:
				case LDY_absX:

				case INX_impl:

				case DEY_impl:

				case BNE_rel:

				case JMP_abs:
				case JMP_ind:


			}
		}

		void reset() {
			reg.regreset();
			reg.PC = reg.readword(0xFFFC);
		}
	}


			
