import java.util.concurrent.*;
import java.util.concurrent.atomic.*;

public class piMonteCarloParalelo extends Thread{
  private double cx, cy;
  private static AtomicLong exitos = new AtomicLong();
  private long vueltas;
  
  public piMonteCarloParalelo(long n){vueltas = n;}
  
  public void run(){
    ThreadLocalRandom g = ThreadLocalRandom.current();	
    for(long i=0; i<vueltas; i++){
      cx = g.nextDouble(1.0);
      cy = g.nextDouble(1.0);
      if(Math.sqrt(Math.pow(cx, 2)+Math.pow(cy, 2))<=1)
        exitos.getAndIncrement();
    }
  }
  
  public static void main(String[] args) throws Exception{
    long nVueltas = 400000000;
    double cxx, cyy;
    long exitosSec   = 0;
    
    //procesamieto en secuencial...
    long inicTiempo = System.nanoTime();
    for(long j=0; j<nVueltas; j++){
      cxx = Math.random();
      cyy = Math.random();
      if(Math.sqrt(Math.pow(cxx, 2)+Math.pow(cyy, 2))<=1)
        exitosSec++;
    }
    long tiempoTotal = (System.nanoTime()-inicTiempo)/(long)1.0e9;

    System.out.println("Aproximacion secuencial: "+4.0*exitosSec/nVueltas);
    System.out.println("Valor Real: "+Math.PI);
    System.out.println("en "+tiempoTotal+" segundos...");
    
    //procesamiento en paralelo
    int nThreads = 8;

    inicTiempo   = System.nanoTime();
    piMonteCarloParalelo[] h = new piMonteCarloParalelo[nThreads];
    for(int i=0; i<nThreads; i++)h[i]=new piMonteCarloParalelo((long)(nVueltas/nThreads));
    for(int i=0; i<nThreads; i++)h[i].start();
    for(int i=0; i<nThreads; i++)h[i].join();
    tiempoTotal = (System.nanoTime()-inicTiempo)/(long)1.0e9;

    System.out.println("Aproximacion paralela: "+4.0*(exitos.get())/nVueltas);
    System.out.println("Valor Real: "+Math.PI);
    System.out.println("en "+tiempoTotal+" segundos...");
  }
}
