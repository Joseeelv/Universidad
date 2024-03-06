from bottle import get, run # request o route

@get('/cars') # o @route('/cars', method='GET')
def getcars():
   cars = [ {'name': 'Audi', 'price': 52642},
       {'name': 'Mercedes', 'price': 57127},
       {'name': 'Skoda', 'price': 9000},
       {'name': 'Volvo', 'price': 29000},
       {'name': 'Bentley', 'price': 350000},
       {'name': 'Citroen', 'price': 21000},
       {'name': 'Hummer', 'price': 41400},
       {'name': 'Volkswagen', 'price': 21600} ]

   return dict(data=cars)

run(host='localhost', port=8084)
