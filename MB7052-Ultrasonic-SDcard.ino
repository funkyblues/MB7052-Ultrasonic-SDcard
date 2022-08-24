#include <swRTC.h>

#include <SPI.h>
#include <SD.h>

// 파일 선언
File myFile;

// 시간 클래스 선언
swRTC rtc;  //클래스 개체 선언



const int pwPin1 = 3;
long sensor, mm, inches;


void setup() {
  rtc.stopRTC();            //정지
  rtc.setTime(8, 53, 00);  //시, 분, 초
  rtc.setDate(13, 8, 2022); //일, 월, 년
  rtc.startRTC();           //시작

  Serial.begin(9600);
  
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) { // SD카드 모듈을 초기화합니다.
    Serial.println("initialization failed!"); // SD카드 모듈 초기화에 실패하면 에러를 출력합니다.
    while (1);
  }
  Serial.println("initialization done.");

  // 파일을 열어 쓸 준비를 합니다. 한 번에 하나의 파일만 열 수 있습니다.
  myFile = SD.open("ultra.txt", FILE_WRITE); // 두 번째 인자가 있으면 쓰기모드입니다.

  if (myFile) { 
    myFile.close(); // 파일을 닫습니다.
    Serial.println("done.");
  } else {
    // 파일이 열리지 않으면 에러를 출력합니다.
    Serial.println("error opening test.txt");
  }
}

void read_sensor (){
  sensor = pulseIn(pwPin1, HIGH);
  mm = sensor/5.7;
  inches = mm/25.4;
}
void print_range(){
//  Serial.print("S1");
//  Serial.print("=");
  Serial.println(mm);
//  Serial.print(" ");
//  Serial.println(inches);
}
void loop() { 
  read_sensor();
  print_range();
  Serial.print(rtc.getHours(), DEC);
  Serial.print(":");
  Serial.print(rtc.getMinutes(), DEC);
  Serial.print(":");
  Serial.print(rtc.getSeconds(), DEC);
  Serial.print("\t"); 

  Serial.print(rtc.getYear(), DEC);
  Serial.print("/");
  Serial.print(rtc.getMonth(), DEC);
  Serial.print("/");
  Serial.println(rtc.getDay(), DEC);
  Serial.print("data: ");
  Serial.println(mm);

  myFile = SD.open("ultra.txt", FILE_WRITE); // 두 번째 인자가 있으면 쓰기모드입니다.

  if (myFile) { // 파일이 정상적으로 열리면 파일에 문자를 작성(추가)합니다.
    Serial.println("Writing to ultra.txt...");

/////////////////////////////////////////////////////////////////////////////time

    myFile.print(rtc.getHours(), DEC);
    myFile.print(", ");
    myFile.print(rtc.getMinutes(), DEC);
    myFile.print(", ");
    myFile.print(rtc.getSeconds(), DEC);
    myFile.print(", "); 
    myFile.print(rtc.getYear(), DEC);
    myFile.print(", ");
    myFile.print(rtc.getMonth(), DEC);
    myFile.print(", ");
    myFile.print(rtc.getDay(), DEC);
    myFile.print(", ");
    
/////////////////////////////////////////////////////////////////////////////
    
    myFile.println(mm);
    myFile.close(); // 파일을 닫습니다.
    Serial.println("done");
    delay(1000);
  } 
  else {
    // 파일이 열리지 않으면 에러를 출력합니다.
    Serial.println("SD fail");
    delay(1000);
  }
}
