#ifndef __CONSTS_H__
#define __CONSTS_H__
#define TIMER_MIN 100

#define __遍历取值 0x05761088//
#define __对话基址1 0x05761E5C //0x05694A94
#define __对话基址2 0x05761EBC //
#define __角色坐标 0x057621D4
#define __角色状态 0x05874FB0 //0不动 1 动 2放技能中
#define __鼠标状态 0x059047B0
#define __副本ID 0x056389E0
#define __副本难度 __遍历取值

#define __副本难度偏移 0x20c
#define __角色下标偏移 0x108
#define __当前角色数量 0xa70
#define __角色数量偏移2 0x3c0
#define __最大角色数量 0xa78
#define __角色状态偏移 0x338c
#define __角色面向偏移1 0x3980
#define __角色面向偏移2 0x397c
#define __无视建筑偏移 0x408
#define __无视地形偏移 0x40C
#define __A星_当前房间X 0xcc
#define __A星_当前房间Y 0xd0
#define __坐标偏移 0xb8
#define __大区域偏移 0x1E4
#define __小区域偏移 0x1Ec


#define __人物基址  0x05874FB0 //7度_获取
#define __人偶基址  0x057884A4 //7度_获取
#define __人偶等级  0x024680FB //7度_获取
#define __制裁基址  0x05760014 //7度_获取
#define __禁闭基址  0x05761810 //7度_获取
#define __鼠标基址  0x058A1C20 //7度_获取
#define __鼠标技能  0x0574C4FC //7度_获取
#define __鼠标内存  0x03433E00 //7度_获取
#define __评分基址  0x0575FB74 //7度_获取
#define __商店基址  0x05761798 //7度_获取
#define __背包基址  0x0576179C //7度_获取
#define __时间基址  0x020A028 //7度_获取
#define __喇叭公告  0x02A66610 //7度_获取
#define __冰心公告  0x02A66670 //7度_获取
#define __安图公告  0x02A65E50 //7度_获取
#define __加密基址  0x058B6A78 //7度_获取
#define __解密基址  0x058B6A18 //7度_获取
#define __特殊解密  0x04DE9408 //7度_获取
#define __加密参数1  0x04DE8F00 //7度_获取
#define __加密参数2  0x04DE9100 //7度_获取

#define __技能ID值  0x0578B360 //7度_获取
#define __技能特效  0x0330A4F2 //7度_获取
#define __物品编号  0x05738A84 //7度_获取
#define __等级限制  0x02787891 //7度_获取
#define __游戏设置  0x057462E8 //7度_获取
#define __游戏句柄  0x058D84F4 //7度_获取
#define __死亡后摇  0x0279AEE8 //7度_获取
#define __金库金币  0x058A5C38 //7度_获取
#define __数量地址  0x06794CB0 //7度_获取
#define __动画基址  0x0571A314 //7度_获取
#define __深渊基址  0x05760250 //7度_获取
#define __延时基址  0x04630214 //7度_获取
#define __房间编号  0x05761790 //7度_获取
#define __是否进图  0x0572F0B0 //7度_获取
#define __房间数据  0x0572DD24 //7度_获取
#define __房间索引  0x0572DD54 //7度_获取
#define __取房间宽  0x0267ACE0 //7度_获取
#define __取房间高  0x0267AE50 //7度_获取
#define __取房间ID  0x05761790 //7度_获取

#define __卖修基址  0x059047B0 //7度_获取
#define __仓库基址  0x03327420 //7度_获取
#define __对话基址  0x058A41DC //7度_获取
#define __任务对话  0x05761E08 //7度_获取
#define __BOSS地址  0x057218C8 //7度_获取
#define __BOSS基址  0x05760650 //7度_获取
#define __后台按键  0x029D8CF0 //7度_获取
#define __按键基址  0x06633E78 //7度_获取
#define __装备目录  0x067FA678 //7度_获取
#define __人偶目录  0x06804314 //7度_获取
#define __怪物目录  0x06802958 //7度_获取
#define __经验胶囊  0x0573997C //7度_获取
#define __地图基址  0x058D8334 //7度_获取
#define __称号基址  0x0576181C //7度_获取
#define __背包强化  0x0206B30D //7度_获取
#define __记录基址  0x0573F92C //7度_获取
#define __组装地址  0x032FEC60 //7度_获取
#define __加速地址  0x04630670 //7度_获取
#define __封包获取  0x046306AC //7度_获取
#define __封包处理  0x058AB8D4 //7度_获取
#define __屏蔽柱子  0x026D88FF //7度_获取
#define __屏蔽对话  0x0352E44B //7度_获取
#define __柱子消失  0x036D3145 //7度_获取
#define __地下出怪_A  0x0313197B //7度_获取
#define __地下出怪_B  0x03131955 //7度_获取
#define __无视柱子_1  0x02569BB1 //7度_获取
#define __无视柱子_2  0x02569BC2 //7度_获取
#define __无视柱子_3  0x02569BD2 //7度_获取
#define __无视柱子_4  0x02569BF4 //7度_获取
#define __按键基址_1  0x037D5501 //7度_获取
#define __按键基址_2  0x037D54E0 //7度_获取
#define __按键基址_3  0x037D6D8F //7度_获取
#define __屏蔽图纸窗口  0x02A8D1DD //7度_获取
#define __剧情副本ID  0x058B6A18 //7度_获取
#define __城镇加速  0x027252BC //7度_获取
#define __GM权限模式  0x02334DC0 //7度_获取
#define __领主死亡延迟  0x02766FA9 //7度_获取
#define __地图信息CALL  0x01FAA2E0 //7度_获取

