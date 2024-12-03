public class UsaHeterogenea extends Thread{
  public static void main(String [] args){
    Ejercicio5 heterogenea = new Ejercicio5();

    //Creamos y lanzamos varias hebras 
    int nHebras = 10;
    int incrementoVariable = 1000;

    Thread[] hebras = new Thread[nHebras]; //Creamos un pool de hebras.

    //Creamos las hebras 
    for(int i = 0; i < nHebras; i++){
      hebras[i] = new Thread(()->{
        for(int j = 0 ; j < incrementoVariable; j++)
          heterogenea.incrementaN();
          heterogenea.incrementaM();
      });

      hebras[i].start();
    }
  
    //Ahora ejecutamos por cada hebra del pool

    for(Thread thread : hebras){
      try{  
        thread.join();
      }catch(Exception e){};
    }

    //Mostramos los valores de las variables
    System.out.println("El valor de la variable n es: " +heterogenea.getN()+ " (sincronizada)");
    System.out.println("El valor de la variable m es: " +heterogenea.getM()+ " (no sincronizada)");
  }
}
