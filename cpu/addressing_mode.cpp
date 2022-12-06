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
