#include "strt_up_policy.h"

namespace tricycle {


StartupPolicy::StartupPolicy() {}

StartupPolicy::~StartupPolicy() {}

void StartupPolicy::Register(std::string name, ResBuf<Material>* buf,
                              double threshold) {
  trackers_.push_back(Tracker(name, buf, threshold));
}

void StartupPolicy::Unregister(const std::string& name) {
  for (std::vector<Tracker>::iterator it = trackers_.begin();
       it != trackers_.end(); ++it) {
    if (it->name == name) {
      trackers_.erase(it);
      return;
    }
  }
}

bool StartupPolicy::full() const {
  for (std::vector<Tracker>::const_iterator it = trackers_.begin();
       it != trackers_.end(); ++it) {
    if (it->buf->quantity() < it->threshold) {
      return false;
    }
  }
  return true;
}

bool StartupPolicy::full(const std::string& name) const {
  for (std::vector<Tracker>::const_iterator it = trackers_.begin();
       it != trackers_.end(); ++it) {
    if (it->name == name) {
      return it->buf->quantity() >= it->threshold;
    }
  }
  return false;
}

int StartupPolicy::n_trackers() const { return trackers_.size(); }

}  // namespace tricycle
