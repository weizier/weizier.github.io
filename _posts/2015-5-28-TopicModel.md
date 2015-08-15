---
layout: post
title: Topic Model
---

一．主题模型的引入
主题模型是一个统计模型，用来抽离出一批文档中的“主题”。直觉上，已知一篇文档的一个特定主题，则我们有理由相信一些词会更可能出现在这篇文档中。“狗”和“骨头”更有可能出现在一篇有关于狗的文档中，“猫”和“喵”更有可能出现在有关于猫的文档中，而英语当中的“the”和“is”在这些文档中出现的概率相当。一般来说一篇文档都含有多个主题，这些主题之间所占比例有所不同，一篇文档10%是有关猫90%有关狗，那么这篇文档“狗”这个词出现的次数可能会是“猫”的9倍。
如果上边的说法还不够形象，下边有两句话：
“马云、马化腾和李彦宏”
“阿里巴巴、腾讯和百度掌门人”
如果按照jaccard距离来表征两句话的相似性，将会得到两句话完全不相干的错误结论，这显然是不对的。但是一进行语义分析才发现这两句话其实说的完全一回事。或者更准确的说，在这里把两句话的主题抽离出来，将会得到“企业家”、“互联网”、“BAT”等等这些主题，这样就发现两句话主题上是完全相同的，由此可知这两句话具有很高的相似性。
主题模型中的主题实际就是一个标签，用这个标签尽最大可能去概括一段话或一篇文档的内容。这里有点类似小学时候经常被老师要求“总结中心思想”的作用，主题在这里就是“中心思想”。但又不仅仅是“中心思想”，数学上的主题模型更像一个语料库，在这个语料库里每一个词都有一个对应的概率分布去表征这个词的出现，在特定的主题里边，有些词出现概率高，另外一些词出现概率低，比如上边的主题是“狗”的文档中，“骨头”出现的概率就要比“喵”高。

二．数学解释
主题模型就是用来对文档建模的数学工具，它是一个生成模型，何谓生成模型，就是要求得目标概率，必须先通过求联合概率，然后再利用概率运算公式得到。一般符合下式：

其中，是要求的结果，表示给定输入量，输出关于输入的概率分布。从上式中可以明显看到生成模型的结果并不是直接从数据中得到的，它有一个中间过程。
而判别模型则不同，完全省掉了中间求联合概率的步骤，直接从数据训练样本中学习最终所要预测的概率，即（当然，这里是针对概率模型而言，另一种是非概率模型，那就相应的是直接从训练样本中学习到决策函数F(X)的是判别模型.）。
回到主题模型，在主题模型的框架里，每一篇文档的产生都遵循着这样一个步骤：每一篇文档都有一系列主题，这些主题共同符合一定的概率分布（当然不同文档的主题概率分布不尽相同），依据这个概率分布随机选择一个主题，然后再从这个主题里按照另一个概率分布选择一个词。这个词就是文档的第一个词，其余的词都是这个过程。用公式来表示就是：

其实，这个式子的更准确表示形式应该是：

对于最后一个等式的成立，我认为是近似了的，这是我个人的想法，不知道对不对，求高人指正。（2015.3.3更新：这里实际暗含着一个假设，那就是文档和词在主题给定下的时候是条件独立的。用数学来表示为P(A,C|B)=P(A|B)P(C|B)）
从上述的运算过程中，我们可以明确的知道P(词|文档)的得到是通过一系列运算得到的，并不是直接从训练数据样本中得到的，所以说主题模型是一个生成模型。

矩阵表示形式是：

主题模型有很多方法，主要有两种：pLSA(Probabilistic latent semantic analysis)和LDA(Latent Dirichlet allocation)。下面主要对这两种方法展开来讲。

三．Probabilistic latent semantic analysis
pLSA的另一个名称是probabilistic latent semantic indexing(pLSI)，假设在一篇文档d中，主题用c来表示，词用w来表示，则有如下公式：

pLSA有假定：在主题给定下，文档和词是条件独立的。

第一个等式是对称形式，其主要思路是认为文档和词都按照一定的概率分布（分别是P(d|c)和P(w|c)）从主题c中产生；第二个等式是非对称形式，更符合我们的直觉，主要思路是从该文档中按照一定概率分布选择一个主题（即P(c|d)），然后再从该主题中选择这个词，这个概率对应是P(w|c)，这个公式恰好和上文所讲的一致。即把这里的非对称形式的公式左右都除以P(d)便得到下面这个公式：

