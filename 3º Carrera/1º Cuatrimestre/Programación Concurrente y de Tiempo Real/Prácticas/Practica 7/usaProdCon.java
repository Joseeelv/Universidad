class Producer extends Thread {
  private monitor mon;

  Producer(monitor m) {
      mon = m;
  }

  public void run() {
      for (int i = 0; i < 10; i++) {
          try {
              mon.Append(i);
              System.out.println("Produced: " + i);
              Thread.sleep((int) (Math.random() * 100));
          } catch (InterruptedException e) {
              e.printStackTrace();
          }
      }
  }
}

class Consumer extends Thread {
  private monitor mon;

  Consumer(monitor m) {
      mon = m;
  }

  public void run() {
      for (int i = 0; i < 10; i++) {
          try {
              int value = mon.Take();
              System.out.println("Consumed: " + value);
              Thread.sleep((int) (Math.random() * 100));
          } catch (InterruptedException e) {
              e.printStackTrace();
          }
      }
  }
}

public class usaProdCon {
  public static void main(String[] args) {
      monitor m = new monitor();

      Producer p1 = new Producer(m);
      Consumer c1 = new Consumer(m);
      Consumer c2 = new Consumer(m);

      p1.start();
      c1.start();
      c2.start();
  }
}