public class RecursoParaLE {
  private String data = "Contenido inicial";

  // Método para leer el recurso
  public String leer() {
      return data;
  }

  // Método para escribir en el recurso
  public void escribir(String nuevoDato) {
      data = nuevoDato;
  }
}
