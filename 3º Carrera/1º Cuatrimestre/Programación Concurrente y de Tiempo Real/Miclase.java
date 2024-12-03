import java.lang.Runnable;
public class Miclase implements Runnable{
	String palabra_;
	
	public Miclase (String palabra){
		palabra_ = palabra;
	}
	public void run(){
		for(int i = 0; i < 10; i++)
			System.out.println(palabra_);
	
	}
	
	public static void main(String [] args){
		//Creamos dos objetos de la clase Miclase
		Miclase a1 = new Miclase("A1");
		Miclase a2 = new Miclase("A2");
		//Creamos dos hilos para esos dos objetos
		Thread t1 = new Thread(a1);
		Thread t2 = new Thread(a2);
		//Lanzamos y ejecutamos el hilo t1
		t1.setDaemon(true);
		t1.start();
		// System.out.println("Prioridad del hilo t1: " +t1.getPriority());
		// t1.setPriority(1); //Modificamos la prioridad a 1 del hilo t1.
		System.out.println("Prioridad del hilo t1: " +t1.getPriority() + " y es deminio: " + t1.isDaemon());
		//Lanzamos y ejecutamos el hilo t2
		t2.start();
		System.out.println("Prioridad del hilo t2: " +t2.getPriority());
	}
}