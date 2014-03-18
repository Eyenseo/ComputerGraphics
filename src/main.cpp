#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "include/vec3.hpp"

static double window_width_  = 1024;
static double window_height_ = 768;

static double global_x_translation      = 0;
static double global_y_translation      = 0;
static double global_z_translation      = -15;
static double global_x_translation_prev = global_x_translation;
static double global_y_translation_prev = global_y_translation;
static double global_z_translation_prev = global_z_translation;

static double global_x_rotation      = 0;
static double global_y_rotation      = 0;
static double global_z_rotation      = 0;
static double global_x_rotation_prev = global_x_rotation;
static double global_y_rotation_prev = global_y_rotation;
static double global_z_rotation_prev = global_z_rotation;

static int mouse_down_x = 0;
static int mouse_down_y = 0;

//draw a sphere composed of triangles
void DrawSphere(const Vec3& ctr, double r) {
  Vec3   normal, v1;
  double a1, a1d,
         a2, a2d,
         s1, s2,
         c1, c2;
  int i, j,
      n1 = 32, n2 = 32;

  a1d = M_PI / n1;
  a2d = M_PI / n2;

  glShadeModel(GL_SMOOTH);
  for(i = 0; i < n1; i++) {
    a1 = i * a1d;

    glBegin(GL_TRIANGLE_STRIP);
    for(j = 0; j <= n2; j++) {
      a2 = (j + .5 * (i % 2)) * 2 * a2d;

      s1 = sin(a1);
      c1 = cos(a1);
      s2 = sin(a2);
      c2 = cos(a2);

      normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
      v1     = ctr + r * normal;

      glNormal3dv(normal.p);
      glVertex3dv(v1.p);

      s1 = sin(a1 + a1d);
      c1 = cos(a1 + a1d);
      s2 = sin(a2 + a2d);
      c2 = cos(a2 + a2d);

      normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
      v1     = ctr + r * normal;

      glNormal3dv(normal.p);
      glVertex3dv(v1.p);
    }
    glEnd();
  }
}

void DrawPyramid(const Vec3& center, double base_length, double height,
                 double rotation_x = 0, double rotation_y = 0,
                 double rotation_z = 0) {
  double half_base_length = .5 * base_length;

  Vec3 base_bottom_left  = Vec3(-half_base_length, -half_base_length, 0);
  Vec3 base_top_left     = Vec3(-half_base_length, half_base_length, 0);
  Vec3 base_top_right    = Vec3(half_base_length, half_base_length, 0);
  Vec3 base_bottom_right = Vec3(half_base_length, -half_base_length, 0);
  Vec3 top               = Vec3(0, 0, height);

  auto face
    = [](Vec3 v1, Vec3 v2, Vec3 v3) {
        Vec3 normal = (v2 - v1) % (v3 - v1);

        normal.Normalize();

        glNormal3dv(normal.p);
        glVertex3dv(v1.p);
        glVertex3dv(v2.p);
        glVertex3dv(v3.p);
      };

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(center.p[0], center.p[1], center.p[2]);
  glRotatef(rotation_x, 1.0f, 0.0f, 0.0f);
  glRotatef(rotation_y, 0.0f, 1.0f, 0.0f);
  glRotatef(rotation_z, 0.0f, 0.0f, 1.0f);

  glBegin(GL_TRIANGLES);
  //Base !!Counter clockwise from below!!
  face(base_top_right, base_bottom_right, base_bottom_left);
  face(base_bottom_left, base_top_left, base_top_right);
  //First Side
  face(base_bottom_right, top, base_bottom_left);
  //Second Side
  face(base_bottom_left, top, base_top_left);
  //Third Side
  face(base_top_left, top, base_top_right);
  //Fourth Side
  face(base_top_right, top, base_bottom_right);
  glEnd();

  glPopMatrix();
}

