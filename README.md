# AirQualitySensor
The Air Quality Sensor uses an [ESP32 ESP-WROOM32 development board](https://www.amazon.com/gp/product/B08NW6YZ8W?ie=UTF8&th=1&linkCode=li2&tag=kreativedilla-20&linkId=b257795f61c66c3e0b282562729fc08c&language=en_US&ref_=as_li_ss_il) and a [MQ135 Air Quality Sensor](https://amzn.to/3GJi63w)

The VCC pin on the MQ135 is connected to the 3.3v pin on the ESP32 board.

The GND pin on the MQ135 is connection the GND pin on the ESP32 board.

The A0 pin on the MQ135 is connection the GPIO36 pin on the ESP32 board.

The MQTT connection will publish the Air Quality in PPM on a 30 second interval by default. 

You will need to add in your SSID, the Password, the MQTT broker IP address and the MQTT Topic. 

If using Home Assistant and have Mosquitto/MQTT setup, you can configure a new sensor in the configuration.yml file similar to:
```
mqtt:
  sensor:
   - name: "Air Quality"
     state_topic: "airquality/location"
     unit_of_measurement: "ppm"
     device_class: "aqi"
```
