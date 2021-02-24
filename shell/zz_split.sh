#! /bin/sh
string="/mnt/sata/0/0 
/mnt/sata/1/0 
/mnt/sata/2/0

"
i=0
var_path_pre="/mnt/sata/"
var_path_suf="/0"
#var_path=$var_path_pre""$i""$var_path_suf

while [ $i -lt 20 ]
do
	echo "i = $i"
	var_path=$var_path_pre""$i""$var_path_suf	
	echo "var_path = $var_path"
	i=`expr $i + 1`

	result=$(echo $string | grep "${var_path}")
	#result=$(echo $s1 | grep "${s2}")

	if [[ "$result" != "" ]]
	then
		echo "string include $var_path"
		break
	else
		echo "string not include $var_path"
	fi
done

#if
if [ $i -gt 19 ]
 then
 echo "not find sata,core_func deploy failed,now exit"
 #exit
else
 echo "ulimit -c unlimited"
fi
echo $string


