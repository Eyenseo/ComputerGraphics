#include "include/physic.hpp"
Physic::Physic() {}

Physic::~Physic() {}

void Physic::collision(std::forward_list<Hitable*>objects) {
  using Inter = std::forward_list<Hitable*>::iterator;
  const Inter end = objects.end();

  for(Inter i = objects.begin(); i != end; ++i) {
    SphereBB* s1 = dynamic_cast<SphereBB*>(*i);
    OOBB*     o1 = (s1 == nullptr) ? dynamic_cast<OOBB*>(*i) : nullptr;

    for(Inter j = i; j != end; ++j) {
      SphereBB* s2 = dynamic_cast<SphereBB*>(*j);
      OOBB*     o2 = (s2 == nullptr) ? dynamic_cast<OOBB*>(*j) : nullptr;

      if(s1 != nullptr && s2 != nullptr) {
        collision(*s1, *s2);
      } else if(o1 != nullptr && o2 != nullptr) {
        collision(*o1, *o2);
      } else if(s1 != nullptr && o2 != nullptr) {
        collision(*s1, *o2);
      } else {
        collision(*s2, *o1);
      }
    }
  }
}

void Physic::collision(SphereBB& a, SphereBB& b) {
  if(&a != &b) {
    GLVector<XYZW> vec = *a.origin_ - *b.origin_;
    GLVector<XYZW> n   = vec;
    n.Normalize();

    if(vec * n < 1 && vec * n > 0) {
      GLVector<XYZW> so = a.speed_;
      GLVector<XYZW> po = b.speed_;
      double buff1;
      double buff2;

      buff1     = (so - po) * (*a.origin_ - *b.origin_);
      buff2     = (*a.origin_ - *b.origin_).Length2();
      a.speed_ -= (buff1 / buff2) * (*a.origin_ - *b.origin_);

      buff1     = (po - so) * (*b.origin_ - *a.origin_);
      buff2     = (*b.origin_ - *a.origin_).Length2();
      b.speed_ -= (buff1 / buff2) * (*b.origin_ - *a.origin_);
    }
  }
}

void Physic::collision(SphereBB& a, OOBB& b) {
  // auto fun7 = [&](Sphere& s) {
  //// table box
  // struct Face {
  // GLVector<XYZW> a;
  // GLVector<XYZW> b;
  // GLVector<XYZW> c;
  // GLVector<XYZW> d;
  // GLVector<XYZW> n;

  // Face(GLVector<XYZW>&& A, GLVector<XYZW>&& B,
  // GLVector<XYZW>&& C, GLVector<XYZW>&& D)
  // : a(A), b(B), c(C), d(D) {
  // GLVector<XYZ> buff = (b - a) % (c - a);
  // buff.Normalize();
  // n[0] = buff[0];
  // n[1] = buff[1];
  // n[2] = buff[2];
  // n[3] = 1;
  // n   *= -1;
  // }
  // };

  // static Face left
  // = Face(GLVector<XYZW>(-7, 5, 6,
  // 1), GLVector<XYZW>(-7, -5, 6, 1),
  // GLVector<XYZW>(-7, -5, 5,
  // 1), GLVector<XYZW>(-7, 5, 5, 1));
  // static Face bottom
  // = Face(GLVector<XYZW>(-7, -5, 6,
  // 1), GLVector<XYZW>(7, -5, 6, 1),
  // GLVector<XYZW>(7, -5, 5,
  // 1), GLVector<XYZW>(-7, -5, 5, 1));
  // static Face right
  // = Face(GLVector<XYZW>(7, -5, 6,
  // 1), GLVector<XYZW>(7, 5, 6, 1),
  // GLVector<XYZW>(7, 5, 5,
  // 1), GLVector<XYZW>(7, -5, 5, 1));
  // static Face top
  // = Face(GLVector<XYZW>(7, 5, 6,
  // 1), GLVector<XYZW>(-7, 5, 6, 1),
  // GLVector<XYZW>(-7, 5, 5,
  // 1), GLVector<XYZW>(7, 5, 5, 1));

  //// auto gun = [&](Face& f) {
  //// fun6({1, 0, 0});
  //// glLineWidth(4);
  //// glBegin(GL_LINES);
  //// glVertex3dv(f.a);
  //// glVertex3dv(f.b);
  //// glVertex3dv(f.b);
  //// glVertex3dv(f.c);
  //// glVertex3dv(f.c);
  //// glVertex3dv(f.d);
  //// glVertex3dv(f.d);
  //// glVertex3dv(f.a);
  //// glEnd();
  //// glLineWidth(1);
  //// };
  ////// hitbox
  //// gun(left);
  //// gun(bottom);
  //// gun(right);
  //// gun(top);

  // auto hun = [&](Face& f) {
  // GLVector<XYZW> vec = f.a - s.origin_;

  // if(vec * f.n < .5 && vec * f.n > -.5) { // 1 = sphere radius
  // double dot_wall_speed = f.n * s.speed;
  // s.speed   -= 2 * f.n * dot_wall_speed;
  // s.speed[2] = 0;
  // s.speed[3] = 0;
  // }
  // };

  // hun(left);
  // hun(bottom);
  // hun(right);
  // hun(top);
  // };
}

void Physic::collision(OOBB& a, SphereBB& b) {
  collision(b, a);
}

void Physic::collision(OOBB& a, OOBB& b) {}
