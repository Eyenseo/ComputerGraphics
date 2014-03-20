#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <iostream>

#include "include/cube.hpp"
#include "include/pyramid.hpp"
#include "include/sphere.hpp"

static double window_width_  = 1024;
static double window_height_ = 768;

static double global_x_translation_      = 0;
static double global_y_translation_      = 0;
static double global_z_translation_      = -15;
static double global_x_translation_prev_ = global_x_translation_;
static double global_y_translation_prev_ = global_y_translation_;
static double global_z_translation_prev_ = global_z_translation_;

static double global_x_rotation_      = 0;
static double global_y_rotation_      = 0;
static double global_z_rotation_      = 0;

static int mouse_down_x_ = 0;
static int mouse_down_y_ = 0;

static std::vector<Drawable*> objects_;

/**
 * The function will add / decrease the global zoom / the distance to 0,0,0
 *
 * @param window   Will hold The window that received the event
 * @param x_offset x offset of the mouse wheel - either +1 or -1
 * @param y_offset y offset of the mouse wheel - either +1 or -1
 */
void mouse_scroll_callback(GLFWwindow* window, double x_offset,
                           double y_offset) {
  global_z_translation_ += y_offset / 4.0;
}

/**
 * The function will update the previous values of the global rotation if the
 * CTRL-key is no longer pressed and the mouse position to prevent jumping.
 * If the CTRL-KEy is pressed it will update the translation values.
 *
 * @param window   Will hold the window that received the event
 * @param key      Will hold the number of the key that triggered the event
 * @param scancode Will hold the system-specific scancode of the key.
 * @param action   Will hold the action that occurred - GLFW_PRESS, GLFW_RELEASE
 *                 or GLFW_REPEAT
 * @param mods     Will hold Bit field that describes which modifier keys were
 *                 held down.
 */
void key_callback(GLFWwindow* window, int key, int scancode,
                  int action, int mods) {
  if(key == 341 ) {
    double x_pos, y_pos;
    glfwGetCursorPos(window, &x_pos, &y_pos);

    mouse_down_x_ = x_pos;
    mouse_down_y_ = y_pos;

    if(action == GLFW_PRESS && glfwGetMouseButton(window, 0) == GLFW_PRESS) {
      global_x_translation_prev_ = global_x_translation_;
      global_y_translation_prev_ = global_y_translation_;
      global_z_translation_prev_ = global_z_translation_;
    }
  }
}

/**
 * The function will change the global rotation if the CTRL-Key and the left
 * mouse button is pressed and translation if only the left mouse button is
 * pressed.
 *
 * @param window Will hold the window that received the event
 * @param x_pos  Will hold the new x-coordinate, in screen coordinates,
 *               of the cursor.
 * @param y_pos  Will hold the new y-coordinate, in screen coordinates,
 *               of the cursor.
 */
void mouse_position_callback(GLFWwindow* window, double x_pos, double y_pos) {
  if(glfwGetMouseButton(window, 0) == GLFW_PRESS) {
    if(glfwGetKey(window, 341) == GLFW_PRESS) { // CTRL/STRG
      global_x_rotation_ = global_x_rotation_
                           + (y_pos - mouse_down_y_) / 8;
      global_z_rotation_ = global_z_rotation_
                           + (x_pos - mouse_down_x_) / 8;

      glfwSetCursorPos(window, mouse_down_x_,mouse_down_y_);
    } else {
      global_x_translation_ = global_x_translation_prev_
                              + (x_pos - mouse_down_x_) / 35.5;
      global_y_translation_ = global_y_translation_prev_
                              - (y_pos - mouse_down_y_) / 26.5;
    }
  }
}

/**
 * The function will capture the position where the left mouse button went down
 * and will update the previous values of the global rotation and translation if
 * the left mouse button is released
 *
 * @param window Will hold the window that received the event
 * @param button Will hold the mouse button that was pressed or released.
 * @param action Will hold one of GLFW_PRESS or GLFW_RELEASE.
 * @param mods   Will hold Bit field that describes which modifier keys were
 *               held down.
 */
void mouse_button_callback(GLFWwindow* window, int button, int action,
                           int mods) {
  if(button == 0) {
    if(action == GLFW_PRESS) {
      double x_pos, y_pos;

      glfwGetCursorPos(window, &x_pos, &y_pos);

      mouse_down_x_ = x_pos;
      mouse_down_y_ = y_pos;
    } else {

      global_x_translation_prev_ = global_x_translation_;
      global_y_translation_prev_ = global_y_translation_;
      global_z_translation_prev_ = global_z_translation_;
    }
  }
}

