public class UsaEL extends Thread {
  public static void main(String[] args) {
    MonitorLE monitor = new MonitorLE();
    RecursoParaLE recurso = new RecursoParaLE();

    // Crea hilos lectores
    Thread lector1 = new Thread(new Lector(monitor, recurso));
    Thread lector2 = new Thread(new Lector(monitor, recurso));

    // Crea hilos escritores
    Thread escritor1 = new Thread(new Escritor(monitor, recurso));
    Thread escritor2 = new Thread(new Escritor(monitor, recurso));

    lector1.start();
    lector2.start();
    escritor1.start();
    escritor2.start();
}
}

class Lector implements Runnable {
private MonitorLE monitor;
private RecursoParaLE recurso;

public Lector(MonitorLE monitor, RecursoParaLE recurso) {
    this.monitor = monitor;
    this.recurso = recurso;
}

@Override
public void run() {
    while (true) {
        monitor.entrarLector();
        System.out.println("Lector leyendo: " + recurso.leer());
        monitor.salirLector();

        try {
            Thread.sleep(1000);  // Simula la lectura
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
}

class Escritor implements Runnable {
private MonitorLE monitor;
private RecursoParaLE recurso;

public Escritor(MonitorLE monitor, RecursoParaLE recurso) {
    this.monitor = monitor;
    this.recurso = recurso;
}

@Override
public void run() {
    while (true) {
        monitor.entrarEscritor();
        String nuevoDato = "Nuevo contenido: " + System.currentTimeMillis();
        recurso.escribir(nuevoDato);
        System.out.println("Escritor escribiendo: " + nuevoDato);
        monitor.salirEscritor();

        try {
            Thread.sleep(2000);  // Simula la escritura
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
}
