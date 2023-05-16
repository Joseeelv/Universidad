from bottle import route, run, template

@route('/')
@route('/hello/<name>')
def greet(name='Stranger'):
  return template('<b> Hello {{name}}, how are you?', name=name)

run(host='localhost', port=8082)