---
title: "Linux操作系统——课堂笔记"
date: 2022-12-12T10:54:50+08:00
draft: true
---

## 重定向和管道

### 重定向
执行一个shell命令行时通常会自动打开三个标准文件
- 标准输入文件（stdin）代码为 0 ，使用 < 或 << 
- 标准输出文件（stdout）代码为 1 ，使用 > 或 >>
- 标准错误输出文件（stderr）代码为 2 ，使用 2> 或 2>>
### 输入重定向
- 输入重定向主要用于改变一个命令的输入源，指输入可以不来自标准输入（键盘），而来自一个指定的文件。
- 一般的命令格式为“命令<文件名”
### 重定向标准输出
- ">" 将命令执行的结果输出到指定文件  
```
 [euler@euler ~]$ echo "hello world 1" > a.txt
 [euler@euler ~]$ cat a.txt
 hello world 1
 ```
- ">>" 将命令执行的结果追加输出到指定文件  
```
[euler@euler ~]$ echo "hello world 2" > a.txt
[euler@euler ~]$ cat a.txt
hello world 1
hello world 2
```
### 重定向标准错误
命令执行出错时一般会把错误信息打印到标准错误，而不是标准输出
```
[euler@euler ~]$ ls /usr/bim/ > b.txt
ls: 无法访问/usr/bim/: 没有那个文件或目录
```
#### 重定向标准输出、错误
将输出、错误一起重定向到文件
```
[euler@euler ~]$ ls -l a.txt b.tct
ls: 无法访问b.tct: 没有那个文件或目录

[euler@euler ~]$ ls -l a.txt b.tct > f.txt 2&>1
[euler@euler ~]$ cat f.txt
ls: 无法访问b.tct: 没有那个文件或目录
```
重定向到不同文件
```
[euler@euler ~]$ mkdir -v 2021101401 /usr/bin >output.log 2>error.log
[euler@euler ~]$ cat output.log
mkdir: 已创建目录 "2021101401"
[euler@euler ~]$ cat error.log
mkdir: 无法创建目录"/usr/bin": 文件已存在 
```
将命令的执行结果输出到指定的文件，不是直接显示在屏幕上。
![](/img/image.png)
### 管道
管道可以把一系列命令连接起来，这意味着第一个命令的输出会作为第二个命令的输入通过管道传给第二个命令。  
语法：
`command1|command2|command3|command4`  
示例：
```
[euler@euler ~]$ ls -l | grep 2021
-rw-r--r--.  1 euler euler  14697388 12月  7  2021 hugo_0.80.0_Linux-64bit.deb
drwxr-xr-x.  2 euler euler      4096 10月  9 14:42 linux.2021
```
### wc(word count)
- 可以显示行数、单词数和字符数
- 选项说明：  
 -l:仅显示多少行  
 -w:仅显示多少字（英文单词）  
 -m:多少字符  
 ```
 [euler@euler ~]$ wc -l linux.test1.py
10003 linux.test1.py
```
### xargs(eXtended ARGuments)
-I用来指定替代字符串，后续出现替代字符串的地方都用标准输入的内容替代。并且对于标准输入的每一行，都会执行一次命令。  
例：查到特定文件，显示每个文件加上.bak
```
[euler@euler ~]$ find ./linux-5.9.1 -name *.conf | xargs -I {} echo {}.bak
./linux-5.9.1/Documentation/networking/mac80211_hwsim/wpa_supplicant.conf.bak
./linux-5.9.1/Documentation/networking/mac80211_hwsim/hostapd.conf.bak
./linux-5.9.1/Documentation/docutils.conf.bak
./linux-5.9.1/tools/lib/traceevent/Documentation/asciidoc.conf.bak
./linux-5.9.1/tools/lib/perf/Documentation/asciidoc.conf.bak
./linux-5.9.1/tools/perf/Documentation/asciidoc.conf.bak
./linux-5.9.1/tools/testing/ktest/examples/snowball.conf.bak
./linux-5.9.1/tools/testing/ktest/examples/test.conf.bak
./linux-5.9.1/tools/testing/ktest/examples/crosstests.conf.bak
./linux-5.9.1/tools/testing/ktest/examples/include/min-config.conf.bak
./linux-5.9.1/tools/testing/ktest/examples/include/bisect.conf.bak
./linux-5.9.1/tools/testing/ktest/examples/include/tests.conf.bak
./linux-5.9.1/tools/testing/ktest/examples/include/defaults.conf.bak
./linux-5.9.1/tools/testing/ktest/examples/include/patchcheck.conf.bak
./linux-5.9.1/tools/testing/ktest/examples/kvm.conf.bak
./linux-5.9.1/tools/testing/ktest/sample.conf.bak
./linux-5.9.1/arch/parisc/defpalo.conf.bak
```

