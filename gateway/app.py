from flask import Flask, request, jsonify
from flask_cors import CORS
import json
import requests
import traceback
import paho.mqtt.client as mqtt

mqtt_host = 'iot.cht.com.tw'
mqtt_port = 1883
apikey = "DK4BA551BG9YT4BWXM"
iot_url = '/v1/device/18751814981/rawdata'

mqttClient = mqtt.Client()

def onstart_mqtt():
    mqttClient.username_pw_set(username=apikey, password=apikey)
    mqttClient.connect(mqtt_host,mqtt_port,60)
    mqttClient.loop_start()

app = Flask(__name__)

CORS(app)


def byte2bitmap(num):
    bits = bin(num).replace('0b', '').rjust( 4 , '0')
    arr = []
    for bit in bits:
        arr.append(int(bit))
    print(arr)
    return arr

def on_publish(uri, payload, qos):
    mqttClient.publish(uri,payload, qos)


@app.route('/main')
def main():
    return 'how are you'

@app.route('/image', methods=['GET'])
def image():
    return 'image'

@app.route('/broadcast', methods=['POST'])
def broadcast():
    try:
        req = request.get_json(force=True)
        print(req['data'])
        arr = byte2bitmap(int(req['data']))
        data = [{"id":"1", "value":["20"]}] 
        on_publish( iot_url, json.dumps(data), 1)
        
    except:
        traceback.print_exc()
    return 'broadcast'

if __name__ == '__main__':
    onstart_mqtt()
    app.run(host='0.0.0.0', port=80, debug=False)
