// 命令に対応した処理
		// 演算命令
		// adc: 指定したアドレスの値とAレジスタの値を足した結果をAレジスタに格納
		void adc(struct Register& reg, u16& addr){
			u8 u8_1; 
			u16 u16_1;

			u8_1 = read(addr, cpu_mem);
			u16_1 = static_cast<u16>(u8_1);
			if((reg.P | CARRY_FLAG)==1) u16_1 |= (1 << 8);
			check_carry_flag(u16_1, reg);
			check_overflaw_flag(ADC_FLAG, u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			check_negative_flag_u16(u16_1, reg);
			reg.A = static_cast<u8>(u16_1);
		}

		// sbc: 指定したアドレスの値からAレジスタの値を引いた結果をAレジスタに格納
		void sbc(struct Register& reg, u16& addr){
			u8 u8_1, u8_2;
			u16 u16_1;

			u8_1 = read(addr, cpu_mem);
			u8_2 = ~reg.A;
			u16_1 = static_cast<u16_1>(u8_1) + static_cast<u16_1>(reg.A) + 1;
			check_carry_flag(u16_1, reg);
			check_overflaw_flag(SBC_FLAG, u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			check_negative_flag_u16(u16_1, reg);
			reg.A = static_cast<u8>(u16_1);
		}

		// 論理演算
		// and: 指定したアドレスの値とAレジスタをANDした結果をAレジスタに格納
		void and(struct Register& reg, u16& addr){
			u8 u8_1;

			u8_1 = read(addr, cpu_mem);
			reg.A &= u8_1;
			check_zero_flag_u8(reg.A, reg);
			check_negative_flag_u8(reg.A, reg);
		}

		// ora: 指定したアドレスの値とAレジスタをORした結果をAレジスタに格納
		void ora(struct Register& reg, u16& addr){
			u8 u8_1;

			u8_1 = read(addr, cpu_mem);
			reg.A |= u8_1;
			check_zero_flag_u8(reg.A, reg);
			check_negative_flag_u8(reg.A, reg);
		}

		// eor: 指定したアドレスの値とAレジスタをXORした結果をAレジスタに格納
		void eor(strucrt Register& reg, u16& addr){
			u8 u8_1;

			u8_1 = read(addr, cpu_mem);
			reg.A ^= u8_1;
			check_zero_flag_u8(reg.A, reg);
			check_negative_flag_u8(reg.A, reg);
		}

		// シフト，ローテーション
		// asl: Carry flagにAレジスタのビット7を格納
		//      Aレジスタを左に1シフト，ビット0は0
		void asl(struct Register& reg){
			u16 u16_1;

			u16_1 = static_cast<u16>(reg.A);
			u16_1 <<= 1;
			check_carry_flag(u16_1, reg);
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			reg.A = static_cast<u8>(u16_1);
		}

		// lsr: Carry flagにAレジスタのビット0を格納
		//      Aレジスタを右に1シフト，ビット7には0

		void lsr(struct Register& reg){
			u16 u16_1;

			u16_1 = static_cast<u16>(reg.A);
			u16_1 <<= 8;
			check_carry_flag(u16_1, reg);
			u16_1 >>= 9;
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			reg.A = static_cast<u8>(u16_1);
		}

		// rol: Carry flagにAレジスタのビット7を格納
		//      Aレジスタを左に1シフト，その後Aレジスタのビット0にCarry flagの値を格納
		void rol(struct Register& reg){
			u16 u16_1;
			u16_1 = static_cast<u16>(reg.A);
			u16_1 <<= 1;
			if(reg.P & CARRY_FLAG) u16_1 |= (1 << 0);
			check_carry_flag(u16_1, reg);
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			reg.A = static_cast<u8>(u16_1);
		}

		// ror: Carry flagにAレジスタのビット0
		//      Aレジスタを右に1シフト，その後Aレジスタのビット7にCarry flagの値を格納
		void ror(strucrt Register& reg){
			u16 u16_1;
			u8 u8_1;

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
	    // A and M の結果でZフラグをセットし，Mのビット7をNへ，ビット6をVフラグへ転送
		void bit(struct Register& reg, u16& addr){
			u8 u8_1, u8_2;
			
			u8_1 = read(addr, cpu_mem);
			u8_2 = u8_1 & reg.A;
			check_zero_flag_u8(u8_2, reg);
			check_negative_flag_u8(u8_1, reg);
			check_overflaw_flag(u8_1, reg);
		}

		// ジャンプ
		// jmp: 指定したアドレスをPCレジスタに格納
		void jmp(struct Register& reg, u16& addr){
			reg.PC = addr;
		}

		// jsr: サブルーチンへジャンプ
		//      ジャンプ先のアドレスをアドレス指定によって取得した後，PCを上位バイト，下位バイトの順で
		//      スタックへプッシュ．このときのPCはjsrの最後のバイトアドレス，その後ジャンプ先へジャンプ
		void jsr(struct Register& reg, u16& addr){
			u8 u8_1, u8_2;
			u16 u16_1;

			u16_1 = reg.PC  - 1;
			u8_1 = static_cast<u8>(u16_1);
			u16_1 >>= 8;
			u8_2 = static_cast<u8>(u16_1);
			stack_push(reg, u8_2, cpu_mem);
			stack_push(reg, u8_1, cpu_mem);
			reg.PC = addr;
		}
		
		// 割り込み
		// brk: ソフトウェア割り込みを発生

		// rti: 割り込みから復帰
		//      スタックから，ステータスレジスタ，PCの下位バイト，上位バイトの順にポップ


		// 比較
		// cmp: Aレジスタの値と指定したアドレスの値を比較
		void cmp(struct Register& reg, u16& addr){
			u8 u8_1;
			u16 u16_1;

			u8_1 = read(addr, cpu_mem);
			u8_1 = ~u8_1;  
			u16_1 = static_cast<u16>(reg.A) + static_cast<u16>(u8_1) + 1;
			check_negative_flag_u16(u16_1, reg);
			check_zero_flag_u16(u16_1, reg);
			check_carry_flag(u16_1, reg);
		}

		// cpx: Xレジスタと指定したアドレスの値を比較
		void cpx(struct Register& reg, u16& addr){
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
		void cpy(struct Register& reg, u16& addr){
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
		void inc(struct Register& reg, u16& addr){
			u8 u8_1;

			u8_1 = read(addr, cpu_mem);
			u8_1++;
			write(addr, u8_1, cpu_mem);
			check_negative_flag_u8(u8_1, reg);
			check_zero_flag_u8(u8_1, reg);
		}

		// dec: 指定したアドレスの値を1減算
		void dec(struct Register& reg, u16& addr){
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
			u16_1 = static_cast<u16>(reg.Y) + u8_1 + 1;
			u8_1 = static_cast<u8>(u16_1);
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
		void cld(strucrt Register& reg){
			reg.P &= ~DECIMAL_FLAG;
		}

		// sed: Decimalフラグをセット
		void sed(struct Register& reg){
			reg.P |= DECIMAL_FLAG;
		}

		// clv: オーバフローフラグをクリア
		void clv(strucrt Register& reg){
			reg.P &= ~OVERFLAW_FLAG; 
		}

		// ロード
		// lda: 指定したアドレスに格納されている値をAレジスタにロード
		void lda(struct Register& reg, u16& addr, vector<u8>& cpu_mem, vector<u8>& ppu_mem){
			if(addr == 0x2007) ppu_read(cpu_mem, ppu_mem, reg.A);
			else {
				reg.A = read(addr, cpu_mem);
				//cout << setfill('0') << right << setw(2) << "reg.A = " << hex << +reg.A << endl;
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
			reg.X = reg.A
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
		void pha(struct Register& reg){
			stack_push(reg, reg.A, cpu_mem);
		}

		// pla: スタックの値をAレジスタに格納
		void pla(struct Register& reg){
			stack_pull(reg, reg.A, cpu_mem);
			check_negative_flag_u8(reg.A, reg);
			check_zero_flag_u8(reg.A, reg);
		}

		// php: ステータスレジスタの値をスタックへプッシュ
		void php(struct Register& reg){
			stack_push(reg, reg.P, cpu_mem);
		}

		// plp: スタックの値をステータスレジスタに格納
		void plp(struct Register& reg){
			stack_pull(reg, reg.P, cpu_mem);
		}
