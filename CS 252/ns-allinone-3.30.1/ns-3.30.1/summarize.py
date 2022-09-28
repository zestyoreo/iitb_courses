import os

import pandas as pd


def summary():
    df = pd.read_csv('out-nsta-udp.txt', sep='\t')
    df = df.drop(df.columns[[0, -1]], axis=1)
    aggregates = df.agg([min, max, sum], axis=1)
    time = pd.DataFrame({'Time': map(float, range(1, 1 + len(df)))})

    return pd.concat([time, aggregates], axis=1).round(decimals=4)


if __name__ == '__main__':
    os.chdir(os.path.abspath(os.path.dirname(__file__)))

    print(summary().to_string(index=False))