#define __自动捡物  0x028E7FB7 //7度_获取
#define __入包范围  0x028E7F85 //7度_获取
#define __JF1  0x028DC650 //7度_获取
#define __JF2  0x028DC610 //7度_获取
#define __JF3  0x026B5D10 //7度_获取
#define __JF4  0x028DECC0 //7度_获取
#define __DNFsleep  0x04630214 //7度_获取
#define __strange  0x0313197B //7度_获取
#define __HOOK入包  0x0297986E //7度_获取
#define __入包地址1  0x028DC650 //7度_获取
#define __入包地址2  0x028DC610 //7度_获取
#define __入包地址3  0x026B5D10 //7度_获取
#define __入包地址4  0x026B5CC0 //7度_获取
#define __入包地址5  0x027CC540 //7度_获取

#define __邮箱基址  0x05876BB0 //7度_获取
#define __邮箱_ECX  0x058B7AD0 //7度_获取
#define __邮箱CALL  0x02A514C0 //7度_获取
#define __接收CALL  0x02A4D6B0 //7度_获取
#define __删除CALL  0x02A514C0 //7度_获取
#define __邮件界面CALL  0x03327420 //7度_获取
#define __关闭界面CALL  0x03321A90 //7度_获取
#define __界面_I D  0x31F //7度_获取
#define __关闭界面push  0x2D6 //7度_获取
#define __邮寄大区CALL  0x04A98FD4 //7度_获取
#define __邮寄大区HOOK指针1  0x02A41417 //7度_获取
#define __邮寄大区HOOK指针2  0x0183A311 //7度_获取
#define __邮寄手续费地址  0x02A38E36 //7度_获取

#define __魔法星弹  0x02FF4560 //7度_获取
#define __鬼剑十字斩  0x030951C1 //7度_获取
#define __鬼剑崩山击  0x030C9908 //7度_获取
#define __鬼剑裂波斩  0x0346CF88 //7度_获取
#define __光环48024  0x02865677 //7度_获取
#define __黄圈48012  0x02855919 //7度_获取
#define __技能23501  0x0241A421 //7度_获取
#define __GSD_天照  0x0308A533 //7度_获取
#define __念气环绕女  0x02E9672E //7度_获取
#define __念气环绕男  0x02DFC7EA //7度_获取
#define __修罗邪光斩  0x030F9D60 //7度_获取
#define __修罗闪电被动  0x01C5B3B0 //7度_获取
#define __希拉技能静态  0x018794FE //7度_获取
#define __暗夜手里剑  0x018794FE //7度_获取
#define __缔造炽炎星陨  0x0241A421 //7度_获取

#define __任务基址  0x057617D0 //7度_获取
#define __完成CALL  0x01F42E00 //7度_获取
#define __接受CALL  0x01F42F00 //7度_获取
#define __提交CALL  0x01F42E80 //7度_获取
#define __放弃CALL  0x01F42F50 //7度_获取
#define __跳过CALL  0x01CCF880 //7度_获取
#define __任务数据  0x0573B9F0 //7度_获取
#define __任务指针  0x01F42DE0 //7度_获取
#define __卡称号_1  0x01CD44C2 //7度_获取
#define __卡称号_2  0x01CD4348 //7度_获取
#define __卡称号_3  0x01CD4355 //7度_获取
#define __黑钻硬币A  0x0336F4AA //7度_获取
#define __黑钻硬币B  0x0336F4B3 //7度_获取
#define __任务跳过判断  0x057617EC //7度_获取
#define __对话任务CALL  0x01CD4080 //7度_获取

#define __收包基址  0x058B7AD0 //7度_获取
#define __收包中转  0x02575123 //7度_获取
#define __收包CALL  0x02575110 //7度_获取
#define __直接入包  0x02575118 //7度_获取
#define __独家收包  0x0257AAB5 //7度_获取
#define __收包跳回  0x0257AABB //7度_获取
#define __收包_Ret  0x0257AB43 //7度_获取
#define __收包点_A  0x0253D494 //7度_获取
#define __收包点_B  0x0253D497 //7度_获取
#define __收包点_1  0x0257AB4A //7度_获取
#define __收包点_2  0x02575110 //7度_获取
#define __收包点_3  0x0257AB4F //7度_获取
#define __另类收包_1  0x02575118 //7度_获取
#define __另类收包_2  0x0257511F //7度_获取
#define __发包数据_1  0x03F0FE90 //7度_获取
#define __发包数据_2  0x05671BDC //7度_获取
#define __拦截收包_A  0x0257AB3C //7度_获取
#define __拦截收包_B  0x0257AB43 //7度_获取
#define __新增收包点1  0x0257519F //7度_获取
#define __新增收包点2  0x02372810 //7度_获取

