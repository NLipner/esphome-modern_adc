import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_NAME, CONF_PIN, CONF_ID

modern_adc_ns = cg.esphome_ns.namespace("modern_adc")
ModernADCSensor = modern_adc_ns.class_("ModernADCSensor", sensor.Sensor, cg.Component)

CONFIG_SCHEMA = sensor.sensor_schema().extend({
    cv.Required(CONF_PIN): cv.pin,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await sensor.register_sensor(var, config)
    cg.add(var.set_pin(config[CONF_PIN]))
    cg.add(var.set_name(config[CONF_NAME]))