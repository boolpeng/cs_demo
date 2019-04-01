# cs_demo
该cs_demo还未完善！

说明：
  1. 对于kv键用C++unordered_map存储
  2. 利用mysql实现数据持久化，即：在存储前先将kv数据写入数据库。服务器重启后，先遍历数据库将数据写回unordered_map
  3. 基本过程(如）：
  1). 客户端发送put(key, value)
  2). 将 put+key+value连接成一个字符串，发送给服务器
  3). 服务器解析接收到的字符串，解析flag、key和value。通过对解析的对第一个word（get, put, delete等）进行分析，调用对应的执行函数
  4). 服务器返回请求（若需要）
