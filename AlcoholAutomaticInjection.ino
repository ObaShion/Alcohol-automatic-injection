//servoのライブラリーを宣言する
#include <Servo.h>
#include <LiquidCrystal.h>
Servo myservo;
//servoのピンはデータを９番に接続
const int PIN_SERVO_PWM = 9;
//超音波センサーはechoピンを３番,tringピンを２番に接続
const int ECHOPIN = 3;
const int TRIGPIN = 2;

// servo instance
Servo servo;

// status definitions
int pumping = 0;
int pumpcount = 0;


void setup() {
  // Initialize for Serial debug
  Serial.begin(9600);

  // Initialize for servo
  servo.attach(PIN_SERVO_PWM);
  servo.write(0);

  // Initialize for button
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(PIN_SERVO_PWM, OUTPUT);

}

void loop() {
  /*超音波センサーで距離の測定
    https://osoyoo.com/ja/2018/08/28/arduino-lesson-ultrasonic-sensor-hc-sr04-module/
    を参考にしました。
  */
  float duration, distance;
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  duration = pulseIn(ECHOPIN, HIGH);

  //distanceに距離を代入
  distance = (duration / 2) * 0.0344;

  /*distanceが２０以上でservoが元の位置に戻る
    distanceが２０以下でservoが動く
    https://github.com/mnishikawa/Arduino/blob/master/autosanitizer/autosanitizer.ino
    を参考にしました。
  */
  if (distance > 20) {
    servo.write(0);
  } else if (distance < 20) {
    servo.write(180);
  }

  //distanceの値を調べる。ツール¥シリアルモニターで確認できます。
  Serial.print("Distance:");
  Serial.print(distance);
  Serial.println(" cm");

  //wait for loop
  delay(500);

}

