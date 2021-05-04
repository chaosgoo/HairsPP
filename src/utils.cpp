#include "utils.h"

/**
 * @brief 计算16校验和计算
 * @param src 待校验内容
 * @param length 待校验内容长度
 * @retval 校验和
 * */
int checkSum(const char* src, int length) {
  int16_t sum = 0;
  for (int i = 0; i < length; i++) {
    sum += src[i];
  }
  sum = (sum & 0xff) + (sum >> 16);
  return ~sum & 0xff;
}

/**
 * @brief 16进制字符转int
 * @param ch 待转换内容
 * @retval 校验和
 * */
int c2i(char ch) {
  // 如果是数字，则用数字的ASCII码减去48, 如果ch = '2' ,则 '2' - 48 = 2
  if (isdigit(ch)) return ch - 48;

  // 如果是字母，但不是A~F,a~f则返回
  if (ch < 'A' || (ch > 'F' && ch < 'a') || ch > 'z') return -1;

  // 如果是大写字母，则用数字的ASCII码减去55, 如果ch = 'A' ,则 'A' - 55 = 10
  // 如果是小写字母，则用数字的ASCII码减去87, 如果ch = 'a' ,则 'a' - 87 = 10
  if (isalpha(ch)) return isupper(ch) ? ch - 55 : ch - 87;

  return -1;
}

/**
 * @brief 校验接收到的配置合法性
 * @param content 接收到的数据
 * @retval 合法性
 * */
bool validPreference(const char* preference) {
  return checkSum(preference, 3) == preference[3];
}