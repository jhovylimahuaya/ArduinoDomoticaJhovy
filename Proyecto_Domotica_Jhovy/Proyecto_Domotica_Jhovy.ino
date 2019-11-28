#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };//Ponemos la dirección MAC de la Ethernet Shield
IPAddress ip(172,22,10,7); //Asignamos  la IP al Arduino
byte gateway[] = { 172, 22, 10, 60 };                   // gateway IP
byte subnet[] = { 255, 255, 255, 192 };
EthernetServer server(80); //Creamos un servidor Web con el puerto 80 que es el puerto HTTP por defecto

int FOTRESISPin=A0;
int sensorValue = 0;
//int PIRPin= 12;
int RELPin1 = 22;
int RELPin2 = 23;
int RELPin3 = 24;
int RELPin4 = 25;
String EstatusSensor="OFF";

String estado1="OFF"; //Estado del Led 1 inicialmente "OFF"
String estado2="OFF"; //Estado del Led 2 inicialmente "OFF" 
String estado3="OFF"; //Estado del Led 2 inicialmente "OFF" 
String estado4="OFF"; //Estado del Led 2 inicialmente "OFF" 
String estado5="OFF"; //Estado del Led 2 inicialmente "OFF" 

void setup()
{
  Serial.begin(9600);
 
  // Inicializamos la comunicación Ethernet y el servidor
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
  pinMode(RELPin1, OUTPUT);
  pinMode(RELPin2, OUTPUT);
  pinMode(RELPin3, OUTPUT);
  pinMode(RELPin4, OUTPUT);
  
  digitalWrite(RELPin1, LOW);
  digitalWrite(RELPin2, LOW);
  digitalWrite(RELPin3, LOW);
  digitalWrite(RELPin4, LOW);
  
}
void loop()
{
  EthernetClient client = server.available(); //Creamos un cliente Web
  //Verificamos si se detecte un cliente a través de una petición HTTP
  sensorValue = analogRead(FOTRESISPin);
  //Serial.println(sensorValue);

  

  if (EstatusSensor=="ON"){
    if(sensorValue > 600)
    {
      digitalWrite(RELPin1,HIGH);
      Serial.println("Está oscureciendo");
      estado1="ON";
      
      }else{
        digitalWrite(RELPin1,LOW);
        //Serial.println("Aún es temprano");
        estado1="OFF";
      }
  }
  else{
    //Serial.println("sensor apagado");
  }
  
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true; //Una petición HTTP acaba con una línea en blanco
    String cadena=""; //Creamos una cadena de caracteres vacía
    while (client.connected()) {
      if (client.available()) {
        
        char c = client.read();//Leemos la petición HTTP carácter por carácter
        Serial.write(c);//Visualizamos la petición HTTP por el Monitor Serial
        
        if(cadena.length()<50)
        {
                    cadena.concat(c);//concatenmos el String 'cadena' con la petición HTTP (c). De esta manera convertimos la petición HTTP a un String
       
                   //Ya que hemos convertido la petición HTTP a una cadena de caracteres, ahora podremos buscar partes del texto.
                   int posicion=cadena.indexOf("Data="); //Guardamos la posición de la Palabra "Data=" a la variable 'posicion'
           
                    if(cadena.substring(posicion)=="Data=1")//Si en la posición hay "Data=1"
                    {
                      digitalWrite(RELPin1,HIGH);
                      estado1="ON";
                    }
                    else if(cadena.substring(posicion)=="Data=2")//Si en posición hay "Data=2"
                    {
                      digitalWrite(RELPin1,LOW);
                      estado1="OFF";
                    }
                    else if(cadena.substring(posicion)=="Data=3")//Si en la posición hay "Data=3"
                    {
                      digitalWrite(RELPin2,HIGH);
                      estado2="ON";
                    }
                    else if(cadena.substring(posicion)=="Data=4")//Si en la posición hay "Data=4"
                    {
                      digitalWrite(RELPin2,LOW);
                      estado2="OFF";
                    } 
                    else if(cadena.substring(posicion)=="Data=5")//Si en la posición hay "Data=5"
                    {
                      digitalWrite(RELPin3,HIGH);
                      estado3="ON";
                    }
                    else if(cadena.substring(posicion)=="Data=6")//Si en la posición hay "Data=6"
                    {
                      digitalWrite(RELPin3,LOW);
                      estado3="OFF";
                    } 
                    else if(cadena.substring(posicion)=="Data=7")//Si en la posición hay "Data=7"
                    {
                      digitalWrite(RELPin4,HIGH);
                      estado4="ON";
                    }
                    else if(cadena.substring(posicion)=="Data=8")//Si en la posición hay "Data=8"
                    {
                      digitalWrite(RELPin4,LOW);
                      estado4="OFF";
                    } 
                    else if(cadena.substring(posicion)=="Data=9")//Si en la posición hay "Data=9"
                    {
                      EstatusSensor="ON";
                    }else if(cadena.substring(posicion)=="Data=10")//Si en la posición hay "Data=10"
                    {
                      EstatusSensor="OFF";
                    }
                    else if(cadena.substring(posicion)=="Data=11")//Si en la posición hay "Data=11"
                    {
                      
                      digitalWrite(RELPin1,HIGH);
                      estado1="ON";
                      digitalWrite(RELPin2,HIGH);
                      estado2="ON";
                      digitalWrite(RELPin3,HIGH);
                      estado3="ON";
                      digitalWrite(RELPin4,HIGH);
                      estado4="ON";
                      estado5="ON";
                      
                    }else if(cadena.substring(posicion)=="Data=12")//Si en la posición hay "Data=12"
                    {
                      EstatusSensor="OFF";
                      digitalWrite(RELPin1,LOW);
                      estado1="OFF";
                      digitalWrite(RELPin2,LOW);
                      estado2="OFF";
                      digitalWrite(RELPin3,LOW);
                      estado3="OFF";
                      digitalWrite(RELPin4,LOW);
                      estado4="OFF";
                      estado5="OFF";
                      
                    }
                          
        }
        
        //Cuando reciba una línea en blanco, quiere decir que la petición HTTP ha acabado y el servidor Web está listo para enviar una respuesta
        if (c == 'n' && currentLineIsBlank) {
 
            // Enviamos al cliente una respuesta HTTP
            client.println("HTTP/1.1 200 OK");
            
            client.println("Content-Type: text/html");
            client.println();
 
            //Página web en formato HTML
            client.println("<html>");                 
            const char http_Head[] PROGMEM =
            "<head><style>"
            "body {"
                  "background-color: #d0e4fe;"
            "}"
            "h1 {"
                "color: Orange;"
                "text-align: center;"
            "}"
            "p {"
                "font-family: 'Times New Roman';"
                "font-size: 20px;"
                "text-align: left;" 
                "color: Blue;"
            "}"
            "ul.a {"
                "list-style-type: circle;"
            "}"
            "</style></head>"
            "<h1>Control de mis luces</h1>";
            client.println(http_Head);
            client.println("<body>");
            client.println("<div style='text-align:center;'>");
            client.println("Estado del Sensor = ");client.print(EstatusSensor);            
            client.println("<br />"); 
            if(EstatusSensor=="OFF"){
              client.print("<button onClick=location.href='./?Data=9' style='background:green; width:50px; height: 30px;'>ON</button>");
            }else{ 
              client.print("<button onClick=location.href='./?Data=10' style='background:red; width:50px; height: 30px;'>OFF</button>");
            }           
            client.println("<br /><br />");
            if(EstatusSensor=="OFF"){
              client.println("Estado del LED 1 = ");client.print(estado1);            
              client.println("<br />");
                          
              if(estado1=="OFF"){
                client.print("<button onClick=location.href='./?Data=1' style='background:green; width:50px; height: 30px;'>ON</button>");
              }else{ 
                client.print("<button onClick=location.href='./?Data=2' style='background:red; width:50px; height: 30px;'>OFF</button>");
              }   
              client.println("<br /><br />");
            }       
            client.println("Estado del LED 2 = ");client.print(estado2);            
            client.println("<br />");            
            if(estado2=="OFF"){
                client.print("<button onClick=location.href='./?Data=3' style='background:green; width:50px; height: 30px;'>ON</button>");
              }else{ 
                client.print("<button onClick=location.href='./?Data=4' style='background:red; width:50px; height: 30px;'>OFF</button>");
              }            
            client.println("<br /><br />");
            client.println("Estado del LED 3 = ");client.print(estado3);            
            client.println("<br />");            
            if(estado3=="OFF"){
                client.print("<button onClick=location.href='./?Data=5' style='background:green; width:50px; height: 30px;'>ON</button>");
              }else{ 
                client.print("<button onClick=location.href='./?Data=6' style='background:red; width:50px; height: 30px;'>OFF</button>");
              }
            client.println("<br /><br />");  
            client.println("Estado del LED 4 = ");client.print(estado4);            
            client.println("<br />");            
            if(estado4=="OFF"){
                client.print("<button onClick=location.href='./?Data=7' style='background:green; width:50px; height: 30px;'>ON</button>");
              }else{ 
                client.print("<button onClick=location.href='./?Data=8' style='background:red; width:50px; height: 30px;'>OFF</button>");
              }
            client.println("<br /><br />");
            client.println("Estado de Encender/Apagar todo= ");client.print(estado5);            
            client.println("<br />");
            client.print("<button onClick=location.href='./?Data=11' style='background:green; width:70px; height: 50px;'>ON</button>");
            client.print("<button onClick=location.href='./?Data=12' style='background:red; width:70px; height: 50px;'>OFF</button>");
            client.println("<br /><br />");   
            client.println("</b></body>");
            client.println("</html>");
            break;
        }
        if (c == 'n') {
          currentLineIsBlank = true;
        }
        
        else if (c != 'r') {
          currentLineIsBlank = false;
        }
        
      }
    }
    //Dar tiempo al navegador para recibir los datos
    delay(1);
    client.stop();// Cierra la conexión
  }
   
}
