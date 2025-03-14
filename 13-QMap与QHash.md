# QMap

QMap是一个以升序键顺序存储键值对的数据结构

- QMap原型为class QMap<K, T>模板

- QMap中的键值对根据key进行了排序

- QMap中的key类型必须重载operator <  (小于操作符)



**QMap使用实例一**

```cpp
QMap<QString,int>map;

map.insert("key 2", 2);
map.insert("key 0", 0);
map.insert("key 1", 1);

for(int i=0; i<3; i++){
    qDebug()<< map.value("key" + "QString::number(i)）;
}

QList<QString>list = map.keys();
for(int i=O; i<list.count(); i++)
{
    qDebug()<< list[i];                         
}
```

**QMap使用实例二**

```cpp
QMap<QString,int>map;
map["key 2"] = 2;
map["key o"] = 0;
map["key l"] = 1;
for(int i=0; i<3; i++){
    qDebug()<<map["key" + QString::number(i)];
}
QMapIterator<QString,int> it(map);
while( it.hasNext())
{
    it.next();
    qDebug()<< it.key()":"<<it.value（);
}
```



**QMap的注意事项**

- 通过key获取Value时
  - 当key存在，返回对应的Value
  - 当key不存在，返回值类型所对应的“零”值

- 插入键值对时
  - 当key存在，更新Value的值
  - 当key不存在，插入新的键值对



**QMap.cpp**

```cpp
#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QMap>
#include<QMapIterator>//迭代器
 
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    QMap<QString, int> map;
    map["key 2"] = 2;
    map["key 0"] = 0;
    map.insert("key 1", 1);
 
   //map.insert("key 1", 4);//前面已有key 1，所有这里会更新key的键值为4
 
    QList<QString> list = map.keys();
 
    for(int i=0; i<list.count(); i++)
    {
        qDebug() << list[i];//打印排序好的key 0、key 1、key 2
    }
 
    QList<int> vlist = map.values();
 
    for(int i=0; i<vlist.count(); i++)
    {
        qDebug() << vlist[i];//打印0、1、2
    }
 
    QMapIterator<QString,int> it(map);//it指向第一个元素之前的位置
    while(it.hasNext())
    {
        it.next();
        qDebug() << it.key() << ":" << it.value() ;
    }
 
    return a.exec();
}
```



------

# QHash

QHash是Qt中的哈希数据结构

- QHash原型为class QHash<K, T>模板

- QHash中的键值对在内部无序排列

- QHash中的Key类型必须重载operator ==

- QHash中的Key对象必须重载全局哈希函数（qHash()）



**QHash使用示例**

```cpp
QHash<Qstring, int> hash;
hash["key 2"] = 2;
hash["key o"] = 0;
hash["key 1"] = 1;
QHash<Qstring, int>::const iterator i;
for(i=hash.constBegin();i!= hash.constEnd();++i){
	qDebug()<< i.key()<< ":"<< i.value();
}
```



**QHash.cpp**

```cpp
#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QHash>
 
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    QHash<QString, int> map;
    map["key 2"] = 2;
    map["key 0"] = 0;
    map.insert("key 1", 1);
 
   //map.insert("key 1", 4);//前面已有key 1，所有这里会更新key的键值为4
 
    QList<QString> list = map.keys();
 
    for(int i=0; i<list.count(); i++)
    {
        qDebug() << list[i];//打印排序好的key 0、key 1、key 2
    }
 
    QList<int> vlist = map.values();
 
    for(int i=0; i<vlist.count(); i++)
    {
        qDebug() << vlist[i];//打印0、1、2
    }
 
    QHash<QString,int>::const_iterator i;
 
    for(i=map.constBegin(); i!=map.constEnd(); ++i)
    {
        qDebug() << i.key() << ":" << i.value() ;
    }
 
    return a.exec();
}
```



------

# QMap和QHash的对比分析

QMap和QHash的接口相同，可直接替换使用

- QHash的`查找速度快`于QMap

- QHash`占用的存储空间多`于QMap

- QHash以任意的方式存储元素

- QMap`以Key顺序存储`元素

- QHash的键类型必须提供operator == () 和 qHash(key)函数

- QMap的键类型必须提供operator <



# 文本编辑器自动加入后缀名

```c++
QString MainWindow::showFileDialog(QFileDialog::AcceptMode mode, QString title)
{
    QString ret = "";
    QFileDialog fd;
    QStringList filters;
    QMap<QString, QString> map;
 
    const char* fileArray[][2]=
    {
        {"Text(*.txt)",    ".txt"},
        {"All Files(*.*)",   "*" },
        {NULL,               NULL}
    };
 
    for(int i=0; fileArray[i][0] != NULL; i++)
    {
        filters.append(fileArray[i][0]);
        map.insert(fileArray[i][0], fileArray[i][1]);
    }
 
    fd.setWindowTitle(title);
    fd.setAcceptMode(mode);
 
 
    fd.setNameFilters(filters);
 
    if(mode==QFileDialog::AcceptOpen)
    {
        fd.setFileMode(QFileDialog::ExistingFile);
    }
 
    if(fd.exec()==QFileDialog::Accepted)
    {
        ret = fd.selectedFiles()[0];
 
        QString posix = map[fd.selectedNameFilter()];//把下拉中选中的后缀对应键值取出
 
        if(posix != "*" && !ret.endsWith(posix))
        {
            ret += posix;
        }
    }
    return ret;
}
```

