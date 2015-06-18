#!/bin/bash
#150506083631_3984.dat
readRealFileInfo(){
	while read line; do
		IFS="! "
		STR_ARRAY=( $line)
		if [ ${STR_ARRAY[0]} == $1 ]
			then
				filename=${STR_ARRAY[0]}
				abspath=${STR_ARRAY[1]}
				path=$(dirname $abspath)
		fi
	done < "/home/lukas/.trashBin/.dir"
}
checkValidFile(){
	if [ -e /home/lukas/.trashBin/$1 ]
		then
			echo "File exists.nice."
		else
			echo "File $1 not found.exiting."
			exit
	fi
	
	if [ ! -n $1 ]
		then
			echo "empty input. exiting."
			exit	
	fi
}
moveFile(){
	mv /home/lukas/.trashBin/$1 $path
	mv $path/$1 $abspath
}
cleanDirectoryFile(){
	sed -i '/'$1'/d' '/home/lukas/.trashBin/.dir'
}
checkValidFile $1
readRealFileInfo $1
moveFile $1
cleanDirectoryFile $1