#define __文本CALL  0x037C2730 //7度_获取
#define __卖物CALL  0x03403D20 //7度_获取
#define __分解CALL  0x0264E2A0 //7度_获取
#define __卖物校验  0x03403DBC //7度_获取
#define __卖物权限  0x03403D7C //7度_获取
#define __整理参数_A  0x046621C4 //7度_获取
#define __整理参数_B  0x0680DB40 //7度_获取
#define __整理背包CALL  0x0264DB40 //7度_获取
#define __按钮基址  0x0566BAD4 //7度_获取
#define __出售提示_ECX  0x05892F80 //7度_获取
#define __出售提示CALL  0x0333AA90 //7度_获取

#define __内存汇编  0x0259383B //7度_获取
#define __动态汇编A  0x046307C4 //7度_获取
#define __动态汇编B  0x04630784 //7度_获取

#define __结构技能CALL  0x02569B10 //7度_获取
#define __组48基址  0x05880DDC //7度_获取
#define __标识CALL  0x0385CDD0 //7度_获取
#define __技能CALL  0x025689E0 //7度_获取
#define __释放CALL  0x02405AE0 //7度_获取
#define __自身CALL  0x0249DC80 //7度_获取
#define __男枪CALL  0x02404EE0 //7度_获取
#define __技能参数  0x05761D84 //7度_获取
#define __女鬼CALL  0x0249DC80 //7度_获取
#define __模拟44CALL  0x02405A20 //7度_获取
#define __技能_OBJ  0x02BDF950 //7度_获取
#define __写入对象  0x028EC570 //7度_获取
#define __取标记OBJ  0x032EBDD0 //7度_获取
#define __OBJ移动CALL  0x028EAED0 //7度_获取
#define __攻击阵营  0x03607FD0 //7度_获取
#define __加密坐标  0x03855C10 //7度_获取
#define __技能坐标  0x026D1F80 //7度_获取
#define __目录基址  0x06806B8C //7度_获取
#define __路径基址  0x057616F8 //7度_获取
#define __副本信息  0x057616E4 //7度_获取
#define __路径CALL  0x03980450 //7度_获取
#define __加载CALL  0x037C6AE0 //7度_获取
#define __分割CALL  0x03859100 //7度_获取
#define __秒杀CALL  0x0289E630 //7度_获取
#define __不死秒杀CALL  0x03855AA0 //7度_获取
#define __扣血秒杀CALL  0x02750330 //7度_获取
#define __人偶秒杀CALL  0x0258FD40 //7度_获取
#define __怪物秒杀CALL  0x02590050 //7度_获取
#define __技能置空CALL  0x022EE790 //7度_获取

#define __剧情基址  0x0572DC30 //7度_获取
#define __选图基址  0x05761088 //7度_获取
#define __进图CALL  0x0379AB00 //7度_获取
#define __选图CALL  0x03777230 //7度_获取
#define __回城CALL  0x022D40B0 //7度_获取
#define __选择角色参数  0x05761088 //7度_获取
#define __选择角色CALL  0x03744E50 //7度_获取

#define __界面CALL  0x022D8150 //7度_获取
#define __坐标顺图_A  0x01FE7EE0 //7度_获取
#define __坐标顺图_B  0x0208D1C0 //7度_获取
#define __坐标顺图_C  0x0208CBD0 //7度_获取
#define __爆物CALL  0x02BFFC30 //7度_获取
#define __重置CALL  0x027CD610 //7度_获取
#define __初始CALL  0x02487AF0 //7度_获取
#define __创建CALL  0x02A98BD0 //7度_获取
#define __销毁CALL  0x028E6F10 //7度_获取
#define __穿戴CALL  0x0282FB00 //7度_获取
#define __脱卸CALL  0x02791400 //7度_获取
#define __刷新CALL  0x02769D80 //7度_获取
#define __血量CALL  0x027659C0 //7度_获取
#define __存仓CALL  0x0265A300 //7度_获取
#define __拾取CALL  0x0264D1F0 //7度_获取
#define __丢弃CALL  0x02651EC0 //7度_获取
#define __加密CALL  0x038559A0 //7度_获取
#define __强顺CALL  0x029765B0 //7度_获取
#define __过图CALL  0x01A9DAD0 //7度_获取
#define __坐标CALL  0x026D1F80 //7度_获取
#define __无敌CALL  0x037DB210 //7度_获取
#define __光环CALL  0x029F18F0 //7度_获取
#define __TypeCALL  0x026234D0 //7度_获取
#define __异常CALL  0x0272DFD0 //7度_获取
#define __评分CALL  0x02914DD0 //7度_获取
#define __移动CALL  0x01E862C0 //7度_获取
#define __变量入栈CALL  0x022F0E20 //7度_获取
#define __男法瞬移CALL  0x0249DC30 //7度_获取
#define __真实穿装备CALL  0x0265F2E0 //7度_获取
#define __冷却判断CALL  0x029943C0 //7度_获取
#define __城镇移动CALL  0x03772240 //7度_获取
#define __深渊出怪CALL  0x024225F0 //7度_获取
#define __评分生效CALL  0x0291B2A0 //7度_获取

