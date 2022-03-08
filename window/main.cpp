#include <cstdlib>
#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

int main(){

    // GLFWの初期化(GLFW)
    if(glfwInit() == GL_FALSE){
        
        //初期化失敗
        cerr << "Can't initialize GLFW" << endl;
        return 1;
    }

    //終了時の処理登録(GLFW)
    atexit(glfwTerminate);

    //ウィンドウの作成（GLFW）
    GLFWwindow * const window(glfwCreateWindow(/* int width = */640, 
                                               /* int height =  */480, 
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
    glClearColor(/* GLfloat red = */ 0.2f, 
                 /* GLfloat green =  */ 0.2f, 
                 /* GLfloat blue =  */ 0.2f, 
                 /* GLfloat alpha =  */ 0.0f);

    // ループ処理
    // ウィンドウが開いている間繰り返す
    while (glfwWindowShouldClose(/* GLFWwindow * window =  */ window) == GL_FALSE){
        // ウィンドウを削除（GLFW）
        glClear (/* GLbitfield mask =  */ GL_COLOR_BUFFER_BIT);

        // 描画処理

        // カラーバッファ入れ替え <= ダブルバッファリング（GLFW）
        glfwSwapBuffers(window);

        // イベント待ち（GLFW）
        glfwWaitEvents();
    }
    
    return 0;
}