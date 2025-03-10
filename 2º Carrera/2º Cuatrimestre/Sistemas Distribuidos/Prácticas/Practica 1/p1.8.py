#8. Implementa una funcion prime(a,b) para que devuelva una lista
#conlos números primos en el intervalo cerrado[a,b].Por ejemplo,
# la invocación prime(2, 10) deberá devolver como resultado[2, 3, 5, 7].

def prime(a,b):
    if a is None or b is None:
        raise TypeError ("Parametro de Intervalo nulo")
    if type(a) is not int or type(b) is not int:
        raise TypeError("Los valores deben de ser enteros")
    primo=[]
    for i in range (a,b):
        for j in range(2, int(i/2)+1):
            if i % j == 0:
                break
        else:
            primo.append(i)
    return primo
    
    
#main
p=prime(2,10)
print(p)

