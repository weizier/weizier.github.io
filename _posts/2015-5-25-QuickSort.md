---
layout: post
title: Quick Sort
---

From Wikipedia:on average, the algorithm takes O(n log n) comparisons to sort n items. In the worst case, it makes O(n2) comparisons, though this behavior is rare.

通常来说，我们认为最优的排序算法是快速排序，它的时间复杂度一般来说是O(n*log(n))，最坏情况下的时间复杂度为O(n^2)

快排的基本思想有两条：
> 选定一个基准，遍历整个数组，将比基准小的数放到基准前边，比基准大的数放到基准右边。
> 分治法，对基准点左右两个子区间递归调用第一步

对于第一步，也就是如何将比基准小的数放到左边，比基准大的数放到右边，每个人的做法也些微的不同，但是基本思想都是一样的。
另外，对于基准的选取也有随机和不随机的两种方法。

下面以例子来讲解一下我见到过的一些做法。


原始数据为：
	8 9 5 7 4 6 3 6 
####挖坑填数
> 将第一个数用一个临时变量保存下来，相当于在该位置上挖了一个坑。然后维护两个指针i和j，i对应为从前往后扫描的指针，j对应为从后往前扫的指针，并保持i<j。
在遍历过程中，如果坑挖在前边，则从后面的指针处扫描找到一个数比当前坑中的数字小的数字填在当前坑中（默认为升序），如果坑挖在后边，则从前边指针扫描找到一个数比当前坑中数字大的数填在坑中。每一次循环遍历过程中的基准点都是最先找到的那个基准点。循环一直到i<j不再满足为止。
> 递归的实现是将前一轮基准点左边（或右边）的子区间首末位置赋值给i和j。
> 重复上述过程

C++代码为：
	#include <iostream>
	using namespace std;
	//快速排序
	void quick_sort(int s[], int l, int r)
	{
		if (l < r)
		{
			//Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
			int i = l, j = r, x = s[l];
			while (i < j)
			{
				while(i < j && s[j] >= x) // 从右向左找第一个小于x的数
					j--;
				if(i < j)
					s[i++] = s[j];

				while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数
					i++;
				if(i < j)
					s[j--] = s[i];
			}
			s[i] = x;
			for(int i=0;i<8;i++){
				cout<<s[i];
			}
			cout<<endl;
			quick_sort(s, l, i - 1); // 递归调用
			quick_sort(s, i + 1, r);
		}
	}

	main(){
		int s[] = {8,9,5,7,4,6,3,6};
		quick_sort(s,0,7);
		for(int i=0;i<8;i++){
			cout<<s[i];
		}
		cout<<endl;
	}

相关顺序为，假设选择第一个数8作为基准点（随机选择基准点类似），那么每次遍历的结果为：
	4,3,5,6,7,6,8,9
	3,4,5,6,7,6,8,9
	3,4,5,6,6,7,8,9
	3,4,5,6,6,7,8,9

####
	


