#!/bin/sh

cd ..
steps/get_train_ctm.sh data/train/ data/lang exp/tri1
cd task7/

grep $1 ../exp/tri1/ctm > instances.txt

python3 get_clips.py