#define __发包_EAX  0x05671BDC //7度_获取
#define __发包基址  0x058AB8D4 //7度_获取
#define __缓冲CALL  0x037C22C0 //7度_获取
#define __发包CALL  0x037C3B00 //7度_获取
#define __密钥CALL  0x03941FE0 //7度_获取
#define __赋值CALL  0x037C1A50 //7度_获取
#define __加密包CALL  0x037C23D0 //7度_获取
#define __写wordCALL  0x037C2400 //7度_获取
#define __写DwordCALL  0x037C2430 //7度_获取
#define __加密数据_1  0x038559A0 //7度_获取
#define __加密数据_2  0x03855A20 //7度_获取
#define __加密数据_3  0x03855AA0 //7度_获取
#define __加密数据_4  0x03855B20 //7度_获取
#define __加密数据_5  0x03855880 //7度_获取

#define __拍卖行基址  0x03997270 //7度_获取
#define __拍卖行地址  0x0336755C //7度_获取
#define __金币拍卖行  0x02397ECB //7度_获取
#define __HOOK扫拍  0x020052A1 //7度_获取
#define __打开参数  0x05761798 //7度_获取
#define __打开CALL  0x03323C70 //7度_获取
#define __搜索CALL  0x033613E0 //7度_获取
#define __购买CALL  0x03348CF0 //7度_获取
#define __向上翻页  0x03352850 //7度_获取
#define __向下翻页  0x03352690 //7度_获取
#define __分解机基址  0x05761758 //7度_获取
#define __拍卖行参数  0x05747D80 //7度_获取
#define __拍卖行CALL  0x022D8150 //7度_获取
#define __打开邮件参数  0x05747B54 //7度_获取
#define __打开邮件CALL  0x022BD470 //7度_获取
#define __拖动物品CALL  0x02653860 //7度_获取
#define __拖动装备CALL  0x029C2730 //7度_获取
#define __快捷键基址CALL  0x022AED10 //7度_获取
#define __设置快捷键CALL  0x022AF0A0 //7度_获取

#define __召唤参数  0x057884D8 //7度_获取
#define __召唤怪物CALL  0x0262FE70 //7度_获取
#define __召唤人偶CALL  0x026300E0 //7度_获取
#define __图纸BUFFCALL  0x02636160 //7度_获取
#define __图纸附伤CALL  0x026325F0 //7度_获取
#define __申请状态内存  0x01960D90 //7度_获取
#define __写入状态内存  0x08CE260 //7度_获取
#define __写入图标内存  0x0A1525F //7度_获取
#define __BUFF参数1  0x01B8B520 //7度_获取
#define __BUFF参数2  0x01B880D0 //7度_获取
#define __BUFF参数3  0x01B843D0 //7度_获取
#define __BUFF参数4  0x01B833D0 //7度_获取
#define __特效基址  0x057130B4 //7度_获取
#define __特效缓冲CALL  0x03D305A0 //7度_获取
#define __特效释放CALL  0x03854190 //7度_获取
#define __修炼BUFF基址  0x05761798 //7度_获取
#define __修炼BUFFCALL  0x03327420 //7度_获取
#define __恢复参数  0x057444D8 //7度_获取
#define __解除参数  0x05760250 //7度_获取
#define __修道场CALL  0x021EC140 //7度_获取
#define __怪物创建CALL  0x028653A0 //7度_获取
#define __技能创建CALL  0x02BDF950 //7度_获取

#define __HOOK倍攻  0x02875EA9 //7度_获取
#define __HOOK变怪  0x0268D9C9 //7度_获取
#define __HOOK技能  0x0330B1E8 //7度_获取
#define __HOOK钩子  0x0287FC6D //7度_获取
#define __钩子偏移  0x0287FD29 //7度_获取
#define __HOOK等级  0x03145F4E //7度_获取
#define __HOOK无敌  0x0276F683 //7度_获取
#define __HOOK爆物  0x02797BA7 //7度_获取
#define __HOOK爆伤  0x02876BF2 //7度_获取
#define __HOOK白字  0x0277146D //7度_获取
#define __HOOK评分  0x02914D10 //7度_获取
#define __HOOK分裂  0x028B44A3 //7度_获取
#define __HOOK炼金  0x034DFBF3 //7度_获取
#define __HOOK多段  0x028B44A3 //7度_获取
#define __HOOK负重  0x0391D9B6 //7度_获取
#define __HOOK怪物血量  0x028AB80D //7度_获取
#define __HOOK技能放大  0x025689F0 //7度_获取
#define __HOOK全局伤害  0x02878372 //7度_获取

