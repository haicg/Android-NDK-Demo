# TestCpuFeature

## 介绍
   用来测试所使用的Android平台的CPU的特性，例如cpu个数，是否支持NEON特性等。

## 编译

```
	cd jni
	ndk-build
```

## 安装
直接本工程中提供的Android.mk进行编译,
会在obj/local目录下生成所有平台的可执行的文件，
然后copy对应版本的可执行程序到开发板上进行运行。
举个例子：
```
cd obj/local/armeabi-v7a/
adb push TestCpuFeature /system/nfs
```

然后在开发板上运行该程序：
```
cd /system/nfs
./TestCpuFeature
```

注意：这边需要在开发板上创建/system/nfs 这个目录，如果你没有对应的权限，则会失败。

## 相关文件
1. cpufeatures 具体实现文件见目录android-ndk-r15c/sources/android/cpufeatures中cpu-features.c
2. /proc/cpuinfo 存放cpu的基本信息
3. /sys/devices/system/cpu/present
4. /sys/devices/system/cpu/possible

