---
layout: post
title: A/B test
---

以下主要翻译自wikipedia

###Statistical Significance
在统计学上，当相应p值低于显著水平（significance level），便可以称之为具有统计显著性。p值是当null hypothesis为真的情况下观察某个事件的概率，而显著性或alpha水平则是当null hypothesis为真的情况下拒绝接受的概率。显著性水平通常都设为0.05，并且都是超参的。在统计学观察中，总有可能存在观测结果是由于采样错误造成的，但是当p值低于某一水平（即显著性水平）时，则我们有充分理由相信观测结果反映了真实情况，而不是由于采样错误得到的。

统计学显著性在统计假设检验的过程中起着关键性的作用，一般用来决定null hypothesis是接受还是拒绝。null hypothesis是个一般性或默认的假设即没有任何事情发生或改变。要拒绝一个null hypothesis(空假设)，则p值必须低于significance level.

如果p值不低于significance level，更可行的方式是增加样本量而不是接受null hypothesis，然后再次观察是否达到了significance level。

###A/B test
有一个公司想做一次促销，于是给他们的2000位客户发送邮件，邮件内容是给了一个优惠码。对于A组客户发送邮件内容为“Offer ends this Saturday! Use code A1”，对于B组客户发送邮件内容为“Offer ends soon! Use code B1”。得到的结果是A组的最终购买率为5%，B组的最终购买率为3%。那是否意味着A组的邮件内容更好呢？也就是在今后的促销中发送邮件内容都与A组保持一致？这里，就关系到显著性水平的衡量了。以确保测试结果反映了真实的情况，而不是由于随机因素的影响。

###[Tests of Significance](http://www.stat.yale.edu/Courses/1997-98/101/sigtest.htm)(这篇文章很值得一看)
在做新药物测试的时候，假定有两种假设
null hypothesis(h0)：新药物和旧药物平均上没有多大差别
alternative hypothesis(ha)：新药物比旧药物更好

试验之后的结论都是跟h0相关的，比如要么“反对h0支持ha”要么“不反对h0”，绝不会出现反对"ha”或者“支持ha”，注意这其中的差别。比如我们的结论假如是“不反对h0”并不表明null hypothesis为真了，只是表明我们还没有充分的证据去反对h0而支持ha。
