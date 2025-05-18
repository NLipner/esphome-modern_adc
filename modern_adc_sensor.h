#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace modern_adc {

class ModernADCSensor : public sensor::Sensor, public Component {
 public:
  void set_pin(uint8_t pin) { pin_ = pin; }
  void setup() override;
  void loop() override;

 protected:
  uint8_t pin_;
  int adc_handle_ = -1;
};

}  // namespace modern_adc
}  // namespace esphome