import numpy as np 
'''
ndarray对象的内容可以通过索引或者切片来访问和修改，与python中list切片操作一样
ndarray数据基于0-n的下标进行索引，切片对象可以通过内置的slice函数,
并设置start,stop,step参数进行，从原数组中切割出一个新数组
'''

a=np.arange(10)
s=slice(2,7,2)#从索引2开始到索引7结束,间隔为2
print(a[s])
#通过冒号分割切片参数start:stop:step来进行切片操作
#冒号:的解释:如果只放置一个参数,如[2],将返回与该索引相对应的单个元素，
#如果为[2:],表示该索引开始以后的项都被提取
#如果使用了两个参数,如[2:7]，那么则表示提取两个索引(不包括停止索引)之间的项
b=a[2:7:2]
print(b)
print(a[5])
print(a[2:7])
print(a[2:])


#多维数组同样适用上述索引提取的方法
aa=np.array([[1,2,3],[4,5,6],[7,8,9]])
print(aa)
print("aa[1:]")
#从某个索引处开始切割
print(aa[1:])
'''
[[4 5 6]
 [9 7 8]]
'''
print(aa[2:])
"""[[9 7 8]]"""
print("-"*5)
#切片还可以包含省略号...,来使选择元祖的长度与数组的维度相同
#如果再行位置适用省略号，它将返回包含行中元素的ndarray
#aaa=np.array([[1,2,3],[4,5,6],[9,7,8]])
print("aa:")
print(aa)
print("-"*5)
print(aa[...,1])#第二列元素
print("-"*5)
print(aa[1,...])#第二行元素
print("-"*5)
print(aa[...,1:])#第二列及剩下的所有元素
print("-"*9)
'''
numpy比一般的python序列提供更多的索引方式,除了之前看到的用整数和切片索引外,
数组可以由整数数组索引,不二索引，及花式索引

'''
#整数数组索引
y=aa[[0,1,2],[0,1,0]]#获取数组中(0,0),(1,1),(2,0)位置处的元素
print(y)
print("-"*9)
#获取4*3数组中的四个角的元素,行索引是[0,0],[3,3],列索引是[0,2]和[0,2]
#待续-------有问题
#返回的结果是包含每个角元素的ndarray对象
bbb=np.array([[0,1,2],[3,4,5],[6,7,8],[9,10,11]])
print("bbb=")
print(bbb)
print("\n")
rows=np.array([[0,0],[3,3]])
cols=np.array([[0,2],[0,2]])
yy=bbb[rows,cols]
print("si ge jiao de yuan su :")
print(yy)
print("\n")
#可以借助切片:或...与索引数组组合
aaa=np.array([[1,2,3],[4,5,6],[7,8,9]])
print(aaa[1:3,1:3])
print("\n")
print(aaa[1:3,[1,2]])
print("\n")
print(aaa[...,1:])
"""
布尔索引
通过一个布尔数组来索引目标数组
布尔索引通过布尔运算(比较运算符)来获取符合指定条件的元素的数组

"""
print("\n")
print(aaa[aaa>5])
#使用~(取补运算符)来过滤NaN
ab=np.array([np.nan,1,2,np.nan,3,4,5])
print(ab[~np.isnan(ab)])
abc=np.array([1,2,3+6j,4.5+5j,6])
print(abc[np.iscomplex(abc)])

'''
花式索引指的是利用整数数组进行
花式索引根据索引数组的值作为目标数组的某个轴的下标来取值,对于使用一维整型数组作为索引,
如果目标是一维数组，那么索引的结果就是对应位置的元素，
如果目标是二维数组，那么就是对应下标的行
花式数组跟切片不一样，它总是将数据赋值到新数组中

'''
#传输顺序索引数组
x=np.arange(32).reshape((8,4))
print("\n")
print(x)
print("\n")
print(x[[4,2,1,7]])#行号索引
#传入倒序索引数组
print("\n")
print(x[[-4,-2,-1,-7]])#行号索引最后一行是-1行，往上倒着数
#传入多个索引数组(要使用np.ix_)
print("\n")
print(x[np.ix_([1,5,7,2],[0,3,1,2])])#待续----后面这个索引数组有什么用