#ifndef Button_HPP
#define Button_HPP value

#include "drawable.hpp"

class Button : public Drawable {
public:


	Button();
	Button(double origin_x, double origin_y, double origin_z);
	Button(double origin_x, double origin_y, double origin_z, unsigned char colors);
	~Button();
	virtual void draw();
};
#endif // ifndef Button_HPP