#define __技能三无  0x024A2520 //7度_获取
#define __物品无消耗  0x026598EF //7度_获取
#define __技能免无色  0x027CE24A //7度_获取
#define __技能无CD  0x02844737 //7度_获取
#define __冷却基址  0x05874E04 //7度_获取
#define __冷却_EAX  0x0664E828 //7度_获取
#define __物品_OBJ  0x038570F0 //7度_获取
#define __全局弱怪  0x028AB812 //7度_获取
#define __另类钩子  0x09FD9BC //7度_获取
#define __全局钩子1  0x02763B80 //7度_获取
#define __全局钩子2  0x0286C43B //7度_获取
#define __物理微秒  0x0273C780 //7度_获取
#define __物理秒杀  0x0273C830 //7度_获取
#define __魔法微秒  0x0273C8E0 //7度_获取
#define __魔法秒杀  0x0273C990 //7度_获取
#define __怪物自杀  0x050BD158 //7度_获取
#define __零血秒杀  0x032F198D //7度_获取
#define __模拟秒杀  0x02766ADF //7度_获取
#define __冰冻基址1  0x025F92B8 //7度_获取
#define __冰冻基址2  0x025F92BE //7度_获取
#define __冰冻基址3  0x025F9406 //7度_获取
#define __冰冻基址4  0x025F940C //7度_获取
#define __冰冻基址5  0x025F943B //7度_获取
#define __冰冻基址6  0x025F9441 //7度_获取
#define __冰冻基址7  0x025F9527 //7度_获取
#define __冰冻基址8  0x025F952D //7度_获取
#define __变怪基址_A  0x03139F64 //7度_获取
#define __变怪基址_B  0x05671BDC //7度_获取
#define __变怪___Jmp  0x03139F65 //7度_获取
#define __基址分裂_A  0x0287DA90 //7度_获取
#define __基址分裂_B  0x0287DA42 //7度_获取
#define __改怪基址_1  0x03139F60 //7度_获取
#define __改怪基址_2  0x05671BDC //7度_获取

#define __技能变大  0x026D3FB0 //7度_获取
#define __基址倍攻  0x0288EDE9 //7度_获取
#define __摸金倍攻  0x0287835F //7度_获取
#define __独家伤害  0x0287832E //7度_获取
#define __TYPE倍攻  0x032F198D //7度_获取
#define __全局伤害  0x02878359 //7度_获取
#define __伤害秒杀  0x0288EDF0 //7度_获取
#define __浮点倍攻  0x027D3304 //7度_获取
#define __OBJ伤害_1  0x02878353 //7度_获取
#define __OBJ伤害_2  0x02878359 //7度_获取
#define __回血秒杀_1  0x03856110 //7度_获取
#define __回血秒杀_2  0x03856138 //7度_获取
#define __自定义返回  0x02875EB3 //7度_获取
#define __自定义伤害  0x02875EBC //7度_获取
#define __自定义下跳  0x03034F94 //7度_获取
#define __白色伤害颜色  0x0330A4F2 //7度_获取
#define __刀刀秒地址  0x03F41748 //7度_获取
#define __刀刀秒VM  0x03F4173E //7度_获取
#define __减血地址  0x03856117 //7度_获取
#define __倍攻基址_1  0x0272FA10 //7度_获取
#define __倍攻基址_2  0x0272FA30 //7度_获取
#define __倍攻基址_3  0x0272FA50 //7度_获取
#define __倍攻基址_4  0x0272FA70 //7度_获取
#define __全局物理攻击  0x03B2F3A0 //7度_获取
#define __全局魔法攻击  0x03B2F880 //7度_获取

#define __最大疲劳  0x05875258 //7度_获取
#define __当前疲劳  0x05875250 //7度_获取
#define __角色等级  0x0574405C //7度_获取
#define __角色数量  0x05737698 //7度_获取
#define __帐号基址  0x0566CD08 //7度_获取
#define __角色基址  0x05760250 //7度_获取
#define __角色指针  0x05761088 //7度_获取
#define __职业基址  0x056577F0 //7度_获取
#define __基本职业  0x05744044 //7度_获取
#define __基本名称  0x05744038 //7度_获取
#define __职业名称  0x05744040 //7度_获取
#define __转职判断  0x05744048 //7度_获取
#define __觉醒次数  0x0574404C //7度_获取
#define __游戏状态  0x056565BC //7度_获取
#define __区域代码  0x0572A640 //7度_获取
#define __城镇代码  0x0572A644 //7度_获取
#define __城镇坐标  0x05874FB8 //7度_获取
#define __角色大区  0x05744058 //7度_获取
#define __角色位置  0x056653C8 //7度_获取
#define __位置基址  0x056565BC //7度_获取
#define __区域参数  0x058A9B44 //7度_获取
#define __区域CALL  0x03717C40 //7度_获取
#define __点券基址  0x05875220 //7度_获取
#define __代币基址  0x05875240 //7度_获取
#define __欢乐代币  0x05875248 //7度_获取
#define __积分基址  0x05875228 //7度_获取
#define __副本名称  0x05788EC8 //7度_获取
#define __副本编号  0x0574400C //7度_获取
#define __房间个数  0x05671BDC //7度_获取

