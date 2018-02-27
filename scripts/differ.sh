#!/bin/bash
# first param = nombre de champions 
# puis les champions
# puis le cycle du dump


RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
max=$1
c=1
list_mine=""
list_zaz=""
while [ $c -le $max ]
do
		list_mine="$list_mine -n $c $2"; 
		list_zaz="$list_zaz $2"; 
		shift
		(( c++ ))
done

list_mine="$list_mine -dump $2"; 
list_zaz="$list_zaz -d $2"; 


exec_mine=`./corewar $list_mine | tail -n 64`

exec_zaz=`./zaz_corewar $list_zaz | tail -n 64`


echo "$exec_mine"
echo ""
echo "$exec_zaz"
echo ""
diff="`diff -u <(echo "$exec_mine") <(echo "$exec_zaz")`"
if [ "$diff" = "" ] 
then
	echo -e "${GREEN}diff ok${NC}"
else
	echo -e "${RED}diff ko${NC}"
	echo "$diff" > diff
fi

