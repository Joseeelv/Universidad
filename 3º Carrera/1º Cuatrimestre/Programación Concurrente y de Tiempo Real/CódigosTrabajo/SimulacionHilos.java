import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.*;

public class SimulacionHilos {
  static int numero_puntos = 1000000;
  static int numero_saltos = 5000; //equivale timestamps
  static double constante = 0.1;  
  static int numero_hilos = 16; // Número de hebras

  public static void main(String[] args) throws InterruptedException, ExecutionException {
    // Inicializamos un pool de hilos con ExecutorService
    ExecutorService executor = Executors.newFixedThreadPool(numero_hilos);

    int puntos_proceso = numero_puntos / numero_hilos;
    double[] A = new double[numero_puntos];
    double[] A_antiguo = new double[numero_puntos];
    double[] A_temporal = new double[numero_puntos];

    // Inicializa los valores
    InicializaValores(A, A_antiguo, puntos_proceso);

    // Medir tiempo de inicio con nanoTime
    long tiempo_inicio = System.nanoTime();

    // Enviar los trabajos a las hebras
    for (int t = 0; t < numero_saltos; t++) {
      // System.out.println("Timestep " + t + " comenzando simulación...");

      // Crear tareas para cada hilo
      List<Callable<Void>> tareas = new ArrayList<>();
      for (int i = 0; i < numero_hilos; i++) {
        final int hilo = i;
        tareas.add(() -> {
          int inicio = hilo * puntos_proceso;
          int fin = (hilo == numero_hilos - 1) ? numero_puntos : (hilo + 1) * puntos_proceso;
          for (int punto = inicio + 1; punto < fin - 1; punto++) {
            A_temporal[punto] = 2.0 * A[punto] - A_antiguo[punto] + constante * (A[punto - 1] - (2.0 * A[punto]) + A[punto + 1]);
          }
          return null;
        });
      }

      // Ejecutamos las tareas
      executor.invokeAll(tareas);

      // Sincronización: Copiar los valores actualizados
      System.arraycopy(A, 0, A_antiguo, 0, numero_puntos);
      System.arraycopy(A_temporal, 0, A, 0, numero_puntos);
    }

    // Medir tiempo de finalización con nanoTime
    long tiempo_fin = System.nanoTime();
    // Mostrar el tiempo en milisegundos (convertimos nanosegundos a milisegundos)
    System.out.println("Tiempo total de ejecución: " + (tiempo_fin - tiempo_inicio) / 1e6 + " ms");

    // Imprimir resultados
    ImprimeResultadosSimulacion(A);

    // Terminamos el pool de hilos
    executor.shutdown();
  }

  public static void InicializaValores(double[] A, double[] A_antiguo, int puntos_proceso) {
    // Inicializamos los valores
    for (int punto = 0; punto < numero_puntos; punto++) {
      A[punto] = Math.sin(punto); // Inicializamos con el valor del seno de ese punto
      A_antiguo[punto] = A[punto];
    }
  }

  public static void ImprimeResultadosSimulacion(double[] A) {
    // Devolvemos el valor del resultado
    System.out.println("El resultado de la simulación para una onda con " + numero_puntos + " puntos, " + numero_hilos + " hilos, " + numero_saltos + " timestamps y una constante " + constante + ":");
    // for (int i = 0; i < A.length; i++) {
    //   System.out.println("A[" + i + "] = " + A[i]);
    // }
    System.out.println("Simulación completada");
  }
}