#define __检测调用  0x02A5CC20 //7度_获取
#define __动态CRC  0x058ADA44 //7度_获取
#define __动态扫描  0x058B6A18 //7度_获取
#define __换装效验  0x0282FB50 //7度_获取
#define __物攻检测  0x03B33064 //7度_获取
#define __魔攻检测  0x03B33084 //7度_获取
#define __入包检测  0x028F1000 //7度_获取
#define __攻击检测  0x026F5CC7 //7度_获取
#define __耐久校验  0x03855E08 //7度_获取
#define __怪物检测1  0x038A78E8 //7度_获取
#define __怪物检测2  0x038A78EF //7度_获取
#define __伤害检测1  0x03F0B77A //7度_获取
#define __伤害检测2  0x03F0B77E //7度_获取
#define __坐标检测1  0x028F0C70 //7度_获取
#define __坐标检测2  0x028F0C80 //7度_获取
#define __钩子检测1  0x02766B03 //7度_获取
#define __钩子检测2  0x0286C4B3 //7度_获取
#define __钩子检测3  0x03F0C341 //7度_获取
#define __扩展后台检测  0x029C0132 //7度_获取
#define __技能后台检测  0x029C0059 //7度_获取
#define __模拟BOSS检测  0x037DEE67 //7度_获取
#define __特效CALL检测  0x0F60420 //7度_获取
#define __物理微秒检测1  0x0273C7A1 //7度_获取
#define __物理微秒检测2  0x0273C7AA //7度_获取
#define __物理秒杀检测1  0x0273C851 //7度_获取
#define __物理秒杀检测2  0x0273C85A //7度_获取
#define __魔法微秒检测1  0x0273C901 //7度_获取
#define __魔法微秒检测2  0x0273C90A //7度_获取
#define __魔法秒杀检测1  0x0273C9B1 //7度_获取
#define __魔法秒杀检测2  0x0273C9BA //7度_获取

#define __攻击速度  0x9C8 //7度_获取
#define __移动速度  0x9C0 //7度_获取
#define __释放速度  0x9D0 //7度_获取
#define __物理攻击  0x7F8 //7度_获取
#define __魔法攻击  0x808 //7度_获取
#define __无视物攻  0x838 //7度_获取
#define __无视魔攻  0x840 //7度_获取
#define __独立攻击  0xCA0 //7度_获取
#define __锻造独立  0xCC0 //7度_获取
#define __体力偏移  0x68C //7度_获取
#define __精神偏移  0x69C //7度_获取
#define __力量偏移  0x684 //7度_获取
#define __智力偏移  0x694 //7度_获取
#define __强化偏移  0xE70 //7度_获取
#define __增幅偏移  0xEA0 //7度_获取
#define __锻造偏移  0xEE0 //7度_获取
#define __附魔偏移  0xE80 //7度_获取
#define __负重偏移  0x9A0 //7度_获取
#define __全属强偏移  0xC84 //7度_获取
#define __技能栏偏移  0x88 //7度_获取
#define __技能名称  0x74 //7度_获取
#define __技能等级  0xF9C //7度_获取
#define __技能无色  0xAA0 //7度_获取
#define __超级技能  0xBE8 //7度_获取
#define __技能冷却1  0x728 //7度_获取
#define __技能冷却2  0x73C //7度_获取
#define __技能冷却3  0x750 //7度_获取
#define __技能冷却4  0x764 //7度_获取
#define __技能冷却5  0x778 //7度_获取
#define __技能冷却6  0x78C //7度_获取

