(deftemplate aeronave	
	(slot id)
	(slot compania)
	(slot origen)
	(slot destino)
	(slot velocidad)
	(slot peticion (allowed-values Ninguna Despegue Aterrizaje Emergencia Rumbo))
	(slot estado (allowed-values enTierra Ascenso Crucero Descenso) (default enTierra))
)
(deftemplate aerodromo
	(slot id)
	(slot ciudad)
	(slot radar (allowed-values ON OFF))
	(slot visibilidad)
	(slot velocidadViento)
)

(deftemplate piloto
	(slot id)
	(slot estado (allowed-values OK SOS Ejecutando Stand-By) (default Stand-By))
)

(deftemplate vuelo
	(slot id-Aerodromo-Origen)
	(slot id-Aerodromo-Destino)
	(slot distancia)
	(slot velocidad (default 240))
	(slot velocidadCrucero (default 700))
)

;;Hechos Iniciales
(deffacts iniciales		
	(aeronave (id "FX001") (compania "IBERIA") (origen "XRY") (destino "Madrid") (velocidad 0) (peticion Despegue ) (estado enTierra))
	(aeronave (id "FX001") (compania "IBERIA") (origen "XRY") (destino "Barcelona") (velocidad 240) (peticion Despegue) (estado enTierra)))
	(aerodromo (id "XRY") (ciudad "Jerez") (radar ON) (visibilidad 10) (velocidadViento 50))
	(piloto (id "P001") (estado OK))
	(vuelo (id-Aerodromo-Origen "XRY") (id-Aerodromo-Destino "Madrid") (distancia 3000) (velocidad 240))
)

;;Regla de Despegar
(defrule despegar
	?aeronave <- (aeronave (peticion Despegue) (origen ?o) (destino ?d) (estado enTierra) (id ?id) (compania ?comp))
	?piloto <- (piloto (estado OK))
	?aerodromo <- (aerodromo (radar ON) (visibilidad ?v) (velocidadViento ?vv))
	?vuelo <- (vuelo (id-Aerodromo-Origen ?o) (id-Aerodromo-Destino ?d))
	(test (> ?v 5))
	(test (< ?vv 75))
	
	=>
	(modify ?piloto (estado Ejecutando))
	(modify ?aeronave (peticion Ninguna) (estado Ascenso))
	
	(printout t "La aernonave " ?id " de la compañia " ?comp " va a realizar el despegue desde la estación " ?o "hasta " ?d crlf)
	
)

;;Regla de Excepción
(defrule excepcion
	?piloto <- (piloto (estado ?estado))
	?aerodromo <-(aerodromo (radar ON))
	?aeronave <- (aeronave (peticion Despegue) (estado enTierra) (origen ?o) (id ?id) 
		(compania ?comp))
	(test (neq ?estado OK))
	
	=>
	//moficiamos la peticion
	(modify ?aeronave (peticion Emergencia))
	(printout t "ATENCION: La aeronave " ?id "de la compañia " ?comp
		" ha realizado una petición de Emergencia debido a que el piloto no está en estado OK." crfl)
)

;;Regla de Crucero
;; FUNCION DE CALCULAR LAS HORAS
(deffunction calcularHoras (?velocidad ?distancia)
	(div ?distancia ?velocidad)
)

;;FUNCION DE CALCULAR LOS MINUTOS
(deffunction calcularMinutos (?velocidad ?distancia)
  (mod (div ?distancia ?velocidad) 60)
)

(defrule crucero
	?aeronave <- (aeronave (estado Ascenso) (velocidad ?v)
		(peticion Ninguna) (id ?id))
	?piloto <- (piloto (estado Ejecutando))
	?vuelo <- (vuelo (distancia ?d))
	(test (> ?v 0))
	=>
	(modify ?aeronave (estado Crucero))
	
	;Función que calcula el tiempo para llegar al destino
	(bind ?horas (calcularHoras ?v ?d))
	(bind ?minutos (calcularMinutos ?v ?d))
	
	;Imprimimos por pantalla 
	(printout t "El tiempo estimado del viaje que va a realizar la aeronave " ?id
		"es de " ?horas " horas " y ?minutos " minutos " crlf)
	 ; Cambiar el estado del piloto a Stand-by
	 
   (modify ?piloto (estado Stand-By))
)