注意：这里的w和词都是指单个的词，并不是用来表征整篇文档的词向量
用盘子表示法（英语是Plate notation，不知道翻译对不对）如下：

最大的矩形（盘子）里装有M个小盘子，即有M篇文档，每一篇文档d自身有个概率P(d)，从d到主题c有一个概率分布P(c|d)，随后从主题c到词w又是一个概率分布P(w|c)，由此构成了w和c的联合概率分布P(w,d).
     
pLSA的参数个数是cd+wc，所以参数个数随着文档d的增加而线性增加。（LDA原文：The linear growth in parameters suggests that the model is prone to over-fitting）。但是很重要的的是，pLSA只是对已有文档的建模，也就是说生成模型只是适合于这些用以训练pLSA算法的文档，并不是新文档的生成模型。这一点很重要，因为我们后文要说的pLSA很容易过拟合，还有LDA为了解决这些问题引入的狄利克雷分布都与此有关。(In addition, although PLSA is a generative model of the documents in the collection it is estimated on, it is not a generative model of new documents. 
The LDA model is essentially the Bayesian version of PLSA model. The Bayesian formulation tends to perform better on small datasets because Bayesian methods can avoid overfitting the data. For very large datasets, the results of the two models tend to converge.  两段话都摘自维基百科)

四．Latent Dirichlet allocation
     在LDA中，每一篇文档都被看做是有一系列主题，在这一点上和pLSA是一致的。实际上，LDA的不同之处在于，pLSA的主题的概率分布P(c|d)是一个确定的概率分布，也就是虽然主题c不确定，但是c符合的概率分布是确定的，比如符合高斯分布，这个高斯分布的各参数是确定的，但是在LDA中，这个高斯分布都是不确定的，高斯分布又服从一个狄利克雷先验分布(Dirichlet  prior)，说的绕口一点是主题的概率分布的概率分布，除了主题有这个特点之外，另外词在主题下的分布也不再是确定分布，同样也服从一个狄利克雷先验分布。所以实际上LDA是pLSA的改进版，延伸版。
这个改进有什么好处呢？就是我们上文说的pLSA容易过拟合，何谓过拟合？过拟合就是训练出来的模型对训练数据有很好的表征能力，但是一应用到新的训练数据上就挂了。这就是所谓的泛化能力不够。我们说一个人适应新环境的能力不行，也可以说他在他熟悉的环境里过拟合了。
那为什么pLSA容易过拟合，而LDA就这么牛逼呢？这个要展开讲，可以讲好多好多啊，可以扯到频率学派和贝叶斯学派关于概率的争论，这个争论至今悬而未决，在这里，我讲一下我自己的看法，说的不对的，希望指正。
pLSA中，主题的概率分布P(c|d)和词在主题下的概率分布P(w|c)既然是概率分布，那么就必须要有样本进行统计才能得到这些概率分布。更具体的讲，主题模型就是为了做这个事情的，训练已获得的数据样本，得到这些参数，那么一个pLSA模型便得到了，但是这个时候问题就来了：这些参数是建立在训练样本上得到的。这是个大问题啊！你怎么能确保新加入的数据同样符合这些参数呢？你能不能别这么草率鲁莽？但是频率学派就有这么任性，他们认为参数是存在并且是确定的， 只是我们未知而已，并且正是因为未知，我们才去训练pLSA的，训练之后得到的参数同样适合于新加入的数据，因为他们相信参数是确定的，既然适合于训练数据，那么也同样适合于新加入的数据了。
但是真实情况却不是这样，尤其是训练样本量比较少的情况下的时候，这个时候首先就不符合大数定律的条件（这里插一句大数定律和中心极限定理，在无数次独立同分布的随机事件中，事件的频率趋于一个稳定的概率值，这是大数定律；而同样的无数次独立同分布的随机事件中，事件的分布趋近于一个稳定的正态分布，而这个正太分布的期望值正是大数定律里面的概率值。所以，中心极限定理比大数定律揭示的现象更深刻，同时成立的条件当然也要相对来说苛刻一些。 非数学系出身，不对请直接喷），所以频率并不能很好的近似于概率，所以得到的参数肯定不好。我们都知道，概率的获取必须以拥有大量可重复性实验为前提，但是这里的主题模型训练显然并不能在每个场景下都有大量的训练数据。所以，当训练数据量偏小的时候，pLSA就无可避免的陷入了过拟合的泥潭里了。为了解决这个问题，LDA给这些参数都加入了一个先验知识，就是当数据量小的时候，我人为的给你一些专家性的指导，你这个参数应该这样不应该那样。比如你要统计一个地区的人口年龄分布，假如你手上有的训练数据是一所大学的人口数据，统计出来的结果肯定是年轻人占比绝大多数，这个时候你训练出来的模型肯定是有问题的，但是我现在加入一些先验知识进去，专家认为这个地区中老年人口怎么占比这么少？不行，我得给你修正修正，这个时候得到的结果就会好很多。所以LDA相比pLSA就优在这里，它对这些参数加入了一些先验的分布进去。（但是我这里并没有任何意思说贝叶斯学派优于频率学派，两学派各有自己的优势领域，比如很多频率学派对贝叶斯学派的攻击点之一是，在模型建立过程中，贝叶斯学派加入的先验知识难免主观片面，并且很多时候加入都只是为了数学模型上运算的方便。我这里只是举了一个适合贝叶斯学派的例子而已）
但是，当训练样本量足够大，pLSA的效果是可以等同于LDA的，因为过拟合的原因就是训练数据量太少，当把数据量提上去之后，过拟合现象会有明显的改观。

