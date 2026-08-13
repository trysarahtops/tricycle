#ifndef CYCLUS_TRICYCLE_STRT_UP_POLICY_H_
#define CYCLUS_TRICYCLE_STRT_UP_POLICY_H_

#include <string>
#include <vector>
#include "cyclus.h"

#include "material.h"
using cyclus::toolkit::ResBuf;
using cyclus::Material;

namespace tricycle {

/// StartupPolicy tracks an arbitrary number of resource inventories
/// (cyclus::toolkit::ResBuf<Material>) and determines whether ALL of them
/// have reached or exceeded a caller-specified quantity threshold. It's
/// meant to gate an archetype's ability to "start up" (begin producing,
/// begin trading, etc.) until every tracked material stockpile is
/// sufficiently stocked.
///
/// Thresholds are typically driven by user input via #pragma cyclus var
/// state variables on the archetype -- see startup_policy_snippet.cycpp.h
/// for the standard way to expose them in an input file. This class itself
/// holds no #pragma cyclus var state; it's a plain (non-Agent) toolkit
/// helper, consistent with other Cyclus toolkit capability classes.
///
/// Typical use in an archetype:
///
///   // my_facility.h (private section)
///   #include "toolkit/startup_policy.h"
///   #include "toolkit/startup_policy_snippet.cycpp.h"
///   cyclus::toolkit::ResBuf<cyclus::Material> feed_inv;
///   cyclus::toolkit::ResBuf<cyclus::Material> topup_inv;
///   cyclus::toolkit::StartupPolicy startup_policy;
///
///   // my_facility.cc
///   void MyFacility::EnterNotify() {
///     cyclus::Facility::EnterNotify();
///     std::map<std::string, ResBuf<Material>*> bufs;
///     bufs["feed"] = &feed_inv;
///     bufs["topup"] = &topup_inv;
///     for (int i = 0; i < startup_commods.size(); ++i) {
///       startup_policy.Register(startup_commods[i], bufs[startup_commods[i]],
///                                startup_thresholds[i]);
///     }
///   }
///
///   void MyFacility::Tick() {
///     if (!startup_policy.full()) {
///       return;  // one or more tracked inventories not yet at threshold
///     }
///     // ... normal operation ...
///   }
class StartupPolicy {
 public:
  StartupPolicy() = default;
  ~StartupPolicy() = default;

  /// Registers a resource buffer to be tracked by this policy. `name` is
  /// an arbitrary label used only for lookup/Unregister (e.g. a commodity
  /// or inventory name); `buf` is the inventory to watch; `threshold` is
  /// the minimum quantity that buf must reach (buf->quantity() >=
  /// threshold) for this tracker to be considered satisfied.
  ///
  /// The StartupPolicy does not own `buf` -- the archetype must keep the
  /// ResBuf alive for as long as it is registered.
  ///
  /// Throws cyclus::ValueError if `name` is already registered. Call
  /// Unregister(name) first (or check via full(name)/n_trackers()) if you
  /// intend to replace an existing tracker.
  void Register(std::string name, ResBuf<Material>* buf, double threshold);

  /// Removes a previously registered tracker by name. No-op if the name
  /// isn't currently tracked.
  void Unregister(const std::string& name);

  /// Returns true only if every registered inventory's current quantity
  /// is at or above its registered threshold. If nothing has been
  /// registered, returns true (vacuously) -- callers relying on this
  /// policy to gate startup should register at least one tracker.
  bool full() const;

  /// Convenience accessor: is a specific tracked inventory (by name) at
  /// or above its threshold? Returns false if `name` isn't registered.
  bool full(const std::string& name) const;

  /// Number of trackers currently registered.
  int n_trackers() const;
  void UpdateThreshold(const std::string& name, double new_threshold);

 private:
  FRIEND_TEST(FusionPowerPlantTest, StartupPolicyRegistration);
   struct Tracker {
    Tracker(ResBuf<Material>* buf_, double threshold_)
        : buf(buf_), threshold(threshold_) {}
    ResBuf<Material>* buf;
    double threshold;
  };

  std::map<std::string,Tracker> trackers_;
};

}  // namespace tricycle

#endif  // CYCLUS_TRICYCLE_STRT_UP_POLICY_H_
