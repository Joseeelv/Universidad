import requests

print('Bienvenido a...')

response = requests.get('http://localhost:8086/listCourses')

print(response.status_code)

print(response.text)