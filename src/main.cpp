#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <forward_list>
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
#include "include/table.hpp"
#include "include/button.hpp"

#include "include/physic.hpp"

static std::forward_list<std::function<void(int, int, int)>> key_callbacks_;
static std::forward_list<std::function<void(
    unsigned int, unsigned int, unsigned int, unsigned int)>> mouse_callbacks_;
static std::forward_list<Drawable*> objects_;
static std::forward_list<Hitable*> hitables_;
static std::forward_list<Button*> buttons_;

static double window_width_ = 1024;
static double window_height_ = 768;

static double global_x_translation_ = 0;
static double global_y_translation_ = 0;
static double global_z_translation_ = -25;
static double global_x_translation_prev_ = global_x_translation_;
static double global_y_translation_prev_ = global_y_translation_;
static double global_z_translation_prev_ = global_z_translation_;

static double global_x_rotation_ = 0;
static double global_y_rotation_ = 0;
static double global_z_rotation_ = 0;

static int mouse_down_x_ = 0;
static int mouse_down_y_ = 0;


static double mouse_divider_ = 0.35;
static bool speed_button_pressed_ = false;

static Table* table;
static Sphere* interactive;
static Sphere* selected_;

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
  static double start_time = glfwGetTime();  // Set the initial time to now
  static double fps = 0.0;                   // Set the initial FPS value to 0.0

  // Set the initial frame count to -1.0 (it gets set to 0.0 on the next line).
  // Because
  // we don't have a start time we simply cannot get an accurate FPS value on
  // our very
  // first read if the time interval is zero, so we'll settle for an FPS value
  // of zero instead.
  static double frame_count = -1.0;

  // Here again? Increment the frame count
  frame_count++;

  // Ensure the time interval between FPS checks is sane (low cap = 0.0 i.e.
  // every frame, high cap = 10.0s)
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
    // Calculate the FPS as the number of frames divided by the duration in
    // seconds
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
    start_time = glfwGetTime();
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
void mouse_scroll_callback(GLFWwindow* /*window*/, double /*x_offset*/,
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
void key_callback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action,
                  int mods) {
  // std::cout << key << std::endl;
  for(auto fun : key_callbacks_) {
    fun(key, action, mods);
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
    if(glfwGetKey(window, 341) == GLFW_PRESS) {
      speed_button_pressed_ = true;
    } else if(glfwGetKey(window, 340) == GLFW_PRESS) {  // CTRL/STRG
      global_x_rotation_ = global_x_rotation_ + (y_pos - mouse_down_y_) / 8;
      global_z_rotation_ = global_z_rotation_ + (x_pos - mouse_down_x_) / 8;

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
                           int /*mods*/) {
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  for(auto fun : mouse_callbacks_) {
    fun(button, action, x, y);
  }
}

/**
 * Control newly created Objects via:
 *   Movement:
 *     w x-axis +
 *     s x-axis -
 *     d y-axis +
 *     a y-axis -
 *     e z-axis +
 *     q z-axis -
 *   Scale:
 *     r x-axis +
 *     R x-axis -
 *     f y-axis +
 *     F y-axis -
 *     v z-axis +
 *     V z-axis -
 *   Rotate:
 *     t x-axis +
 *     T x-axis -
 *     g y-axis +
 *     G y-axis -
 *     b z-axis +
 *     B z-axis -
 *
 *   Stop Sphere from moving:
 *     m
 */
void selected_callback() {
  // Moveable
  key_callbacks_.push_front([&](int key, int action, int) {
    if(selected_ != nullptr && (GLFW_KEY_M == key)
       && (action == GLFW_REPEAT || action == GLFW_PRESS)) {

      Hitable* hitable = dynamic_cast<Hitable*>(selected_);
      if(hitable != nullptr && dynamic_cast<Sphere*>(hitable) != nullptr) {
        hitable->set_moveable(!hitable->is_moveable());
        hitable->set_speed(GLVector<XYZW>::NVec);
      }
    }
  });

  // Movement
  key_callbacks_.push_front([&](int key, int action, int) {
    if(selected_ != nullptr && (GLFW_KEY_W == key)
       && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
      selected_->set_origin_y(selected_->get_origin_y() + .05);
    }
  });
  key_callbacks_.push_front([&](int key, int action, int) {
    if(selected_ != nullptr && (GLFW_KEY_A == key)
       && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
      selected_->set_origin_x(selected_->get_origin_x() - .05);
    }
  });
  key_callbacks_.push_front([&](int key, int action, int) {
    if(selected_ != nullptr && (GLFW_KEY_S == key)
       && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
      selected_->set_origin_y(selected_->get_origin_y() - .05);
    }
  });
  key_callbacks_.push_front([&](int key, int action, int) {
    if(selected_ != nullptr && (GLFW_KEY_D == key)
       && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
      selected_->set_origin_x(selected_->get_origin_x() + .05);
    }
  });
  key_callbacks_.push_front([&](int key, int action, int) {
    if(selected_ != nullptr && (GLFW_KEY_E == key)
       && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
      selected_->set_origin_z(selected_->get_origin_z() + .05);
    }
  });
  key_callbacks_.push_front([&](int key, int action, int) {
    if(selected_ != nullptr && (GLFW_KEY_Q == key)
       && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
      selected_->set_origin_z(selected_->get_origin_z() - .05);
    }
  });

  // Scale
  key_callbacks_.push_front([&](int key, int action, int modifier) {
    if(selected_ != nullptr && (GLFW_KEY_R == key)
       && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
      if(modifier == GLFW_MOD_SHIFT) {
        selected_->set_scale_y(selected_->get_scale_y() + .05);
      } else {
        double scale_y = selected_->get_scale_y();
        if(scale_y > .25) {
          selected_->set_scale_y(scale_y - .05);
        }
      }
    }
  });
  key_callbacks_.push_front([&](int key, int action, int modifier) {
    if(selected_ != nullptr && (GLFW_KEY_F == key)
       && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
      if(modifier == GLFW_MOD_SHIFT) {
        selected_->set_scale_y(selected_->get_scale_y() + .05);
      } else {
        double scale_y = selected_->get_scale_y();
        if(scale_y > .25) {
          selected_->set_scale_y(scale_y - .05);
        }
      }
    }
  });
  key_callbacks_.push_front([&](int key, int action, int modifier) {
    if(selected_ != nullptr && (GLFW_KEY_V == key)
       && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
      if(modifier == GLFW_MOD_SHIFT) {
        selected_->set_scale_y(selected_->get_scale_y() + .05);
      } else {
        double scale_y = selected_->get_scale_y();
        if(scale_y > .25) {
          selected_->set_scale_y(scale_y - .05);
        }
      }
    }
  });

  // Rotate
  key_callbacks_.push_front([&](int key, int action, int modifier) {
    if(selected_ != nullptr && (GLFW_KEY_T == key)
       && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
      if(modifier == GLFW_MOD_SHIFT) {
        selected_->set_rotation_y(selected_->get_rotation_y() + .5);
      } else {
        selected_->set_rotation_y(selected_->get_rotation_y() - .5);
      }
    }
  });
  key_callbacks_.push_front([&](int key, int action, int modifier) {
    if(selected_ != nullptr && (GLFW_KEY_G == key)
       && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
      if(modifier == GLFW_MOD_SHIFT) {
        selected_->set_rotation_y(selected_->get_rotation_y() + .5);
      } else {
        selected_->set_rotation_y(selected_->get_rotation_y() - .5);
      }
    }
  });
  key_callbacks_.push_front([&](int key, int action, int modifier) {
    if(selected_ != nullptr && (GLFW_KEY_B == key)
       && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
      if(modifier == GLFW_MOD_SHIFT) {
        selected_->set_rotation_y(selected_->get_rotation_y() + .5);
      } else {
        selected_->set_rotation_y(selected_->get_rotation_y() - .5);
      }
    }
  });
}

void register_callbacks(GLFWwindow* window) {
  //  The function will update the previous values of the global rotation if the
  //  CTRL-key is no longer pressed and the mouse position to prevent jumping.
  //  If the CTRL-KEy is pressed it will update the translation values.
  key_callbacks_.push_front([window](int key, int action, int) {
    if(key == 340) {
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
  key_callbacks_.push_front([window](int key, int, int) {
    if((GLFW_KEY_ESCAPE == key)) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
  });

  mouse_callbacks_.push_front([window](int button, int action, unsigned int x,
                                       unsigned int y) {
    if(button == 0) {
      if(action == GLFW_PRESS) {
        mouse_down_x_ = x;
        mouse_down_y_ = y;
      } else if(action == GLFW_RELEASE) {
        global_x_translation_prev_ = global_x_translation_;
        global_y_translation_prev_ = global_y_translation_;
        global_z_translation_prev_ = global_z_translation_;
      }
    }
  });
  mouse_callbacks_.push_front([window](int button, int action, unsigned int,
                                       unsigned int) {
    if(button == 0) {
      if(action == GLFW_RELEASE) {
        for(auto button : buttons_) {
          button->set_pressed(false);
        }
      }
    }
  });

  selected_callback();
}

/**
 * The function will initialise GLFW.
 *
 * @param  window Reference Pointer to a variable for the created window
 * @return        May return an error code 0 for success negative for failure
 */
int init_glfw(GLFWwindow*& window) {
  if(!glfwInit()) {
    return -1;
  }

  // Antialiasing
  glfwWindowHint(GLFW_SAMPLES, 4);
  window = glfwCreateWindow(window_width_, window_height_,
                            "Simple 3D Animation", NULL, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  glewInit();

  glfwSetCursorPosCallback(window, &mouse_position_callback);
  glfwSetScrollCallback(window, &mouse_scroll_callback);
  glfwSetMouseButtonCallback(window, &mouse_button_callback);
  glfwSetKeyCallback(window, &key_callback);

  register_callbacks(window);

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

  glFrustum(-.5, .5, -.5, .5, 1, 200);

  // Apply gobal movement
  glTranslated(global_x_translation_, global_y_translation_,
               global_z_translation_);

  // Apply global rotation
  glRotated(global_x_rotation_, 1, 0, 0);
  glRotated(global_y_rotation_, 0, 1, 0);
  glRotated(global_z_rotation_, 0, 0, 1);

  // Reset modelview
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/**
 * The function will initialise the lighting
 */
void init_lighting() {
  GLfloat ambient[] = {4.75, 4.75, 4.75, 1};
  GLfloat white_color[] = {.25, .25, .25, 1};

  GLfloat pos_0[] = {15, 15, 13, 1};
  GLfloat pos_1[] = {0, 0, 50, 1};
  GLfloat pos_2[] = {15, 50, 15, 1};

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT0, GL_POSITION, pos_0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white_color);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_color);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, .00f);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, .00f);
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.00025);
  glEnable(GL_LIGHT0);

  glLightfv(GL_LIGHT1, GL_POSITION, pos_1);
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
  glEnable(GL_LIGHT1);

  glLightfv(GL_LIGHT2, GL_POSITION, pos_2);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, white_color);
  glLightfv(GL_LIGHT2, GL_SPECULAR, white_color);
  glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, .00f);
  glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, .00f);
  glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.00045);
}

