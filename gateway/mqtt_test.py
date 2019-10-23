import paho.mqtt.client as mqtt
import json
import traceback
mqtt_host = 'iot.cht.com.tw'
mqtt_port = 1883
apikey = "DK4BA551BG9YT4BWXM"

url = mqtt_host + "/v1/device/18751814981/rawdata"


mqtt_client = mqtt.Client()
mqtt_client.username_pw_set(username=apikey, password=apikey)
mqtt_client.connect(mqtt_host, mqtt_port, 60)
mqtt_client.loop_start()

rawdata =[{"id":"1", "value":["10"]}]
try:
    mqtt_client.publish(url, json.dumps(rawdata), 1)
    print("publish")
except:
    traceback.print_exc()


