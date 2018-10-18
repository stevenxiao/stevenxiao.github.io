# gRPC简介

`gRPC`是`Google`开源的一种`RPC`通信协议，它基于`HTTP 2.0`，并使用`Protobuf`作为其数据传输协议。

## Protocol Buffer

`Protocol Buffer` 是`Google`开源的一种序列化结构化数据通信协议（后面简称`Protobuf`），类似于`XML`， 但是`Protobuf`更小巧，更快，更简单。下面看一个示例：

```protobuf
syntax ="proto3" //version 3

message InstallData {
    string request_id = 1; //mongoID
    string source = 2; // adn就传adn，3s就传3s

    int32 offer_id = 3;
    int32 channel_id = 4;
    string subid = 5;

    string devid = 6;
    string gaid = 7;
    string idfa = 8;

    string mac = 9;
    string imei = 10;

    UserAgentDetail ua_detail = 11;
    string ip = 12;
    int32 timestamp = 15;

    map<string, string> store_data = 14; // 回传调用 grpc click 时的 store_data 参数

    Source3SData source_3s = 16;  // 3s 的在 grpc click 逻辑中产生的3s专用业务数据
}

message UserAgentDetail {
    string device = 1;
    string os = 2;
    string ua = 3;
}

message Source3SData {
    int32 offer_id = 1;
    int32 channel_id = 2;
    string subid = 3;
    string subid_origin = 6;
    string query = 4;
    string options = 5;
    string mtg_clickid = 7;
    string sss_clickid = 8;
    string devid = 9;
    string ip = 10;
}
```

上面的定义第一行指定了使用的`Protobuf`的版本是第`3`版（如果没有指定的话，默认是第`2`版的， 这里我们主要以第`3`版为例）。

接下来定义了三个`message`，`Protobuf`中每一个`message`都可以看做是一个独立的数据块，它可以包含应用中所需要的各种数据，当然也可以包含其他的`message`,在`InstallData`中就包含了另外两个数据块`UserAgentDetail`和`Source3SData`。

在`message`中，我们可以看到每个字段都有三部分组成：

*   数据类型： 限定该字段所能存储的数据的类型，不能存储其他的类型。`Protobuf`的数据类型以及其对应其他语言的类型可以在[这里](https://developers.google.com/protocol-buffers/docs/proto3#scalar)找到。
*   字段的标识名
*   分配的域数字：每个字段都会对应的一个唯一且独一无二的数字，这个数字是用来标识二进制格式数据中对应字段的标签



## gRPC





## 当弱类型语言遇上强类型数据结构