/**
 * The function will create all objects to be rendered
 */
void make_objects() {
  Drawable* temp;

  double dif_x = -4;
  double dif_y = -4;

  // temp = new Sphere(0, 0, 0);
  temp = new Sphere(dif_x, dif_y, 6.61);
  interactive = dynamic_cast<Sphere*>(temp);
  temp->set_color(.7, .7, .7, 0);
  objects_.push_front(temp);
  hitables_.push_front((Sphere*)temp);

  for(unsigned int i = 0; i < 40; ++i) {
    switch(i % 3) {
    case 0:
      dif_x += 1.1;
    // temp->set_color(i+40, i/2+40, i/2+40, 0);
      break;
    case 1:
      dif_x += 1.1;
    // temp->set_color(i/2+40, i+40, i/2+40, 0);
      break;
    case 2:
      dif_x -= 1.1;
      dif_y += 1.1;
    // temp->set_color(i/2+40, i/2+40, i+40, 0);
    }
    temp = new Sphere(dif_x, dif_y, 5.61);
    objects_.push_front(temp);
    hitables_.push_front((Sphere*)temp);
  }
  (*hitables_.begin())->set_moveable(false);
  ((Sphere*)*hitables_.begin())->set_color(123, 12, 12, 0);
selected_ = ((Sphere*)*hitables_.begin());
  temp = new Cube(2, -2, 5.9);
  temp->set_color(213, 123, 34, 0);
  temp->set_rotation_x(45);
  temp->set_rotation_z(45);
  objects_.push_front(temp);
  hitables_.push_front((Cube*)temp);
  (*hitables_.begin())->set_moveable(false);

  temp = new Cube(-2, 2, 5.61);
  temp->set_color(213, 123, 34, 0);
  temp->set_scale_y(0.25);
  objects_.push_front(temp);
  hitables_.push_front((Cube*)temp);
  (*hitables_.begin())->set_moveable(false);

  temp = new Cube(-4, 4, 5.71);
  temp->set_color(213, 123, 34, 0);
  temp->set_rotation_x(45);
  temp->set_rotation_z(45);
  temp->set_scale_y(0.25);
  objects_.push_front(temp);
  hitables_.push_front((Cube*)temp);
  (*hitables_.begin())->set_moveable(false);

  temp = new Cube(-1.25, -2, 5.32);
  temp->set_color(36, 156, 49, 0);
  temp->set_rotation_x(8);
  temp->set_rotation_y(-8);
  temp->set_rotation_z(45);
  temp->set_scale_x(2);
  temp->set_scale_y(2);
  temp->set_scale_z(0.01);
  objects_.push_front(temp);
  hitables_.push_front((Cube*)temp);
  (*hitables_.begin())->set_moveable(false);

  temp = new Table(0, 0, 0);
  // temp->set_rotation_y(45);
  table = (Table*)temp;
  temp->set_color(15, 36, 117, 0);
  objects_.push_front(temp);
  hitables_.push_front((Table*)temp);
  (*hitables_.begin())->set_moveable(false);

  temp = new Cube(0, 0, 0);
  temp->set_color(16, 75, 25, 0);
  temp->set_rotation_x(90);
  temp->set_scale_x(200);
  temp->set_scale_y(0.05);
  temp->set_scale_z(200);
  objects_.push_front(temp);
  hitables_.push_front((Cube*)temp);
  (*hitables_.begin())->set_moveable(false);
}

