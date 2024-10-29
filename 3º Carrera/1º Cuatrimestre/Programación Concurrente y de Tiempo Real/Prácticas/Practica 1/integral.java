import java.util.Random;
import java.util.Scanner;
public class integral {
  public static void main(String[] args){
    System.out.println("Introduce el numero de iteraciones:");
    Scanner s = new Scanner(System.in);
    int iter = s.nextInt();
    Integral_MonteCarloX(iter);
    Integral_MonteCarloSENx(iter);
  }
  static void Integral_MonteCarloX(int iteraciones){
    double exitos = 0;
    double x,y;
    Random numero = new Random();
    for(int i = 0; i < iteraciones; i++){
      x = numero.nextDouble();
      y = numero.nextDouble();
      if(y < f2(x))
        exitos++;
    }
    System.out.println("Resultado de la integral de x:" + (exitos/iteraciones));
  }
  static void Integral_MonteCarloSENx(int iteraciones){
    double exitos = 0;
    double x,y;
    Random numero = new Random();
    for(int i = 0; i < iteraciones; i++){
      x = numero.nextDouble();
      y = numero.nextDouble();
      if(y < f1(x))
        exitos++;
    }
    System.out.println("Resultado de la integral de sen(x):" + (exitos/iteraciones));
  }
  static double f2(double n){return n;}
  static double f1(double n){return Math.sin(n);}
}
