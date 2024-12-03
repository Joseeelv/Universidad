public class MonitorLE {
    private int lectores = 0;  // Número de lectores actuales
    private boolean escribiendo = false;  // Estado del escritor
    private final Object lock = new Object();  // Objeto de bloqueo para el monitor

    // Método para que un lector entre
    public void entrarLector() {
        synchronized (lock) {
            while (escribiendo) {  // Si hay un escritor, los lectores deben esperar
                try {
                    lock.wait();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
            lectores++;  // Incrementa el contador de lectores
        }
    }

    // Método para que un lector salga
    public void salirLector() {
        synchronized (lock) {
            lectores--;  // Decrementa el contador de lectores
            if (lectores == 0) {  // Si no hay lectores, notifica a los escritores
                lock.notifyAll();
            }
        }
    }

    // Método para que un escritor entre
    public void entrarEscritor() {
        synchronized (lock) {
            while (lectores > 0 || escribiendo) {  // Espera a que no haya lectores o escritores
                try {
                    lock.wait();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
            escribiendo = true;  // El escritor comienza a escribir
        }
    }

    // Método para que un escritor salga
    public void salirEscritor() {
        synchronized (lock) {
            escribiendo = false;  // El escritor termina de escribir
            lock.notifyAll();  // Notifica a los lectores y escritores
        }
    }
}
