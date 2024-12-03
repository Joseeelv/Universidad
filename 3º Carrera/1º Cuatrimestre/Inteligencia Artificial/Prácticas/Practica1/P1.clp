(deftemplate persona
  (multislot nombre)
  (slot edad (type INTEGER))
  (slot DNI (type INTEGER))
  (slot profesion (type STRING))
  (slot nacionalidad (allowed-values Es En It Fr))  ;; Espacio añadido y comas eliminadas
)

(deffacts iniciales
  ;; hechos estructurados
  (persona (nombre "Jose Luis")
           (edad 23)
           (DNI 123456789)
           (profesion "estudiante")
           (nacionalidad Es)
  )
  
  (persona (nombre "Manolo")
           (edad 40)
           (DNI 987654321)
           (profesion "profesor")
           (nacionalidad En)
  )
  
  ;; hechos no estructurados
  (ciudad Cadiz Cadiz)
  (ciudad Puerto Real Cadiz)
)

(deffacts inicio
	(soltero Jose)
	(soltera Manuela)
)
	

(deftemplate Rectangulo
	(slot base)
	(slot altura)
)

(deftemplate personita
	(slot nombre)
	(slot cabello (allowed-values rubio moreno pelirrojo castagno))
	(slot ojos (allowed-values azules marrones verdes negros))
)
(assert (personita (nombre Juan) (cabello moreno) (ojos verdes)))
(assert (personita (nombre Elena) (cabello rubio) (ojos negros)))
(assert (personita (nombre Jorge) (cabello rubio) (ojos negros)))
(assert (personita (nombre Pascual) (cabello moreno) (ojos negros)))