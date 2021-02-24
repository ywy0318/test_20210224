#/bin/bash
core_func(){
        # 修改  kernelwatchdog = 0 
	grep "kernelwatchdog" /config/dvr/config_mac.ini >/dev/null
	if [ $? != 0 ]
	then
		echo "not find the keyword kernelwatchdog"
		##在第3行增加新的语句
		sed -i '3a kernelwatchdog = 0'  /config/dvr/config_mac.ini
	else
		B=`grep "kernelwatchdog" /config/dvr/config_mac.ini -n|cut -d : -f 1`
	
		## 删除旧行代码 ##
		sed ''"$B"'d' /config/dvr/config_mac.ini -i
		B=`expr $B - 1`
	
	        ##增加新行代码 ##
		sed -i ''"$B"'a kernelwatchdog = 0'  /config/dvr/config_mac.ini
	fi
	
	
	## 在 ./closedog 后添加新的语句 
	B=`grep "./closedog" /tdfs/loadbefore -n|cut -d : -f 1`
	if [ $? != 0 ]
	then
		echo "not find the keyword ./closedog"
		exit
	fi
	
	grep "echo 123456 > /dvrfile/core_flg.ini" /tdfs/loadbefore >/dev/null
	if [ $? = 0 ]
	then
	        ##删除旧的已有的代码 ##
		A=`grep "echo 123456 > /dvrfile/core_flg.ini" /tdfs/loadbefore -n|cut -d : -f 1`
		sed ''"$A"'d' /tdfs/loadbefore -i
	fi
	##增加新的语句##
	sed -i ''"$B"'a echo 123456 > /dvrfile/core_flg.ini'  /tdfs/loadbefore
	
	grep "echo 0 > /proc/sys/kernel/tdlsm/lsm_enable" /tdfs/loadbefore >/dev/null
	if [ $? = 0 ]
	then
		A=`grep "echo 0 > /proc/sys/kernel/tdlsm/lsm_enable" /tdfs/loadbefore -n|cut -d : -f 1`
		sed ''"$A"'d' /tdfs/loadbefore -i
	fi
	B=`expr $B + 1`	                                                           
	sed -i ''"$B"'a echo 0 > /proc/sys/kernel/tdlsm/lsm_enable'  /tdfs/loadbefore
	
	grep "echo 123456 > /dvr/core_flg.ini" /tdfs/loadbefore >/dev/null
	if [ $? = 0 ]
	then
		A=`grep "echo 123456 > /dvr/core_flg.ini" /tdfs/loadbefore -n|cut -d : -f 1`
		sed ''"$A"'d' /tdfs/loadbefore -i
	fi
	B=`expr $B + 1`	
	sed -i ''"$B"'a echo 123456 > /dvr/core_flg.ini'  /tdfs/loadbefore
	
	
		##获取硬盘目录 ##
	A=`df|grep sata|awk '{print $NF}'`
	i=0
	var_path_pre="/mnt/sata/"
	var_path_suf="/0"
	
	while [ $i -lt 20 ]
	do
		#echo "i = $i"
		var_path=$var_path_pre""$i""$var_path_suf	
		#echo "var_path = $var_path"
		i=`expr $i + 1`

		result=$(echo $string | grep "${var_path}")

		if [[ "$result" != "" ]]
		then
			echo "string include $var_path"
			break
		else
			echo "string not include $var_path"
		fi
	done
	if [ $i -gt 19 ]
	 then
	 echo "not find sata,core_func deploy failed,now exit"
	 exit
	fi
		
	grep "> /proc/sys/kernel/core_pattern" /tdfs/loadbefore >/dev/null
	if [ $? = 0 ]
	then
	        ##删除旧的代码##
		C=`grep "> /proc/sys/kernel/core_pattern" /tdfs/loadbefore -n|cut -d : -f 1`
		sed ''"$C"'d' /tdfs/loadbefore -i
	fi
	echo $var_path
	echo ''"$B"'a echo "'"$var_path"'/core.%e.%p.%h.%t" > /proc/sys/kernel/core_pattern'
	sed -i ''"$B"'a echo "'"$var_path"'/core.%e.%p.%h.%t" > /proc/sys/kernel/core_pattern'  /tdfs/loadbefore
	
	## 注释该语句 ./ TODO & ## 
	grep "./TODO &" /tdfs/loadbefore >/dev/null
	if [ $? != 0 ]
	then
		echo "not find the keyword ./TODO &"
	else
		B=`grep "./TODO &" /tdfs/loadbefore -n|cut -d : -f 1`
		sed ''"$B"'d' /tdfs/loadbefore -i
		B=`expr $B - 1`
		sed -i ''"$B"'a #./TODO &'  /tdfs/loadbefore
	fi
	
	grep "ulimit -c unlimited" /tdfs/loadbefore >/dev/null
	if [ $? = 0 ]
	then
		A=`grep "ulimit -c unlimited" /tdfs/loadbefore -n|cut -d : -f 1`
		sed ''"$A"'d' /tdfs/loadbefore -i
	fi
	B=`expr $B + 1`	
	sed -i ''"$B"'a ulimit -c unlimited'  /tdfs/loadbefore
	
	B=`expr $B + 1`
	

	
	
	##放开注释，并添加新语句 ## 
	grep "sh load -d" /tdfs/loadbefore >/dev/null
	if [ $? != 0 ]
	then
		echo "not find the keyword: sh load -d"
		exit
	fi
	sed ''"$B"'d' /tdfs/loadbefore -i
	B=`expr $B - 1`
	sed -i ''"$B"'a sh load -d'  /tdfs/loadbefore
	
	##增加新的一行
	grep "./gui &" /tdfs/loadbefore >/dev/null
	if [ $? = 0 ]
	then
		A=`grep "./gui &" /tdfs/loadbefore -n|cut -d : -f 1`
		sed ''"$A"'d' /tdfs/loadbefore -i
	fi
	B=`expr $B + 1`	
	sed -i ''"$B"'a ./gui &'  /tdfs/loadbefore

        ##增加新的一行
	grep "./dvr1 &" /tdfs/loadbefore >/dev/null
	if [ $? = 0 ]
	then
		A=`grep "./dvr1 &" /tdfs/loadbefore -n|cut -d : -f 1`
		sed ''"$A"'d' /tdfs/loadbefore -i
	fi
	B=`expr $B + 1`
	sed -i ''"$B"'a ./dvr1 &'  /tdfs/loadbefore
	echo "deploy succeed"
}
help_func(){
	echo -e "the program is designed to improve wokers' efficiency.it include the paramter: help,core,fortest,"
	echo -e "logman,getlog,macip,randompasson,randompassoff.the details are as follows:"
        echo -e "core: automatically deploy the environment for generating core files"
	echo -e "fortest: designed for colleagues working for test to slove the aging problem"
	echo -e "logman: deploy the logman-initiated environment"
	echo -e "getlog: Collect device information for problem analysis,for example:./oneKey.sh getlog 10.30.30.212"
	echo -e "macip: deploy mac and ip,for example:./oneKey.sh macip 10.30.30.253"
	echo -e "randompasson: Random password open"
	echo -e "randompassoff: Random password close"
	echo -e "flash: Automatically download  flash detection tools to update software"
	echo -e "flash2File: Automatically download  flash detection tools to update software and save the results in the disk"
}
fortest(){
	##在文件结尾添加新的语句
	grep "telnetd &" /tdfs/loadbefore >/dev/null
	if [ $? = 0 ]
	then
		B=`grep "telnetd &" /tdfs/loadbefore -n|cut -d : -f 1`
		sed ''"$B"'d' /tdfs/loadbefore -i
	fi
	echo "telnetd &" >>/tdfs/loadbefore
	
	##在文件头修改注释
	head -n 10 /tdfs/loadbefore|grep "/sbin/getty -L ttyS000 115200 vt100 -n root -I" -n >/dev/null
	if [ $? = 0 ]
	then
		B=`head -n 10 /tdfs/loadbefore|grep "/sbin/getty -L ttyS000 115200 vt100 -n root -I" -n|cut -d : -f 1`
		##删除该语句
		sed ''"$B"'d' /tdfs/loadbefore -i
		##添加新的语句
		sed ''"$B"'i /sbin/getty -L ttyS000 115200 vt100 -n root -I "Auto login as root ..." &' /tdfs/loadbefore -i
	else
		sed '2i /sbin/getty -L ttyS000 115200 vt100 -n root -I "Auto login as root ..." &' /tdfs/loadbefore -i	
	fi
	
	##修改第三条语句
	head -n 10 /tdfs/loadbefore|grep "/sbin/getty -L ttyS1 9600 vt100" -n >/dev/null
	if [ $? = 0 ]
	then
		B=`head -n 10 /tdfs/loadbefore|grep "/sbin/getty -L ttyS1 9600 vt100" -n|cut -d : -f 1`
		##删除该语句
		sed ''"$B"'d' /tdfs/loadbefore -i
		##添加新的语句
		sed ''"$B"'i #/sbin/getty -L ttyS1 9600 vt100' /tdfs/loadbefore -i
	else
		sed '3i #/sbin/getty -L ttyS1 9600 vt100' /tdfs/loadbefore -i	
	fi
	
	touch /dvr/telnetd.in
	echo "deploy succeed"
}
logman(){

        ##设置logman启动环境##
	cd /dvr/
	touch /dvrfile/logman
	ls|grep  journald -w >/dev/null
	if [ $? != 0 ]
	then
		echo "can not find journald in /dvr"
		exit
	fi
	./journald –d
        
	ls|grep  logman -w >/dev/null
	if [ $? != 0 ]
	then
		cd /nand/tools
		ls|grep logman.tar.gz -w
		if [ $? != 0 ]
		then
			echo "can not find logman.tar.gz in /nand/tools "
			exit
		else
			tar -xzf logman.tar.gz
		fi
	fi
	chmod 777 logman
	./logman -d $1
        echo "deploy succeed"
}
getlog(){
	ls /nand/tools/|grep -v bak|grep -w getlog.sh >/dev/null
	if [ $? = 0 ]
	then
		##直接运行即可##
		echo $1
		cd /nand/tools/
		chmod 777 /nand/tools/getlog.sh 
		./getlog.sh $1 
	else
		cd /nand/tools/
		ls /nand/tools/|grep getlog.tar.gz -w >/dev/null
		if [ $? != 0 ]
		then
			echo "can not find getlog.tar.gz in /nand/tools/"
			exit
		fi
		tar -xzf /nand/tools/getlog.tar.gz
		chmod 777 /nand/tools/getlog.sh 
		./getlog.sh $1
	fi
		
}
macip(){
	##将ip后两位进行替换到文本中
	
	##对参数进行切割，取得后两位
	A=`echo $1|cut -d . -f 4`
	B=`echo $1|cut -d . -f 3`

	##获取原mac前四位地址
	mac1=`grep mac1 /config/dvr/config_mac.ini|cut -d = -f 2|cut -d ";" -f 1|cut -d : -f 1`
	mac2=`grep mac1 /config/dvr/config_mac.ini|cut -d = -f 2|cut -d ";" -f 1|cut -d : -f 2`
	mac3=`grep mac1 /config/dvr/config_mac.ini|cut -d = -f 2|cut -d ";" -f 1|cut -d : -f 3`
	mac4=`grep mac1 /config/dvr/config_mac.ini|cut -d = -f 2|cut -d ";" -f 1|cut -d : -f 4`
	
	##mac5为 "网卡的mac地址"
	mac5=`grep mac1 /config/dvr/config_mac.ini|cut -d ";" -f 2`	
	
	##进行替换语句
	grep mac1 /config/dvr/config_mac.ini -n|cut -d : -f 1 >/dev/null
	if [ $? = 0 ]
	then
		##找到该行号
		C=`grep mac1 /config/dvr/config_mac.ini -n|cut -d : -f 1`
		##删除该语句
		sed ''"$C"'d' /config/dvr/config_mac.ini -i
		##添加新的语句
		sed ''"$C"'i   mac1                           = '"$mac1"':'"$mac2"':'"$mac3"':'"$mac4"':'"$B"':'"$A"';'"$mac5"''   /config/dvr/config_mac.ini -i
	else
		sed '2i   mac1                           = '"$mac1"':'"$mac2"':'"$mac3"':'"$mac4"':'"$B"':'"$A"';'"$mac5"''   /config/dvr/config_mac.ini -i
	fi
	
	##修改  /config/dvr/config_net.ini 文件
	grep  -w "ipaddress"   /config/dvr/config_net.ini -n >/dev/null
	if [ $? = 0 ]
	then
		##找到该行号
		C=`grep  -w "ipaddress"   /config/dvr/config_net.ini -n|cut -d : -f 1`
		##删除该语句
		sed ''"$C"'d' /config/dvr/config_net.ini -i
		##添加新的语句
		sed ''"$C"'i   ipaddress   =  '"$1"''   /config/dvr/config_net.ini -i
	else
		sed '5i   ipaddress   =  '"$1"''   /config/dvr/config_net.ini -i
	fi
	
}
randompasson(){
	ls   /config/dvr/|grep bak -v|grep root_pwdupdate -w >/dev/null
	if [ $? != 0 ]
	then
		ls   /config/dvr/|grep root_pwdupdate.bak -w >/dev/null
		if [ $? != 0 ]
		then	
			echo "can not find the file root_pwdupdate and root_pwdupdate.bak"
			exit
		else
			mv  /config/dvr/root_pwdupdate.bak  /config/dvr/root_pwdupdate
		fi	
	fi
	echo "deploy successed"
}
randompassoff(){
	ls   /config/dvr/|grep bak -v|grep root_pwdupdate -w >/dev/null
	if [ $? = 0 ]
	then
		mv  /config/dvr/root_pwdupdate  /config/dvr/root_pwdupdate.bak
	fi
	passwd
	if [ $? != 0 ]
	then
		echo "failed passwd"
	fi
	echo "deploy successed"
}
flash(){
	ls /dvr|grep  inotify-arm-hisiv300-linux >/dev/null
	if [ $? != 0 ]
	then
		echo "find inotify-arm-hisiv300-linux in /dvr failed "
	fi
	./inotify-arm-hisiv300-linux & >/dev/null
}
flash2file(){
	ls /dvr|grep  inotify-arm-hisiv300-linux >/dev/null
	if [ $? != 0 ]
	then
		echo "find inotify-arm-hisiv300-linux in /dvr failed "
	fi
	A=`df|grep sata|awk '{print $NF}'`
	echo $A
	year=`date|awk '{print $6}'`
	month=`date|awk '{print $2}'`
	day=`date|awk '{print $3}'`
	time=`date|awk '{print $4}'`
	
	##备份到磁盘上
	echo "$month $day $time"
	./inotify-arm-hisiv300-linux  & > $A/inotify_result.$year.$month.$day.$time
}

