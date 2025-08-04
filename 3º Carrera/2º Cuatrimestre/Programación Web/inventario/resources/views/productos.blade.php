<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Productos</title>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
  <div class="container mt-5">
    <h1 class="text-center mb-4">Lista de Productos</h1>
    <ul class="list-group">
      @foreach ($productos as $producto)
        <li class="list-group-item d-flex justify-content-between align-items-center">
          <span>{{ $producto->nombre }}</span>
          <span class="badge bg-primary rounded-pill">${{ $producto->precio }}</span>
        </li>
      @endforeach
    </ul>
  </div>
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>


