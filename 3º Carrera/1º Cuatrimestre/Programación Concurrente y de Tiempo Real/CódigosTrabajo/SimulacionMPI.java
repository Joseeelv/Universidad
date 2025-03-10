import mpi.*;
public class SimulacionMPI {
  static int numero_puntos = 1000;
  static int numero_saltos = 50; //equivale timestamps
  static double constante = 0.1;  

  public static void main(String[] args){
    MPI.init(args);
    int rank = MPI.COMM_WORLD.Rank();
    int size = MPI.COMM_WORLD.Size();
    
    int puntos_proceso = numero_puntos / size;
    double[] A = new double[puntos_proceso + 2];
    double[] A_antiguo = new double[puntos_proceso + 2]; //Almacenará los valores antiguos
    double[] A_temporal = new double[puntos_proceso + 2];

    InicializaValores(A, A_antiguo, rank, puntos_proceso);

    for(int t = 0; t < numero_saltos; t++){
      //Enviamos y recibimos los puntos extremos con los vecinos
      if (rank > 0){ //Enviamos el punto al proceso anterior
        MPI.COMM_WORLD.Send(new double[]{A[1]}, 0, 1, MPI.DOUBLE, rank - 1, 0);
        MPI.COMM_WORLD.Recv(A, puntos_proceso + 1, 1, MPI.DOUBLE, rank + 1, 1);
      }
      if (rank < size - 1){ //Enviamos al siguiente proceso 
        MPI.COMM_WORLD.Send(new double[]{A[puntos_proceso]}, 0, 1, MPI.DOUBLE, rank + 1, 1);
        MPI.COMM_WORLD.Recv(A, puntos_proceso + 1, 1, MPI.DOUBLE, rank + 1, 1);
      }

      //Aplicamos la formula de la onda para actualizar los valores.
      for(int punto = 0; punto < puntos_proceso; punto++){
        A_temporal[punto] = 2.0 * A[punto] - A_antiguo[punto] + constante * (A[punto-1] - (2.0 * A[punto]) + A[punto+1]);
      }
      
      //Copiamos los valores del A_temp en el array 'A' para obtener el resultado e iniciar el calculo en el siguiente punto
      System.arraycopy(A, 0, A_antiguo, 0, puntos_proceso + 2);
      System.arraycopy(A_temporal, 0, A, 0, puntos_proceso + 2);
    }

    //Guardamos todos los resultados en el proceso raiz
    double[] A_global = null;
    if (rank == 0){
      A_global = new double[numero_puntos];
    }
    MPI.COMM_WORLD.Gather(A, 1, puntos_proceso, MPI.DOUBLE, A_global, 0, puntos_proceso, MPI.DOUBLE, 0);

    if (rank == 0){
      //Mostramos los resultados de la simulación en el equipo cuyo rank sea 0.
      ImprimeResultadosSimulacion(A_global);
    }
    //Terminamos el ámbito de MPI
    MPI.Finalize();
  }

  public static void InicializaValores(double[] A, double[] A_antiguo, int rank, int puntos_proceso){
    //Inicializamos los valores
    for(int punto = 1; punto <= puntos_proceso; punto++){
      A[punto] = Math.sin((rank * puntos_proceso) + 1); //Inicializamos con el valor del seno de ese punto
      A_antiguo[punto] = A[punto];
    }
  }

  public static void ImprimeResultadosSimulacion(double[] A){
    //Devolvemos el valor del resultado
    System.out.println("El resultado de la sumulación para una onda con " +numero_puntos+ " puntos, " +numero_saltos+ " timestamps y una constante " +constante+ ":");
    
    for(int i = 0; i < A.length; i++){
      System.out.println("A["+i+"] = " + A[i]);
    }
    System.out.println("Simulación completada");
 }
}
