#pragma once

#include "esphome/core/component.h"
#include "esphome/components/cover/cover.h"

namespace esphome {
namespace somfy_cover {

class SomfyCoverHub : public Component {
 private:
   byte gdo0_, gdo2_, csn_, sck_, mosi_, miso_;

 public:
  void register_cover(cover::Cover *obj) { this->covers_.push_back(obj); }
  void setup() override;
  void dump_config() override;

  inline void set_gdo0(byte gdo0) {
    gdo0_ = gdo0;
  }
  inline void set_gdo2(byte gdo2) {
    gdo2_ = gdo2;
  }
  inline void set_csn(byte csn) {
    csn_ = csn;
  }
  inline void set_sck(byte sck) {
    sck_ = sck;
  }
  inline void set_mosi(byte mosi) {
    mosi_ = mosi;
  }
  inline void set_miso(byte miso) {
    miso_ = miso;
  }

  inline byte get_gdo0() const {
    return gdo0_;
  }
  
 protected:
  std::vector<cover::Cover *> covers_;
};

} //namespace somfy_cover_hub
} //namespace esphome
