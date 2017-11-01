# `Python`中`argparse`的用法

`argparse`是`Python`标准库中的命令行分析模块，其功能非常强大。`argparse`是基于`optparse`发展而来的，不过现在`optparse`已经被弃用了。类似的还有`getopt`包，这个包跟`C`语言中的`getopt()`函数的功能比较类似。
本文主要记录一下`argparse`的主要用法。

## 基础

首先看一下`argparse`的简单用法,下面这个代码片段只是建立了一个分析器，并没有任何的作用：
```python
import argparse

parser = argparse.ArgumentParser()
parser.parse_args()
```

执行这段代码会得到如下的输出：
```bash
$ python prog.py
$ python prog.py -h
usage: prog.py [-h]

optional arguments:
-h, --help  show this help message and exit

$ python prog.py --verbose
usage: prog.py [-h]
prog.py: error: unrecogonized argument: --verbose

$ python prog.py foo
usage: prog.py [-h]
prog.py: error: unrecogonized argument: foo
```

## 添加位置参数（`Position arguments`）
在`argparse`中添加一个必须的参数非常简单，如下所示：
```python
import argparse

parser = argparse.ArgumentPArser()
parse.add_argument("echo")
args = parse.parse_args()

print(args.echo)
```
这段代码中添加了一个必须的参数`echo`，运行一下：
```Bash
$ python prog.py
usage: prog.py [-h] echo
prog.py: error: the following arguments are reuqired: echo

$ python prog.py --help
usage: prog.py [-h] echo

positional arguments:
    echo

optional arguments:
    -h, --help: show this help message and exit

$ python prog.py foo
foo
```
1. 第一次运行的时候，因为没有传入必须的参数，所以运行出错，并给出了错误的原因：`echo`是必须传入的参数。
2. 第二次运行`help`指令，查看所有的参数，可以看到`echo`是`positional arguments`，而不是`optional arguments`。
3. 传入参数`foo`，会看到程序正常运行，并打印出结果。

从上面可以看出，通过`argparse`来管理命令行参数非常简单，值需要调用`add_argument`函数，就可以添加想要的参数。但是默认的情况下，参数的类型都是`str`类型的，那如果想要一个指定类型的参数，该怎么办呢？非常简单，`add_argument`函数有一个可选参数`type`，默认是`str`的，你可以指定你想要的类型，如`int`:
```Python
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("square", type=int, help="display a square of a given number")
parser.parse_args()

print(args.square**2)
```

