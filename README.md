Douban FM
========
Douban FM客户端Linux版

目前只有最基本的播放功能

## 截图

![截图](https://raw.githubusercontent.com/YiShuiHanXL/DoubanFM/master/snapshot.png)

所用图片资源来自这里，并感谢：

https://github.com/zonyitoo/doubanfm-qt

## TODO:

登陆；

加红心；

不再听到；

界面美化；

音量控制；

暂停。

Qt version: 4.6.3

依赖：phonon libphonon-dev libqt4-phonon libqjson-dev

## 安装方法
```bash
qmake doubanfm.pro
make
```

直接运行doubanfm即可

在装有多块声卡的机器上如果听不到声音，可以试着切换声卡驱动程序。在System Settings里，找到Audio Output-Music，调高Internal Audio Analog Stereo的优先级。



## LICENSE
本项目基于MIT协议发布
MIT: [http://rem.mit-license.org]
