#! /bin/sh
s1="abcdefg"
s2="bcd"
result=$(echo $s1 | grep "${s2}")
if [[ "$result" != "" ]]
then
	echo "$s1 include $s2"
else
	echo "$1 not include $s2"
fi
