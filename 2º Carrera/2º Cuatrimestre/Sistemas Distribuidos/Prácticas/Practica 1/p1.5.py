#ejercicio 5 practica 1
mylist = [5,2] #declaramos la lista inicial
e=(input("Introduce un elementos a la lista: "))
if (e==""):
    raise TypeError ("No puedes añadir valores nulos en la lista")
#definimos la funcion añadirlista
def list_add(mylist,e):
    i=0
    mylist.append(e)
    while i is not len(mylist):
        print (mylist[i],)
        i+=1

list_add(mylist,e)