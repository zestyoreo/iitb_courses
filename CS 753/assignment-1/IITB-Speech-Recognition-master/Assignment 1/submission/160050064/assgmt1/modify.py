from fst import FST
import argparse
import copy


parser = argparse.ArgumentParser()
parser.add_argument('--prefix', action='store_true')
parser.add_argument('--suffix', action='store_true')
parser.add_argument('--name',   type=str,   required=True)
parser.add_argument('--file',   type=str,   required=True)


if __name__ == '__main__':
    args = parser.parse_args()
    fst = FST(args.name)
    fst.load(args.file)
    
    if args.prefix:
        fst_prefix = copy.deepcopy(fst)
        fst_prefix.name = '{}Prefix'.format(fst.name)
        for state in range(fst_prefix.num_states):
            fst_prefix.final_states.append(state)
        fst_prefix.write_fst()
    
    if args.suffix:
        fst_suffix = copy.deepcopy(fst)
        fst_suffix.name = '{}Suffix'.format(fst.name)
        for state in range(fst_suffix.num_states):
            fst_suffix.add_arc(fst_suffix.initial_state, state, fst_suffix.eps, fst_suffix.eps)
        fst_suffix.write_fst()