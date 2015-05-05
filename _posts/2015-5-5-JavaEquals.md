---
layout: post
title: equals() and '==' in Java
---

总的来说，"=="就是来比较两个引用的值是否相等，我们都知道Java中的引用是存在于stack空间的， 然后其内的值指向堆空间或data segment，引用相当于本质上的指针。因此判断两个引用的值是否相等，那么也就意味着判断两个引用是否指向同一个heap空间或data segment对象。若是同一个对象，那么返回true，若不是同一个对象，即便对象其内容完全相同，但由于其地址不一样，所以相对应的引用值也不可能相同。那么如何判断判断两个对象其内的内容是否相同呢？唯一的方法就是去override每一个类继承自Object类的equals方法。在这个重写的equals方法内，使得两个具有相同内容但是不同引用值的两个对象互相之间equals。同时一定记得的是，重写equals方法则一定要重写hashCode()方法。

下面的摘自于[StackOverflow中的回答](http://stackoverflow.com/questions/7520432/java-vs-equals-confusion)

> if a class does not override the equals method, then it defaults to the equals(Object o) method of the closest parent class that has overridden this method.
> If no parent classes have provided an override, then it defaults to the method from the ultimate parent class, Object, and so you're left with the Object#equals(Object o) method. Per the Object API this is the same as ==; that is, it returns true if and only if both variables refer to the same object, if their references are one and the same. Thus you will be testing for object equality and not functional equality.
> Always remember to override hashCode if you override equals so as not to "break the contract". As per the API, the result returned from the hashCode() method for two objects must be the same if their equals methods shows that they are equivalent. The converse is not necessarily true.