五．LDA的具体数学形式
在正式讲LDA的数学模型之前，先讲两个比较基础的模型。

1.Unigram model
每一篇文档的概率是组成这篇文档所有词的概率之乘积。表示如下：

实际上，正确的推导应该是

最后一步里，把概率的计算进行了简化，粗暴地认为词与词之间没有联系。盘子表示法如下：

M篇文档，每一篇文档有N个词，词与词之间是相互独立存在的。

2.Mixture of unigrams
Unigram model 没有主题，文档直接被分解成词，而Mixture of unigrams 模型则给文档一个主题，并且从这个主题中去按照一定概率分布去选择所需要的词。图模型如下：

用数学公式来表示就是

也就是说，主题z在这里是一个隐变量，但需要注意的是，虽然要对z求和，但是表示的意思却是每篇文档却只有一个主题。
解释一下：第一个等号这里，由于文档d由词组成，故可以用词向量来表示；第二个等号，mixture of unigrams模型中一篇文档只能属于一个主题z，但是并没有明确文档d到底属于哪个主题，所以d有可能属于任意一个主题，只是属于每一个主题的概率有所不同而已，因此必须对z求和。但本质上d只有一个主题，这一点可从最后一个式子得到体现，文档中的每一个词wn都从同一个主题产生，只是整篇文档有可能属于若干个主题而已，所以才对主题求和。
整篇文档或者说对应的词向量有可能属于多个主题，但同一时刻下文档里的每一个词同属于一个特定的主题，而pLSA则不同，文档里的每一个词有可能分属于不同的主题。

3.LDA
终于要讲到LDA了，其实弄清楚上述这些基本模型之后，LDA就是水到渠成的事情了，因为Mixture of unigrams模型只有一个主题，这显然不符合实际情况，一篇文档很有可能包含多个不同的主题，而这些主题服从一个概率分布，用来表示。另外正如上文已经讲到过的，这个概率分布又服从另一个概率分布，用，这个就是大名鼎鼎的狄利克雷分布了，专门用来表征分布的分布。除了主题之后，词的分布也服从一个狄利克雷分布，用。这样一来就有下面的公式：





提一句，如果按照这个公式的形式来表示pLSA，那么有

同理，另两个公式只需把LDA公式对应含有两个超参数拿掉就可。
根据这个公式，可以非常方便的观察到pLSA和LDA的区别。

其中，α和β是dirichlet的参数，对于M篇文档都一样，用来控制每篇文档的两个概率分布；θ对于每一篇文档都一样，用来表征文档的主题分布；z是每个词的隐含主题，w是文档里的词。（原文中如此说：The parameters α and β are corpus-level parameters, assumed to be sampled once in the process of generating a corpus. The variables θ are document-level variables, sampled once per document. Finally, the variables z and w are word-level variables and are sampled once for each word in each document.）
图模型如下：

从图中可知，α和β是文集（corpus）级别的参数，所以在M篇文档外边，θ是文档级别的参数，在N个词盘子的外边，z和w是一一对应的，每个词对应一个隐含主题。
下边这个图是个神图，怎么能如此机智呢？把这些复杂隐晦的关键点全都形象的图形化了，不得不佩服。

