import json

from bottle import put, request, response, run # o route

_names=["UnNombre"]

# o @route('/names/<oldname>', method='PUT')
@put('/names/<oldname>')
def update_handler(oldname):
   try:
      data = json.load((request.body))
      print(data)
   except:
      raise ValueError

   newname = data['name']
   _names.remove(oldname)
   _names.append(newname)

   # return 200 Success
   response.headers['Content-Type'] = 'application/json'
   return json.dumps({'name': newname})

run(host='localhost', port=8085)