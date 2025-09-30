<!DOCTYPE html>
<html lang="{{ str_replace('_', '-', app()->getLocale()) }}">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Internet y Negocio Electrónico - Tienda Virtual</title>
    <link rel="stylesheet" href="/css/ine.css">
</head>
<body>
    <header>
        <img src="/img/logo-ine.png" title="logotipo" alt="logotipo" class="logo" />
        <form name="search" class="form-search" action="{{ route('home') }}">
            <input id="text" name="text" type="text" placeholder="Buscar...">
            <button>Buscar</button>
        </form>
        <div class="button-links">
            <a href="#">Login</a>
            <a href="#">Registro</a>
            <a href="#"><img class="cart-ico" src="/img/cart.png" title="carrito" alt="carrito" /></a>
        </div>
    </header>

    <main>
        <section class="product-list">
            <article class="product">
                <h2>Producto 1</h2>
                <img src="/img/product/product-1.png" title="Producto 1" alt="Producto 1">
                <p>Precio: 10.00 €</p>
                <button>Ver Detalle</button>
            </article>
            <article class="product">
                <h2>Producto 2</h2>
                <img src="/img/product/product-2.png" title="Producto 2" alt="Producto 2">
                <p>Precio: 20.00 €</p>
                <button>Ver Detalle</button>
            </article>
            <article class="product">
                <h2>Producto 3</h2>
                <img src="/img/product/product-3.png" title="Producto 3" alt="Producto 3">
                <p>Precio: 30.00 €</p>
                <button>Ver Detalle</button>
            </article>
            <article class="product">
                <h2>Producto 4</h2>
                <img src="/img/product/product-4.png" title="Producto 4" alt="Producto 4">
                <p>Precio: 40.00 €</p>
                <button>Ver Detalle</button>
            </article>
            <article class="product">
                <h2>Producto 5</h2>
                <img src="/img/product/product-5.png" title="Producto 5" alt="Producto 5">
                <p>Precio: 50.00 €</p>
                <button>Ver Detalle</button>
            </article>
            <article class="product">
                <h2>Producto 6</h2>
                <img src="/img/product/product-6.png" title="Producto 6" alt="Producto 6">
                <p>Precio: 60.00 €</p>
                <button>Ver Detalle</button>
            </article>
        </section>
    </main>

    <footer>
        <p>&copy; 2024 Tienda Virtual. Todos los derechos reservados.</p>
    </footer>
</body>
</html>
