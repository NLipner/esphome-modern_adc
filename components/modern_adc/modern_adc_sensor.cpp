#include "modern_adc_sensor.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"

namespace esphome {
namespace modern_adc {

static const char *TAG = "modern_adc";

void ModernADCSensor::setup() {
  adc_oneshot_unit_handle_t handle;
  adc_oneshot_unit_init_cfg_t init_config = {
      .unit_id = ADC_UNIT_1,
  };
  adc_oneshot_new_unit(&init_config, &handle);

  adc_oneshot_chan_cfg_t config = {
      .atten = ADC_ATTEN_DB_6,
      .bitwidth = ADC_BITWIDTH_DEFAULT,
  };
  adc_oneshot_config_channel(handle, static_cast<adc_channel_t>(pin_), &config);
  this->adc_handle_ = reinterpret_cast<int>(handle);
}

void ModernADCSensor::loop() {
  int raw = 0;
  adc_oneshot_unit_handle_t handle = reinterpret_cast<adc_oneshot_unit_handle_t>(adc_handle_);
  adc_oneshot_read(handle, static_cast<adc_channel_t>(pin_), &raw);
  float voltage = raw * 3.3f / 4095.0f;
  ESP_LOGD(TAG, "ADC Reading: %d -> Voltage: %.3f", raw, voltage);
  publish_state(voltage);
}

}  // namespace modern_adc
}  // namespace esphome