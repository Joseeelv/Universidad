#ejercicio 7 practica 1
#7. Implemente la función dict_add(mydict, t) para que añada la tupla (clave, valor)
#t pasada por parámetro al diccionario mydict.

def dict_add(mydict , t):
    if t is None:
        raise TypeError ("T es un valor nulo")
    if type (t) is not tuple:
        raise TypeError ("T no es una tupla")
    
    diccionario = mydict #metemos la tupla en el diccionario
    diccionario[t[0]]= t[1]
    return diccionario

#main 
mydict = {1: 'manzana'}
t = (2, 'fresa')
a=dict_add(mydict,t)
print(a)