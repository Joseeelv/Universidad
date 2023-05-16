import json
import requests
from requests.structures import CaseInsensitiveDict

mykey = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
mycity = "Cádiz"
units = "metric" #Por defecto, la temperatura está en grados Kelvin, para obtener grados Fahrenheit->imperial y Celsius->metric

url = "https://api.openweathermap.org/data/2.5/weather?appid=" + mykey + "&q=" + mycity + "&units=" + units

headers = CaseInsensitiveDict()
headers["Accept"] = "application/json"

resp = requests.get(url, headers=headers)
json_data = json.loads(resp.text)

#Con el código http podemos ver si ha habido algún error
print("Status code: " + str(resp.status_code))

#Mostramos la temperatura en la ciudad indicada
print("Temperature: " + str(json_data["main"]["temp"]) + "º\n")

#Mostramos los datos crudos para que se vea todo lo que devuelve el endpoint "weather"
print("Raw data: " + resp.text)