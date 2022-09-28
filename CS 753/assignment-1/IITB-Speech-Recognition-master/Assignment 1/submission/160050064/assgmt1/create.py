from fst import FST
import argparse


parser = argparse.ArgumentParser()
parser.add_argument('--fst',    action='store_true')
parser.add_argument('--isyms',  action='store_true')
parser.add_argument('--osyms',  action='store_true')
parser.add_argument('--name',   type=str,   required=True)
parser.add_argument('--file',   type=str,   required=True)


if __name__ == '__main__':
    args = parser.parse_args()
    fst = FST(args.name)
    fst.initial_state = fst.new_state()
    fst.final_states.append(fst.new_state())
    with open(args.file, 'r') as f:
        for line in f:
            if fst.name == 'L':
                word, phones = line.strip().split('\t')
                tokens = phones.split()
            elif fst.name == 'S':
                word = line.strip().split('\t')[0]
                tokens = list(word)
            
            if len(tokens) == 1:
                fst.add_arc(fst.initial_state, fst.final_states[0], word, tokens[0])
            else:
                state = fst.new_state()
                fst.add_arc(fst.initial_state, state, word, tokens[0])
                for phone in tokens[1:-1]:
                    state = fst.new_state()
                    fst.add_arc(state - 1, state, fst.eps, phone)
                fst.add_arc(state, fst.final_states[0], fst.eps, tokens[-1])
    if args.fst:
        fst.write_fst()
    if args.isyms:
        fst.write_isyms()
    if args.osyms:
        fst.write_osyms()
