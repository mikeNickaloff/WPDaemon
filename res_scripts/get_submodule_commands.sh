#!/bin/bash
./jq -c ".subcommands[]| if .name == \"$1\" then .subcommands[$3].$2 else \"{}\"  end" ./commands.txt > ./tmp.txt

while read LINE; do
  export LEN=${#LINE}
  if [ "$LEN" -gt "4" ]; then
	echo $LINE > ./tmp2.txt;
        ./jq -c . ./tmp2.txt;
  fi
done < ./tmp.txt
if [ ! -f "./tmp2.txt" ]; then
    echo \"No Parameters\" > ./tmp2.txt
    echo \"No Parameters\"\n
fi
rm ./tmp.txt
rm ./tmp2.txt
#cat ./tmp2.txt

