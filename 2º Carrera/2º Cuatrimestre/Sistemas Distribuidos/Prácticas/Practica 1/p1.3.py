#ejercicio 3 practica 1

with open("texto.txt","r") as f:
    cadena = f.readlines()
aux = str(cadena)
i=0
while i is not len(cadena):
    aux=cadena[i]
    i=+1
print(len(aux))
with open("resultado.txt","w") as fichero:
    fichero.writelines(aux)