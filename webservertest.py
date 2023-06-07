import requests

url = 'http://192.168.43.78:80'
data = "helloo"
response = requests.post(url, data=data)

print(response.text)