void make_buttons(GLFWwindow*& window) {
  Button* temp = nullptr;

  temp = new Button(0, 0, "./img/new.bmp");
  temp->set_color(0, 0, 1, 0);
  temp->set_color(1, 0, 0, 1);
  temp->set_scale(0.25);
  temp->set_on_release([temp]() {
    for(auto object : objects_) {
      delete object;
    }
    objects_.clear();
    hitables_.clear();
    make_objects();
  });
  mouse_callbacks_.push_front([temp](unsigned int button, unsigned int action,
                                     unsigned int x, unsigned int y) {
    if(button == 0) {
      if(action == GLFW_PRESS) {
        temp->on_press(x, y);
      } else if(action == GLFW_RELEASE) {
        temp->on_release(x, y);
      }
    }
  });
  buttons_.push_front(temp);

  temp = new Button(0, 64, "./img/Kugel.bmp");
  temp->set_color(0, 0, 1, 0);
  temp->set_color(1, 0, 0, 1);
  temp->set_scale(0.25);
  temp->set_on_release([temp]() {
    // TODO use modelview to get a better position
    Sphere* s = new Sphere(0, 0, 7);
    objects_.push_front(s);
    hitables_.push_front(s);
    selected_ = s;

    temp->set_color(0, 0, 1, 0);
  });
  mouse_callbacks_.push_front([temp](unsigned int button, unsigned int action,
                                     unsigned int x, unsigned int y) {
    if(button == 0) {
      if(action == GLFW_PRESS) {
        temp->on_press(x, y);
      } else if(action == GLFW_RELEASE) {
        temp->on_release(x, y);
      }
    }
  });
  buttons_.push_front(temp);

  temp = new Button(0, 128, "./img/exit.bmp");
  temp->set_color(0, 0, 1, 0);
  temp->set_color(1, 0, 0, 1);
  temp->set_scale(0.25);
  temp->set_on_release([temp, window]() {
    glfwSetWindowShouldClose(window, GL_TRUE);
  });
  mouse_callbacks_.push_front([temp](unsigned int button, unsigned int action,
                                     unsigned int x, unsigned int y) {
    if(button == 0) {
      if(action == GLFW_PRESS || action == GLFW_REPEAT) {
        temp->on_press(x, y);
      } else if(action == GLFW_RELEASE) {
        temp->on_release(x, y);
      }
    }
  });
  buttons_.push_front(temp);
}

