// strt_up_policy.cycpp.h
//
// Include this in the private section of an archetype header (after
// #include "toolkit/startup_policy.h") to expose user-settable startup
// commodities/thresholds and declare the StartupPolicy member itself.
//
//   class MyFacility : public cyclus::Facility {
//     ...
//    private:
//     #include "toolkit/startup_policy_snippet.cycpp.h"
//   };
//
// The two vectors below are parallel: startup_thresholds[i] is the minimum
// quantity required of startup_commods[i] before the facility is allowed
// to start up. It is the archetype's responsibility (in EnterNotify) to
// map each commodity name to the ResBuf that actually tracks it and call
// startup_policy.Register(name, buf, threshold) for each pair -- the
// preprocessor can't infer that mapping automatically.

#pragma cyclus var { \
  "default": [], \
  "uilabel": "Startup Commodities", \
  "uitype": ["oneormore", "commodity"], \
  "doc": "Commodities whose inventories are tracked to determine whether " \
         "this facility is allowed to start up. Paired index-for-index " \
         "with startup_thresholds." }
std::vector<std::string> startup_commods;
// required for compilation but not added by the cycpp preprocessor...
std::vector<int> cycpp_shape_startup_commods;

#pragma cyclus var { \
  "default": [], \
  "uilabel": "Startup Thresholds", \
  "doc": "Minimum quantity required, for each commodity in " \
         "startup_commods (same order), before this facility is allowed " \
         "to start up." }
std::vector<double> startup_thresholds;
// required for compilation but not added by the cycpp preprocessor...
std::vector<int> cycpp_shape_startup_thresholds;

// The actual policy object. Not itself a #pragma cyclus var -- it's
// populated in EnterNotify() from the two vectors above plus the
// archetype's own ResBuf members.
cyclus::toolkit::StartupPolicy startup_policy;
