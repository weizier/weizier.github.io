---
layout: post
title: Introduction to MongoDB
---

MongoDB是一个非关系型数据库，也就是NOSQL的代表。安装成功之后，有两个执行程序非常重要，分别是mongod.exe和mongo.exe，前者是server，后者是shell。数据文件都存放在F:/data/db文件夹下。为了方便以后我们能够轻松启动这两个文件，我们把mongod.exe和mongo.exe这两个文件所在路径添加到系统的PATH环境变量里，这样下次我们在命令行窗口直接输入mongod和mongo的时候，系统会到这两个路径下寻找是否有这两个可执行文件，从而方便我们快速启动mongdb服务。

pymongo 的最新版是3.0，但是我这里升级不到该最新版本，所以依然使用的2.8，但是2.8有一些命令和3.0并不相同，故下了一个2.8的Documentation在F:/Program Files/MongoDB目录下。

使用pymongo并不复杂，下面介绍一些基本操作。需要注意的是，在所有对数据库进行操作之前，都必须先把mongod.exe执行，也就是先启动server才行。

	#coding:utf8
	"""
	----------------------------------
	在运行之前一定要记得先把server打开
	----------------------------------
	"""
	import pymongo
	client = pymongo.MongoClient(‘localhost’,27017)  #建立与MongoDB的连接
	db = client.xuwei                             #创建一个名为‘xuwei’的数据库。
	collection=db.xwcollection                     #获取一个名为‘xwcollection’的collection
	post = {"author": "Mike",        
		  "text": "My first blog post!",
		  "tags": ["mongodb", "python", "pymongo"]}  #建立要插入的数据，也就是Document
	post_id=collection.insert(post)                   #插入Document，并获得相应id
	a=collection.find_one()                         #找到collection中的第一个Document
	b=collection.find_one({‘author’:’Mike’})   #找到符合条件的Document,注意查询条件是dict
	collection.find_one({"_id": post_id})             #通过_id这个属性来寻找也是可以的
	new_post=[{"author": "Mike", 
			   "text": "Another post!",
			   "tags": ["bulk", "insert"],
			   "date": datetime.datetime(2009, 11, 12, 11, 14)},
			   {"author": "Eliot",
			   "title": "MongoDB is fun",
			   "text": "and pretty easy too!",
			   "date": datetime.datetime(2009, 11, 10, 10, 45)}]  #NOSQL对非结构化数据支持

	#千万注意这里的存储形式！！因为new_post是一个list，其内是两个dict。
	#并不是全盘把new_post存到一个document里，而是把new_post当做两个document。
	new_post_id=collection.insert(new_posts)      #非结构化数据格式在MongoDB里叫BSON
	for post in collection.find():        #collection的find()返回一个cursor，用for来迭代
		post                       #find()也可以如同find_one()加入一些查询的限制条件
	count = collection.count()          #对collection里存储的Document进行计数
	c=collection.find({"author": "Mike"}).count()         #对符合条件的查询结果进行计数
	for post in collection.find({"author":’Mike’}).sort("date"):  
		print post                        #对符合条件的查询结果按照date键值进行排序


另外，一个非常重要的值得注意的问题是：在非正常关闭mongoDB之后，重新启动mongod.exe，这个时候mongod这个server会报错：dbexit:really exiting now.当出现这种错误的时候，一般就说明上次MongoDB非正常关闭，数据库已经将你的数据锁死了，具体表现是data/db路径下的mongod.lock这个文件。所以我们先要把它给删掉，并且在命令行下执行mongod --repair以恢复数据。然后再重新启动mongod.exe，这样就不会报错。
正常的关闭数据库的方式是在mongo shell（也就是另开一个cmd，在里面启动mongo）里use admin，然后db.shutdownServer()，可以仔细观察mongod界面出现了什么变化，然后再在mongo shell里使用quit()方法退出mongo shell。这样便可正常退出了。修复的过程中，是对所有数据库都进行修复，所以整个过程可能会比较慢，修复之后的数据会替换原始的数据。并且似乎官网上说明64bit版本的mongodb会默认开启journal机制，然后这个会很好的解决意外关闭而数据丢失的问题。

mongodb在windows下存储果然非常耗存储，原本阿里巴巴竞赛的数据大小为五百多兆，想将之存储到mongodb数据库中，存储下来有好几个文件，比如我命名的数据库名称为“alibaba”，然后有这几个文件出现：alibaba.0,alibaba.1,alibaba.2,alibaba.3，文件大小分别为64M，128M，256M，512M，从这可以看出，MongoDB的存储方式是慢慢变大的，但是这个时候再要变大，便报错了，在mongodb的官方文档中曾经有说过，在32位windows下的版本不支持超过2G的文件。这里还不到2G便不支持了。

一般来说，32位的CPU都能安装64位系统，并且以后都是64位系统的趋势，如果内存大小超过4G的话，安装32位系统无法完全用到这4G，相当于很多都被浪费了。所以尽量安装64位系统吧。

use database_name
db.collection_name.remove({}) 这是删除collection_name这个集合中的所有数据，但是保留集合本身

db.collection_name.drop()   集合本身也被删除
db.dropDatabase()           删除整个数据库


mongodb无法存储包含有python中set的对象，必须先将set转化为list之后才行。


