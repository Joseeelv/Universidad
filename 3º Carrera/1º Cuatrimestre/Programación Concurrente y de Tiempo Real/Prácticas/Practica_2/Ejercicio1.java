import java.lang.Thread;
class Ejercicio1 extends Thread {
  public static int n_ = 0;
  int n_iter;
  int modo;
  public Ejercicio1(int modo, int iteraciones){
    this.modo = modo;
    n_iter = iteraciones;
  }
  public void run(){
    switch (modo) {
      case 1: for(int i = 0; i < n_iter; i++)n_++; break;
      case 0: for(int i = 0; i < n_iter; i++)n_--; break;
    }
    System.out.println("Valor final de n:" +n_);
  }
  public static void main(String [] args){
    //creamos los hilos
    Thread a = new Ejercicio1(1,10000);
    Thread b = new Ejercicio1(0,10000);
    //lanzo los hilos
    a.start();
    b.start();
    try{
      a.join();
      b.join();
    }catch(InterruptedException e){} 
  }
}