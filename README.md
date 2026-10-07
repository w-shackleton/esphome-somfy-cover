# Somfy cover (blinds etc) component for ESPHome

This module allows for controlling Somfy blinds, shutters etc from ESPHome. It
is based heavily on @evgeni's work here: https://github.com/evgeni/esphome-configs/

This code was hand-written (no AI was used in its creation).

# Circuitry

Follow instructions for the CC1101 driver here: https://github.com/LSatan/SmartRC-CC1101-Driver-Lib

...or at @evgeni's website here: https://www.die-welt.net/2021/06/controlling-somfy-roller-shutters-using-an-esp32-and-esphome/

# ESPHome configuration

Import this module:

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/w-shackleton/esphome-somfy-cover
    components: [ somfy_cover ]
```

Configure your CC1101 remote, specifying which pins you used:

```yaml
somfy_cover:
  id: somfy_remote
  gdo0: 13
  gdo2: 33
  csn: 14
  sck: 15
  mosi: 16
  miso: 32
```

...and configure some covers:

```yaml
cover:
  - platform: somfy_cover
    id: bedroom_blind
    name: Bedroom blind
    # Which remote (above) is this cover using?
    somfy_cover_hub_id: somfy_remote
    # Unique secret code for this remote
    remote_code: 0x42424242
    # Unique key for storing rolling codes in the ESP32's EEPROM
    rolling_code_key: bedroom_blind

    # Configure a "program" button to pair the blind
    program_button:
      name: Bedroom blind program
    # Some blinds need the "UpDown" button to be pressed to pair
    updown_button:
      name: Bedroom blind UpDown
  # ...and configure more covers
  - platform: somfy_cover
    id: Study blind
    ...
```