/**
 * The function will initialise GLFW.
 * 
 * @param  window Reference Pointer to a variable for the created window
 * @return        May return an error code 0 for success negative for failure
 */
int init_glfw(GLFWwindow*& window) {
  if(!glfwInit())
    return -1;

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

  return 0;
}

/**
 * The function will initialise the view of the scene / clear the frame to be
 * rendered again. This includes to apply the global transformations
 */
void init_view() {
  glClearColor(0.8, 0.8, 0.8, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Reset view
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(-15, 15, -10, 10, -20, 20);
  glFrustum(-1, 1, -1, 1, 1, 200);

  //Reset modelview
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //Apply gobal movement
  glTranslated(global_x_translation_, global_y_translation_,
               global_z_translation_);
  //Apply global rotation
  glRotated(global_x_rotation_, 1, 0, 0);
  glRotated(global_y_rotation_, 0, 1, 0);
  glRotated(global_z_rotation_, 0, 0, 1);
}

/**
 * The function will initialise the lighting
 */
void init_lighting() {
  GLfloat ambient[]     = {1.5, 1.5, 1.5, 1};
  GLfloat red_color[]   = {0.5, 0, 0, 1}; //rgb ? a?
  GLfloat green_color[] = {0, 0.5, 0, 1};
  GLfloat blue_color[]  = {0, 0, 0.5, 1};
  GLfloat white_color[] = {1.5, 1.5, 1.5, 1};

  GLfloat pos_1[] = {2, 2, 10, 1}; //rgbw <- w @0 = infinity
  GLfloat pos_2[] = {-2, -2, -10, 1};
  GLfloat pos_3[] = {2, -2, 10, 1};
  GLfloat pos_4[] = {-2, 2, -10, 1};

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glShadeModel(GL_SMOOTH);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT1, GL_POSITION, pos_1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, red_color);
  glLightfv(GL_LIGHT1, GL_SPECULAR, white_color);
  //glEnable(GL_LIGHT1);

  glLightfv(GL_LIGHT2, GL_POSITION, pos_2);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, green_color);
  glLightfv(GL_LIGHT2, GL_SPECULAR, white_color);
  //glEnable(GL_LIGHT2);

  glLightfv(GL_LIGHT3, GL_POSITION, pos_3);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, blue_color);
  glLightfv(GL_LIGHT3, GL_SPECULAR, white_color);
  //glEnable(GL_LIGHT3);

  glLightfv(GL_LIGHT4, GL_POSITION, pos_4);
  glLightfv(GL_LIGHT4, GL_DIFFUSE, white_color);
  glLightfv(GL_LIGHT4, GL_SPECULAR, white_color);
  glEnable(GL_LIGHT4);
}

/**
 * The function will create all objects to be rendered
 */
void make_objects() {
  objects_.push_back(new Sphere(-3, 0, 0, .5));
  objects_.push_back(new Sphere(-3, -3, 0, .5));
  objects_.push_back(new Sphere(-3, -3, -3, .5));
  objects_.push_back(new Pyramid(3, 0, 0, 1));
  objects_.push_back(new Pyramid(3, 3, 0, 1));
  objects_.push_back(new Pyramid(3, 3, 3, 1));
  objects_.push_back(new Cube(0, 0, 0, 1));

  objects_.at(0)->set_color(0.5, 0, 1, true);
  objects_.at(1)->set_color(1, 0, .5, true);
  objects_.at(2)->set_color(0.5, 1, 0, true);
  objects_.at(3)->set_color(1, .5, 0, true);

  (*(objects_.end() - 1))->set_color(1, 0, 0, false);
  (*(objects_.end() - 1))->set_color(0, 0, 1, true);
}

/**
 * The function will call the draw method from all drawable objects
 */
void draw() {
  for(std::vector<Drawable*>::iterator i = objects_.begin();
      i != objects_.end();
      ++i) {
    (*i)->draw();
  }
}


int main() {
  GLFWwindow* window = NULL;
  int error          = 0;

  printf("Here we go!\n");

  if((error = init_glfw(window)) != 0) {
    return error;
  }

  make_objects();

  while(!glfwWindowShouldClose(window)) {
    init_view();
    init_lighting();

    draw();

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();

  printf("Goodbye!\n");

  return 0;
}
