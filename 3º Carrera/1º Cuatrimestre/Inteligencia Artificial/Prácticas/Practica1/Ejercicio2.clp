(deffacts Coches
    (coche Modelo1 12000 pequeño 65 no 4.7)
    (coche Modelo2 12500 pequeño 80 si 4.9)
    (coche Modelo3 13000 mediano 100 si 7.8)
    (coche Modelo4 14000 grande 125 si 6.0)
    (coche Modelo5 15000 pequeño 147 si 8.5)
)

(deftemplate caracteristicas
    (slot precio (type INTEGER))
    (slot maletero (type STRING) (default "grande"))
    (slot caballos (type INTEGER) (default 80))
    (slot abs (type STRING) (default "si"))
    (slot litros (type FLOAT) (default 8.0))
)