# HairsPP

语言: 中文, [English](README.En.md)

![https://img.shields.io/badge/license-GNU-blue.svg?style=flat-square](https://img.shields.io/badge/license-GNU-blue.svg?longCache=true&style=flat-square)
![https://img.shields.io/badge/version-v0.02-orange.svg?style=flat-square](https://img.shields.io/badge/version-v0.02-yellow.svg?longCache=true&style=popout-square)

<img src="./img/Prd_Crop.png" width=480 /><img src="./img/PCB_Crop.png" width=480 />

[HairsPP](https://github.com/chaosgoo/HairsPP) 是Hairs Plus Plus的简写。[HairsPP](https://github.com/chaosgoo/HairsPP)是一个三键的机械键盘。
* 支持热插拔
* 支持连发模式
* 易学的源码
* 自定义按键映射

## TODO
* ~~20210412:电路~~ 
* ~~20210418:初版源码~~ 
* 壳体 
* PC端配置软件


## 食用指南
开关状态(左5号右6号) | 模式名称 | 描述 
:-:|:-:|:-:
00 | 配置模式 | 串口发送三个字符会自动分配到三个键上，一切正常串口会收到"ok"字符。
10 | 连发模式 | 按住按钮会不断触发点击事件
01 | 复位模式 | 恢复默认键位，通电前配置才有效
11 | 常规模式 | 普通键盘的普通行为


## 材料清单

<img src="./img/Bom.png" width=480 />

序号 | 名称 | 数量 | 备注
-|-|-|-
1|ATMega32u4 | 1 | 主控芯片 QFN44封装
2|AP2112K-3.3 | 1 | 5V转3.3V芯片 SOT-23-5
3|16Mhz晶振 | 1 | 2.0*1.6
4|1uF电容 | 1 | 0603
5|22pf电容 | 2 | 0603
6|10uf电容 | 2 | 0603
7|1KΩ电阻 | 5 | 0805
8|10KΩ电阻 | 1 | 0805
9|22Ω电阻 | 2 | 0805
10|凯华热插拔轴座 | 3 | 1511系列
11|轴体 | 3 | 任意轴体
12|2位拨码开关 | 1 | 1.27mm
13|Type-C接口 | 1 | 16p
14|肖特基二极管 | 1 | BAT60JFILM SOD-323
15|微动开关 | 1 | 3x4x2.5 四脚贴片
