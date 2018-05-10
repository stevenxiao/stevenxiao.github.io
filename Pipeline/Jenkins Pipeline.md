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

`Jenkinsfile`的语法是一种类`Groovy`的`DSL`，但也有一些特殊的规则：

* 最顶层必须是是`pipeline{}`块
* 没有分号`(:)`作为语句的结束符，每一行都是一个单独的声明
* 块只能包含`Section`，`Directive`，`Steps`或者赋值语句
* 属性引用语句会被当成没有参数的方法调用，例如，`input`会被当成`input()`

