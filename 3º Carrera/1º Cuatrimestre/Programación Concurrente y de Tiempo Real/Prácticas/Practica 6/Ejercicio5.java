public class Ejercicio5 { //Clase Heterogénea
  private int n = 0;
  private int m = 0;

  public Ejercicio5(){};

  public synchronized void incrementaN(){
    n++;
  }

  public synchronized int getN(){
    return n;
  }

  public void incrementaM(){
    m++;
  }

  public int getM(){
    return m;
  }
}
