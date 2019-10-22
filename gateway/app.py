from flask import Flask, request, jsonify, send_file
from flask_cors import CORS
import json
import requests
import traceback
import paho.mqtt.client as mqtt
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np

N = 2
TOTAL = 4*N
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


def alert(num):
    # set platform alert to 1
    data = {"id" :"alert", "value":["0"]}
    on_publish( iot_url, json.dumps(data), 1)
    print("alert : " + str(num))


def byte2bitmap(num):
    bits = bin(num).replace('0b', '').rjust( 4 , '0')
    arr = []
    dot = 0
    for bit in bits:
        if(int(bit) == 1):
            dot += 1
        arr.append(int(bit))

    return arr,dot


def bitmap2str(arr):
    bm = [[0 for i in range(6)] for j in range(6)]            
    x=0
    y=0
    dot_x =[]
    dot_y =[]
    for block in arr:
        bm[y][x] = block[0]
        bm[y][x+1]=block[1]
        bm[y+1][x] = block[2]
        bm[y+1][x+1] = block[3]
        x = x + 2
        if x == 6:
            x = 0
            y = y + 2 
    for i in range(6):
        for j in range(6):
            if(bm[i][j] == 1):
                print(j,i)
                dot_x.append(j+1)
                dot_y.append(i+1)
    plt.plot(dot_x, dot_y, 'ro')
    plt.axis([0,7,0,7])
    plt.savefig('tmp.png')
    return bm
    
def arr2str(arr):
    ret = ''
    for i in arr:
        ret += ''.join((map(str,i)))
    return ret

def on_publish(uri, payload, qos):
    mqttClient.publish(uri,payload, qos)


@app.route('/figure')
def getFig():    
    return send_file('./tmp.png',attachment_filename="figure.png", mimetype='image/png')

@app.route('/main')
def main():
    return 'how are you'

@app.route('/image', methods=['GET'])
def image():
    return 'image'

@app.route('/broadcast', methods=['POST','GET'])
def broadcast():
    try:
        req = request.get_json(force=True)
        #print(str(request.values))
        print(req['data'])
        arr = list()
        dot = 0
        for i in req['data']:                
            t,d = byte2bitmap(ord(i) - 0x41)
            dot += d
            arr.append(t)
        if (dot >= TOTAL/2):
            alert(1)
        else:
            alert(0)
        twoD_arr = bitmap2str(arr)
        print(twoD_arr)
        s = arr2str(twoD_arr)
        data = [{"id":"sensor", "value":[s]}] 
        on_publish( iot_url, json.dumps(data), 1)
        
    except:
        traceback.print_exc()
    return 'broadcast'

if __name__ == '__main__':
    onstart_mqtt()
    app.run(host='0.0.0.0', port=8000, debug=False)
