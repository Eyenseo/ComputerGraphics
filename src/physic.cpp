#include "include/physic.hpp"
#include "include/hitable.hpp"

Physic::Physic()
    : hitables_(nullptr) {
}

Physic::Physic(std::forward_list<Hitable*>* hitables)
    : hitables_(hitables) {
}

Physic::~Physic() {
}

void Physic::collision(Hitable* h) {
  if(h->is_hitable()) {
    for(auto& hitable : *hitables_) {
      if(h != hitable && hitable->is_hitable()) {
        std::unique_lock<std::mutex>(hitable->m_);

        for(auto& other_box : hitable->bounding_box_list_) {
          SphereBB* s1 = dynamic_cast<SphereBB*>(other_box);
          OBB* o1 = (s1 == nullptr) ? dynamic_cast<OBB*>(other_box) : nullptr;
          std::unique_lock<std::mutex>(h->m_);

          for(auto& h_box : h->bounding_box_list_) {
            SphereBB* s2 = dynamic_cast<SphereBB*>(h_box);
            OBB* o2 = (s2 == nullptr) ? dynamic_cast<OBB*>(h_box) : nullptr;

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
      b.hitable_->speed_ -= 2 * (b.hitable_->speed_ * n) * n;

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
