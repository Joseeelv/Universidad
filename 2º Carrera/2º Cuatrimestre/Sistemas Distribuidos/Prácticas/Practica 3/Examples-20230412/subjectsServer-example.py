import json

from bottle import run, request, response, get, post, put

# Simulamos base de datos en memoria
database = dict() #key: code, value: course

# Creamos una clase Course (Curso) con un constructor que tiene: nombre y código de asignatura, que inicializamos
class Course:
   def __init__(self, code, name):
       self.code = code
       self.name = name

@post('/addCourse')
def add_course():
   #import pdb; pdb.set_trace()

   data = request.json
   # Datos del JSON
   code = data.get('code')
   name = data.get('name')

   course = Course(code, name)

   # persistencia (tendríamos que implementar los métodos de conexión con la base de datos etc.)
   # save_data(course)

   # Añadimos instancia a nuestra base de datos
   database[code] = course

   # Una vez almacenada la instancia, es conveniente devolver una respuesta al usuario
   # Construimos la cabecera: 'application/json' indicamos que vamos a devolver un JSON
   response.headers['Content-Type'] = 'application/json'

   dict_to_parse = {'code': code, 'name': name}

   # Devolvemos el JSON
   return json.dumps(dict_to_parse)


@get('/listCourses')
def list_asignaturas():
   asignaturas = []

   for key, value in database.items():
       asignaturas.append({'code': key, "name": value.name})

   response.headers['Content-Type'] = 'application/json'

   return json.dumps(asignaturas)

@put('/updateCourse/<course_code>')
def update_course(course_code):
   # Suponemos que la asignatura está en la base de datos
   course = database[course_code]

   response.headers['Content-Type'] = 'application/json'

   new_name = request.json.get('name')

   course.name = new_name

   dict_to_parse = {'code': course_code, 'name': course.name}

   # Devolvemos el JSON
   return json.dumps(dict_to_parse)

if __name__ == '__main__':
   run(host='localhost', port=8086, debug=True)