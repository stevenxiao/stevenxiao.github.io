# 创建Pipeline

## 经典界面

1. 登录`Jenkins`经典界面

2. 点击左侧`pannel`的“新建任务”
   ![新建任务](.\images\new_01.jpg "新建任务")

3. 在新建`Job`页面输入任务名称并选择“流水线”(`Pipeline`)，点击“确认”后即可进入`Pipeline`的配置页面。

      ![Job选择界面](.\images\Job_1.jpg)

      也可以创建一个`multibranch`的`Pipeline`，在`Job`创建页面选择`Multibranch Pipeline`即可。

      ![Multibranch](.\images\Multi_Job_1.jpg)

      我们主要用到的是后面这种`Pipeline`，所以后面主要介绍这种模式。

4. 配置`Pipeline`
  设置源
  ![设置`repo`源](.\images\Source_1.jpg)
  点击“增加源”，在下拉菜单中选择`Git`创建一个源配置项：
  ![源2](.\images\Source_2.jpg)
  按自己的需求，设置好`Repository`，`Credentials`，`Behaviours`等，对于每一项的具体含义，可以点击后面的帮助按钮查看。

5. 配置`Build Configutration`
      这部分配置目前只支持`Jenkinsfile`，所以不需要做任何修改。
      ![Build Conf](.\images\build_conf_1.jpg)

