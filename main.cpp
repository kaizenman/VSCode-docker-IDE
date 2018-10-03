#ifdef __APPLE__
#   include <OpenGL/gl.h>
#   include <GLFW/glfw3.h>
#   include <OpenGL/glu.h>
#elif _WIN32
#   include <Windows.h>
#   include <GL/glew.h>
#   include <gl/glu.h>
#   include <GLFW/glfw3.h>
#   include <GL/freeglut.h>
#elif __ANDROID__
#   include <jni.h>
#   include <android/log.h>
#   include <GLES2/gl2.h>
#   include <GLES2/gl2ext.h>
#   include <stdio.h>
#   include <stdlib.h>
#   include <math.h>
#elif __linux__
#   include <stdio.h>
#   include <stdlib.h>
#   include <X11/X.h>
#   include <X11/Xlib.h>
#   include <GL/gl.h>
#   include <GLFW/glfw3.h>
#   include <GL/glx.h>
#   include <GL/glu.h>
#endif

#include <iostream>

void CrossPlatformHelloFunc()
{
#ifdef _WIN32
	//define something for Windows (32-bit and 64-bit, t  his part is common)
	std::cout << "Hello, Windows!" << std::endl;
#ifdef _WIN64
	//define something for Windows (64-bit only)
#else
	//define something for Windows (32-bit only)
#endif
#elif __linux__ 
	std::cout << "Hello, Linux!" << std::endl;
#elif __unix__
	// Unix
#elif defined(_POSIX_VERSION)
	// POSIX
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
	// iOS Simulator
#elif TARGET_OS_IPHONE
	// iOS device
#elif TARGET_OS_MAC
    std::cout << "Hello, MacOSX" << std::endl;
	// Other kinds of Mac OS
#else
#   error "Unknown Apple platform"
#endif
#elif __ANDROID__
    std::cout << "Hello, Android" << std::endl;
	// Android
#endif
}


#ifdef __ANDROID__
  #define  LOG_TAG    "libgl2jni"
  #define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
  #define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

  static void printGLString(const char *name, GLenum s) {
      const char *v = (const char *) glGetString(s);
      LOGI("GL %s = %s\n", name, v);
  }

  static void checkGlError(const char* op) {
      for (GLint error = glGetError(); error; error
              = glGetError()) {
          LOGI("after %s() glError (0x%x)\n", op, error);
      }
  } 

  auto gVertexShader =
      "attribute vec4 vPosition;\n"
      "void main() {\n"
      "  gl_Position = vPosition;\n"
      "}\n";

  auto gFragmentShader =
      "precision mediump float;\n"
      "void main() {\n"
      "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
      "}\n";

  GLuint loadShader(GLenum shaderType, const char* pSource) {
      GLuint shader = glCreateShader(shaderType);
      if (shader) {
          glShaderSource(shader, 1, &pSource, NULL);
          glCompileShader(shader);
          GLint compiled = 0;
          glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
          if (!compiled) {
              GLint infoLen = 0;
              glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
              if (infoLen) {
                  char* buf = (char*) malloc(infoLen);
                  if (buf) {
                      glGetShaderInfoLog(shader, infoLen, NULL, buf);
                      LOGE("Could not compile shader %d:\n%s\n",
                              shaderType, buf);
                      free(buf);
                  }
                  glDeleteShader(shader);
                  shader = 0;
              }
          }
      }
      return shader;
  }

  GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
      GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
      if (!vertexShader) {
          return 0;
      }

      GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
      if (!pixelShader) {
          return 0;
      }

      GLuint program = glCreateProgram();
      if (program) {
          glAttachShader(program, vertexShader);
          checkGlError("glAttachShader");
          glAttachShader(program, pixelShader);
          checkGlError("glAttachShader");
          glLinkProgram(program);
          GLint linkStatus = GL_FALSE;
          glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
          if (linkStatus != GL_TRUE) {
              GLint bufLength = 0;
              glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
              if (bufLength) {
                  char* buf = (char*) malloc(bufLength);
                  if (buf) {
                      glGetProgramInfoLog(program, bufLength, NULL, buf);
                      LOGE("Could not link program:\n%s\n", buf);
                      free(buf);
                  }
              }
              glDeleteProgram(program);
              program = 0;
          }
      }
      return program;
  }

  GLuint gProgram;
  GLuint gvPositionHandle;

  bool setupGraphics(int w, int h) {
      printGLString("Version", GL_VERSION);
      printGLString("Vendor", GL_VENDOR);
      printGLString("Renderer", GL_RENDERER);
      printGLString("Extensions", GL_EXTENSIONS);

      LOGI("setupGraphics(%d, %d)", w, h);
      gProgram = createProgram(gVertexShader, gFragmentShader);
      if (!gProgram) {
          LOGE("Could not create program.");
          return false;
      }
      gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
      checkGlError("glGetAttribLocation");
      LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
              gvPositionHandle);

      glViewport(0, 0, w, h);
      checkGlError("glViewport");
      return true;
  }

  const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
          0.5f, -0.5f };

  void renderFrame() {
  //  LOGI("HELLO HELLO HELLO HELLO HELLO HELLO HELLO HELLO");
      static float grey;
      grey += 0.01f;
      if (grey > 1.0f) {
          grey = 0.0f;
      }
      glClearColor(grey, grey, grey, 1.0f);
      checkGlError("glClearColor");
      glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
      checkGlError("glClear");

      glUseProgram(gProgram);
      checkGlError("glUseProgram");

      glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
      checkGlError("glVertexAttribPointer");
      glEnableVertexAttribArray(gvPositionHandle);
      checkGlError("glEnableVertexAttribArray");
      glDrawArrays(GL_TRIANGLES, 0, 3);
      checkGlError("glDrawArrays");
  }

  extern "C" {
      JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
      JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj);
  };

  JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
  {
      setupGraphics(width, height);
  }

  JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj)
  {
      renderFrame();
  }


