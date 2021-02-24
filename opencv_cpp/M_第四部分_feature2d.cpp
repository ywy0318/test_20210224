/*
第四部分
features2d组件,是OpenCV的2D功能框架
在OpenCV2中,将features2d组件与其余相关组件配合使用，达到了较好的效果;

自OpenCV2以来的众多注明的特征检测算子(SIFT,SURF,ORB算子)所以来的稳定版
的特征检测与匹配相关的核心源代码已经从官方发行的OpenCV3中移除,而转移到了
一个名为xfeatures2D的第三方库中了;此库还处在开发阶段,现阶段想投入使用
要额外到github下载,并需要进行繁琐的配置;此库运行效果不稳定;

主要内容:
特征检测和描述
特征检测器(Feature Detectors)通用接口
描述符提取器(Descriptor Extractors)通用接口
描述符匹配器(Descriptor Matchers)通用接口
通用描述符(Generic Descriptor)匹配器通用接口
关键点绘制函数和匹配功能绘制函数


*/