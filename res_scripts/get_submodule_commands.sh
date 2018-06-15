#!/bin/bash
./jq -c ".subcommands[]| if .name == \"$1\" then .subcommands[].$2 else \"{}\"  end" ./commands.txt > ./tmp.txt
while read LINE; do
  export LEN=${#LINE}
  if [ "$LEN" -gt "4" ]; then
	echo $LINE > ./tmp2.txt;
        ./jq -c . ./tmp2.txt;
  fi
done < ./tmp.txt
#cat ./tmp2.txt
rm ./tmp.txt
rm ./tmp2.txt
