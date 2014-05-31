#include "include/physic.hpp"
#include "include/hitable.hpp"

Physic::Physic() {
}

Physic::Physic(std::forward_list<Hitable*> objects) {
  for(auto object : objects) {
    for(auto box : object->bounding_box_list) {
      boxes_.push_front(box);
    }
  }
}

Physic::~Physic() {
}

void Physic::collision() {
  using Inter = std::forward_list<BoundingBox*>::iterator;
  const Inter end = boxes_.end();

  for(Inter i = boxes_.begin(); i != end; ++i) {
    (*i)->hitable_->step();

    if((*i)->collide_) {
      SphereBB* s1 = dynamic_cast<SphereBB*>(*i);
      OBB* o1 = (s1 == nullptr) ? dynamic_cast<OBB*>(*i) : nullptr;

      for(Inter j = i; j != end; ++j) {
        if(*i != *j) {
          SphereBB* s2 = dynamic_cast<SphereBB*>(*j);
          OBB* o2 = (s2 == nullptr) ? dynamic_cast<OBB*>(*j) : nullptr;

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
  }
}

void Physic::collision(SphereBB& a, SphereBB& b) {
  if(&a != &b) {
    const GLVector<XYZW> distance = *a.origin_ - *b.origin_;
    const double distance_length_sq = distance.Length2();
    const double orgin_length_sq
        = [](double x) { return x * x; }(a.radius_ + b.radius_);

    if(distance_length_sq < orgin_length_sq) {
      GLVector<XYZW> n = distance;
      n.Normalize();

      if(a.hitable_->is_moveable() && b.hitable_->is_moveable()) {
        // Calculate new speed direction
        const GLVector<XYZW> a_speed = a.hitable_->speed_;
        {
          const GLVector<XYZW> a_sub_b = *a.origin_ - *b.origin_;
          a.hitable_->speed_ -= ((a_speed - b.hitable_->speed_) * a_sub_b
                                 / a_sub_b.Length2()) * a_sub_b;
        }
        {
          const GLVector<XYZW> b_sub_a = *b.origin_ - *a.origin_;
          b.hitable_->speed_ -= ((b.hitable_->speed_ - a_speed) * b_sub_a
                                 / b_sub_a.Length2()) * b_sub_a;
        }

        // Move objects out of each other
        const GLVector<XYZW> half_intersection
            = (distance - n * b.radius_ - n * a.radius_) / 2;
        *a.origin_ -= half_intersection;
        *b.origin_ += half_intersection;
      } else if(a.hitable_->is_moveable()) {
        // Mirror speed
        a.hitable_->speed_ -= 2 * (a.hitable_->speed_ * n) * n;

        // Move object out of the unmoveable one
        *a.origin_ -= (distance - n * b.radius_ - n * a.radius_);
      } else if(b.hitable_->is_moveable()) {
        // Mirror speed
        b.hitable_->speed_ -= 2 * (b.hitable_->speed_ * n) * n;

        // Move object out of the unmoveable one
        *b.origin_ += (distance - n * b.radius_ - n * a.radius_);
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
  const GLVector<XYZW> distance = closest - *a.origin_;
  const double distance_length_sq = distance.Length2();

  if(distance_length_sq < a.radius_ * a.radius_) {
    GLVector<XYZW> n = distance;
    n.Normalize();

    if(a.hitable_->is_moveable() && b.hitable_->is_moveable()) {
      // Calculate new speed direction
      const GLVector<XYZW> a_speed = a.hitable_->speed_;
      const GLVector<XYZW> a_sub_b = *a.origin_ - *b.origin_;
      const GLVector<XYZW> b_sub_a = *b.origin_ - *a.origin_;

      a.hitable_->speed_ -= ((a_speed - b.hitable_->speed_) * a_sub_b
                             / a_sub_b.Length2()) * a_sub_b;
      b.hitable_->speed_ -= ((b.hitable_->speed_ - a_speed) * b_sub_a
                             / b_sub_a.Length2()) * b_sub_a;

      // Move objects out of each other
      const GLVector<XYZW> half_intersection = (distance - n * a.radius_) / 2;
      *a.origin_ += half_intersection;
      *b.origin_ -= half_intersection;
    } else if(a.hitable_->is_moveable()) {
      // Mirror speed
      a.hitable_->speed_ -= 2 * (a.hitable_->speed_ * n) * n;

      // Move object out of the unmoveable one
      *a.origin_ += (distance - n * a.radius_);
    } else if(b.hitable_->is_moveable()) {
      // Mirror speed
      b.hitable_->speed_ -=  2 * (b.hitable_->speed_ * n) * n;

      // Move object out of the unmoveable one
      *b.origin_ -= (distance - n * a.radius_);
    }
  }
}

void Physic::collision(OBB& a, SphereBB& b) {
  collision(b, a);
}

void Physic::collision(OBB& a, OBB& b) {
}
