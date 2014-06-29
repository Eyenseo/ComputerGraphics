#ifndef Cylinder_HPP
#define Cylinder_HPP value

#include "drawable.hpp"
#include "hitable.hpp"
#include "obb.hpp"
#include "cylinderBB.hpp"

class Cylinder : public Drawable, public Hitable {
protected:
	OBB obb_;
	SphereBB* cb_;
	GLVector<XYZW>& origin_ = Drawable::origin_;

public:
	Cylinder();
	Cylinder(double origin_x, double origin_y, double origin_z);
	Cylinder(double origin_x, double origin_y, double origin_z, unsigned char colors);
	~Cylinder();

	virtual void draw();
	virtual void step();

	virtual void set_rotation(const GLVector<XYZ>& rotation);
	virtual void set_rotation(double rotation_x, double rotation_y,
							double rotation_z);
	virtual void set_rotation_x(double rotation);
	virtual void set_rotation_y(double rotation);
	virtual void set_rotation_z(double rotation);


	virtual void set_scale(const GLVector<XYZ>& scale);
	virtual void set_scale(double scale);
	virtual void set_scale(double scale_x, double scale_y, double scale_z);
	virtual void set_scale_x(double scale_x);
	virtual void set_scale_y(double scale_y);
	virtual void set_scale_z(double scale_z);
};
#endif // ifndef Cylinder_HPP
