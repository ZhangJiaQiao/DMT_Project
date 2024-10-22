# 《线积分卷积与双色调映射相结合的彩色素描模拟方法》

### 1.项目目标：
结合线积分卷积与双色调映射技术，改进一种彩色素描模拟方法，用代码实现彩色素描的非真实感绘制。

### 2.项目概述：
首先基于k-means聚类对彩色图像进行分割，通过计算色彩差异性为每个区域指定两种基本色，并利用双色调映射技术生成彩色纹理。同时，利用霓虹变换生成素描轮廓线。最后，将轮廓与彩色纹理相融合来得到彩色素描效果。

环境：Matlab

### 3.项目步骤：
这个项目可分为两个独立的子任务，一是主副色调“彩图”的生成，二是“轮廓图”的生成，这两个任务可以独立起来进行，相互不影响，那么项目框架就比较明了。

（1）用k-means分割对图像进行预处理

（2）在步骤（1）的基础上确定图像区域的基本色并计算其密度

（3）生成图像的噪声图

（4）区域纹理方向的确定

（5）在（3）（4）的基础上进行线积分卷积，生成图像的卷积纹理

（6）在（5）的基础上叠加纸肌理

（7）利用霓虹变换生成图像的素描轮廓

（8）将主副色调用双色调映射进行融合，再叠加轮廓图

### 4.知识储备（待补充）：
* k-means分割方法
* 噪声图生成
* 傅里叶变换
* 线积分卷积
* 双色调映射
* 霓虹变换

### 4.小组分工：
| 姓名          |工作                                              |
| ------------  | :---------------------------------------------: |
| 张家侨        |图像位图提取，项目框架搭建，报告汇总与项目监督        |
| 张涵玮        |图像位图提取，项目框架搭建，最终融合与项目优化        |
| 张  骏        |k-means分割，颜色基本色确定与双色调映射实现          |
| 张漫榕        |k-means分割，颜色基本色确定与生成素描轮廓            |
| 张彬熠        |生成噪声图，区域纹理方向确定，生成卷积纹理与叠加纸肌理 |
| 袁均良        |生成噪声图，区域纹理方向确定，生成卷积纹理与叠加纸肌理 |

### 5.项目进度：
1.1 图像预处理 ———— 100%

k-means 算法：基于距离相似性的聚类算法,通过比较样本之间的相似性,
按照距离将样本聚成不同的簇。两个点的距离越近,其相似度就越大。彩色
图像中的每一个像素是三维空间中的一个点,三维对应红、绿、蓝三原色的
强度,基于 K-means 聚类算法的图像分割,以图像的像素为数据点进行聚类,
然后将每个像素点以其对应的聚类中心替代,重构该图像。

***

1.2 颜色基本色并计算密度 ———— 100%

***

1.3 生成噪声图像————100%

***

1.4 区域纹理方向确定————100%

***

1.5 生成卷积纹理————100%

***

1.6 叠加纸肌理————100%

***

1.7 生成素描轮廓————100%

***

1.8 主色调与副色调的融合————100%
