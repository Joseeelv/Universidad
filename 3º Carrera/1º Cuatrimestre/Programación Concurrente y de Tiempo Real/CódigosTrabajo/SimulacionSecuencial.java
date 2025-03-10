import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class SimulacionSecuencial {
    static int numero_puntos = 100000;
    static int numero_saltos = 5000;
    static double constante = 0.1;

    public static void main(String[] args) {
        double[] A = new double[numero_puntos];
        double[] A_antiguo = new double[numero_puntos]; // Almacenará los valores antiguos
        double[] A_temporal = new double[numero_puntos];

        InicializaValores(A, A_antiguo);
        
        // Medir tiempo de ejecución
        long tiempo_inicio = System.nanoTime();
        
        // Actualizamos la onda para cada paso de tiempo
        for (int tiempo = 1; tiempo <= numero_saltos; tiempo++) {
            ActualizaOnda(A, A_antiguo, A_temporal, constante);
        }

        long tiempo_fin = System.nanoTime();
        System.out.println("Tiempo total de ejecución: " + (tiempo_fin - tiempo_inicio) / 1e6 + " ms");
        System.out.println("El resultado de la simulación para una onda con " + numero_puntos + " puntos, " + numero_saltos + " timestamps y una constante " + constante + ":");

    }

    public static void InicializaValores(double[] A, double[] A_antiguo) {
        // Inicializamos los valores
        for (int punto = 0; punto < A.length; punto++) {
            A[punto] = Math.sin(punto); // Inicializamos con el valor del seno de ese punto
            A_antiguo[punto] = A[punto];
        }
    }

    public static void ActualizaOnda(double[] A, double[] A_antiguo, double[] A_temporal, double constante) {
        // Simulación
        for (int tiempo = 0; tiempo < numero_saltos; tiempo++) {
            // Actualizamos los puntos aplicando la fórmula de la ecuación de onda discreta
            for (int punto = 1; punto < numero_puntos - 1; punto++) {
                A_temporal[punto] = 2.0 * A[punto] - A_antiguo[punto] + constante * (A[punto - 1] - (2.0 * A[punto]) + A[punto + 1]);
            }
            // Copiamos los valores del A_temp en el array 'A' para obtener el resultado e iniciar el cálculo en el siguiente punto
            System.arraycopy(A, 0, A_antiguo, 0, numero_puntos);
            System.arraycopy(A_temporal, 0, A, 0, numero_puntos);
        }
    }
}
