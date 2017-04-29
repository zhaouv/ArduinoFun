#include <aJSON.h>

#include<ESP8266WiFi.h>
#include<ESP8266WiFiMulti.h>


WiFiServer server(80);//初始化服务器端口80
int lnum;
char numbuf[20];
char *json_String;

void setup() {
  //Serial.begin(115200);
  WiFi.mode(WIFI_AP);//作为热点
  WiFi.softAP("Hello_IOT","12345678"); //热点名称和密码
  server.begin();//开启HTTP Server，默认IP192.168.4.1

  Serial.begin(115200);
  IPAddress HTTPS_ServerIP = WiFi.softAPIP();//获取Server IP
  Serial.print("Server IP is:");
  Serial.println(HTTPS_ServerIP);
  //使用ESP自带的LED，HIGH灯灭，可换其它管脚
  lnum=14;
  pinMode(lnum, OUTPUT);
  digitalWrite(lnum, HIGH);
}

void loop() {
  //检查是否有浏览器端的客户访问ESP8266
  WiFiClient client = server.available();
  if (!client) {
    /*
    aJsonObject* jname = aJson.parse("{\"a\":[1,2,3,4,5,{\"b\":2}],\"c\":123,\"d\":\"123\"}");
    json_String=aJson.print(jname);
    Serial.println(json_String);
    free(json_String);
    aJsonObject* aname = aJson.getObjectItem(jname, "a");
    json_String=aJson.print(aname);
    Serial.println(json_String);
    free(json_String);
    aname = aJson.getObjectItem(jname, "c");
    json_String=aJson.print(aname);
    Serial.println(json_String);
    free(json_String);
    aname = aJson.getObjectItem(jname, "d");
    json_String=aJson.print(aname);
    Serial.println(json_String);
    free(json_String);
    aJson.deleteItem(jname);
    delay(1000);
    */
    return;
  }
  Serial.println("Somebody has connect:)");

  String request =client.readStringUntil('\r');
  Serial.println(request);
  String val;
  
  int numsindex=request.indexOf("/vauygrfuybvs");
  int numeindex=request.indexOf("vauygrfuybve");
  String jsonsstr="";
  if (numsindex != -1 && numeindex != -1){
    for(numsindex+=13;numsindex<numeindex;numsindex++){
      if(request[numsindex]!='`')jsonsstr+=request[numsindex];
      if(request[numsindex]=='`')jsonsstr+='\"';
    }
    Serial.println(jsonsstr);
    //const char *ptemp=jsonsstr.c_str();
    //json_String=(char *)ptemp;
    aJsonObject* jsonobj = aJson.parse((char *)jsonsstr.c_str());
    for(int index_uyagw=0;index_uyagw<17;index_uyagw++){
      sprintf(numbuf,"%d",index_uyagw);
      aJsonObject* ueygfev = aJson.getObjectItem(jsonobj,numbuf);
      if(ueygfev){
        json_String=aJson.print(ueygfev);
        Serial.println(json_String);
        if(String(json_String)=="\"ON\"")digitalWrite(index_uyagw, HIGH);
        if(String(json_String)=="\"OFF\"")digitalWrite(index_uyagw, LOW);
        free(json_String);
      }
    }
    aJson.deleteItem(jsonobj);
    val="json";
  }
  
  numsindex=request.indexOf("/sfwaieruhgnums");
  numeindex=request.indexOf("sfwaieruhgnume");
  String numstr="";
  if (numsindex != -1 && numeindex != -1){
    //Serial.print(numsindex);
    //Serial.print(numeindex);
    for(numsindex+=15;numsindex<numeindex;numsindex++)
      numstr+=request[numsindex];
    Serial.print(numstr);
    lnum=atoi(numstr.c_str());
  }
  
  
  if (request.indexOf("/OFF") != -1){
    val="OFF";
    digitalWrite(lnum, LOW);
  } else if (request.indexOf("/ON")!= -1) {
    val="ON";
    digitalWrite(lnum, HIGH);
  }
  Serial.println(val);
  
  //给客户端的反馈信息
  sprintf(numbuf,"%d",lnum);
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type:text/html\r\n\r\n";
  s += "<!doctype html><html><body>\r\n";
  s += "<br><input id=\"dnum\" type=\"edit\" value=\""+String(numbuf)+"\">";
  s += "<br>";
  s += "<br><input type=\"button\" value=\"Turn led ON\" onclick=\"setonoff('/ON')\">";
  s += "<br>";
  s += "<br><input type=\"button\" value=\"Turn led OFF\" onclick=\"setonoff('/OFF')\">";
  s += "<br>";
  s += "<br>"+String(val)+"\r\n";
  s += "<script>\r\n";
  s += "function setonoff(onoffstr){location.href=onoffstr+'/sfwaieruhgnums'+dnum.value+'sfwaieruhgnume';}";
  s += "\r\n</script>";
  s += "</body></html>\r\n";
  //Serial.print(s);
  
  client.flush();
  client.print(s);
  delay(1);
  Serial.println("Clientdisconected.");
}

