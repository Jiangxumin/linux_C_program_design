#!/bin/bash

#kpkg-deb 配置config变量
Package=""
Version=""
Architecture=""
Maintainer=""
Pre_Depends=""
Depends=""
Description=""
InstallDir=""

#dpkg-deb 源码目录
packageSrcDir=""

datetime=`date -d today +"%Y%m%d%H%M"`

# deb包存贮路径，由 调用者提供
packageStorageDir=$1

#####################################################
#####################################################
copy()
{
#	echo "_______copy_________"
	echo "$S1" | grep '<='  && return 1;
	des=`echo $1 | cut -d '<' -f 1`
	src=`echo $1 | cut -d '=' -f 2`	
	echo "mkdir -p ${Package}Tmp/$des"
	mkdir -p ${Package}Tmp/$des

	echo "cp $2/$src  ${Package}Tmp/$des"
	echo ""
}

####################################################
installDir()
{
	echo "==== installDir === "
	argDir=`echo $1 | sed 's/^\ //g'` # > /dev/null
	echo $argDir

	while [ "$argDir" != "" ] 
	do
		arg=`echo $argDir | cut -d ' ' -f 1` # 取出第一个 
		if [ "$arg" != "" ];then
			echo "install $arg"	
			copy "$arg" "$2" "$3"

		fi
		if [ "$argDir" == "" ];then return 1; fi
		argDir=`echo $argDir | sed "s#$arg##g"`
	done 

	#创建 /DEBIAN/control
	mkdir -p ${Package}Tmp/DEBIAN/
echo "Package: ${Package}
Version: ${Version}   
Architecture: ${Architectur}
Maintainer: ${Maintainer}
Pre-Depends: ${Pre_Depends}
Depends: $Depends
Description: $Description" > "${Package}Tmp"/DEBIAN/control

	#打包deb
	echo "dpkg-deb -b "${Package}Tmp" ${Package}_${Version}_${datetime}.deb"
	dpkg-deb -b "${Package}Tmp" ${Package}_${Version}_${datetime}.deb
	mv ${Package}_${Version}_${datetime}.deb  ${packageStorageDir}/
}

###################################################################
# 读取 config 文件
#  
###################################################################
while read line
do
 option=`echo $line | cut -d ':' -f 1 | sed 's/\ $//g'`> /dev/null
 #arg=`echo $line | sed 's/^.*://g' | sed 's/^.*\ //g'` > /dev/null
 arg=`echo $line | sed 's/^.*://g'` # | sed 's/^.*\ //g'` > /dev/null
 if [ "$option" != "InstallDir" ];then
		 arg=`echo $arg | sed 's/^.*\ //g'` > /dev/null
 fi
 case $option in
	 "Package")
		 echo "Package=$arg"
		 Package=$arg
		 ;;
	 "Version")
		 echo "Version=$arg"
		 Version=$arg
		 ;;
	 "Architecture")
		 echo "Architectur=$arg"
		 Architectur=$arg
		 ;;
	 "Maintainer")
		 echo "Maintainer=$arg"
		 Maintainer=$arg
		 ;;
	 "Pre-Depends")
		 echo "Pre-Depends=$arg"
		 Pre_Depends=$arg
		 ;;
	 "Depends")
		 echo "Depends=$arg"
		 Depends=$arg
		 ;;
	 "Description")
		 echo "Description=$arg"
		 Description=$arg
		 ;;
	 "InstallDir")
		 echo "InstallDir=$arg"
		 installDir "$arg" "." ".";
		 ;;
	 *)
		 echo "$option"
		 ;;
 esac
done < config 

