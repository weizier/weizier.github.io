---
layout: post
title: 一道谷歌面试算法题
---
[相关链接](http://blog.csdn.net/morewindows/article/details/8212446)
Google面试题：一个大小为n的数组，里面的数都属于范围[0, n-1]，有不确定的重复元素，找到至少一个重复元素，要求O(1)空间和O(n)时间。

最简答的解法就是重新开辟一个长度为n的数组，然后对原数组从头扫描到尾，对每个数进行计数，并存储在以这个数字为索引的新数组中，如果大于1了，那么表明这个数就是重复的数字。这种方法的时间复杂度为O(N)，但是空间复杂度也为O(N)。这显然是不符合题目要求的。

题目要求O(1)，那么根据之前在听七月算法的视频中提到的，一般O(1)也就意味着要么新开辟的空间为常数空间，要么直接在原始数组中直接处理，也就是in-place.这这道题中，想了想， 暂时还没想到新开辟常数空间的好方法。那既然O(1)有两种方法，何尝不试试直接在数组上进行处理呢？

于是就有了和基数排序相类似的技巧.

首先给定一个数组，从头扫描到尾，如果某个索引值下存储的数跟该索引值不相等，则将该存储值交换到相对应的索引位置上，一直持续这个过程。于是可以仔细想想，在上面的这个问题中，一旦有某个数重复了，则在操作这个数的时候必定会在第二次碰到这个数的时候陷入死循环，从而我们知道了这个数重复了。
这个思想其实和另外开辟一个数组来保存每个数出现次数的思想有异曲同工之妙，只不过此处是直接在原始数组上直接进行操作而已。

刚才在群里发问，对于范围为[0,n]的长度为n的整型数组，需要设计一个算法，统计每个数重复的次数，要求时间复杂度为O(N),空间复杂度为O(1)

5 5 2 4 6 2 1
第一步：a[0]=5,与第五个位置上的数据2进行交换，并把5改成-1，变成2,5,2,4,6,-1,1
第二步：由于第0位数据非负，继续处理第0位，将第2位上的数为2交换到第0位上来，并且第二位设为-1：2,5,-1,4,6,-1,1.
第三步：由于第0位数据依然非负，继续处理第0位，去观察第2位上的数，为负数了，表明曾经见过2，因此第0位上的2不再有意义，直接可以跳过了，当然也可以处理成其他的数。
第四步：a[1]=5,同样去第五个位置，发现已经是-1了， 对其再减1,得到-2,表示5已经出现2次了，并且和第三步类似，第一位也可以跳过，继续下一个位置上的数。此时2,5,-1,4,6,-2,1
第五步：a[2]=-1，不做任何处理，直接下一步循环
以此类推，根据上面的步骤，也就是必须保证当前第i个位置前的所有元素都必须处理完毕，并且那些从其他位置交换过来的数据也都要保证被处理完毕。

其他依次类推

但是也有缺点，就是需要更改原始数组，那么有没有不需要更改原始数组的方法呢？

答案是肯定的，在做类似操作的时候，我们不去真正做交换，而是对于访问过的数在以该数做索引值的元素上进行取反操作。
比如数组a = [3,1,2,1]，对其进行扫描，a[0]=3,也就是说我们访问到了一个3，那我如何记录我访问了一次这个3呢？不能重新开辟一个新的空间，那我只能想到在原始数组上进行思考，在3对应的那个位置上做手脚，比如可以将3对应位置的元素进行取反操作，如果我下次再访问到3，我同样在3位置上进行操作，这时就会发现3位置上的元素已经进行取反操作了，这样就证明了3这个元素已经被访问过了。
	3,1,2,1
	3,1,2,-1
	3,-1,2,-1
	3,-1,-2,-1
	本次循环便可发现位置1上对应的元素已经被取反过了，从而得出1是一个重复的数字。
	
但是，正如上面链接中所说到的那样，当a = [0,1,2,3,0,2]的时候，便不会把0当做重复的数字，2倒是可以正常的判断出来，但是0由于其取反操作无效，所以才会出现这种情况。
但是注意a = [2,0,1,2,0,2]时可以判断出来0为重复的元素。仔细想想为什么？

那如何解决这个问题呢？当我们知道数组中元素的范围时，比如都小于n，那么我们可以对访问过元素相对应的索引值上的数值进行加n操作，当第二次访问到这个数值时，我们可以去这个数对应的索引位置上判断该索引位置上的元素是否大于n，如果大于，则表明已经访问过这个那个索引位置的数了。

个人总结：感觉这是一个非常有效的方法，甚至可以利用这种方法来对数组中元素个数进行计数，都是利用索引位置来做文章，如果访问过某个元素，则在这个元素为索引位置的元素上进行操作。比如我们访问到了一个元素3,不是在本地进行操作，而是去以3为索引位置的元素上进行操作，因为我们必须以索引位置来记录访问的数到底是什么数。同时进行操作的时候， 我们希望对数组更改的尽量少，比如这里的取反操作，加n的操作，我自己想到的是加小数点的操作，访问过几次则加几个小数点。这样在回复初始数组的时候也特别容易。

非常棒的想法，以下是我自己的扩展，感觉非常有可行性：如果数组中可以存入小数的话，我甚至可以用类似的方法对出现的数进行计数，用小数点后的数字来表示这个数访问的次数。或者如果不能存入小数的话，我们也可以通过加上不同次数的n来表示访问次数，比如这个数小于n，则表示这个数还没访问过，如果处于n到2n之间，则表示访问过1次，如果2n到3n之间，则访问过2次，以此类推。尤其是第二种思路，可以应用到对数组进行计数的方法。时间复杂度为O(N)，空间复杂度为O(1)，直接在原始数组上进行操作。
注意有前提：必须要求数组中的每个元素都有相对应的索引位置，也就是说数组存储的数据范围要在数组的大小之内。这行才能保证访问某个元素的时候数值刚好有对应的索引位置让其进行操作。