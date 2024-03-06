#Implemente una función en Python que realice la intersección de dos
#listas. Tenga en cuenta que no puede haber elementos repetidos.


def insercion(l1,l2):
    return list(set(l1)&set(l2))

#main
lista1= ['RedBull', 'Mercedes', 'Ferrari', 'Alpine', 'Shakira', 'Fiat']
lista2= ['Mercedes', 'AstonMartin', 'Citroen', 'Fiat', 'Seat', 'Ferrari']
Resultado = insercion(lista1,lista2)
print(Resultado)