#!/bin/bash

# 生成目录

echo "bash makedir.sh 参数1（文件夹前缀） 参数2（文件夹个数）"
echo "例如： bash makedir.sh 27-  5"

dir=$1

i=0
j=0

while [ $i -lt $2 ]
do
	if [ $i -lt 10 ]
	then
		if [ -d "$dir$j$i" ]
		then
			echo "$dir$j$i""已存在"
		else
			mkdir "$dir$j$i"
		fi
	else
		if [ -d "$dir$i" ]
		then
			echo "$dir$i""已存在"
		else
			mkdir "$dir$i"
		fi
	fi
#	echo $i
	i=`expr $i + 1`
done

