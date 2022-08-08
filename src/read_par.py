from sys import displayhook
import pandas as pd

df = pd.read_parquet("/root/arrow-report/input/sample.parquet")

for col in df.columns:
    df[col].values[:] = 0

df.columns = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k']

df = df.iloc[0:1000, :]

displayhook(df)

# df.to_parquet("/root/arrow-report/input/sample-out.parquet")
