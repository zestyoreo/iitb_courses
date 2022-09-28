import argparse
import subprocess


parser = argparse.ArgumentParser()
parser.add_argument('--path',   type=str,   required=True)
parser.add_argument('--word',   type=str,   required=True)


if __name__ == '__main__':
    args = parser.parse_args()
    word_length = len(args.word)
    pronunciations = []
    for idx in range(1, word_length):
        prefix = subprocess.check_output("./lookup.sh 3 {}/QPrefix.fst {}".format(args.path, args.word[:idx]), shell=True).decode('utf-8').strip()
        suffix = subprocess.check_output("./lookup.sh 3 {}/QSuffix.fst {}".format(args.path, args.word[idx:]), shell=True).decode('utf-8').strip()
        if prefix != "" and suffix != "":
            pronunciation = ' '.join(tok for tok in (prefix + ' ' + suffix).split() if tok != '<eps>')
            pronunciations.append((abs(word_length / 2 - idx), pronunciation))
    if len(pronunciations) == 0:
        print("Failed to generate pronunciation!")
    else:
        print(sorted(pronunciations)[0][1])