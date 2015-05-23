---
layout: post
title: Feature Selection
---

The central assumption when using a feature selection technique is that the data contains many redundant or irrelevant features. Redundant features are those which provide no more information than the currently selected features, and irrelevant features provide no useful information in any context.
    也就是说特征选择的基本假设是：在当前的特征组合中，存在许多冗余和无关的特征。冗余特征指那些对模型不会提供更多信息的特征，而无关特征是指那些根本就和模型的结果毫无关系的特征。
    特征选择(feature selection) 和 特征抽取(feature extraction)不同，特征选择是从当前特征里选取到一组最佳的特征，特征选择并不创造新的特征出来；而特征抽取则是创造一些新的特征出来。特征选择一般用在有许多特征但训练样本非常少的领域，比如文本分类，每个词都是一个特征，而用来训练的数目往往都是比较少的。
特征选择至少有三个好处：更佳的解释能力；更短的训练时间，计算效率会更高；更好的泛化能力（因为特征数目减少，模型复杂度大大降低，故过拟合的可能性也降低，从而泛化能力得到提升）；一般来说，剔除一些冗余和无关特征之后，模型的健壮性更好，从而模型的准确率提高。
有三种方法： wrapper method, filter method and embedded method。
Wrapper method也就是对每一个特征组合进行训练并得到一个模型，并考察这个模型的泛化能力。对特征组合优劣的判断方法是选取那些泛化能力最好的并且特征数目最少的组合方式。
Filter method 包括卡方检验（Chi-Square test），互信息（也就是信息增益）等等。它的判断标准是对每一个特征进行打分，按照这个打分来取得分数最高的那些特征。而这个分数一般是特征与分类结果的相关性。某一项特征对结果分类有越大的相关性，则这个特征就有越高的分数。而度量这一点的明显就是决策树经常提到的信息增益，或者说是特征与分类结果的互信息。相比wrapper来说，filter的主要优势在于计算成本更低。实际的应用中，一般是用filter method得到一些特征，然后再对这些特征用wrapper method来获取最优的特征组合。
Wrapper方法：1，计算成本太高；2，容易过拟合。
filter方法：1，倾向于选择冗余的特征，因为它并不考虑特征之间的关系。所以那些凡是跟分类关系很大的特征全部被保留，而不管这些特征是否是冗余的。2，计算成本相对来说小很多
Embedded method主要是指L1范数，在SVM里提到过。L1范数的主要作用便是使得模型参数变得稀疏，从而达到特征选择的目的。
但信息增益最大的问题还在于它只能考察特征对整个系统的贡献，而不能具体到某个类别上，这就使得它只适合用来做所谓“全局”的特征选择（指所有的类都使用相同的特征集合），而无法做“本地”的特征选择（每个类别有自己的特征集合，因为有的词，对这个类别很有区分度，对另一个类别则无足轻重）。