#!/bin/bash
checkRecBinDirectory(){
	if [ -d "/home/lukas/.trashBin" ]
		then
			echo "RecBinDir exists. fine."
		else
			echo "RecBin doesn't exist. Creating directory:"
			mkdir /home/lukas/.trashBin
			touch /home/lukas/.trashBin/.dir
			echo "done"
	fi
}
generateFileName(){
	timestamp=$(date +%y%m%d%H%M%S)
	pid="$$"
}
writeToDirectoryFile(){
	abspath=$(realpath $1)
	echo "temporary file is called:"
	echo "$timestamp"_"$pid.dat! $abspath" >> /home/lukas/.trashBin/.dir
	cat /home/lukas/.trashBin/.dir
}
moveFileToRecycleBin(){
	mv "$(realpath $1)" "/home/lukas/.trashBin/"
	mv "/home/lukas/.trashBin/$1" "/home/lukas/.trashBin/$timestamp"_"$pid.dat"
}
checkValidFile(){
	if [ -e $(realpath $1) ]
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
echo "-->Welcome to RecycleBin V1.0!!!<--"
checkValidFile $1
checkRecBinDirectory # gucken ob alle Verzeichnisse angelegt sind
generateFileName # spezifischen Dateinamen erzeugen
writeToDirectoryFile $1 # .dir befuellen
moveFileToRecycleBin $1 # datei tatsaechlich verschieben
