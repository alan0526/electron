// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_API_ATOM_API_POWER_MONITOR_H_
#define ATOM_BROWSER_API_ATOM_API_POWER_MONITOR_H_

#include "atom/browser/api/trackable_object.h"
#include "atom/browser/lib/power_observer.h"
#include "base/compiler_specific.h"
#include "native_mate/handle.h"
#include "ui/base/idle/idle.h"

namespace atom {

namespace api {

class PowerMonitor : public mate::TrackableObject<PowerMonitor>,
                     public PowerObserver {
 public:
  static v8::Local<v8::Value> Create(v8::Isolate* isolate);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  explicit PowerMonitor(v8::Isolate* isolate);
  ~PowerMonitor() override;

  // Called by native calles.
  bool ShouldShutdown();

#if defined(OS_LINUX)
  // Private JS APIs.
  void BlockShutdown();
  void UnblockShutdown();
#endif

  // base::PowerObserver implementations:
  void OnPowerStateChange(bool on_battery_power) override;
  void OnSuspend() override;
  void OnResume() override;

 private:
  void QuerySystemIdleState(v8::Isolate* isolate,
                            int idle_threshold,
                            const ui::IdleCallback& callback);
  void QuerySystemIdleTime(const ui::IdleTimeCallback& callback);

  DISALLOW_COPY_AND_ASSIGN(PowerMonitor);
};

}  // namespace api

}  // namespace atom

#endif  // ATOM_BROWSER_API_ATOM_API_POWER_MONITOR_H_
