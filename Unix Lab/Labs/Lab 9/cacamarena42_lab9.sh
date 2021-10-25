#!/bin/bash

cut -d ' ' -f 1 $1 | sort | uniq -c | sort -gr | head -n 5 | sed -e "s/^ *//" -e "s/ /\t/" | sed "1 i .TS\ncenter box;\ncb s\ncb lb\nn 1.\nTop Requesters\n=\nCount\tHost\n" | groff -t -T ascii | cat -s

cut -d ' ' -f 7 $1 | sort | uniq -c | sort -gr | head -n 5 | sed -e "s/^ *//" -e "s/ /\t/" | sed "1 i .TS\ncenter box;\ncb s\ncb lb\nn1.\nTop Requested Resources\n=\nCount\tResource\n" | groff -t -T ascii | cat -s