#else
  void DrawAQuad() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1., 1., -1., 1., 1., 20.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

    glBegin(GL_QUADS);
    glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
    glColor3f(0., 1., 0.); glVertex3f(.75, -.75, 0.);
    glColor3f(0., 0., 1.); glVertex3f(.75, .75, 0.);
    glColor3f(1., 1., 0.); glVertex3f(-.75, .75, 0.);
    glEnd();
  }

  // X11 OpenGL window
  #ifdef __linux__
  Display                 *dpy;
  Window                  root;
  GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
  XVisualInfo             *vi;
  Colormap                cmap;
  XSetWindowAttributes    swa;
  Window                  win;
  GLXContext              glc;
  XWindowAttributes       gwa;
  XEvent                  xev;

  int main(int argc, char *argv[]) {

    dpy = XOpenDisplay(NULL);

    if (dpy == NULL) {
      printf("\n\tcannot connect to X server\n\n");
      exit(0);
    }

    root = DefaultRootWindow(dpy);

    vi = glXChooseVisual(dpy, 0, att);

    if (vi == NULL) {
      printf("\n\tno appropriate visual found\n\n");
      exit(0);
    }
    else {
      printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
    }


    cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

    XMapWindow(dpy, win);
    XStoreName(dpy, win, "VERY SIMPLE APPLICATION");

    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);

    glEnable(GL_DEPTH_TEST);

    while (1) {
      XNextEvent(dpy, &xev);

      if (xev.type == Expose) {
        XGetWindowAttributes(dpy, win, &gwa);
        glViewport(0, 0, gwa.width, gwa.height);
        DrawAQuad();
        glXSwapBuffers(dpy, win);
      }

      else if (xev.type == KeyPress) {
        glXMakeCurrent(dpy, None, NULL);
        glXDestroyContext(dpy, glc);
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
        exit(0);
      }
    } /* this closes while(1) { */
  } /* this is the } which closes int main(int argc, char *argv[]) { */

  #else
  int main(int argc, char ** argv) {
    CrossPlatformHelloFunc();
    if (!glfwInit()) {
        fprintf( stderr, "Failed to initialize GLFW\n");
        return -1;
      }

  // @TODO: need to understand what it is
  #ifdef __APPLE__
    /* We need to explicitly ask for a 3.2 context on OS X */
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #endif
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    // Open a window and create its OpenGL context
    GLFWwindow* window;
    window = glfwCreateWindow(1024, 768, "Turtorial 1", NULL, NULL);
    if (window == NULL) {
      fprintf(stderr, "Failed to open GLFW window");
      glfwTerminate();
      return -1;
    }

    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);

    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {
      /* Render here */
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the buffers
      glViewport(0, 0, 1024, 768);
      DrawAQuad();

      /* Swap front and back buffers */
      glfwSwapBuffers(window);
      /* Poll for and process events */
      glfwPollEvents();
    }
  std::cout << "Hi";
    glfwTerminate();
    return 0;
  }
  #endif

#endif