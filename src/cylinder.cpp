#include <GL/gl.h>
#include <include/cylinder.hpp>
#include <include/gl_vec.hpp>
#include <cmath>
//#include <iostream>
//#include <sstream>

Cylinder::Cylinder()
	: Drawable()
	, Hitable(){
	cb_ = new SphereBB(this, &origin_, 1.0);
	  add_bounding_box(cb_);
	}

Cylinder::Cylinder(double origin_x, double origin_y, double origin_z)
	: Drawable(origin_x, origin_y, origin_z)
	, Hitable(){
	cb_ = new SphereBB(this, &origin_, 1.0);
	  add_bounding_box(cb_);
	}

Cylinder::Cylinder(double origin_x, double origin_y, double origin_z,
           unsigned char colors)
	: Drawable(origin_x, origin_y, origin_z, colors)
	, Hitable(){
	cb_ = new SphereBB(this, &origin_, 1.0);
	  add_bounding_box(cb_);
	}

Cylinder::~Cylinder() {}

void Cylinder::step() {
   if(moveable_) {
    //TODO review slow speeds are a problem on edges
    speed_ = speed_ + (GLVector<XYZW>::ZVec * (-9.81 * 0.005))
             - (speed_ * fraction_);
    origin_ += speed_ * 0.16;
  }
}

void Cylinder::draw() {
	#ifndef M_PI
	#define M_PI 3.14159265359
	#endif
	int hoehe = 1;
	int durchmesser = 1;

	  set_material_color(1, 0);
	  set_material_color(2, 1);

	glEnable(GL_NORMALIZE);
	  rotate_from(rotation_[0], rotation_[1], rotation_[2], origin_[0], origin_[1], origin_[2]);
	  glScalef(scale_[0], scale_[1], scale_[2]);

	for( double angle = 0.0; angle < M_PI*4; angle += (M_PI / 360.0) ) {
		glBegin(GL_LINE_STRIP);
		glVertex3f( ( 0.5*(cos(angle)*durchmesser) ), ( (0) ), ( 0.5*(sin(angle)*durchmesser) ) );
		glVertex3f( ( 0.5*(cos(angle)*durchmesser) ), ( (hoehe) ), ( 0.5*(sin(angle)*durchmesser) ) );
		glVertex3f( (0.0 * ( cos( angle )) * 1 ), (0.0 * ( sin( angle ) * 1)) , 0);
	}
	glEnd ();
	glPopMatrix();
}

void Cylinder::set_rotation(const GLVector<XYZ>& rotation) {
  Drawable::set_rotation(rotation);
  obb_.update_rotation(rotation_);
}

void Cylinder::set_rotation(double rotation_x, double rotation_y,
                        double rotation_z) {
  Drawable::set_rotation(rotation_x, rotation_y, rotation_z);
  obb_.update_rotation(rotation_);
}

void Cylinder::set_rotation_x(double rotation) {
  Drawable::set_rotation_x(rotation);
  obb_.update_rotation(rotation_);
}

void Cylinder::set_rotation_y(double rotation) {
  Drawable::set_rotation_y(rotation);
  obb_.update_rotation(rotation_);
}

void Cylinder::set_rotation_z(double rotation) {
  Drawable::set_rotation_z(rotation);
  obb_.update_rotation(rotation_);
}

void Cylinder::set_scale(const GLVector<XYZ>& scale) {
  set_scale(scale[0], scale[1], scale[2]);
  obb_.update_scale(scale_);
}

void Cylinder::set_scale(double scale) {
  Drawable::set_scale(scale, scale, scale);
  obb_.update_scale(scale_);
}

void Cylinder::set_scale(double scale_x, double, double) {
  Drawable::set_scale(scale_x, scale_x, scale_x);
  obb_.update_scale(scale_);
}

void Cylinder::set_scale_x(double scale_x) {
  Drawable::set_scale(scale_x, scale_x, scale_x);
  obb_.update_scale(scale_);
}

void Cylinder::set_scale_y(double scale_y) {
  Drawable::set_scale(scale_y, scale_y, scale_y);
  obb_.update_scale(scale_);
}

void Cylinder::set_scale_z(double scale_z) {
  Drawable::set_scale(scale_z, scale_z, scale_z);
  obb_.update_scale(scale_);
}

