#include "parse/parse.hpp"
#include "cpu/cpu.hpp"
#include "ppu/ppu.hpp"
//#include "window/window.hpp"
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

#define BUFF_SIZE 32 * 240
#define PIXEL_SIZE 256 * 240

int cnt;
int prom_size;
int crom_size;
char outfile[]="sample/sample1.nes";
vector<u8> pROM;
vector<u8> cROM;
vector<u8> cpu_mem(0xffff + 1, 0);
vector<u8> ppu_mem(0x3fff + 1, 0);
vector<u8> sprite1(8, 0);
vector<u8> sprite2(8, 0);

GLubyte bits[BUFF_SIZE];
GLubyte bits_color_tmp[PIXEL_SIZE * 3];
GLubyte bits_color[PIXEL_SIZE * 3];

int main(){
    int result=0;
    struct Register reg;
    struct cpu cpu;
    cout << "start" << endl;
    result = myparse(cnt, prom_size, crom_size, outfile, pROM, cROM, cpu_mem, ppu_mem);
    if(result==1) cout << "どんまい" << endl;
//    cout << "pROM: " << endl;
//    cnt = 0;
 //   for(int i=0; i<static_cast<int>(pROM.size()); i++){
//		cnt = cnt + 1;
//		cout << setfill('0') << right << setw(2) << hex << +pROM.at(i) << " ";
//		if((cnt > 14) && (cnt % 16) == 0) cout << endl;
//	}

//    cout << "ppu_mem: " << endl;
//    cout << "name_table0: " << endl;
//     for(int j=0x2000; j<static_cast<int>(ppu_mem.size()); j++){
//		cnt = cnt + 1;
//		cout << setfill('0') << right << setw(2) << hex << +ppu_mem.at(j) << " ";
//		if((cnt > 14) && (cnt % 16) == 0) cout << endl;
//        if(j==0x23BF) cout << "type_table0" << endl;
//        if(j==0x23ff) cout << "name_table1" << endl;
//        if(j==0x27bf) cout << "type_table1" << endl;
//        if(j==0x27ff) cout << "name_table2" << endl;
//        if(j==0x2bbf) cout << "type_table2" << endl;
//	} 
    //reg.regreset()
    //cout << "aaa" << endl;
    //cout <<  "before: " << hex << reg.PC << endl;
    reg.regreset();
    //cout << "after: " << hex << reg.PC << endl;
    cpu.run(reg, cpu_mem, ppu_mem);

    int index = 0, index_tmp=0, color_cnt=0;
    for(u16 i=0x2000; i<=0x23BF; i++){
        //index = (((i-0x2000) / 32) *  32 * 8 * 3) + (((i-0x2000) % 32) * 3 * 8);
		index = i - 0x2000;
		//cout << "test_start" << endl;
//		cout << "ppu_mem[" << i <<"]: " << hex << +ppu_mem[i] << endl;
       
        if(ppu_mem[i]==0){
//			cout << "ppu_mem[i]==0" << endl;
//			cout << index << endl;
//			for(int j=0; j<8; j++){
//            	for(int k=0; k<8; k++){
//                	bits_color_tmp[index++] = 0x00;
//                	bits_color_tmp[index++] = 0x00;
//                	bits_color_tmp[index++] = 0x00;
//            	}
				//cout << "test_before" << endl;
//            	index = index + (256 * 3);
				//cout << "test_after" << endl;
           /* for(int j=0; j<8; j++){
                bits_color_tmp[index++] = 0x00;
                bits_color_tmp[index++] = 0x00;
                bits_color_tmp[index++] = 0x00;
            }*/
//			}

        }else{
			cout << "index: " << index << endl;
			cout << "ppu_mem not equal zero: " << index << endl;
			cout << "i: " << hex << +i << endl;
			index = ((index / 32) * 32 * 8 * 8 * 3) + ((index % 32) * 3 * 8);
            for(int j=0; j<16; j++){
                if(j < 8){ 
					sprite1[j] = ppu_mem[ppu_mem[i] * 0x0010 + j];
					if(j==0) cout << "sprite1: " << endl;
					cout << bitset<8>(sprite1[j]) << endl;
				}else{ 
					sprite2[j] = ppu_mem[ppu_mem[i] * 0x0010 + j];
					if(j==8) cout << "sprite2: " << endl;
					cout << bitset<8>(sprite2[j]) << endl;
				}				
            }
            for(int j=0; j<8; j++){
				index_tmp = index;
                for(int k=0; k<8; k++){
					int sprite1_num, sprite2_num;
						sprite1_num = (sprite1[j] >> k) & 1;
						sprite2_num = (sprite2[j] >> k) & 1;
                    if(sprite1_num == 0 && sprite2_num == 0){
                        bits_color_tmp[index++] = colors[ppu_mem[0x3F00]][0];
                        bits_color_tmp[index++] = colors[ppu_mem[0x3F00]][1];
                        bits_color_tmp[index++] = colors[ppu_mem[0x3F00]][2];
						cout << "case 0" << endl;
                    }
                    else if(sprite1_num == 0 && sprite2_num == 1){
                        bits_color_tmp[index++] = colors[ppu_mem[0x3F01]][0];
                        bits_color_tmp[index++] = colors[ppu_mem[0x3F01]][1];
                        bits_color_tmp[index++] = colors[ppu_mem[0x3F01]][2];
						cout << "case 1" << endl;
                    }
                    else if(sprite1_num == 1 && sprite2_num == 0){
                        bits_color_tmp[index++] = colors[ppu_mem[0x3F02]][0];
                        bits_color_tmp[index++] = colors[ppu_mem[0x3F02]][1];
                        bits_color_tmp[index++] = colors[ppu_mem[0x3F02]][2];
						cout << "case 2" << endl;                       
                    }
                    else if(sprite1_num == 1 && sprite2_num == 1){
                        bits_color_tmp[index++] = colors[ppu_mem[0x3F03]][0];
                        bits_color_tmp[index++] = colors[ppu_mem[0x3F03]][1];
                        bits_color_tmp[index++] = colors[ppu_mem[0x3F03]][2];
						color_cnt++;
						cout << "case 3" << endl;          
                    }
                }
                index = index_tmp + (256 * 3) ;
            }
            }
    }

    cout << "0x3F00, 0 color: " << hex << +colors[ppu_mem[0x3F00]][0] << endl;
    cout << "0x3F01, 0 color: " << hex << +colors[ppu_mem[0x3F01]][1] << endl;
    cout << "0x3F02 at ppu_mem: " << hex << +ppu_mem[0x3F02] << endl;
    cout << "0x3F02, 0 color: " << hex << +colors[ppu_mem[0x3F02]][0] << endl;
	cout << "color_cnt = " << color_cnt << endl;

    cnt = 0;
    for(int i=0; i<256 * 240 * 3; i++){
		cnt = cnt + 1;
		cout << setfill('0') << right << setw(2) << hex << +bits_color_tmp[i];
//         << " ";
		if((cnt > 14) && ((cnt % 256) == 0)) cout << endl;
        else if((cnt > 0) && ((cnt % 3) == 0)) cout << ", ";
        else cout << " ";
	}


//    for(int i=32; i<64; i++){
//        bits[i] = 0xFF;
//    }
 	
//    for(int i=0; i<BUFF_SIZE; i++){
//    	if(bits[i] == 0xFF){
//			index = i * 8 * 3;
//			//cout << "before: " << index << endl;
//				for(int j=0; j<8; j++){
//					bits_color[index++] = 255;
//					bits_color[index++] = 0;
//					bits_color[index++] = 0;
//				}
			//cout << "after:" << index << endl;
//		}
  //  }

//    for(int i=0; i<BUFF_SIZE; i++){
//    	if(bits[i] == 0xFF){
//			index = i * 8 * 3;
			//cout << "before: " << index << endl;
//				for(int j=0; j<8; j++){
//					bits_color_tmp[index++] = 255;
//					bits_color_tmp[index++] = 0;
//					bits_color_tmp[index++] = 0;
//				}
//			cout << "after:" << index << endl;
//		}
//    }

    for(int i=0; i<240; i++){
        for(int j=0; j<256; j++){
            for(int k=0; k<3; k++){
                bits_color[((240-1-i)*256*3)+(j*3)+k] = bits_color_tmp[(i*256*3)+(j*3)+k];
            }
        }
    }


	cout << index << endl;
    // GLFWの初期化(GLFW)
    if(glfwInit() == GL_FALSE){
        
        //初期化失敗
        cerr << "Can't initialize GLFW" << endl;
        return 1;
    }

    //終了時の処理登録(GLFW)
    atexit(glfwTerminate);

    //ウィンドウの作成（GLFW）
    GLFWwindow * const window(glfwCreateWindow(/* int width = */256, 
                                               /* int height =  */240, 
                                               /* const char * title =   */"Hello!", 
                                               /* GLFWmonitor * monitor =  */NULL, 
                                               /* GLFWwindow * share =  */NULL));
    
    if(window == NULL){
        // ウィンドウ作成に失敗した場合
        cerr << "Can't create GLFW window." << endl;
        return 1;
    }

    // 作成したウィンドウを処理対象とする（GLFW）
    glfwMakeContextCurrent( /* GLFWwindow * window = */ window);

    // 背景色（OpenGL）
    glClearColor(/* GLfloat red = */ 0.0f, 
                 /* GLfloat green =  */ 0.0f, 
                 /* GLfloat blue =  */ 0.0f, 
                 /* GLfloat alpha =  */ 0.0f);

    // ループ処理
    // ウィンドウが開いている間繰り返す
    while (glfwWindowShouldClose(/* GLFWwindow * window =  */ window) == GL_FALSE){
        // ウィンドウを削除（GLFW）
        glClear (/* GLbitfield mask =  */ GL_COLOR_BUFFER_BIT);
	
        // 描画処理
		glRasterPos2i(-1, -1);
		glDrawPixels(256, 240, GL_RGB, GL_UNSIGNED_BYTE, bits_color);
        
		// カラーバッファ入れ替え <= ダブルバッファリング（GLFW）
        glfwSwapBuffers(window);

        // イベント待ち（GLFW）
        glfwWaitEvents();
    }

	
    //cout << +reg.PC << endl;
    //cpu.exec();
    //for(int i=0; i<)
    
//    cout << "cpu_mem: " << endl;
//    cnt = 0;
//    cout << "00: ";
//    for(int i=0; i<static_cast<int>(cpu_mem.size()); i++){
//		cnt = cnt + 1;
//		cout << setfill('0') << right << setw(2) << hex << +cpu_mem.at(i) << " ";
//		if((cnt > 14) && (cnt % 16) == 0) {
//            cout << endl;
//            cout << setfill('0') << right << setw(2) << hex << +cnt << ": ";
//        }
//	}

//    cout << "ppu_mem: " << endl;
//    cnt = 0;
//    for(int j=0; j<static_cast<int>(ppu_mem.size()); j++){
//		cnt = cnt + 1;
//		cout << setfill('0') << right << setw(2) << hex << +ppu_mem.at(j) << " ";
//		if((cnt > 14) && (cnt % 16) == 0) {
//            cout << endl;
//            cout << setfill('0') << right << setw(2) << hex << +cnt << ": ";
//        }
//	}

    return 0;
};