#define __物品栏  0x64BC //7度_获取
#define __技能栏  0x6440 //7度_获取
#define __加密评分  0x110 //7度_获取
#define __C_E_评分  0xC0C //7度_获取
#define __倍攻偏移  0x1B0 //7度_获取
#define __入包偏移  0x61E8 //7度_获取
#define __穿戴偏移  0x7B4 //7度_获取
#define __位置偏移  0x108 //7度_获取
#define __角色数量偏移  0xB32 //7度_获取
#define __区域偏移  0xCBC4 //7度_获取
#define __徽章镶嵌  0x10F4 //7度_获取
#define __套装结构  0xF54 //7度_获取
#define __特效偏移  0x104A //7度_获取
#define __人偶代码  0x6CAC //7度_获取
#define __变大偏移  0x2F0 //7度_获取
#define __怪物变大  0x6710 //7度_获取
#define __爆物偏移  0x1789 //7度_获取
#define __动作CALL  0x4D4 //7度_获取
#define __扣血CALL  0x430 //7度_获取
#define __不死偏移  0x32CC //7度_获取
#define __物品CALL  0x860 //7度_获取
#define __阵营偏移  0x828 //7度_获取
#define __快捷栏装备  0x5E8 //7度_获取
#define __设计图人偶  0x4C8 //7度_获取
#define __设计图怪物  0x4C0 //7度_获取
#define __设计图BUFF  0x4C4 //7度_获取
#define __设计图附伤  0x4BC //7度_获取
#define __装备属性  0xB7C //7度_获取
#define __耐久偏移  0x5F4 //7度_获取
#define __装备品级  0x178 //7度_获取
#define __无敌偏移  0xA0C //7度_获取
#define __霸体偏移  0x91C //7度_获取
#define __材料开始  0x4B4 //7度_获取
#define __材料结束  0x4B8 //7度_获取
#define __物品内存  0x154 //7度_获取
#define __冰冻开始  0xB54 //7度_获取
#define __冰冻结束  0xB58 //7度_获取
#define __冰冻尾部  0xB5C //7度_获取
#define __刷新参数1  0x208 //7度_获取
#define __刷新参数2  0x6A8 //7度_获取
#define __任务首地址  0x68 //7度_获取
#define __任务尾地址  0x6C //7度_获取
#define __首地址  0xC0 //7度_获取
#define __尾地址  0xC4 //7度_获取
#define __开箱首地址  0x1730 //7度_获取
#define __开箱尾地址  0x1734 //7度_获取
#define __X坐标  0x1D4 //7度_获取
#define __Y坐标  0x1D8 //7度_获取
#define __Z坐标  0x1DC //7度_获取
#define __任务类型  0x134 //7度_获取
#define __地面物品  0x16C4 //7度_获取
#define __攻击指针  0x3DE0 //7度_获取
#define __按键偏移  0x3DB0 //7度_获取
#define __满血偏移  0x38B8 //7度_获取
#define __满蓝偏移  0x38C0 //7度_获取
#define __代码偏移  0x400 //7度_获取
#define __名称偏移  0x404 //7度_获取
#define __人物等级  0x10D0 //7度_获取
#define __数量偏移  0x2A0 //7度_获取
#define __方向偏移  0xB8 //7度_获取
#define __地图偏移  0xC8 //7度_获取
#define __类型偏移  0xA4 //7度_获取
#define __发包拾取  0xAC //7度_获取
#define __是否开门  0x118 //7度_获取
#define __通关偏移  0xADC //7度_获取
#define __当前房间X  0xBCC //7度_获取
#define __当前房间Y  0xBD0 //7度_获取
#define __BOSS房间X  0xC70 //7度_获取
#define __BOSS房间Y  0xC78 //7度_获取
#define __深渊房间X  0xC80 //7度_获取
#define __深渊房间Y  0xC88 //7度_获取
#define __怪物血量  0x3B04 //7度_获取

