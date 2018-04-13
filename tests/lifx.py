
import requests

with open('lifx_token.txt', 'r') as myfile:
    token=myfile.read().replace('\n', '')


headers = {
    "Authorization": "Bearer %s" % token,
}

#response = requests.get('https://api.lifx.com/v1/lights/all', headers=headers)
#print(response.text)
data = {
    "period": 2,
    "cycles": 6,
    "color": "green",
    "from_color": "blue"
}

response = requests.post('https://api.lifx.com/v1/lights/all/effects/breathe', data=data, headers=headers)
