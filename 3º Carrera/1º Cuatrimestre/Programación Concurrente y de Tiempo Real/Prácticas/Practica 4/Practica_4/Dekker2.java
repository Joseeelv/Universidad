class Dekker2 {
  /* Number of processes currently in critical section */
  static volatile int inCS = 0;
  /* Process p wants to enter critical section */
  static volatile boolean wantp = false;
  /* Process q wants to enter critical section */    
  static volatile boolean wantq = false;
  /* Which processes turn is it */
  static volatile int turn = 1;
  static volatile int N_Iteraciones = 10000;
  static volatile int contador = 0;

  class P extends Thread {
	  public void run() {
	    for(int i = 0; i < N_Iteraciones; i++) {
	      /* Non-critical section */
	      wantp = true;
	      while (wantq) {
	          if (turn == 2) {
	              wantp = false;
	              while (turn == 2)
	                  Thread.yield();
	              wantp = true;
	          }
	      }
	      inCS++;
	      contador++;
	      Thread.yield();
	      /* Critical section */
	      System.out.println("Number of processes in critical section: "
	              + inCS);
	      inCS--;
	      contador--;
        turn = 2;
        wantp = false;
        N_Iteraciones++;
      }
    }
  }
  
  class Q extends Thread {
      public void run() {
				 for(int i = 0; i < N_Iteraciones; i++) {
          /* Non-critical section */
          wantq = true;
          while (wantp) {
            if (turn == 1) {
              wantq = false;
              while (turn == 1)
	              Thread.yield();
              wantq = true;
            }
          }
          inCS++;
          contador++;
          Thread.yield();
          /* Critical section */
          System.out.println("Number of processes in critical section: "
                  + inCS);
          inCS--;
          contador--;
          turn = 1;
          wantq = false;
          N_Iteraciones++;
	    }
    }
  }

  Dekker2() {
    Thread p = new P();
    Thread q = new Q();
    p.start();
    q.start();
    try{
	    p.join();
	    q.join();
    }catch (Exception e){}
  }

  public static void main(String[] args){
    new Dekker2();
    System.out.println("Contador: " +contador);
  }
}