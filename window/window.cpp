#include "window.hpp"
#include "../ppu/ppu.hpp"
#include <cstdlib>
#include <bitset>
#include <iostream>
#include <GLFW/glfw3.h>


// ppu_memのバッググラウンドパレットの情報をもとにRGBの情報を格納したバッファを作成
void buff_create(vector<u8>& ppu_mem, GLubyte* bits_color_tmp){
    int index=0, index_tmp=0, color_cnt=0;
    vector<u8> sprite1(8, 0);
    vector<u8> sprite2(8, 0);

    for(u16 i=NAMETAB0_ADDR; i<=NAMETAB0_END; i++){
        //index = (((i-0x2000) / 32) *  32 * 8 * 3) + (((i-0x2000) % 32) * 3 * 8);
		index = i - NAMETAB0_ADDR;
		//cout << "test_start" << endl;
//		cout << "ppu_mem[" << i <<"]: " << hex << +ppu_mem[i] << endl;
       
        if(ppu_mem[i]!=0){
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
//			cout << "index: " << index << endl;
//			cout << "ppu_mem not equal zero: " << index << endl;
//			cout << "i: " << hex << +i << endl;
			index = ((index / TILE_SIZE) * TILE_SIZE * BYTE_SIZE * BYTE_SIZE * 3) + ((index % TILE_SIZE) * 3 * BYTE_SIZE);
            for(int j=0; j<16; j++){
                if(j < 8){ 
					sprite1[j] = ppu_mem[ppu_mem[i] * SPRITE_POSITION + j];
//					if(j==0) cout << "sprite1: " << endl;
//					cout << bitset<8>(sprite1[j]) << endl;
				}else{ 
					sprite2[j-8] = ppu_mem[ppu_mem[i] * SPRITE_POSITION + j];
//					if(j==8) cout << "sprite2: " << endl;
//					cout << bitset<8>(sprite2[j-8]) << endl;
				}				
            }
            for(int j=0; j<8; j++){
				index_tmp = index;
                for(int k=7; k>=0; k--){
					int sprite1_num, sprite2_num;
						sprite1_num = (sprite1[j] >> k) & 1;
						sprite2_num = (sprite2[j] >> k) & 1;
                        //cout << "sprite1: " << sprite1_num << ", sprite2: " << sprite2_num << endl;

                    if(sprite1_num == 0 && sprite2_num == 0){
                        bits_color_tmp[index++] = colors[ppu_mem[BG_PALATTE0_ADDR]][0];
                        bits_color_tmp[index++] = colors[ppu_mem[BG_PALATTE0_ADDR]][1];
                        bits_color_tmp[index++] = colors[ppu_mem[BG_PALATTE0_ADDR]][2];
						//cout << "case 0" << endl;
                    }
                    else if(sprite1_num == 0 && sprite2_num == 1){
                        bits_color_tmp[index++] = colors[ppu_mem[BG_PALATTE1_ADDR]][0];
                        bits_color_tmp[index++] = colors[ppu_mem[BG_PALATTE1_ADDR]][1];
                        bits_color_tmp[index++] = colors[ppu_mem[BG_PALATTE1_ADDR]][2];
						//cout << "case 1" << endl;
                    }
                    else if(sprite1_num == 1 && sprite2_num == 0){
                        bits_color_tmp[index++] = colors[ppu_mem[BG_PALATTE2_ADDR]][0];
                        bits_color_tmp[index++] = colors[ppu_mem[BG_PALATTE2_ADDR]][1];
                        bits_color_tmp[index++] = colors[ppu_mem[BG_PALATTE2_ADDR]][2];
						//cout << "case 2" << endl;                       
                    }
                    else if(sprite1_num == 1 && sprite2_num == 1){
                        bits_color_tmp[index++] = colors[ppu_mem[BG_PALATTE3_ADDR]][0];
                        bits_color_tmp[index++] = colors[ppu_mem[BG_PALATTE3_ADDR]][1];
                        bits_color_tmp[index++] = colors[ppu_mem[BG_PALATTE3_ADDR]][2];
						color_cnt++;
						//cout << "case 3" << endl;          
                    }
                }
                index = index_tmp + (PIXEL_LINE_SIZE * 3) ;
            }
            }
    }
}