#define __动画偏移  0x7604 //7度_获取
#define __坐标顺图  0x1744 //7度_获取
#define __顺图偏移  0x8C //7度_获取
#define __坐标CALL_1  0xCC //7度_获取
#define __坐标CALL_2  0xB0 //7度_获取
#define __取坐标CALL  0xC8 //7度_获取
#define __移动偏移_1  0x69C //7度_获取
#define __移动偏移_2  0x6B0 //7度_获取
#define __过图CALL偏移  0xB8 //7度_获取
#define __是否材料  0x594 //7度_获取
#define __任务条件  0x2D0 //7度_获取
#define __任务副本  0x2B8 //7度_获取
#define __任务材料首  0x2F4 //7度_获取
#define __任务材料尾  0x2F8 //7度_获取
#define __任务完成等级  0x1C4 //7度_获取
#define __任务接收等级  0x1CC //7度_获取
#define __宽高偏移  0x2AC //7度_获取
#define __数组偏移  0x2C0 //7度_获取
#define __起始坐标X  0xCC //7度_获取
#define __起始坐标Y  0xD0 //7度_获取
#define __地图名称  0x1A0 //7度_获取
#define __编号偏移  0x19C //7度_获取
#define __门型偏移  0xC8 //7度_获取
#define __城镇参数X  0x7E0 //7度_获取
#define __城镇参数Y  0x7E4 //7度_获取
#define __武器偏移  0x3260 //7度_获取
#define __称号偏移  0x3264 //7度_获取
#define __上衣偏移  0x3268 //7度_获取
#define __头肩偏移  0x326C //7度_获取
#define __下装偏移  0x3270 //7度_获取
#define __鞋子偏移  0x3274 //7度_获取
#define __腰带偏移  0x3278 //7度_获取
#define __项链偏移  0x327C //7度_获取
#define __手镯偏移  0x3280 //7度_获取
#define __戒指偏移  0x3284 //7度_获取
#define __辅助装备  0x3288 //7度_获取
#define __魔法石__  0x328C //7度_获取
#define __副武器__  0x3290 //7度_获取
#define __耳环偏移  0x3294 //7度_获取
#define __帽子装扮  0x3230 //7度_获取
#define __头部装扮  0x3234 //7度_获取
#define __脸部装扮  0x3238 //7度_获取
#define __上衣装扮  0x323C //7度_获取
#define __下装装扮  0x3240 //7度_获取
#define __鞋子装扮  0x3244 //7度_获取
#define __胸部装扮  0x3248 //7度_获取
#define __腰部装扮  0x324C //7度_获取
#define __皮肤装扮  0x3250 //7度_获取
#define __光环装扮  0x3254 //7度_获取
#define __武器装扮  0x3258 //7度_获取
#define __扩展光环  0x325C //7度_获取
#define __宠物偏移  0x3298 //7度_获取
#define __宠物红装  0x329C //7度_获取
#define __宠物蓝装  0x32A0 //7度_获取
#define __宠物绿装  0x32A4 //7度_获取
#define __名称装饰  0x32A8 //7度_获取
#define __勋章偏移  0x32B0 //7度_获取
#define __物品栏偏移  0x58 //7度_获取
#define __物品栏1  0xC //7度_获取
#define __物品栏2  0x10 //7度_获取
#define __物品栏3  0x14 //7度_获取
#define __物品栏4  0x18 //7度_获取
#define __物品栏5  0x1C //7度_获取
#define __物品栏6  0x20 //7度_获取
#define __技能A  0x0 //7度_获取
#define __技能S  0x4 //7度_获取
#define __技能D  0x8 //7度_获取
#define __技能F  0xC //7度_获取
#define __技能G  0x10 //7度_获取
#define __技能H  0x14 //7度_获取
#define __技能Q  0x18 //7度_获取
#define __技能W  0x1C //7度_获取
#define __技能E  0x20 //7度_获取
#define __技能R  0x24 //7度_获取
#define __技能T  0x28 //7度_获取
#define __技能Y  0x2C //7度_获取


#define __血量偏移 __怪物血量
#define __地面物品名称偏移 __地面物品
#define __图内副本ID __副本编号
#define __图内副本名称 __副本名称
#define __坐标结构偏移1 __顺图偏移
#define __坐标结构偏移2 __坐标顺图
#define __开门偏移 __是否开门
#define __密包CALL __加密包CALL



//键码
#define VK_0  48
#define VK_1  49
#define VK_2  50
#define VK_3  51
#define VK_4  52
#define VK_5  53
#define VK_6  54
#define VK_7  55
#define VK_8  56
#define VK_9  57
#define VK_A  65
#define VK_B  66
#define VK_C  67
#define VK_D  68
#define VK_E  69
#define VK_F  70
#define VK_G  71
#define VK_H  72
#define VK_I  73
#define VK_J  74
#define VK_K  75
#define VK_L  76
#define VK_M  77
#define VK_N  78
#define VK_O  79
#define VK_P  80
#define VK_Q  81
#define VK_R  82
#define VK_S  83
#define VK_T  84
#define VK_U  85
#define VK_V  86
#define VK_W  87
#define VK_X  88
#define VK_Y  89
#define VK_Z  90


#define VK_ID_F1 L"VK_ID_F1"
#define VK_ID_F2 L"VK_ID_F2"
#define VK_ID_F3 L"VK_ID_F3"
#define VK_ID_F4 L"VK_ID_F4"
#define VK_ID_F5 L"VK_ID_F5"
#define VK_ID_F6 L"VK_ID_F6"
#define VK_ID_F7 L"VK_ID_F7"
#define VK_ID_F8 L"VK_ID_F8"
#define VK_ID_F9 L"VK_ID_F9"
#define VK_ID_F10 L"VK_ID_F10"
#define VK_ID_F11 L"VK_ID_F11"
#define VK_ID_F12 L"VK_ID_F12"
#define VK_ID_END L"VK_ID_END"
#define VK_ID_HOME L"VK_ID_HOME"


#define MY_MESSAGE_ID 16524
#define MESSAGE_HOOK_ADDRESS 0x400400
#define __CALL地址 0x400500
#define __CALL参数 0x400800
#define __空白地址 0x400900


#define 搬砖 1
#define 剧情 2
#define 深渊 3
#define 黄龙 4
#define 练习 5

// 对象代码
#define Code_成长之泉水 490007518
#define Code_肉块 10158893
#define Code_鸡腿 10158901
#define Code_通关营火 48026
#define Code_吞噬魔 107000902
#define Code_蔡依林 110525

// 副本编号
#define 格蓝迪 104

// 异常代码
#define 卖物异常 0
#define 刷图异常 1
#endif // !__CONSTS_H__

