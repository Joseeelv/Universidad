import java.util.Random;
public class Integral_Newton_Raphson {
  public static void main(String[] args){

  }

  static void Newton_RaphsonF1(double punto, int iteraciones){
    Random Xn = new Random();
    for(int i = 0; i < iteraciones; i++){
      if(f(Xn) != 0){
        double x1 = Xn - f(Xn) / fprima((Xn));
      }
    }
  }

  static double f(double n){return (Math.cos(n)-Math.pow(n,3));}
  static double fprima(double n){return (-Math.sin(n)-3*Math.pow(n,2));}
  static double f2(double n){return (Math.pow(n,2)-5);}

}
