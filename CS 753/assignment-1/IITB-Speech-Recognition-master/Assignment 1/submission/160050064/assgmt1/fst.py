class FST:
    def __init__(self, name="", eps='<eps>'):
        self.name = name
        self.eps = eps
        self.num_states = 0
        self.final_states = []
        self.arcs = []
        self.input_symbols = set()
        self.output_symbols = set()

    def new_state(self):
        self.num_states += 1
        return self.num_states - 1

    def add_arc(self, src, dest, in_label, out_label):
        self.arcs.append((src, dest, in_label, out_label))
        self.input_symbols.add(in_label)
        self.output_symbols.add(out_label)

    def load(self, file):
        self.initial_state = -1
        with open(file, 'r') as f:
            for line in f:
                tokens = line.strip().split('\t')
                if len(tokens) == 4:
                    tokens[0], tokens[1] = int(tokens[0]), int(tokens[1])
                    if self.initial_state == -1:
                        self.initial_state = tokens[0]
                    self.num_states = max(self.num_states, tokens[0], tokens[1])
                    self.add_arc(tokens[0], tokens[1], tokens[2], tokens[3])
                else:
                    self.final_states.append(int(tokens[0]))
        self.num_states += 1

    def write_isyms(self):
        with open('{}.isyms'.format(self.name), 'w') as f:
            f.write("{} 0\n".format(self.eps))
            self.input_symbols.discard(self.eps)
            for idx, symbol in enumerate(sorted(self.input_symbols), 1):
                f.write(f"{symbol} {idx}\n")
            f.flush()

    def write_osyms(self):
        with open('{}.osyms'.format(self.name), 'w') as f:
            f.write("{} 0\n".format(self.eps))
            self.output_symbols.discard(self.eps)
            for idx, symbol in enumerate(sorted(self.output_symbols), 1):
                f.write(f"{symbol} {idx}\n")
            f.flush()

    def write_fst(self):
        with open('{}.txt'.format(self.name), 'w') as f:
            for src, dest, in_label, out_label in self.arcs:
                f.write("{}\t{}\t{}\t{}\n".format(src, dest, in_label, out_label))
            self.final_states = list(set(self.final_states))
            for state in sorted(self.final_states):
                f.write("{}\n".format(state))
            f.flush()
