#!bin/bash
gcc -Wall explorer.c counter.c
path=`./a.out "$@"`
if [ $? -eq 0 ];
then
	cd $path
elif [ "$path" != "" ];
then
	echo $path
fi
