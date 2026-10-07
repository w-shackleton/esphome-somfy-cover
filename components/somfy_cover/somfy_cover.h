#pragma once

#include "esphome/core/component.h"
#include "esphome/components/cover/cover.h"
#include "esphome/components/button/button.h"
#include "somfy_cover_hub.h"

#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <NVSRollingCodeStorage.h>
#include <SomfyRemote.h>

namespace esphome {
namespace somfy_cover {

class SomfyCover : public cover::Cover, public Component {
 private:
  SomfyRemote *remote;
  NVSRollingCodeStorage *storage;

 public:
  SomfyCover() : Cover(), remote(NULL), storage(NULL) {}
  ~SomfyCover() {
    delete remote;
    delete storage;
  }

  void configure(const char* key, uint32_t remoteCode, const SomfyCoverHub* hub);

  void setup() override;
  void loop() override;
  void dump_config() override;
  cover::CoverTraits get_traits() override;
  void sendCC1101Command(Command command);
  
 protected:
  void control(const cover::CoverCall &call) override;
};

class SomfyButton : public button::Button, public Component {
 private:
  Command command;
  SomfyCover *cover_;
 public:

  void setup() override {}
  void press_action() override {
    cover_->sendCC1101Command(command);
  }
  void dump_config() override {}

  void setCover(SomfyCover* cover) {
    cover_= cover;
  }

  void setProgram() {
    command = Command::Prog;
  }

  void setUpDown() {
    command = Command::UpDown;
  }
};

}  // namespace somfy_cover
}  // namespace esphome
