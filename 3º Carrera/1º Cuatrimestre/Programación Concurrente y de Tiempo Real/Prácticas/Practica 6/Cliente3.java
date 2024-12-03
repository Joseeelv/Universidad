import java.io.*;
import java.net.*;

public class Cliente3 {
  public static void main(String[] args) {
    for(;;){
    String serverAddress = "localhost";  // Dirección del servidor
    int serverPort = 2001;  // Puerto del servidor
    String filePath = "hola.txt";  // Ruta del archivo a enviar

    try (Socket socket = new Socket(serverAddress, serverPort)) {
        System.out.println("Conectado al servidor.");

        // Crear flujo de salida hacia el servidor
        OutputStream outputStream = socket.getOutputStream();
        FileInputStream fileInputStream = new FileInputStream(filePath);
        BufferedInputStream bufferedInputStream = new BufferedInputStream(fileInputStream);

        byte[] buffer = new byte[4096];
        int bytesRead;
        while ((bytesRead = bufferedInputStream.read(buffer)) != -1) {
            outputStream.write(buffer, 0, bytesRead);
        }

        System.out.println("Archivo enviado correctamente.");

        // Cerrar conexiones
        bufferedInputStream.close();
        fileInputStream.close();
        outputStream.close();
        socket.close();

    } catch (IOException e) {
        e.printStackTrace();
    }
    }
  }  
}
