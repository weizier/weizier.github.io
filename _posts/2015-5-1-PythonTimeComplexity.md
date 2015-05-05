---
layout: post
title: TimeComplexity in Python
---

[Python官方分析](https://wiki.python.org/moin/TimeComplexity)
[Awesome analysis in Python](https://www.ics.uci.edu/~pattis/ICS-33/lectures/complexitypython.txt)

#List

Python中的list本质上更像Java里的ArrayList，是一个动态的array，在需要的时候可以动态的resize到两倍原来大小。所以其append操作的Amortized time仍为O(1)，但是当list满了的时候，再次append就会要O(n)的时间，但是这极少发生。

list和tuple的主要区别：
- Tuple is immutable,but list is mutable;
- Tuple's index has semantic meanings;
- Tuples have structure, lists have order;
- Tuples are heterogeneous data structures (i.e., their entries have different meanings), while lists are homogeneous sequences;
- Python Tuples are Not Just Constant Lists.

[Very brief distinction between tuple and list](http://stackoverflow.com/questions/626759/whats-the-difference-between-list-and-tuples)

set和dict的联系：
Set is a hash table, implemented very similarly the Python dict with some optimizations that take advantage of the fact that the values are always null (in a set, we only care about the keys).  Set operations do require iteration over at least one of the operand tables (both in the case of union).  Iteration isn't any cheaper than any other collection ( O(n) ), but membership testing is O(1) on average.
所以本质上set和dict都是hash table，只是set只关心key，因此当执行i in set的时候，time complexity就是O(1)了。

刚刚又发现了一个很有意思的现象，python果然强大。
python中的int为4字节，范围在-2^31到2^31-1之间，这和Java是一致的。但是python中的long型几乎是无限大，唯一受限制的是存储空间。所以想要多大就可以多大。这点和Java中的long类型的8字节限制完全不一样。并且python中还提供了一个无限大的数：float('inf'),如下可以验证。
	a = 2**10000
	s = bin(a)
	>>>'0b10000...'
	len(s)
	>>>10003
	if float('inf')>a:
		print 'yes'
	>>>yes