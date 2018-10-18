# YAML语法

## 基本语法

- 使用`#` 来开启注释
- 使用空格缩进来分层，不同的层次之间可以使用不同的空格数目，但是同层元素一定是左对齐的，即前面的空格数相同（不要使用`tab`）
- 破折号后跟一个空格表示列表
- 冒号和空格表示键值对`key : value`
- 简单数据可以不用括号括起来，包括字符串数据
- 用单引号或双引号括起来的数据被当做字符串出来，使用`C`风格的转义字符

##  数组

一个简单的数组，用 `-` 来列出来即可，如下：

```yaml
- apple
- orange
- banana
```

用`JSON`表示如下：

```json
['apple','orange','banana']
```

## 对象

一个接单的对象是一个`key : value`对，如下所示

```yaml
fruit:
    name   : banana
    amount : 3
    price  : 4.99
```

解析成`JSON`可表示为：

```json
{"fruit":{"name":"banana", "amount":3, "price":4.99}}
```

## 对象数组

对于多个属性的数组，可以如下表示：

```yaml
- name: Jane
  age : 12
- name: Jack
  age : 8
```

用`JSON`表示如下：

```json
[{"name":"Jane", "age":12}, {"name":"Jack", "age":8}]
```

## 数组对象

首先大结构是对象，对象内部是数组：

```yaml
name:
   - apple
   - orange
   - banana
price:
   - 4.99
   - 2.34
   - 3.99
```

解析成`JSON`后可表示为：

```json
{"name" : ["apple","orange","banana"], "price" : [4.99, 2.34, 3.99]}
```

## 多维数组

用中括号包括起来，形成一个二维素组：

```yaml
- [apple, 4.99]
- [orange, 2.34]
- [banana, 3.99]
```

解析成`JSON`可表示成：

```json
{["apple", 4.99],["orange", 2.34], ["banana", 3.99]}
```

## 对象的扩展写法

对于`kv`结构的对象，支持使用花括号的方式来替代，如下所示：

```yaml
love:{name: appple, price: 2.99}
hate:{name: orange, price: 3.99}
```

等同于：

```yaml
love:
   name  : apple
   price : 2.99
hate:
   name  : orange
   price : 3.99
```

