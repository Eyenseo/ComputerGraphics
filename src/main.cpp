#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "include/animated_cube.hpp"
#include "include/cube.hpp"
#include "include/pyramid.hpp"
#include "include/sphere.hpp"

static double window_width_  = 1024;
static double window_height_ = 768;

static double global_x_translation_ = 0;
static double global_y_translation_ = 0;
static double global_z_translation_ = -15;
static double global_x_translation_prev_ = global_x_translation_;
static double global_y_translation_prev_ = global_y_translation_;
static double global_z_translation_prev_ = global_z_translation_;

static double global_x_rotation_ = 0;
static double global_y_rotation_ = 0;
static double global_z_rotation_ = 0;

static int mouse_down_x_ = 0;
static int mouse_down_y_ = 0;

static std::vector<Drawable*> objects_;
static std::vector<std::function<void(int, int)> > key_callbacks_;

/**
 * Function taken from http://r3dux.org/2012/07/a-simple-glfw-fps-counter/
 *
 * @param  time_interval time interval for fps check
 * @param  window       pointer to window to receive the FPS in the title
 * @param  window_title  Window title before FPS
 * @return              FPS as double
 */
double calcFPS(double time_interval = 1.0, GLFWwindow* window = NULL,
               std::string window_title = "") {
  // Static values which only get initialised the first time the function runs
  static double start_time = glfwGetTime(); // Set the initial time to now
  static double fps = 0.0;                  // Set the initial FPS value to 0.0

  // Set the initial frame count to -1.0 (it gets set to 0.0 on the next line). Because
  // we don't have a start time we simply cannot get an accurate FPS value on our very
  // first read if the time interval is zero, so we'll settle for an FPS value of zero instead.
  static double frame_count = -1.0;

  // Here again? Increment the frame count
  frame_count++;

  // Ensure the time interval between FPS checks is sane (low cap = 0.0 i.e. every frame, high cap = 10.0s)
  if(time_interval < 0.0) {
    time_interval = 0.0;
  } else if(time_interval > 10.0) {
    time_interval = 10.0;
  }

  // Get the duration in seconds since the last FPS reporting interval elapsed
  // as the current time minus the interval start time
  double duration = glfwGetTime() - start_time;

  // If the time interval has elapsed...
  if(duration > time_interval) {
    // Calculate the FPS as the number of frames divided by the duration in seconds
    fps = frame_count / duration;

    // If the user specified a window title to append the FPS value to...
    if(window != NULL) {
      // Convert the fps value into a string using an output stringstream
      std::ostringstream stream;
      stream << fps;
      std::string fps_string = stream.str();

      // Append the FPS value to the window title details
      window_title += " | FPS: " + fps_string;

      const char* c_str_window_title = window_title.c_str();
      glfwSetWindowTitle(window, c_str_window_title);
    }

    // Reset the frame count to zero and set the initial time to be now
    frame_count = 0.0;
    start_time  = glfwGetTime();
  }
  return fps;
}

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
 * The function will go through a vector with funtions and pass them as
 * parameter int key and int action.
 *
 * @param window   Will hold the window that received the event
 * @param key      Will hold the number of the key that triggered the event
 * @param scancode Will hold the system-specific scancode of the key.
 * @param action   Will hold the action that occurred - GLFW_PRESS, GLFW_RELEASE
 *                 or GLFW_REPEAT
 * @param mods     Will hold Bit field that describes which modifier keys were
 *                 held down.
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods) {
  std::cout << key << std::endl;

  for(std::vector<std::function<void(int, int)> >::iterator i
        = key_callbacks_.begin(); i != key_callbacks_.end(); ++i) {
    (*i)(key, action);
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

      glfwSetCursorPos(window, mouse_down_x_, mouse_down_y_);
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
  if(!glfwInit()) return -1;

  // Antialiasing
  glfwWindowHint(GLFW_SAMPLES, 4);
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

  // TODO clean up - make a system that will make all callbacks on initialisation

  /*
  * The function will update the previous values of the global rotation if the
  * CTRL-key is no longer pressed and the mouse position to prevent jumping.
  * If the CTRL-KEy is pressed it will update the translation values.
  */
  key_callbacks_.push_back(
    [window](int event, int action) {
      if(event == 341) {
        double x_pos, y_pos;
        glfwGetCursorPos(window, &x_pos, &y_pos);

        mouse_down_x_ = x_pos;
        mouse_down_y_ = y_pos;

        if((action == GLFW_PRESS)
           && (glfwGetMouseButton(window, 0) == GLFW_PRESS)) {
          global_x_translation_prev_ = global_x_translation_;
          global_y_translation_prev_ = global_y_translation_;
          global_z_translation_prev_ = global_z_translation_;
        }
      }
    });

  return 0;
}

/**
 * The function will initialise the view of the scene / clear the frame to be
 * rendered again. This includes to apply the global transformations
 */
void init_view() {
  glClearColor(0.8, 0.8, 0.8, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset view
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glOrtho(-15, 15, -10, 10, -20, 20);
  glFrustum(-.5, .5, -.5, .5, 1, 200);

  // Reset modelview
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // Apply gobal movement
  glTranslated(global_x_translation_, global_y_translation_,
               global_z_translation_);
  // Apply global rotation
  glRotated(global_x_rotation_, 1, 0, 0);
  glRotated(global_y_rotation_, 0, 1, 0);
  glRotated(global_z_rotation_, 0, 0, 1);
}

/**
 * The function will initialise the lighting
 */
void init_lighting() {
  GLfloat ambient[]     = {1.5, 1.5, 1.5, 1};
  GLfloat red_color[]   = {0.5, 0, 0, 1}; // rgb ? a?
  GLfloat green_color[] = {0, 0.5, 0, 1};
  GLfloat blue_color[]  = {0, 0, 0.5, 1};
  GLfloat white_color[] = {1.5, 1.5, 1.5, 1};

  GLfloat pos_1[] = {2, 2, 10, 1}; // rgbw
  GLfloat pos_2[] = {-2, -2, -10, 1};
  GLfloat pos_3[] = {2, -2, 10, 1};
  GLfloat pos_4[] = {-2, 2, -10, 1};

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glShadeModel(GL_SMOOTH);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT1, GL_POSITION, pos_1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  red_color);
  glLightfv(GL_LIGHT1, GL_SPECULAR, white_color);
  // glEnable(GL_LIGHT1);

  glLightfv(GL_LIGHT2, GL_POSITION, pos_2);
  glLightfv(GL_LIGHT2, GL_DIFFUSE,  green_color);
  glLightfv(GL_LIGHT2, GL_SPECULAR, white_color);
  // glEnable(GL_LIGHT2);

  glLightfv(GL_LIGHT3, GL_POSITION, pos_3);
  glLightfv(GL_LIGHT3, GL_DIFFUSE,  blue_color);
  glLightfv(GL_LIGHT3, GL_SPECULAR, white_color);
  // glEnable(GL_LIGHT3);

  glLightfv(GL_LIGHT4, GL_POSITION, pos_4);
  glLightfv(GL_LIGHT4, GL_DIFFUSE,  white_color);
  glLightfv(GL_LIGHT4, GL_SPECULAR, white_color);
  glEnable(GL_LIGHT4);
}

/**
 * The function will create all objects to be rendered
 */
void make_objects() {
  Drawable* temp = new Sphere(-3, 0, 0, .5);

  temp->set_color(.5, 0, 1, true);
  objects_.push_back(temp);

  temp = new Sphere(-3, -3, 0, .5);
  temp->set_color(1, 0, .5, true);
  objects_.push_back(temp);

  temp = new Sphere(-3, -3, -3, .5);
  temp->set_color(.5, 1, 0, true);
  objects_.push_back(temp);

  temp = new Pyramid(3, 0, 0, 1);
  temp->set_color(1, .5, 0, true);
  objects_.push_back(temp);

  temp = new Pyramid(3, 3, 0, 1);
  temp->set_color(0, 1, .5, true);
  objects_.push_back(temp);

  temp = new Pyramid(3, 3, 3, 1);
  temp->set_color(0.25, .75, 0, true);
  objects_.push_back(temp);

  temp = new Cube(0, 0, 0, 1);
  temp->set_color(0.5, 0.5, 1, true);
  objects_.push_back(temp);

  temp = new AnimatedCube(0, 0, 4, 1);
  temp->set_color(0, 0, 1, true);
  temp->set_color(1, 0, 0, false);
  key_callbacks_.push_back(
    [temp](int event, int action) {
      if((GLFW_KEY_O == event) && (action == 1))
        ((AnimatedCube*)temp)->open();
    });
  key_callbacks_.push_back(
    [temp](int event, int action) {
      if((GLFW_KEY_C == event) && (action == 1))
        ((AnimatedCube*)temp)->close();
    });
  key_callbacks_.push_back(
    [temp](int event, int action) {
      if((93 == event) && (action == 1)) // 93 = +
        temp->set_scale(temp->get_scale() + .5);
    });
  key_callbacks_.push_back(
    [temp](int event, int action) {
      if((47 == event) && (action == 1)) // 47 = -
        temp->set_scale(temp->get_scale() - .5);
    });
  objects_.push_back(temp);
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
  int error = 0;

  printf("Here we go!\n");

  if((error = init_glfw(window)) != 0) {
    return error;
  }

  make_objects();

  while(!glfwWindowShouldClose(window)) {
    init_view();
    init_lighting();

    draw();

    calcFPS(1, window, "Simple 3D Animation");

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();

  printf("Goodbye!\n");

  return 0;
}