首先，我们假设一篇文档含有3个词，待选主题也是3个，为什么选择3？主要是是为了好用三角形来表示他们的关系，当然如果你有很好的超空间想象能力，你也可以选择更多的词来描述。
外边最大的三角形是word simplex，其内的每一个点都表示一个概率分布，也就是产生这三个词的概率大小。比如p2这个点，它产生word 1的概率是，p2点到word 1对边的距离，也就是p2到底边的距离。由于等边三角形内的任何一点到三条边的距离之和等于高，相当于概率之和为1类似，这就非常好的保证了用距离来度量概率大小的准确性。
小三角形是topic simplex，其内的每一个点表示产生这三个topic的概率分布，和word simplex类似。三个顶点，比如topic1由于它在word simplex内部，所以表示的意义是：由topic1产生三个word的概率分布，即前文公式里的。Topic simplex内部的点则是前文里的。
我们再来看看Mixture of unigrams如何表示在图形中，由于该模型只有一个主题，所以随机在三个主题中，选择一个，假如是topic1，然后再按照topic1到各边的距离（也就是产生各个词的概率大小）来生成3个词。这样整个文档便生成了。在图形中表示就是Topic simplex三个顶点上的随机一个点便是Mixture of unigrams模型。上文中的p(d)可以这样理解，由于要求词向量的概率，那么这些词有可能从任意一个主题产生，所以分别对每个主题下产生这次词向量进行求和。
pLSA的主题不止一个，表示成为Topic simple图里的带叉的点，每个带叉的点便是一个pLSA模型，产生文档的时候，先按照带叉点到Topic simple三条边距离来选择一个主题，然后再按照Mixture of unigrams的形式来选择三个词当中的一个，有几个隐含主题就按照这种方式选几个主题，然后再通过这些主题去产生下一步的词。
LDA相对pLSA的变化就是，它不再仅仅是Topic simple图里的带叉的点，而是一条曲线，一个点表示topic的一个概率分布，虽然topic是有一定随机性的，但是topic的分布不具有随机性，而是确定的点，但现在LDA不仅topic是随机的，topic的分布也是随机性的，所以表现出来就不再是一个确定的点，而是一系列的点，这条曲线由上文中的狄利克雷分布的参数α和β来确定，也就是和，每次产生文档的时候都是按照dirichlet分布来确定一个主题分布的分布和词分布的分布，然后剩下的就和pLSA相同了。
有些人会问，为什么非得要用dirichlet分布呢？对，还真有用其他分布的，比如 logistic normal distribution等等，这些相当于都是LDA的变形，不做过多讨论，感兴趣的可以查阅相关文献。
既然模型已经解释的这么透彻了，那么如何利用数据样本训练出这个模型呢？这里就有很多的数学运算了，基本思路是：由于在文档里，唯一的观察量（也就是模型的输入变量）是词w，w是一个向量，另外已知的是dirichlet分布的参数α和β，其他的都是隐变量，而对于隐变量的最好工具便是EM算法，通过极大化所求目标量的下界来逐步逼近目标量的极大值。具体的数学细节若有时间我再来更新。
最后，就是LDA的应用啦，当然最主要的是文档主题，背后语义的分析等等，当然我们可以将LDA适当做一些变形之后利用到图形处理等领域，把图片当做一个文档，其内的像素点当做一个个词，Deep Learning对于图形的处理已经证明了像素点往上层抽象可以组成一些基本单元，我们可以类似到这里作为主题。（这是我自己瞎诌的，不知道对不对，高手请尽情喷）
2015.3.4添加补充：LSA完全基于线性代数，没有数理统计作为理论支撑，pLSA有了数理统计基础，但是仍然不够，因为它只对文档里的主题和文档里的词作了数理统计分析，并没有对文档的分布做数理统计分析。（LDA创世纪文章里说到pLSA有：it is incomplete in that it provides no probabilistic model at the level of documents）
最后的最后，希望大家踊跃提出文中的错误，先谢谢各位啦！

参考资料：
1.http://en.wikipedia.org/wiki/Topic_model
2.http://en.wikipedia.org/wiki/Probabilistic_latent_semantic_analysis
3.http://en.wikipedia.org/wiki/Latent_Dirichlet_allocation
4.http://blog.csdn.net/huagong_adu/article/details/7937616
5.http://www.xperseverance.net/blogs/2012/03/17/
6.http://jmlr.csail.mit.edu/papers/v3/blei03a.html （LDA的创世纪文章）