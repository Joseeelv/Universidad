public class prodEscalar extends Thread{
  private int inicio_, fin_, idHebra_;
  private static long [] v1_,v2_;
  private static long [] productoParcial_;

  //Constructor
  public prodEscalar(int idHebra, int inicio, int fin){
    idHebra_ = idHebra;
    inicio_ = inicio;
    fin_ = fin;
  }
  
  public void run(){
    int suma=0;
    for(int i = inicio_; i < fin_; i++){
      suma += v1_[i]*v2_[i];
    }
    productoParcial_[idHebra_] = suma;
  }
  
  public static void main(String[] args) throws Exception{  
    int nHebras = 4;
    int TamVector = 1000000;
    v1_ = new long[TamVector];
    v2_ = new long[TamVector];
    productoParcial_ = new long[nHebras];
    //rellenamos los vectore
    for(int i = 0; i < TamVector; i++){
      v1_[i] = 1;
      v2_[i] = 1;
    }

    double inicTiempo = System.nanoTime();
    double tiempoTotal;

    //Creamos las hebras
    prodEscalar[] h = new prodEscalar[nHebras];
    int tamSubvector = TamVector / nHebras;

    for(int i=0; i<nHebras; i++){
      int inicio = i*tamSubvector;
      int fin = (i == nHebras-1) ? TamVector : inicio + tamSubvector;
      h[i]= new prodEscalar(i, inicio, fin);
    }
    for(int i=0; i<nHebras; i++)h[i].start();
    for(int i=0; i<nHebras; i++){
		  try{
			  h[i].join();
		  }catch (InterruptedException e){/*no hacemos nada*/}  
    }
    int prodtotal = 0;
    for(int i = 0; i < nHebras; i++){
      prodtotal += productoParcial_[i];
    }
    tiempoTotal = (System.nanoTime()-inicTiempo)/(long)1.0e9;

    System.out.println("Resultado en paralelo: "+prodtotal+"");
    System.out.println("en "+tiempoTotal+" segundos...");
  }
}
