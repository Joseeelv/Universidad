(deftemplate valvula
	(slot nombre)
	(slot T1 (default 0))
    (slot T2 (default 0))
    (slot presion (default 0))
    (slot estado (default cerrada))
)

(defrule R1
	?v <- (valvula (nombre ?nombre) (estado abierto) (presion 5))
	=>
	(printout t "La valvula " ?nombre "se cierra". crlf)
	(modify ?v (estado cerrada))
	(modify ?v (presion 0))
)

(defrule R2
    ?v <- (valvula (nombre ?nombre) (estado cerrada) (T1 ?t1) (presion ?presion))
	(test (< ?presion 10))
	(test (> ?t1 35))
	=>
	(printout t "La válvula " ?nombre " se abre y se aumenta la presión." crlf)
    
    (bind ?nueva-presion (aumentar-presion ?presion ?T1))
    (modify ?v (estado abierta))
    (modify ?v (presion ?nueva-presion))
)

(deffunction aumentar-presion (?presion ?T1)




)