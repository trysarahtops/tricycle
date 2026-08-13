#include "strt_up_policy.h"

#include "error.h"

namespace tricycle {

void StartupPolicy::Register(std::string name, ResBuf<Material>* buf,
                              double threshold) {
  if (trackers_.find(name) != trackers_.end()) {
    throw cyclus::ValueError(
        "StartupPolicy::Register: tracker '" + name +
        "' is already registered. Call Unregister(name) first, or use "
        "UpdateThreshold(), if you intend to replace or adjust it.");
  }
  trackers_.emplace(name, Tracker(buf, threshold));
}

void StartupPolicy::Unregister(const std::string& name) {
  trackers_.erase(name);
}

void StartupPolicy::UpdateThreshold(const std::string& name,
                                     double new_threshold) {
  std::map<std::string, Tracker>::iterator it = trackers_.find(name);
  if (it == trackers_.end()) {
    throw cyclus::ValueError(
        "StartupPolicy::UpdateThreshold: no tracker registered under '" +
        name + "'.");
  }
  it->second.threshold = new_threshold;
}

bool StartupPolicy::full() const {
  for (std::map<std::string, Tracker>::const_iterator it = trackers_.begin();
       it != trackers_.end(); ++it) {
    if (it->second.buf->quantity() < it->second.threshold) {
      return false;
    }
  }
  return true;
}

bool StartupPolicy::full(const std::string& name) const {
  std::map<std::string, Tracker>::const_iterator it = trackers_.find(name);
  if (it == trackers_.end()) {
    return false;
  }
  return it->second.buf->quantity() >= it->second.threshold;
}

int StartupPolicy::n_trackers() const { return trackers_.size(); }

}  // namespace tricycle