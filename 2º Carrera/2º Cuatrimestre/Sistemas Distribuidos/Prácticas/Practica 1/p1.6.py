#ejercico 6 práctica 1
def list_del(mylist,e):
    lista = mylist.copy()
    lista.remove(e) #eliminamos el valor
    if(len(lista)==0):
        raise TypeError("Lista Vacia")
    #imprimimos por pantalla la lista resultante
    for i in range (len(lista)):
        print(lista[i],)


mylist = [5,2,4] #declaramos la lista inicial
e=int (input("Introduce un elemento a la lista para borrar: "))
if e is None: #el valor introducido es nulo
    raise TypeError ("NO se elimina nada")

list_del(mylist,e)

