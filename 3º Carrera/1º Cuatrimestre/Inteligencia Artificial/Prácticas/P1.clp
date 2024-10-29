(deffacts iniciales
  ;; hechos estructurados
  (persona (nombre Jose Luis)
           (DNI 123456789)
           (profesion estudiante)
           (nacionalidad Es)
           
  (persona (nombre Manolo)
           (DNI 987654321)
           (profesion profesor)
           (nacionalidad En)
           (edad 40))
  ;; hechos no estructurados
  (ciudad Cadiz Cadiz)
  (ciudad Puerto Real Cadiz)
)

(reset)  ;; Inicializa los hechos
(facts)  ;; Muestra los hechos actuales

(assert (ciudad Jerez Cadiz))  ;; Agrega una nueva ciudad
(assert (persona (nombre Maria) (DNI 3432423) (profesion doctora) (nacionalidad Es) (edad 32)))  ;; Agrega una nueva persona

(facts)  ;; Muestra los hechos después de agregar los nuevos hechos
