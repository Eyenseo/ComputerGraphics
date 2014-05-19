#include "include/physic.hpp"
Physic::Physic() {}

Physic::~Physic() {}

void Physic::collision(std::forward_list<Hitable*>objects) {
  using Inter = std::forward_list<Hitable*>::iterator;
  const Inter end = objects.end();

  for(Inter i = objects.begin(); i != end; ++i) {
    SphereBB* s1 = dynamic_cast<SphereBB*>(*i);
    OBB*     o1 = (s1 == nullptr) ? dynamic_cast<OBB*>(*i) : nullptr;

    for(Inter j = i; j != end; ++j) {
      SphereBB* s2 = dynamic_cast<SphereBB*>(*j);
      OBB*     o2 = (s2 == nullptr) ? dynamic_cast<OBB*>(*j) : nullptr;

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
    const GLVector<XYZW> vec = *a.origin_ - *b.origin_;
    GLVector<XYZW> n   = vec;
    n.Normalize();

    if(vec * n < 1 && vec * n > 0) {  // TODO replace with real radius
      const GLVector<XYZW> so = a.speed_;
      const GLVector<XYZW> po = b.speed_;
      {
        const double buff1 = (so - po) * (*a.origin_ - *b.origin_);
        const double buff2 = (*a.origin_ - *b.origin_).Length2();
        a.speed_ -= (buff1 / buff2) * (*a.origin_ - *b.origin_);
      }
      {
        const double buff1 = (po - so) * (*b.origin_ - *a.origin_);
        const double buff2 = (*b.origin_ - *a.origin_).Length2();
        b.speed_ -= (buff1 / buff2) * (*b.origin_ - *a.origin_);
      }
    }
  }
}

GLVector<XYZW> Physic::closest_point_on_OBB(const GLVector<XYZW>& a,
                                            const OBB& b) {
  GLVector<XYZW> d = a - *b.origin_;

  GLVector<XYZW> closest = *b.origin_;

  // For each OBB axis...
  for(int i = 0; i < 3; i++) {
    double dist = d * b.local_axis_[i];

    if(dist > b.half_length_[i]) {
      dist = b.half_length_[i];
    }
    if(dist < -b.half_length_[i]) {
      dist = -b.half_length_[i];
    }

    closest += dist * b.local_axis_[i];
  }

  return closest;
}

void Physic::collision(SphereBB& a, OBB& b) {
  const GLVector<XYZW> closest = closest_point_on_OBB(*a.origin_, b);
 GLVector<XYZW> distance = closest - *a.origin_;

  if(distance * distance <= a.radius_ * a.radius_) {
    distance.Normalize();

    a.speed_ -= 2 * distance * (distance * a.speed_);
    a.speed_[2] = 0;
    a.speed_[3] = 0;
  }
}

void Physic::collision(OBB& a, SphereBB& b) {
  collision(b, a);
}

void Physic::collision(OBB& a, OBB& b) {

}
