#!bin/bash
gcc -Wall explorer.c counter.c
flag_p=""
flag_f=""
path=""
while getopts 'pfd:' flag;
do
	case $flag in
		p) flag_p="p" ;;
		f) flag_f="f" ;;
		d) 
		if [ "$path" != "" ];
		then
			echo "usage: . [-d DIRPATH] [-f] [-p]"
			exit
		else
			path=$OPTARG
		fi ;;		
		\?) 
			echo "usage: . [-d DIRPATH] [-f] [-p]"
			exit ;;
	esac
done
path=`./a.out $path $p$f`
if [ $? -ne 0 ];
then
	echo "Something went wrong. Did you put in a valid directory?"
 
elif [ "$flag_p" = "p" ];
then
	echo $path
else
	cd $path
fi
