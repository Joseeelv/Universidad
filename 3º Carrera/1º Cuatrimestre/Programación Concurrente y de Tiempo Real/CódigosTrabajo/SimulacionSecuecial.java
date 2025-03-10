import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class SimulacionSecuecial{
 static int numero_puntos = 100000;
 static int numero_saltos = 500; //equivale timestamps
 static double constante = 0.1;
 public static void main(String[] args){
  double[] A = new double[numero_puntos];
  double[] A_antiguo = new double[numero_puntos]; //Almacenará los valores antiguos
  double[] A_temporal = new double[numero_puntos];

  InicializaValores(A, A_antiguo);
  long tiempo_inicio = System.nanoTime();
  ActualizaOnda(A, A_antiguo, A_temporal, constante);

  // Craemos el archivo de salida para Gnuplot
  String filename = "resultados_simulacion.txt";
  
  try {
      // Abrir el archivo para escribir los resultados
      BufferedWriter writer = new BufferedWriter(new FileWriter(filename));
      
      // Escribir el estado inicial (t=0)
      EscribirResultadosEnArchivo(writer, A, 0);
      
      // Actualizamos la onda para cada paso de tiempo
      for (int tiempo = 1; tiempo <= numero_saltos; tiempo++) {
          ActualizaOnda(A, A_antiguo, A_temporal, constante);
          EscribirResultadosEnArchivo(writer, A, tiempo);
      }
      
      // Cerrar el archivo después de escribir los resultados
      writer.close();
      
      System.out.println("Resultados guardados en " + filename);
      
  } catch (IOException e) {
      e.printStackTrace();
  }

  long tiempo_fin = System.nanoTime();
    System.out.println("Tiempo total de ejecución: " + (tiempo_fin - tiempo_inicio) / 1e6 + " ms");


}
  public static void InicializaValores(double[] A, double[] A_antiguo){
    //Inicializamos los valores
    for(int punto = 0; punto < A.length; punto++){
      A[punto] = Math.sin(punto); //Inicializamos con el valor del seno de ese punto
      A_antiguo[punto] = A[punto];
    }
  }

  public static void ActualizaOnda(double[] A, double[] A_antiguo, double[] A_temporal, double constante){
    //Simulación
    for(int tiempo = 0; tiempo < numero_saltos; tiempo++){
      //Actualizamos los puntos aplicando la fórmula de la ecucacion de onda discreta      
      for(int punto = 1; punto < numero_puntos-1; punto++){
        A_temporal[punto] = 2.0 * A[punto] - A_antiguo[punto] + constante * (A[punto-1] - (2.0 * A[punto]) + A[punto+1]);
      }
      //Copiamos los valores del A_temp en el array 'A' para obtener el resultado e iniciar el calculo en el siguiente punto
      System.arraycopy(A,0,A_antiguo,0,numero_puntos);
      System.arraycopy(A_temporal, 0, A, 0, numero_puntos);
    }
  }

  public static void ImprimeResultadosSimulacion(double[] A){
    //Devolvemos el valor del resultado
    System.out.println("El resultado de la sumulación para una onda con " +numero_puntos+ " puntos, " +numero_saltos+ " timestamps y una constante " +constante+ ":");
    
    for(int i = 0; i < numero_puntos; i++){
      System.out.println("A["+i+"] = " + A[i]);
    }
    System.out.println("Simulación completada");
 }
 public static void EscribirResultadosEnArchivo(BufferedWriter writer, double[] A, int tiempo) throws IOException {
        // Escribimos los resultados de la simulación en el archivo
        writer.write("t=" + tiempo);
        for (int i = 0; i < numero_puntos; i++) {
            writer.write("\tA[" + i + "]=" + A[i]);
        }
        writer.newLine();
    }
}