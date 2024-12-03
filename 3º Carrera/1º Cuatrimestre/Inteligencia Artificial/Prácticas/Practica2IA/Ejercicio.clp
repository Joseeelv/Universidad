(deftemplate usuario
    (slot DNI)
    (slot Dinero)
    (slot Pin)
)

(deftemplate tarjeta
    (slot DNI)
    (slot Pin)
    (slot Intentos (default 3))
    (slot Limite (default 2000))
    (slot Anno)
    (slot Validada (allowed-values Si No) (default No))
)

(deftemplate cuenta
    (slot DNI)
    (slot Saldo)
    (slot Estado (allowed-values enPantalla Inicial dineroEntregado SuperaLimite SinSaldo))
)
