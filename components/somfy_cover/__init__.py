import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

MULTI_CONF = True
AUTO_LOAD = ["button"]

CONF_SOMFY_COVER_HUB_ID = "somfy_cover_hub_id"

CONF_GDO0 = "gdo0"
CONF_GDO2 = "gdo2"
CONF_CSN = "csn"
CONF_SCK = "sck"
CONF_MOSI = "mosi"
CONF_MISO = "miso"

somfy_cover_ns = cg.esphome_ns.namespace("somfy_cover")
SomfyCoverHub = somfy_cover_ns.class_("SomfyCoverHub", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SomfyCoverHub),
        cv.Required(CONF_GDO0): cv.port,
        cv.Required(CONF_GDO2): cv.port,
        cv.Required(CONF_CSN): cv.port,
        cv.Required(CONF_SCK): cv.port,
        cv.Required(CONF_MOSI): cv.port,
        cv.Required(CONF_MISO): cv.port,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add_library("SmartRC-CC1101-Driver-Lib", "2.5.7")
    cg.add_library("Somfy_Remote_Lib", "0.5.0")

    cg.add(var.set_gdo0(config[CONF_GDO0]))
    cg.add(var.set_gdo2(config[CONF_GDO2]))
    cg.add(var.set_csn(config[CONF_CSN]))
    cg.add(var.set_sck(config[CONF_SCK]))
    cg.add(var.set_mosi(config[CONF_MOSI]))
    cg.add(var.set_miso(config[CONF_MISO]))