## 可选参数(`Optional arguments`)
以上看到的都是添加的`Positional Arguments`，也就是必须的参数，那如何添加一个非必须的参数呢？其实也非常简单，下面来看一段代码：
```Python
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--verbose", help="increse output verbosity")
args = parser.parse_args()
if args.verbose:
    print("verbosity turned on")
```
运行一下：
```Bash
$ python prog.py --verbose
Usage: prog.py [-h] [--verbose VERBOSE]
prog.py: error: argument --verbose: expected one argument
```
可以看到，程序执行失败了，这是为什么呢？这是因为默认情况下所有的参数都会需要一个值，如果只想要一个不需要传值的参数，那么需要设置一下这个参数，只需要在调用`add_argument`的时候多设置一个可选参数即可，如下所示：
```Python
parser.add_argument("--verbose", action="store_true", help="increse output verbosity")
```
修改好了之后，再次执行上面的程序：
```Bash
$ python prog.py --verbose
verbosity turned on
```
可以看到程序执行成功了。但是如果这个时候，再给参数传值的话会发生什么呢？
```Bash
$ python prog.py --verbose 1
usage: prog.py [-h] [--verbose]
prog.py: error: unrcognized arguments 1
```
会看到，`1`被当做一个参数而不是`verbose`的值传入，当然会出错啦，毕竟没有`1`这个参数嘛。
### 短选项(short option)
可以看到，在显示`help`的时候，输入的其实是`-h`而不是`--help`这个全称，如果想为自己的参数定义一个简写，该如何做呢？继续以上面的列子来说，其实很简单，只要在调用`add_argument`的时候，把简写形式传到函数里面就可以了啊，如下所示：
```Python
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-v", "--verbose", action="store_true", help="increase output verbosity")
args = parser.parse_args()
if args.verbose:
    print("verbosity turned on")
```
这个时候，就可以使用`"-v"`来替代`"--verbose"`了：
```Bash
$ python prog.py -v
verbose turned on

$ python prog.py -h
usage: prog.py [-h] [-v]

optional arguments:
    -h, --help show this help message and exit
    -v, --verbose increase output verbose
```
## 组合参数
先来看一段代码：
```Python
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("square", type=int, help="display a square of a given number")
parser.add_argument("-v", "--verbose", action="store_true", 
                    help="increase output verbose")
args = parser.parse_args()
answer = args.square**2
if args.verbose:
    pring("the square of {} equals {}".format(args.square, answer))
```
可以看到，这段代码里面，既含有`positional argument`，也有`optional argument`，执行这段代码：
```Bash
$ python prog.py 2
4

$ python prog.py 2 -v
the square of 2 equals 4
```
那如果当输出的格式有多种的时候，应该怎么办呢？有两种做法，下面先看第一种：
```Python
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("square", type=int, help="display a square of a given number")
parser.add_argument("-v", "--verbose", type=int, 
                    help="increase output verbose")
args = parser.parse_args()
answer = args.square**2
if args.verbose == 2:
    pring("the square of {} equals {}".format(args.square, answer))
elif args.verbose == 1:
    print("{}^2 = {}".format(args.square, answer))
else:
    print(answer)
```
执行这个程序：
```Bash
$ python prog.py 4
16
$ python prog.py 4 -v
usage: prog.py [-h] [-v VERBOSE] square
prog.py: error: argument -v/--verbose: expected one argument
$ python prog.py 4 -v 1
4^2 == 16
$ python3 prog.py 4 -v 2
the square of 4 equals 16
$ python prog.py 4 -v 3
16
```
可以看到，这个程序在`verbose`为`1`和`2`的时候得到了想要的结果，但是对于其他的数值，就有待商榷了。那么有没有办法可以让所有`>2`的值得到想通的结果呢？或者有没有办法限制`verbose`的可选值呢？当然是有的，先看第一种，比较简单，稍微修改一下程序：
```Python
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("square", type=int, help="display a square of a given number")
parser.add_argument("-v", "--verbose", type=int, 
                    help="increase output verbose")
args = parser.parse_args()
answer = args.square**2
if args.verbose >= 2:
    pring("the square of {} equals {}".format(args.square, answer))
elif args.verbose >= 1:
    print("{}^2 = {}".format(args.square, answer))
else:
    print(answer)
```
那如果想要限制`verbose`的值，改怎么做呢？这个时候就要用到`add_argument`的可选参数`choice`了，如下所示：
```Python
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("square", type=int, help="display a square of a given number")
parser.add_argument("-v", "--verbose", type=int, choice=[0,1,2],
                    help="increase output verbose")
args = parser.parse_args()
answer = args.square**2
if args.verbose == 2:
    pring("the square of {} equals {}".format(args.square, answer))
elif args.verbose == 1:
    print("{}^2 = {}".format(args.square, answer))
else:
    print(answer)
```
再次执行上面的程序：
```Bash
$ python prog.py 4 -v 3
usage: prog.py [-h] [-v {0,1,2}] square
prog.py: error: argument -v/--verbose: invalid choice: 3 (choose from 0, 1, 2)
$ python prog.py 4 -h
usage: prog.py [-h] [-v {0,1,2}] square

positional arguments:
  square                display a square of a given number

optional arguments:
  -h, --help            show this help message and exit
  -v {0,1,2}, --verbose {0,1,2}
                        increase output verbose
```

可以看到，对于不属于`[0,1,2]`中的值，程序会直接报错。
下面来看一个更高级的玩法，如果想通过`"-vv"`或者`"-vvvv"`这种形式来控制输出的格式，应该怎么做呢？这可以通过设置`action=count`来达到这个目的：
```Python
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("square", type=int, help="display a square of a given number")
parser.add_argument("-v", "--verbose", action="count", default = 0,
                    help="increase output verbose")
args = parser.parse_args()
answer = args.square**2
if args.verbose >= 2:
    pring("the square of {} equals {}".format(args.square, answer))
elif args.verbose >= 1:
    print("{}^2 = {}".format(args.square, answer))
else:
    print(answer)
```
执行这个程序：
```Bash
$ python prog.py 4
16

$ python prog.py 4 -v
4^2 = 16

$ python prog.py -vv
the square of 4 equals 16

$ python prog.py -vvv
the square of 4 equals 16

$ python prog.py --verbose --verbose
the square of 4 equals 16
```
可以看到，除了设置了`action`之外，还有一个`default`参数被设置为`0`，这是因为，如果不设置这个值的话，当没有参数`"-v"`的时候会报错。

### 冲突选项
有的时候，两个参数之间是互斥的，那么这个时候，当同时使用互斥的参数的时候就需要告诉使用者，这是错误的，可以通过函数`add_mutually_exclusive_group()`来实现这一目标。
```Python
import argparse

parser = argparse.ArgumentParser()
parser.add_mutually_exclusive_group()
parser.add_argument("-v", "--verbose", action="store_true")
parser.add_argument("-q", "--quiet", action="store_true")

parser.add_argument("x", type=int, help="the base")
parser.add_argument("y", type=int, help="the exponent")

args = parser.parse_args()

answer = args.x ** args.y
if args.quiet:
    print(answer)
elif args.verbose:
    print("{} to the power {} equals {}".format(args.x, args.y, answer))
else:
    print("{}^{}={}".format(args.x, args.y, answer))
```
