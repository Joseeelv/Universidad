import java.io.*;
import java.net.*;


public class Servidor3 {
  public static void main(String[] args) {
    int port = 12345;  // Puerto en el que escucha el servidor
    String outputFilePath = "archivo_recibido.txt";  // Ruta donde guardaremos el archivo recibido

    try (ServerSocket serverSocket = new ServerSocket(port)) {
        System.out.println("Esperando conexión del cliente...");
        Socket socket = serverSocket.accept();
        System.out.println("Cliente conectado.");

        // Crear flujo de entrada desde el socket
        InputStream inputStream = socket.getInputStream();
        FileOutputStream fileOutputStream = new FileOutputStream(outputFilePath);
        BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(fileOutputStream);

        byte[] buffer = new byte[4096];
        int bytesRead;
        while ((bytesRead = inputStream.read(buffer)) != -1) {
            bufferedOutputStream.write(buffer, 0, bytesRead);
        }

        System.out.println("Archivo recibido y guardado como: " + outputFilePath);

        // Cerrar conexiones
        bufferedOutputStream.close();
        fileOutputStream.close();
        inputStream.close();
        socket.close();

    } catch (IOException e) {
        e.printStackTrace();
    }
  }
}
