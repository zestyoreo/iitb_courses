#!/bin/bash
if [[ $1 && $2 ]]; then

  local=`pwd`/local

  mkdir -p data data/local data/$1 data/$2

  echo "Preparing train and test data"
  echo "make wav.scp for $1 $2"

  rm -rf data/mfcc data/log

  cd corpus/data

  pushd $1
  cp wav.scp ../../../data/$1/wav.scp
  popd

  pushd $2
  cp wav.scp ../../../data/$2/wav.scp
  popd

  echo "copy spk2utt, utt2spk, text for $1 $2"

  for x in $1 $2; do
    cp $x/spk2utt ../../data/$x/.
    cp $x/utt2spk ../../data/$x/.
    cp $x/text ../../data/$x/.
  done

  pushd ../../data/local
  if [ ! -f  "swahili.arpa" ]; then
    cd ../../corpus/LM
    cp swahili.small.arpa ../../data/local/
  fi
  popd

  echo "Preparing data OK."

  cd ../..
else
  echo "ERROR: Preparing train and test data failed !"
  echo "You must have forgotten to point to the correct train/test directories"
  echo "Usage: ./prepare_data.sh train test"
fi
