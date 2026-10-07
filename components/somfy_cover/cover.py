import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import cover
from esphome.components import button
from . import CONF_SOMFY_COVER_HUB_ID, SomfyCoverHub

somfy_cover_ns = cg.esphome_ns.namespace("somfy_cover")
SomfyCover = somfy_cover_ns.class_("SomfyCover", cover.Cover, cg.Component)
SomfyButton = somfy_cover_ns.class_("SomfyButton", button.Button, cg.Component)

CONF_ROLLING_CODE_KEY = "rolling_code_key"
CONF_REMOTE_CODE = "remote_code"
CONF_PROGRAM_BUTTON = "program_button"
CONF_UPDOWN_BUTTON = "updown_button"

def key(value):
    value = cv.string_strict(value)
    if len(value) >= 16:
        raise cv.Invalid("Rolling code storage keys must be 16 chars at most")
    return value

CONFIG_SCHEMA = cover.cover_schema(SomfyCover).extend(
    {
        cv.GenerateID(CONF_SOMFY_COVER_HUB_ID): cv.use_id(SomfyCoverHub),
        cv.Required(CONF_ROLLING_CODE_KEY): key,
        cv.Required(CONF_REMOTE_CODE): cv.hex_int,

        cv.Optional(CONF_PROGRAM_BUTTON): button.button_schema(SomfyButton).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_UPDOWN_BUTTON): button.button_schema(SomfyButton).extend(cv.COMPONENT_SCHEMA),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_SOMFY_COVER_HUB_ID])
    var = await cover.new_cover(config)

    cg.add(parent.register_cover(var))
    cg.add(var.configure(config[CONF_ROLLING_CODE_KEY], config[CONF_REMOTE_CODE], parent))

    if CONF_PROGRAM_BUTTON in config:
        b = await button.new_button(config[CONF_PROGRAM_BUTTON])
        cg.add(b.setCover(var))
        cg.add(b.setProgram())

    if CONF_UPDOWN_BUTTON in config:
        b = await button.new_button(config[CONF_UPDOWN_BUTTON])
        cg.add(b.setCover(var))
        cg.add(b.setUpDown())
