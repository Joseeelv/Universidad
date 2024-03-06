#ejercicio 4 practica 1
a = int (input("Introduce un valor para x: "))
b = int (input("Introduce un valor para y: "))
c = int (input("Introduce un valor para z: "))
if type(a or b or c) != int:
    raise TypeError("Solo se admiten valores enteros")
def accum(x,y,z):
    suma =0 ##declaramos la variable que contendrá la suma
 #comprobamos que los numeros son entero
 ##comprobamos que los numeros son pares
    if(x%2==0): suma+=x
    if(y%2==0): suma+=y
    if(z%2==0): suma+=z
    return suma    
    

resultado = accum(a,b,c)
print("La suma es: ",resultado) #mprimimos el valor de la suma