// バッファの行を反転（OpenGLの仕様上，下から描画処理するため）
void buff_reverse(GLubyte* bits_color_tmp, GLubyte* bits_color){
    for(int i=0; i<PIXEL_COLUMN_SIZE; i++){
        for(int j=0; j<PIXEL_LINE_SIZE; j++){
            for(int k=0; k<3; k++){
                bits_color[((PIXEL_COLUMN_SIZE-1-i)*PIXEL_LINE_SIZE*3)+(j*3)+k] = bits_color_tmp[(i*PIXEL_LINE_SIZE*3)+(j*3)+k];
            }
        }
    }
}

// バッファの大きさを拡張（今んとこ2 * 2倍に）
void buff_resize(GLubyte* bits_color, GLubyte* bits_color_resize){
    int line_cnt = 0;
    for(int i=0; i<(PIXEL_COLUMN_SIZE * 2); i++) {
        for(int j=0; j<(PIXEL_LINE_SIZE * COLOR_SIZE * 2) ; j++) {
            if((i%2)==1) {
                //if(bits_color_resize[(i-1)*PIXEL_LINE_SIZE*3*2+j]!=0) {
                //    cout << "bits_color_resize: " << hex << +bits_color_resize[(i-1)*PIXEL_LINE_SIZE*3*2+j] << endl;
                //}
                bits_color_resize[i*PIXEL_LINE_SIZE*3*2+j] = bits_color_resize[(i-1)*PIXEL_LINE_SIZE*3*2+j];
            }
            else {
                for(int k=0; k<6; k++) {
                    //if(bits_color[line_cnt]) cout << "bits_color: " << hex << +bits_color[line_cnt] << endl; 
                    if(k<3) {
                        bits_color_resize[i*PIXEL_LINE_SIZE*3*2+j++] = bits_color[line_cnt++];
                        //if(bits_color_resize[j-1]!=0) cout << "bits_color_resize: " << hex << +bits_color_resize[j-1] << endl;
                    }
                    else {
                        if(k==3) {
                            line_cnt = line_cnt - 3;
                        }
                        bits_color_resize[i*PIXEL_LINE_SIZE*3*2+j] = bits_color[line_cnt++];
                        if(k!=5) {
                            j++;
                        }
                    }
                }
            }
        }
//        cout << "line" << dec << i << ":" << line_cnt << endl;
    }
}


int disp(vector<u8>& ppu_mem){

    if(glfwInit() == GL_FALSE){
        
        //初期化失敗
        cerr << "Can't initialize GLFW" << endl;
        return 1;
    }

    //終了時の処理登録(GLFW)
    atexit(glfwTerminate);

    //ウィンドウの作成（GLFW）
    GLFWwindow * const window(glfwCreateWindow(/* int width = */PIXEL_LINE_SIZE * 2, 
                                               /* int height =  */PIXEL_COLUMN_SIZE * 2, 
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
        GLubyte bits_color_tmp[PIXEL_SIZE * 3]; // RGB付きのバッファ
        GLubyte bits_color[PIXEL_SIZE * 3]; // 行を反転させたバッファ（OpenGLの仕様上後ろから描画するため）
        GLubyte bits_color_resize[PIXEL_SIZE * 3 * 4]; // 2 * 2倍に拡大したバッファ（256 * 240は小さすぎた）

        buff_create(ppu_mem, bits_color_tmp);
        buff_reverse(bits_color_tmp, bits_color);
        buff_resize(bits_color, bits_color_resize);

		glRasterPos2i(-1, -1);
		glDrawPixels(PIXEL_LINE_SIZE*2, PIXEL_COLUMN_SIZE*2, GL_RGB, GL_UNSIGNED_BYTE, bits_color_resize);
        
		// カラーバッファ入れ替え <= ダブルバッファリング（GLFW）
        glfwSwapBuffers(window);

        // イベント待ち（GLFW）
        glfwWaitEvents();
    }
    return 0;
}
