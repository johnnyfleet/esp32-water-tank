# Water Tank Meter

As part of the overall project, I'm looking to have a new sensor unit measure the water level in the water tank. That, I'll then shunt off to store in InfluxDB via MQTT. 

To compliment that I also want a simple display to show the water level as it stand and a brief view of the trend. This will be useful in summer to check progress of it. 

## Water tank measurements

- Overall Diameter **360cm approx**
- Overall height
- Thickness of concrete on sides (measure one of the holes)
- Thickness of concrete on top (measure at the hatch) **5.5cm**
- Height of water from the underside the of the hatch when full = **9cm**. (Use this for calibrating 100% full)
- Overall volume = **25,000 litres** (to confirm)

## Water Tank sensor

Equipment

- [ESP32 dev board](https://www.aliexpress.com/item/1005002410521023.html?spm=a2g0o.productlist.0.0.198151a1oYrwx4&algo_pvid=c32935aa-e4d5-4e5a-bb03-01ce31865455&aem_p4p_detail=2021083017182247963328214500066914944&algo_exp_id=c32935aa-e4d5-4e5a-bb03-01ce31865455-2)
- [JSN-SR04T ultrasonic sensor](https://www.aliexpress.com/item/32915100619.html?src=google&src=google&albch=shopping&acnt=494-037-6276&slnk=&plac=&mtctp=&albbt=Google_7_shopping&albagn=888888&isSmbAutoCall=false&needSmbHouyi=false&albcp=9444695485&albag=99457316601&trgt=296904914040&crea=en32915100619&netw=u&device=c&albpg=296904914040&albpd=en32915100619&gclid=Cj0KCQjwg7KJBhDyARIsAHrAXaEmkD2zIck7TjwKIB7ZeLMLwBjNjrpFFkPZ4vekBNj1NNIVMlZyZb0aAnl7EALw_wcB&gclsrc=aw.ds&aff_fcid=70170470166948ecbfe9594e0243e6d9-1630369074650-02858-UneMJZVf&aff_fsk=UneMJZVf&aff_platform=aaf&sk=UneMJZVf&aff_trace_key=70170470166948ecbfe9594e0243e6d9-1630369074650-02858-UneMJZVf&terminal_id=dee080a62a234874bc8fb1981a37a30c) - *note*: has [minimum range of 25cm](https://www.makerguides.com/jsn-sr04t-arduino-tutorial/) so would lose accuracy after that. An alternative in time could be the [A02YYUW Waterproof Ultrasonic Sensor](https://wiki.dfrobot.com/A02YYUW%20Waterproof%20Ultrasonic%20Sensor%20SKU:%20SEN0311)

## Display

Equipment

- [M5Paper](https://shop.m5stack.com/products/m5paper-esp32-development-kit-960x540-4-7-eink-display-235-ppi)

## Wiring
Trying out the JSN-SR04T and wiring up. Using [these instructions](https://www.makerguides.com/jsn-sr04t-arduino-tutorial/)

Using this wiring diagram for the NodeMCU ESP32S

![NodeMCU ESP32S](https://esphome.io/_images/nodemcu_esp32-full.jpg)

Trigger goes to pin: 12 (not 2)
Echo goes to pin 14 (not 3)


