/*
  main.cpp - HairsPP
  Original Copyright (c) 2021 Chaos Goo.  All right reserved.
  New version by Christopher Andrews 2015.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <EEPROM.h>

#include "Keyboard.h"
#include "utils.h"

// 连发间隔 默认10ms
#define TRIGGER_INTERVAL 10

// 拨码开关的引脚5和6
#define SW_1_PIN 6
#define SW_2_PIN 5

extern const uint8_t _asciimap[128] PROGMEM;

// 按键数量
const int keyNum = 3;
// 按键对应引脚
const int keyPin[] = {4, 3, 7};
// 监听器
bool observer[keyNum];
// 具体的按键对应值，请参考"Keyboard.h"内宏定义
byte keyCodes[3] = {KEY_LEFT_CTRL, 'c', 'v'};
// 串口数据缓存
byte preferenceBuffer[10];
// 普通键盘模式
void keyboardMode() {
  if (!digitalRead(SW_1_PIN) && digitalRead(SW_2_PIN)) {
    // 连发模式
    for (int i = 0; i < keyNum; i++) {
      if (digitalRead(keyPin[i]) == LOW) {
        Keyboard.press(keyCodes[i]);
        Keyboard.release(keyCodes[i]);
      }
    }
    delay(TRIGGER_INTERVAL);
  } else {
    // 常规模式
    for (int i = 0; i < keyNum; i++) {
      if (digitalRead(keyPin[i]) == LOW) {
        if (observer[i]) {
          Keyboard.press(keyCodes[i]);
          observer[i] = false;
        }
      } else {
        Keyboard.release(keyCodes[i]);
        observer[i] = true;
      }
    }
  }
}

// 载入预设
void loadPreset() {
  keyCodes[0] = KEY_LEFT_CTRL;
  keyCodes[1] = 'c';
  keyCodes[2] = 'v';
}

// 保存配置
void savePreference() {
  for (int i = 0; i < keyNum; i++) {
    EEPROM.write(i, keyCodes[i]);
    // Serial.print((int)keyCodes[i]);
    // Serial.print(",");
  }
  EEPROM.write(0xF, 16);
}

// 载入配置
void loadPreference() {
  for (int i = 0; i < keyNum; i++) {
    keyCodes[i] = EEPROM.read(i);
  }
}

// 复位
void reset() {
  loadPreset();
  savePreference();
  EEPROM.write(0xF, 1);
}

void setup() {
  // 初始化键盘
  Keyboard.begin();
  // 初始化引脚
  for (int i = 0; i < keyNum; i++) {
    pinMode(keyPin[i], INPUT_PULLUP);
  }
  // 预设配置
  int defFlag = EEPROM.read(0xF);
  if (defFlag != 16) {
    reset();
  }
  loadPreference();
  Serial.begin(9600);
  // 仅仅在启动时候复位
  if (digitalRead(SW_1_PIN) && !digitalRead(SW_2_PIN)) {
    reset();
  }
}

void loop() {
  if (!digitalRead(SW_1_PIN) && !digitalRead(SW_2_PIN)) {
    while (Serial.available() > 0) {
      Serial.readBytes(preferenceBuffer, 4);
      if (checkSum((const char *)preferenceBuffer, 3) == preferenceBuffer[3]) {
        keyCodes[0] = preferenceBuffer[0];
        keyCodes[1] = preferenceBuffer[1];
        keyCodes[2] = preferenceBuffer[2];
        // keyCodes[0] = (byte)_asciimap + (preferenceBuffer[0] & 0xff);
        // keyCodes[1] = (byte)_asciimap + (preferenceBuffer[1] & 0xff);
        // keyCodes[2] = (byte)_asciimap + (preferenceBuffer[2] & 0xff);
        savePreference();
        loadPreference();
        Serial.print("ok");
      } else {
        Serial.print("err");
      }
    }
  } else {
    keyboardMode();
  }
}