###主函数部分##################################
if [[ $# != 1 && $# != 2 ]]
then
	echo "number of parameter is not correct,please use help paramter to see the detail information,such as: ./oneKey.sh help"
	exit
fi
case $1 in
core) core_func
;;
help) help_func
;; 
fortest) fortest
;;
logman) if [ $# != 2 ]
	then
		echo "number of parameter is not correct,for example:./oneKey.sh logman /DVR/zf or ./oneKey.sh logman /APP/zf"
		exit
	fi
	if [[ $2 != "/DVR/zf" && $2 != "/APP/zf" ]]
	then
		echo "The second paramter is not right,it must be /DVR/zf or /APP/zf"
		exit
	fi
	
	logman $2
;;
getlog) if [ $# != 2 ]
	then
		echo "number of parameter is not correct,please enter the pcip,for example:./oneKey.sh getlog 10.30.30.212"
		exit
	fi
	getlog $2
;;
macip) 	if [ $# != 2 ]
	then
		echo "number of parameter is not correct,please enter the macip,for example:./oneKey.sh macip 10.30.30.253"
		exit
	fi
	macip $2
;;
randompasson) randompasson  
;;
randompassoff) randompassoff
;;
flash) flash
;;
flash2file) flash2file
;;
*) echo "the paramter is not right,you can use help to see the details,such as: ./oneKey.sh help"
;;
esac












































