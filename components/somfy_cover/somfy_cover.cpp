#include "esphome/core/log.h"
#include "somfy_cover.h"

namespace esphome {
namespace somfy_cover {

static const char *TAG = "somfy_cover.cover";

#define COVER_OPEN 1.0f
#define COVER_CLOSED 0.0f

void SomfyCover::setup() {}

void SomfyCover::loop() {}

void SomfyCover::configure(const char* key, uint32_t remote_code, const SomfyCoverHub* hub) {
  this->storage_ = new NVSRollingCodeStorage("somfy", key);
  this->remote_ = new SomfyRemote(hub->get_gdo0(), remote_code, this->storage_);
}

void SomfyCover::dump_config() {
    ESP_LOGCONFIG(TAG, "Somfy cover");
}

cover::CoverTraits SomfyCover::get_traits() {
    auto traits = cover::CoverTraits();
    traits.set_is_assumed_state(true);
    traits.set_supports_position(false);
    traits.set_supports_tilt(false);
    traits.set_supports_stop(true);
    return traits;
}

void SomfyCover::control(const cover::CoverCall &call) {
  if (call.get_position().has_value()) {
    float pos = *call.get_position();

    if (pos == COVER_OPEN) {
      ESP_LOGI(TAG, "OPEN");
      send_cc1101_command(Command::Up);
    } else if (pos == COVER_CLOSED) {
      ESP_LOGI(TAG, "CLOSE");
      send_cc1101_command(Command::Down);
    } else {
      ESP_LOGI(TAG, "WAT");
    }

    this->position = pos;
    this->publish_state();
  }

  if (call.get_stop()) {
    ESP_LOGI(TAG, "STOP");
    send_cc1101_command(Command::My);
  }
}

void SomfyCover::send_cc1101_command(Command command) {
  ELECHOUSE_cc1101.SetTx();
  this->remote_->sendCommand(command);
  ELECHOUSE_cc1101.setSidle();
}

}  // namespace somfy_cover
}  // namespace esphome