/**
 * The function will call the draw method from all drawable objects
 */
void draw() {
  for(auto drawable : objects_) {
    drawable->draw();
  }
}

void drawButtons() {
  for(auto button : buttons_) {
    button->draw();
  }
}

GLVector<XYZW> mouse_pos_to_world(const GLMatrix& modelXprojectionINV,
                                  GLint* viewport, GLVector<XYZW> pos) {
  pos[1] = viewport[3] - pos[1];

  // Transformation of normalized coordinates between -1 and 1
  pos[0] = ((pos[0] - viewport[0]) / viewport[2]) * 2.0 - 1.0;
  pos[1] = ((pos[1] - viewport[1]) / viewport[3]) * 2.0 - 1.0;
  pos[2] = pos[2] * 2.0 - 1.0;
  pos[3] = 1.0;

  // Objects coordinates

  GLVector<XYZW> res = modelXprojectionINV * pos;

  assert(res[3] != 0.0);

  res[0] /= res[3];
  res[1] /= res[3];
  res[2] /= res[3];
  return res;
}

void debug_line(GLFWwindow* window, const GLVector<XYZW>& a,
                const GLVector<XYZW>& b) {
  if(speed_button_pressed_ && glfwGetMouseButton(window, 0) == GLFW_PRESS) {
    // This prevents clipping with the near plane
    GLMatrix model;
    glGetDoublev(GL_MODELVIEW_MATRIX, model);

    // Retrieve projection matrix
    GLMatrix projection;
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    GLMatrix mp = model.transpose() * projection.transpose();
    const GLVector<XYZW> clip = projection * GLVector<XYZW>::ZVec * 0.0001;

    glDisable(GL_LIGHTING);
    glColor3f(1, 0, 0);
    glLineWidth(4);

    glBegin(GL_LINES);
    glVertex3dv(a + clip);
    glVertex3dv(b + clip);
    glEnd();

    glLineWidth(1);
    glEnable(GL_LIGHTING);
  }
}