void SetMaterialColor(int side, double r, double g, double b) {
  float amb[4], dif[4], spe[4];
  int   mat;

  dif[0] = r;
  dif[1] = g;
  dif[2] = b;
  for(int i = 0; i < 3; i++) {
    amb[i] = .1 * dif[i];
    spe[i] = .25;
  }

  amb[3] = dif[3] = spe[3] = 1.0;

  switch(side) {
    case 1:
      mat = GL_FRONT;
      break;
    case 2:
      mat = GL_BACK;
      break;
    default:
      mat = GL_FRONT_AND_BACK;
  }

  glMaterialfv(mat, GL_AMBIENT, amb);
  glMaterialfv(mat, GL_DIFFUSE, dif);
  glMaterialfv(mat, GL_SPECULAR, spe);
  glMaterialf(mat, GL_SHININESS, 20);
}

#define ambient_value 0.4

//set viewport transformations and draw objects
void InitLighting() {
  GLfloat ambient[]     = {2, 2, 2, 1};
  GLfloat red_color[]   = {1, 0, 0, 1}; //rgb ? a?
  GLfloat green_color[] = {0, 1, 0, 1};
  GLfloat blue_color[]  = {0, 0, 1, 1};
  GLfloat white_color[] = {1, 1, 1, 1};

  GLfloat red_color_ambient[]
    = {1 / ambient_value, 0 / ambient_value, 0 / ambient_value, 1}; //rgb ? a?
  GLfloat green_color_ambient[]
    = {0 / ambient_value, 1 / ambient_value, 0 / ambient_value, 1};
  GLfloat blue_color_ambient[]
    = {0 / ambient_value, 0 / ambient_value, 1 / ambient_value, 1};

  GLfloat red_pos[]   = {0, 2,  0.5, 1}; //rgbw <- w @0 = infinity
  GLfloat green_pos[] = {2, 0,  0.5, 1};
  GLfloat blue_pos[]  = {0, -2, 0.5, 1};
  GLfloat white_pos[] = {-2, 0, 0.5, 1};

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glShadeModel(GL_SMOOTH);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT1, GL_POSITION, red_pos);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, red_color);
  glLightfv(GL_LIGHT1, GL_SPECULAR, red_color);
  //glLightfv(GL_LIGHT1, GL_AMBIENT, red_color_ambient);
  glEnable(GL_LIGHT1);

  glLightfv(GL_LIGHT2, GL_POSITION, green_pos);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, green_color);
  glLightfv(GL_LIGHT2, GL_SPECULAR, green_color);
  //glLightfv(GL_LIGHT2, GL_AMBIENT, green_color_ambient);
  glEnable(GL_LIGHT2);

  glLightfv(GL_LIGHT3, GL_POSITION, blue_pos);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, blue_color);
  glLightfv(GL_LIGHT3, GL_SPECULAR, blue_color);
  //glLightfv(GL_LIGHT3, GL_AMBIENT, blue_color_ambient);
  glEnable(GL_LIGHT3);

  glLightfv(GL_LIGHT4, GL_POSITION, white_pos);
  glLightfv(GL_LIGHT4, GL_DIFFUSE, white_color);
  glLightfv(GL_LIGHT4, GL_SPECULAR, white_color);
  //glLightfv(GL_LIGHT4, GL_AMBIENT, blue_color_ambient);
  glEnable(GL_LIGHT4);
}

