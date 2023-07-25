#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#define led 10    //設定箭頭LED數量
#define cled 10   //設定中間LED數量
#define speed 50  //動畫速度(ms)
#define ledPin 2  //LED data腳位
#define r 0
#define g 255
#define b 0
Adafruit_NeoPixel strip(led * 2 + cled, ledPin, NEO_GRB + NEO_KHZ800);

int step = 0;                  //步驟狀態機
unsigned long nowtime, time1;  //時間暫存
int mode = 0;                  //運行模式(0:停止1:左2:右)

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
}

void loop() {
  nowtime = millis();
  if (nowtime - time1 > speed) {
    time1 = nowtime;
    if (mode != 0) {
      step++;
      if (step >= led + cled) {
        step = 0;
      }
      for (int i = 0; i < (led + cled); i++) {
        if (mode == 1) {  //左
          if (i <= step) {
            strip.setPixelColor(led + cled - i, strip.Color(r, g, b));
          } else {
            strip.setPixelColor(led + cled - i, strip.Color(0, 0, 0));  //關閉led
          }
          for (int j = 0; j < led; j++) {
            strip.setPixelColor(led + cled + j, strip.Color(0, 0, 0));  //關閉led
          }
        }
        if (mode == 2) {  //右
          if (i <= step) {
            strip.setPixelColor(i + led, strip.Color(r, g, b));
          } else {
            strip.setPixelColor(i + led, strip.Color(0, 0, 0));  //關閉led
          }
          for (int j = 0; j < led; j++) {
            strip.setPixelColor(j, strip.Color(0, 0, 0));  //關閉led
          }
        }
      }
      strip.show();
    } else {  //stop
      for (int i = 0; i < (led * 2 + cled); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));  //關閉led
      }
      strip.show();
    }
  }
}