void mouse_interaction(GLFWwindow* window) {
  // Retrieve model view matrix
  GLMatrix model;
  glGetDoublev(GL_MODELVIEW_MATRIX, model);

  // Retrieve projection matrix
  GLMatrix projection;
  glGetDoublev(GL_PROJECTION_MATRIX, projection);

  GLMatrix mp = model.transpose() * projection.transpose();

  if(mp.inverse()) {
    // Retrieve current cursor position
    double x_pos, y_pos;
    glfwGetCursorPos(window, &x_pos, &y_pos);

    // Build vector of old cursor position
    GLVector<XYZW> mouse_press;
    mouse_press[0] = mouse_down_x_;
    mouse_press[1] = mouse_down_y_;
    mouse_press[2] = 0;

    // Build vector of current cursor position
    GLVector<XYZW> mouse_current;
    mouse_current[0] = x_pos;
    mouse_current[1] = y_pos;
    mouse_current[2] = 0;

    // Retrieve viewport matrix
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    mouse_press = mouse_pos_to_world(mp, viewport, mouse_press);
    mouse_current = mouse_pos_to_world(mp, viewport, mouse_current);

    if(speed_button_pressed_) {
      debug_line(window, mouse_press, mouse_current);

      if(glfwGetMouseButton(window, 0) != GLFW_PRESS) {
        speed_button_pressed_ = false;

        GLVector<XYZW> direction_speed = (mouse_press - mouse_current)
                                         / mouse_divider_;
        direction_speed[2] = 0;

        interactive->add_speed(direction_speed / mouse_divider_);
      }
    }
  }
}

int main() {
  GLFWwindow* window = nullptr;
  int error = 0;

  printf("Here we go!\n\n\
Control newly created Objects via:\n\
  Movement:\n\
    w x-axis +\n\
    s x-axis -\n\
    d y-axis +\n\
    a y-axis -\n\
    e z-axis +\n\
    q z-axis -\n\
  Scale:\n\
    r x-axis +\n\
    R x-axis -\n\
    f y-axis +\n\
    F y-axis -\n\
    v z-axis +\n\
    V z-axis -\n\
  Rotate:\n\
    t x-axis +\n\
    T x-axis -\n\
    g y-axis +\n\
    G y-axis -\n\
    b z-axis +\n\
    B z-axis -\n\
\n\
  Stop Sphere from moving:\n\
    m\n");

  if((error = init_glfw(window)) != 0) {
    return error;
  }

  make_objects();
  make_buttons(window);

  Physic phy(&hitables_);
  phy.start();

  while(!glfwWindowShouldClose(window)) {
    init_view();
    init_lighting();

    draw();
    drawButtons();
    mouse_interaction(window);

    calcFPS(1, window, "Simple 3D Animation");

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  phy.stop();

  glfwTerminate();

  for(auto object : objects_) {
    delete object;
  }
  for(auto button : buttons_) {
    delete button;
  }

  printf("Goodbye!\n");

  return 0;
}
