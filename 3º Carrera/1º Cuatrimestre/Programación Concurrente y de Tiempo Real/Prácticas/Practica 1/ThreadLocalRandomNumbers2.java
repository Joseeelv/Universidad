import java.util.concurrent.ThreadLocalRandom;
 
class ThreadLocalRandomNumbers2 extends Thread{
 
    public void run(){
        try {
            int cota = 10;
            int dato;
            double ddato;
            ThreadLocalRandom g = ThreadLocalRandom.current();
            for(int i = 0; i < 5; i++){
              dato = g.nextInt(cota);
              System.out.println( "Thread " + Thread.currentThread().getName()+ " genera " + dato);
              ddato = g.nextDouble(1.0);
              System.out.println( "Thread " + Thread.currentThread().getName()+ " genera " + ddato);
              ddato = g.nextDouble(40.0);
              System.out.println( "Thread " + Thread.currentThread().getName()+ " genera " + ddato);
            }
        }catch (Exception e) {System.out.println("Exception");}
    }

   public static void main(String[] args) throws InterruptedException{
 
        ThreadLocalRandomNumbers2 t1 = new ThreadLocalRandomNumbers2();
        ThreadLocalRandomNumbers2 t2 = new ThreadLocalRandomNumbers2();
        ThreadLocalRandomNumbers2 t3 = new ThreadLocalRandomNumbers2();
        t1.start(); t2.start(); t3.start();
        t1.join();  t2.join();  t3. join();
        System.out.println( "Main terminando...");

    }
}