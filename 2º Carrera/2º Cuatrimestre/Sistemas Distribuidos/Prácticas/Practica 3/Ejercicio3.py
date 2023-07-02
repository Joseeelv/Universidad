# Desarrolleunserviciowebdegestióndehabitacionesdeunhotel.El
# serviciodebeposeerunalistadehabitacionesycadahabitaciónposeerá,
# mínimo,lossiguientesatributos:
# ■ Identicador.
# ■ Númerodeplazas.
# ■ Listadeequipamiento(porejemplo:armario,aireacondicionado,
# cajafuerte,escritorio,etc.).
# ■ Ocupada(sí/no).
# Sedebenimplementarlossiguientesendpoints:
# a)Dardealtaunanuevahabitación.
# b)Modicarlosdatosdeunahabitación.
# c)Consultarlalistacompletadehabitaciones.
# d)Consultarunahabitaciónmedianteidenticador.
# e)Consultarlalistadehabitacionesocupadasodesocupadas.
# QuedaajuiciodelestudianteidenticarquétipodeoperacionesHTTP
# debeimplementarcadaendpoint (PUT,POST oGET).
# Paralosendpointsb),d)ye),esobligatorioelusodeparámetrosenel
# path delaURL.


from bottle import get, post, request, response
