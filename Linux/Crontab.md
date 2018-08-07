## 命令格式

```shell
crontab [-u user] file
crontab [-u user] -e|-r|-l
```

- `-u user`: 用来设定某个用户的`crontab`服务
- `file`: 用来指定`crontab`所使用的文件名字。如果为空则接受标准输入（键盘）上的命令，并载入`crontab`
- `-e`: 编辑某个用户的`crontab`文件内容，如果不指定用户，则表示编辑当前用户的`crontab`文件
- `-l`: 显示某个用户的`crontab`文件内容，如果不指定用户，在显示当前用户的
- `-r`: 从`/var/spool/cron`目录中删除某个用户的`crontab`文件，如果不指定用户，则删除当前用户的
- `-i`: 在删除用户的`crontab`文件是给出提示

## 文件格式

`* * * * * *`从左往右，每一个星号分别表示“分钟，小时，日期，月份，星期几，执行的命令

## 使用示例

- Exam 1

```shell
* * * * * myCommand
```

每一分钟执行一次`myCommand`

- Exam 2

```shell
3,15 * * * * myCommand
```

每个小时的 3 分，和 15 分执行`myCommand`

- Exam 3

```shell
3,15 8-11 * * * myCommand
```

每天上午的 8 到 11 点的 3 分和 15 分执行`myCommand`

- Exam 4

```shell
3,15 8-11 */2 * * myCommand
```

每隔两天的上午的 8 到 11 点的 3 分和 15 分执行`myCommand`

- Exam 5

```shell
3,15 8-11 * * 1 myCommand
```

每周 1 的上午 8 到 11 点的 3 分和 15 分执行`myCommand`

- Exam 6

```shell
30 21 * * * /etc/init.d/smb restart
```

每天晚上 9 点 30 重启`smb`

- Exam 7

```shell
45 4 1,10,22 * * /etc/init.d/smb restart
```

每个月的 1 号，10 号，22 号的早上 4 点 45 分重启`smb`

- Exam 8

```shell
10 1 * * 6,0 /etc/init.d/smb restart
```

每周 6 和每周日的早上 1 点 10 分重启`smb`
