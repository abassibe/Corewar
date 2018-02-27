#!/bin/bash
# ce script va lancer le differ.sh  autant de fois que preciser en dernier param
# first param = nombre de champions 
# puis les champions
# puis le cycle max du dump


RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
max=$1
c=1
list_call=" $max"
while [ $c -le $max ]
do
		list_call="$list_call $2"; 
		shift
		(( c++ ))
done

mrun=$2
step=$3

echo $list_call
echo $mrun


l=0
while [ $l -le $mrun ]
do
	exec_mine=`./differ.sh $list_call $l | grep diff`
	echo -ne "Dump after \t$l cycles :\t"
	echo $exec_mine
	let "l=l+step"
done

