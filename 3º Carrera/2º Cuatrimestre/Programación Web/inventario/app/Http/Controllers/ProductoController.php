<?php

namespace App\Http\Controllers;

use App\Models\Producto;

class ProductoController extends Controller
{
    public function index() {
        $productos = Producto::all(); // Nos aseguramos de que la base de datos tenga registros y esté conectada
        if ($productos->isEmpty()) {
            return view('productos')->with(['message' => 'No products found.', 'productos' => $productos]);
        }
        return view('productos', compact('productos'));
    }
    
}