//draw the entire scene
void Preview() {
  InitLighting();
  //init viewport to canvassize
  //glViewport(0, 0, window_width_, window_height_);
  //init coordinate system
  //glViewport(window_width_, window_height_, -window_width_, -window_height_);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(-15, 15, -10, 10, -20, 20);
  glFrustum(-1, 1, -1, 1, 1, 200);
  glMatrixMode(GL_MODELVIEW);
  //Reset The Current Modelview Matrix
  glLoadIdentity();
  //Apply gobal movement
  glTranslated(global_x_translation, global_y_translation,
               global_z_translation);
  //Apply global rotation
  glRotated(global_x_rotation, 1, 0, 0);
  glRotated(global_y_rotation, 0, 1, 0);
  glRotated(global_z_rotation, 0, 0, 1);


  ////First sphere
  //SetMaterialColor(3, 1, 0, 0);
  //DrawSphere(Vec3(5, 0, 0), 4);
  ////Second sphere
  //SetMaterialColor(3, 0, 1, 0);
  //DrawSphere(Vec3(-5, 0, 0), 2);
  ////Third sphere
  //SetMaterialColor(3, 0, 0, 1);
  //DrawSphere(Vec3(0, 5, 0), 2);

  // Triangle
  SetMaterialColor(1, 1, 1, 1);
  SetMaterialColor(2, 0, 0, 1);
  glBegin(GL_TRIANGLES);
  glNormal3f(0.0, 0.0, 1.0);
  glVertex3f(0.0, 2.0, 1.0);
  glVertex3f(-2.0, -2.0, 1.0);
  glVertex3f(2.0, -2.0, 1.0);
  glEnd();

  // SetMaterialColor(0, .50, .5, 0.5);
  // DrawSphere(Vec3(0, 0, 0), 1);

  //Red lamp
  //SetMaterialColor(2, .5,.5,.5);
  //DrawSphere(Vec3(0, 4, 0), 1);
  //Green lamp
  //SetMaterialColor(2, .5,.5,.5);
  //DrawSphere(Vec3(-3, -3, 0), 1);
  //Blue lamp
  //SetMaterialColor(2, 0.5, 0.5, .5);
  //DrawSphere(Vec3(3, -3, 0), 1);

  SetMaterialColor(2, .5, .5, .5);
  Vec3 pos = Vec3(0, 0, 1.5);
  // DrawPyramid(pos, 2, 3, -45,-45,45);
  DrawPyramid(pos, 2, 6);
}

void mouse_scroll_callback(GLFWwindow* window, double x_offset,
                           double y_offset) {
  global_z_translation += y_offset / 2.0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods) {
  //std::cout << key << std::endl;
}

void mouse_position_callback(GLFWwindow* window, double x_pos, double y_pos) {
  if(glfwGetMouseButton(window, 0) == GLFW_PRESS) {
    if(glfwGetKey(window, 341) == GLFW_PRESS) {
      global_x_rotation = global_x_rotation_prev + (y_pos - mouse_down_y) / 8;
      global_z_rotation = global_z_rotation_prev + (x_pos - mouse_down_x) / 8;

      //std::cout << "Rotation\tx:" << global_x_rotation
      //<< "\ty:" << global_y_rotation << std::endl;
    } else {
      global_x_translation = global_x_translation_prev
                             + (x_pos - mouse_down_x) / 33;
      global_y_translation = global_y_translation_prev
                             - (y_pos - mouse_down_y) / 33;

      //std::cout << "Translation\tx:" << global_x_translation
      //<< "\ty:" << global_y_translation << std::endl;
    }
  }
}

void mouse_button_callback(GLFWwindow* window, int button, int x_offset,
                           int y_offset) {
  if(button == 0) {
    if(glfwGetMouseButton(window, 0) == GLFW_PRESS) {
      double x_pos, y_pos;

      glfwGetCursorPos(window, &x_pos, &y_pos);

      mouse_down_x = x_pos;
      mouse_down_y = y_pos;
    } else {
      global_x_rotation_prev = global_x_rotation;
      global_y_rotation_prev = global_y_rotation;
      global_z_rotation_prev = global_z_rotation;

      global_x_translation_prev = global_x_translation;
      global_y_translation_prev = global_y_translation;
      global_z_translation_prev = global_z_translation;
    }
  }
}

int main() {
  GLFWwindow* window = NULL;

  printf("Here we go!\n");
  if(!glfwInit()) return -1;
  window = glfwCreateWindow(window_width_, window_height_,
                            "Simple 3D Animation", NULL, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  glfwSetCursorPosCallback(window, &mouse_position_callback);
  glfwSetScrollCallback(window, &mouse_scroll_callback);
  glfwSetMouseButtonCallback(window, &mouse_button_callback);

  glfwSetKeyCallback(window, &key_callback);

  while(!glfwWindowShouldClose(window)) {
    //switch on lighting (or you don't see anything)
    //InitLighting();

    //set background color
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //draw the scene
    Preview();

    //make it appear (before this, it's hidden in the rear buffer)
    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();

  printf("Goodbye!\n");

  return 0;
}