6. 设置扫描间隔
      ![Scan interval](.\images\scan_interval_1.jpg)
      在“扫描`Multibranch Pipeline Triggers`”下根据需要设置扫描代码源的间隔时间。
      基本上新建一个`Pipleline`配置完这些就基本 `OK`了，如果需要配置其他的地方，可以参考[官方文档](https://jenkins.io/doc/book/pipeline/)。
      成功创建之后，过一会儿你会看到你的`Pipeline`界面会对所配置`repo`的所有分支做一次`Test`（当然前提是需要在`repo`里面放置一份`Jenkinsfile`，后面会介绍到）。
      ![Test Result](.\images\success_1.jpg)

##Blue Ocean界面创建

除了通过经典界面创建之外，也可以通过`Blue Ocean`界面创建`Pipeline`。
在`Jenkins`主界面的侧边栏点击`Open Blue Ocean`即可进入`Blue Ocean`界面：
![`Blue Ocean`](.\images\enter_Blue_Ocean.jpg)
进入之后，`Blue Ocean`的界面显示如下：
![Blue Ocean Dash](.\images\blue_ocean_1.jpg)
点击“创建流水线”进入`Pipeline`创建页面：
![创建页面](.\images\create_pipeline_2.jpg)
选择自己的`repo`类型，输入正确的`URL`,并且把`SSH key`添加到自己的`Git Server`点击“创建`Pipeline`”即可创建，创建成功后显示如下：
![创建`Pipeline`成功](.\images\success_2.jpg)

在经典界面查看该`Pipeline`的配置，可以发现其自动生成的配置跟之前手动配置的比较相似。

# Jenkinsfile 文件

`Jenkinsfile`作为定义`Pipeline`流程的文件，在`Pipeline`中有着非常重要的作用！

首先，`Jenkinsfile`定义了整个`Pipeline`所有需要`involve`的任务节点以及这些任务节点运行的顺序，下面先看一个实际的例子：

```groovy
pipeline {
  agent {
    node {
      label 'master'
    }
  }
    
  stages {
    stage('SonarAnalysis') {
      steps {
        script {
                   if (env.BRANCH_NAME == 'master') {
                           echo "${env.BRANCH_NAME}"
                           build job:'3s-portal-Sonar', parameters: [string(name: 'BRANCH_NAME', value: String.valueOf("${env.BRANCH_NAME}"))]
                   }else{
                          echo "${env.BRANCH_NAME}"
                          echo 'pass this steps'
                   }
                }
      }
    }
	stage('WhiteApiTest') {
	  steps {
		  script {
               if (env.BRANCH_NAME == 'master') {
                       echo "${env.BRANCH_NAME}"
                       build job:'3ss_auto_test', parameters: [string(name: 'BRANCH_NAME', value: String.valueOf("${env.BRANCH_NAME}"))]             
               }else{
                      echo "${env.BRANCH_NAME}"
                      build job:'3ss_WhiteApiTest', parameters: [string(name: 'BRANCH_NAME', value: String.valueOf("${env.BRANCH_NAME}"))]
               }
            }
	  }
	}
    stage('SystemApiTest') {
      steps {
        script {
                 if (env.BRANCH_NAME == 'master') {
                         echo "${env.BRANCH_NAME}"
                         build '3S-Server-Test'                 
                 }else{
                        echo "${env.BRANCH_NAME}"
                        echo 'pass this steps'
                 }
              }
      }
    }
  }
}
```

`Jenkinsfile`支持的语法是一种类`Groovy`的`DSL`，但也有一些特殊的规则：

* 最顶层必须是是`pipeline{}`块
* 没有分号`(:)`作为语句的结束符，每一行都是一个单独的声明
* 块只能包含`Section`，`Directive`，`Steps`或者赋值语句
* 属性引用语句会被当成没有参数的方法调用，例如，`input`会被当成`input()`

## Jenkinsfile 之 Section

`Jenkinsfile`中的`Section`可以包含指令和步骤。比较常用的有比如上面给出的示例中的那几个，下面会简单的介绍一下它们的基本含义：

### agent

`agent section`指明了整个`Pipeline`或者指定的`satge`会在哪个`Jenkins`环境中运行，每个`Jenkinsfile`的最顶端都必须要定义一个`agent`，每个`stage`则可以根据实际情况而定。`agent`的参数可以有很多种类型，下面简单介绍几种常用的：

- `any`：可以在任何`agent`上执行`pipeline`或`stage`，例如：`agent any`
- `label`：在`Jenkins`环境中使用`lable`指定的`agent`来运行`pipeline`或者`stage`，例如：`agent {label 'master'}`
- `node`：类似于`label`，但是`node`允许额外的可选参数。我们的示例中使用的就是这种类型来定义`pipeline`需要执行哪个`agent`上。

其他的参数还有很多，如`none`，`docker`和`dockerfile`等，在用到的时候大家可以根据需要去查阅相关的文档。

### post

`post section`可以定义一个或多个`steps`，这些`steps`会根据`pipeline`的运行结果来决定是不是要执行，它支持以下条件块：

- `always`：不管`pipeline`运行完成之后的状态是什么样子，都会被执行到
- `changed`：只有当前执行的结果和上次执行的结果不一样的时候才会执行
- `fixed`：当前执行结果为`success`，上次执行为`fail`才会执行
- `regression`：上次执行结果为`success`，本次执行结果为`fail`,`unstable`,`abort`时才会执行
- `abort`：当前执行被`abort`的时候会执行
- `failure`：当前执行`fail`的时候执行
- `success`：当前执行`success`的时候执行
- `unstable`：当前`pipeline`或`stage`被标记为`unstable`的时候才会执行
- `cleanup`：所有的`post`条件被评估完之后执行，不考虑`pipeline`和`stage`的状态
- 例如：

```groovy
pipeline{
    agent any
    stages{
        stage('Test'){
            steps{
                echo 'Test Step'
            }
        }
    }
    post{
        always{
            echo 'I will always printed!'
        }
    }
}
```

*`Note`*: `post section`需要定义在`Jenkinsfile`的末尾！

### stages

`stages`定义了一个或多个`stage`命令，它描述了`pipeline`将会执行的一系列的操作，比如运行一个`Job`，或者配置环境等等，在本节的一开始我们给出的示例中，`stages section`就包含了3个`stage`，分别对应了该`pipeline`会执行到的3个`Job`，分别是`Sonar`静态扫描，白盒测试和系统`API`黑盒测试。

### steps

`steps section`定义了一系列的需要在`stage`中执行的步骤，每一个`steps`都必须包含一个或多个步骤。

##Jenkinsfile之Directive

在`Jenkinsfile`中可以定义很多的命令(`directive`)，下面讲一下我们会用到的几个命令。

### environment

`environment`命令主要用来定义一些`key-value`对，`key`表示变量名，`value`表示变量的值，在这里定义的变量在后续的步骤中都能够被使用。`environment`命令既可以出现在`pipeline`的最外层，也可以出现在`stage`中。例如：

```groovy
pipeline{
    agent any
    environment {
        CC = 'clang'
    }
    stages{
        stage("Test") {
            environment {
                AC_KEY = "asdasdsswww"
            }
            steps{
                echo "Test step"
            }
        }
    }
}
```

对于一些会重复执行命令的项目来说，这会非常的有帮助。

### stage

`stage`命令被定义在`stages`中，它会包含`steps section`，`agent`（可选）或者其他的命令。

### when

`when`命令允许`pipeline`根据给定的条件来决定是否运行`stage`，它必须包含至少一个条件！只有当所有的条件为`true`的时候，stage才会被执行。例如：

```groovy
pipeline{
    agent any
    stages{
        stage("Test"){
            when{
                branch "master"
            }
            steps{
                echo "Test"
            }
        }
    }
}
```

`when`命令有很多内置的条件，比如`branch`,`allOf`,`anyOf`等，大家可以参考[官方文档](https://jenkins.io/doc/book/pipeline/syntax/#when)。

##Jenkinsfile之并行

`stage`之间是可以并行运行的，但是有一些需要注意的地方，一个`stage`只可以包含一个`steps`或者`parallel`。

