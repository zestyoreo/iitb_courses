#!/bin/sh

cd ..
steps/get_train_ctm.sh data/train/ lang exp/tri1
cd 2D/
echo $1 > texttobespoken.txt
python3 get_audio.py
rm *.txt
rm -r clips/