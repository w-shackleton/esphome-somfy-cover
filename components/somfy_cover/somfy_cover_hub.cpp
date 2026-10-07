#include "somfy_cover_hub.h"
#include "esphome/components/cover/cover.h"
#include <ELECHOUSE_CC1101_SRC_DRV.h>

#define CC1101_FREQUENCY 433.42

namespace esphome {
namespace somfy_cover {

static const char *TAG = "somfy_cover_hub.component";

void SomfyCoverHub::setup(){
    ELECHOUSE_cc1101.setSpiPin(sck_, miso_, mosi_, csn_);
    ELECHOUSE_cc1101.setGDO(gdo0_, gdo2_);
    digitalWrite(gdo0_, LOW);
    ELECHOUSE_cc1101.Init();
    ELECHOUSE_cc1101.setMHZ(CC1101_FREQUENCY);
}

void SomfyCoverHub::dump_config(){
    for (auto *cover : this->covers_) {
        LOG_COVER("  ", "Cover", cover);
    }
}

} //namespace somfy_cover_hub
} //namespace esphome
