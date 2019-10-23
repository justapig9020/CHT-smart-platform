import json
import requests
import traceback
iothost = 'iot.cht.com.tw'
apikey  = 'DK4BA551BG9YT4BWXM'
device = '18751814981'

rawdata = [{"id":"1", "save":True, "value":["20"]}]

try:
    header = {"accept":"application/json", "CK":apikey}
    url = "https://" + iothost + "/iot/v1/device/" + device + "/rawdata"
    response = requests.post(url, data=json.dumps(rawdata), headers=header)
    print(response)
except:
    traceback.print_exc()
    #print("ERROR")




