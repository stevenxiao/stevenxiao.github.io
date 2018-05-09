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

  a. 设置源
  ![设置`repo`源](.\images\Source_1.jpg)

  点击“增加源”，在下拉菜单中选择`Git`创建一个源配置项：

  ![源2](.\images\Source_2.jpg)

  按自己的需求，设置好`Repository`，`Credentials`，`Behaviours`等，对于每一项的具体含义，可以点击后面的帮助按钮查看。

  

  

