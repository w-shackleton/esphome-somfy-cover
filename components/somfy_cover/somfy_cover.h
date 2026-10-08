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
  SomfyRemote *remote_;
  NVSRollingCodeStorage *storage_;

 public:
  SomfyCover() : Cover(), remote_(NULL), storage_(NULL) {}
  ~SomfyCover() {
    delete this->remote_;
    delete this->storage_;
  }

  void configure(const char* key, uint32_t remote_code, const SomfyCoverHub* hub);

  void setup() override;
  void loop() override;
  void dump_config() override;
  cover::CoverTraits get_traits() override;
  void send_cc1101_command(Command command);
  
 protected:
  void control(const cover::CoverCall &call) override;
};

class SomfyButton : public button::Button, public Component {
 private:
  Command command_;
  SomfyCover *cover_;
 public:

  void setup() override {}

  void press_action() override {
    this->cover_->send_cc1101_command(this->command_);
  }

  void dump_config() override {}

  void setCover(SomfyCover* cover) {
    this->cover_= cover;
  }

  void setProgram() {
    this->command_ = Command::Prog;
  }

  void setUpDown() {
    this->command_ = Command::UpDown;
  }
};

}  // namespace somfy_cover
}  // namespace esphome
