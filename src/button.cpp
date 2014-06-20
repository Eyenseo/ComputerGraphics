#include "include/button.hpp"

#include<iostream>
#include <sstream>

Button::Button()
  : Drawable() {}

Button::Button(double origin_x, double origin_y, double origin_z)
  : Drawable(origin_x, origin_y, origin_z) {}

Button::Button(double origin_x, double origin_y, double origin_z,
           unsigned char colors)
  : Drawable(origin_x, origin_y, origin_z, colors)  {}

Button::~Button() {}


void Button::draw() {
	GLVector<XYZW> bottom_left  = GLVector<XYZW>(-.5, -.5, 0, 1);
	  GLVector<XYZW> top_left     = GLVector<XYZW>(-.5, .5, 0, 1);
	  GLVector<XYZW> top_right    = GLVector<XYZW>(.5, .5, 0, 1);
	  GLVector<XYZW> bottom_right = GLVector<XYZW>(.5, -.5, 0, 1);

	  auto face
	    = [&](const GLVector<XYZW>& v1, const GLVector<XYZW>& v2,
	          const GLVector<XYZW>& v3, const GLVector<XYZW>& v4) {
	        GLVector<XYZ> normal = (v2 - v1) % (v3 - v1);


	        glPushMatrix();
	        glEnable(GL_TEXTURE_2D); //Enable texture
	        glBindTexture(GL_TEXTURE_2D,image);
	        glBegin(GL_QUADS);
	        normal.Normalize();
	        glNormal3dv(normal);
	        glTexCoord2f(0,1);
	        glVertex3dv(v1);
	        glTexCoord2f(1,1);
	        glVertex3dv(v2);
	        glTexCoord2f(1,0);
	        glVertex3dv(v3);
	        glTexCoord2f(0,0);
	        glVertex3dv(v4);
	        glEnd();
	        glPopMatrix();
	        glDisable(GL_TEXTURE_2D);

	      };
	  //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	  //glClear(GL_COLOR_BUFFER_BIT);
	  //glEnable(GL_DEPTH_TEST);
	  //glClear(GL_DEPTH_BUFFER_BIT);
	  //glFlush();

	  // faces_->clear();

	  set_material_color(0, 0);

	  // glEnable(GL_RESCALE_NORMAL); // TODO Needed?

	  glMatrixMode(GL_MODELVIEW);
	  rotate_from(rotation_[0], rotation_[1], rotation_[2],
	              origin_[0], origin_[1], origin_[2]);
	  glScalef(scale_[0], scale_[1], scale_[2]);

	  glGetDoublev(GL_MODELVIEW_MATRIX, model_view);


	  // Bottom
	  rotate_from(0, 0, 0, 0, 0, 0);
	  face(top_left, top_right, bottom_right, bottom_left);
	  glEnd();

}
