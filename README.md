# jwmis
青果教务系统客户端（学生版，其实是在为以后抢课做准备）

---

抱歉余课扫描由要跳票了，今天我已经抓取了必要的数据分析，但是发现一个比较糟糕的问题，青果教务系统写得我不想吐槽了，里面有一万个学校的代码写在里面实现一些特殊要求。select框是动态创建的，有的情况是直接在当前页面创建，有些需要另外获取，还不是json格式的数据，而是直接在那个页面通过js用parent直接写进来（大概做这个系统的人根本不不会用ajax吧。。提交的选课数据我也看了，一大堆没用的数据。。。。。。。真不知道怎么吐槽。。今晚刚好又去做试验耽误了不少时间，就先不弄这个鬼玩意了。

---

做本软件一方面是方便抢课（暂时未实现），不要担心，这个软件有考虑服务器压力的，只有在请求失败的时候才会重新请求，而不是无脑刷新（实际上有时候页面等很久加载不出就说明很可能已经挤进去了，只是处理没那么快），并且减少了比必要的请求，这样一来反而减轻了服务器的压力，还能解放双手。顺便以此项目作为练习QT。

本系统根据我们学校的教务管理系统制作，理论支持所有青果教务系统，但不能保证其他学校的教务系统不会因为设置不同/人为修改代码（不过一般学校只会改前端代码，但是可能会影响正则匹配）而无法获取数据。

目前已经实现的功能

* 个人信息查询
* 成绩分布

计划实现的功能

* HTTP5XX错误自动刷新
* 自动重登陆（在发起请求时）
* 抢课功能
* 课表查询与保存（zz青果，人家保存了课表就不用每天去查了，这是减小服务器负担，你就偏不让）

为了避免对服务器造成较大负荷，抢课功能将会在近期抢课完，人比较少，但系统还未关闭时进行抓包。暂时只做余课扫描功能，有条件（因为大一大二的晚一天选，可以再拿他们的账号进一步分析）再做完整的功能（但是很有可能要明年了），当然如果能提供一个测试的服务器或者相关程序给我更好。

另，本来用QT做事希望全平台都能用，但是由于对gbk编码处理暂时还依赖操作系统所以只能在windows下使用，我会抽空研究linux下识别gbk编码的方式的。