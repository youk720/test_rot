#include <Encoder.h>
// ロータリーエンコーダ用ライブラリ導入

// ライブラリのリファレンスページ https://www.pjrc.com/teensy/td_libs_Encoder.html
// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

// エンコーダ接続ピン指定:2=緑, 3=茶, GND=黄
Encoder left(2, 4);
Encoder center(2, 7);
Encoder right(2, 8);
//   avoid using pins with LEDs attached
// 古い値の定義
long positionCenter  = -999;
long positionLeft  = -999;
long positionRight  = -999;
//新しいエンコーダ値のもとの変数定義
long newCenter, newLeft, newRight;

int red, green, blue;

//各種ピン番号を定数に.
#define rot_left_led 3
#define rot_center_led 5
#define rot_right_led 6

#define RedLED 9
#define GreenLED 10
#define BlueLED 11

#define left_sw A0
#define center_sw A1
#define right_sw A2

void setup() {
  Serial.begin(9600);
//  Serial.println("TwoKnobs Encoder Test:");
  pinMode(rot_center_led, OUTPUT);
  pinMode(rot_left_led, OUTPUT);
  pinMode(rot_right_led, OUTPUT);
  pinMode(left_sw, INPUT); //エンコーダ値リセットスイッチ
  pinMode(center_sw, INPUT);
  pinMode(right_sw, INPUT);
}
void loop() {
  //新しいエンコーダの値を代入
  newCenter = center.read();
  newLeft = left.read();
  newRight = right.read();

  // ロータリーエンコーダが動き次第動作
  if (newCenter != positionCenter) {
    center_rotation();
    positionCenter = newCenter;
  }
  if(newLeft != positionLeft){
    left_rotation();
    positionLeft = newLeft;
  }
  if(newRight != positionRight){
    right_rotation();
    positionRight = newRight;
  }


  if (digitalRead(left_sw) == LOW) {
    Serial.read();
    Serial.println("Reset LEFT encoder by switch");
    // 以下でロータリーエンコーダ値を上書き(ただしエンコーダライブラリを入れていないとこの機能は使用不可)
    left.write(0);
  }
  if(digitalRead(center_sw) == LOW){
    Serial.read();
    Serial.println("Reset CENTER encoder by switch");
    center.write(0);
  }
  if(digitalRead(right_sw) == LOW){
    Serial.read();
    Serial.println("Reset RIGHT encoder by switch");
    right.write(0);
  }
  // LED発行
  analogWrite(RedLED, red);
  analogWrite(GreenLED, green);
  analogWrite(BlueLED, blue);

  // ロータリーLED 点滅
  digitalWrite(rot_left_led, LOW);
  digitalWrite(rot_center_led, LOW);
  digitalWrite(rot_right_led, LOW);
}

// エンコーダ左右振り分け
void left_rotation(){
  if(newLeft < positionLeft){
    // 左回りの処理
    if(red<=255){
      red = red + 1;
    }
  }else if(newLeft > positionLeft){
    // 右回りの処理
    if(red!=0){
      red = red - 1;
    }
  }
}

void center_rotation(){
  if(newCenter < positionCenter){
    if (green <= 255) {
      green = green + 1;
    }
  }else if(newCenter > positionCenter){
    if (green != 0) {
      green = green - 1;
    }
  }
}

void right_rotation(){
  if(newRight < positionRight){
    if(blue<=255){
      blue = blue + 1;
    }
  }else if(newRight > positionRight){
    if (blue!=0) {
      blue = blue - 1;
    }
  }
}
