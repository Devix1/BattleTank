#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

int WindowWidth = 640;
int WindowHeight = 480;

void windowSixeCallBack(GLFWwindow* pWindow, int width, int height){
    WindowWidth = width;
    WindowHeight = WindowHeight;
    glViewport(0, 0, WindowWidth, WindowHeight);
}

void glfwKeyCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mode){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(void)
{
   

   
    if (!glfwInit()){
        cout<<"glfwInit failed"<<endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    GLFWwindow* pWindow = glfwCreateWindow(WindowWidth, WindowHeight, "Battle Tanks", nullptr, nullptr);
    if (!pWindow)
    {
        cout<<"glfwCreateWindow failed"<<endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, windowSixeCallBack);
    glfwSetKeyCallback(pWindow, glfwKeyCallBack);
   
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL()) {
        cout << "Can't load GLAD" << endl;
        return -1;
    }

    int major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    cout<<"Renderer"<<glGetString(GL_RENDERER) << endl;
    cout<<"OpenGL version: "<< glGetString(GL_VERSION)<<endl;
    cout << "OpenGL version: " << major << "." << minor << endl;
    cout<< "Press Escape to exit" << endl;

    glClearColor(1,1,0,1);
    
    
    while (!glfwWindowShouldClose(pWindow))
    {
       
        glClear(GL_COLOR_BUFFER_BIT);

       
        glfwSwapBuffers(pWindow);

       
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}