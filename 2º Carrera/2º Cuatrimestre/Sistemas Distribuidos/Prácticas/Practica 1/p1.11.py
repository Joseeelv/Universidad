#Implemente una funcion en Python que realice la unión de dos listas.
#Tenga en cuenta que no puede haber elementos repetidos.

def unionlista(lista1,lista2):
    return list(set(lista1+lista2))



#main
l1= ['RedBull', 'Mercedes', 'Ferrari', 'Alpine', 'Shakira', 'Fiat']
l2= ['Mercedes', 'AstonMartin', 'Citroen', 'Fiat', 'Seat', 'Ferrari']
Resultado = unionlista(l1,l2)
print(Resultado)