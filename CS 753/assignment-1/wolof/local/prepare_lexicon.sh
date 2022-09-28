#!/bin/sh

. ./path.sh

# /!\ MODIFY THE PATH TO LINK TO YOUR KALDI DIR
KALDI_DIR=$KALDI_ROOT/egs/wolof
# /!\ OR COMMENT IT AND CREATE SYMBOLIC LINKS OF utils/ and steps/
# /!\ IN YOUR CURRENT WORK DIRECTORY

mkdir -p lang/dict

##create nonsilence_phones.txt
cat lang/lexicon.txt | awk '{for (i=2;i<=NF;i++) print $i}' | sort -u > lang/dict/nonsilence_phones.txt

##create silence_phones.txt
touch lang/dict/silence_phones.txt
##extra_questions.txt
touch lang/dict/extra_questions.txt

##lexicon.txt
cat lang/lexicon.txt | sed 's/(.)//' > lang/dict/lexicon.txt
#SIL
echo "SIL\tSIL" >> lang/dict/lexicon.txt
echo "<UNK>\tSIL" >> lang/dict/lexicon.txt
echo "SIL" > lang/dict/optional_silence.txt
echo "<UNK>" > lang/oov.txt
echo "SIL" >> lang/dict/silence_phones.txt

$KALDI_DIR/utils/prepare_lang.sh lang/dict "<UNK>" lang/tmp lang
