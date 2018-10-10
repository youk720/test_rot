/* Encoder Library - TwoKnobs Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
   This example code is in the public domain.*/

#include <Encoder.h> 
  /*エンコーダのライブラリ,別機で書き込む場合,IDEの
  * スケッチ>ライブラリをインクルード>ライブラリを管理 へ入り
  * 検索欄に「rotary」で検索し「Encoder by Paul Stoffegen」をインストール
  */
// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knobLeft(5, 6); //左側
Encoder knobRight(7, 8); //右側
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600); //9600bpsでシリアルモニタを監視
  Serial.println("TwoKnobs Encoder Test:");
}

long positionLeft  = -999;
long positionRight = -999;

void loop() {
  long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionLeft = newLeft;
    positionRight = newRight;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }
  //fdafdsasa
}

