- **创建数据库**



- **删除数据库**



- **切换数据库**

  `use db`

- **显示当前所使用的数据库**

  `db`

  ![1615111015816](image/1615111015816.png)

- **显示所有数据库**

  `show dbs`

  ![1615110993205](image/1615110993205.png)

- **创建集合**

    `db.createCollection()`

![1615110552711](image/1615110552711.png)

- **删除集合**



- **显示集合**

  `show collections`

![1615691456600](image/1615691456600.png)

- **查看集合信息**

  `db.getCollectionInfos()`

  ![1615113288341](image/1615113288341.png)



- 插入文档

  `db.collections.insertMany()`
  
  ```
  db.inventory.insertMany([
     { item: "journal", qty: 25, status: "A", size: { h: 14, w: 21, uom: "cm" }, tags: [ "blank", "red" ] },
     { item: "notebook", qty: 50, status: "A", size: { h: 8.5, w: 11, uom: "in" }, tags: [ "red", "blank" ] },
     { item: "paper", qty: 10, status: "D", size: { h: 8.5, w: 11, uom: "in" }, tags: [ "red", "blank", "plain" ] },
     { item: "planner", qty: 0, status: "D", size: { h: 22.85, w: 30, uom: "cm" }, tags: [ "blank", "red" ] },
     { item: "postcard", qty: 45, status: "A", size: { h: 10, w: 15.25, uom: "cm" }, tags: [ "blue" ] }
]);
  ```
  
  ![1615111104024](image/1615111104024.png)
  
  `db.collections.insertOne()`

![1615112008530](image/1615112008530.png)



- 删除文档



- 查找文档

  `db.collections.find({})`

  ![1615111223647](image/1615111223647.png)
  
  `db.collections.find({}).pretty()`
  
  ![1615111323177](image/1615111323177.png)
  
  ![1615111934304](image/1615111934304.png)
  
  `db.find({}, {_id: 0 | 1, key:1,key:1})`
  
  ![1615112499502](image/1615112499502.png)



- 更新文档



