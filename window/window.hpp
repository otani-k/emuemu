#pragma once

//#include <iostream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <GLFW/glfw3.h>


#define BUFF_SIZE 32 * 240
#define PIXEL_SIZE 256 * 240
#define TILE_SIZE 32
#define BYTE_SIZE 8
#define COLOR_SIZE 3
#define PIXEL_COLUMN_SIZE 240
#define PIXEL_LINE_SIZE 256
#define SPRITE_POSITION 0x0010

#define NAMETAB0_ADDR 0x2000
#define NAMETAB0_END 0x23BF
#define BG_PALATTE0_ADDR 0x3F00
#define BG_PALATTE1_ADDR 0x3F01
#define BG_PALATTE2_ADDR 0x3F02
#define BG_PALATTE3_ADDR 0x3F03

using namespace std;

typedef unsigned char u8;
typedef unsigned short int u16;

void buff_create(vector<u8>& ppu_mem, GLubyte* bits_color_tmp);
void buff_reverse(GLubyte* bits_color_tmp, GLubyte* bits_color);
void buff_resize(GLubyte* bits_color, GLubyte* bits_color_resize);
int disp(vector<u8>& ppu_mem);