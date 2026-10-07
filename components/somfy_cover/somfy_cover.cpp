#include "esphome/core/log.h"
#include "somfy_cover.h"

namespace esphome {
namespace somfy_cover {

static const char *TAG = "somfy_cover.cover";

#define COVER_OPEN 1.0f
#define COVER_CLOSED 0.0f

void SomfyCover::setup() {}

void SomfyCover::loop() {}

void SomfyCover::configure(const char* key, uint32_t remoteCode, const SomfyCoverHub* hub) {
  storage = new NVSRollingCodeStorage("somfy", key);
  remote = new SomfyRemote(hub->get_gdo0(), remoteCode, storage);
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
      sendCC1101Command(Command::Up);
    } else if (pos == COVER_CLOSED) {
      ESP_LOGI(TAG, "CLOSE");
      sendCC1101Command(Command::Down);
    } else {
      ESP_LOGI(TAG, "WAT");
    }

    this->position = pos;
    this->publish_state();
  }

  if (call.get_stop()) {
    ESP_LOGI(TAG, "STOP");
    sendCC1101Command(Command::My);
  }
}

void SomfyCover::sendCC1101Command(Command command) {
  ELECHOUSE_cc1101.SetTx();
  remote->sendCommand(command);
  ELECHOUSE_cc1101.setSidle();
}

}  // namespace somfy_cover
}  // namespace esphome
