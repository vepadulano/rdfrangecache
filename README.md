# Caching different partitions of a TBranch with TFilePrefetch

The goal of these tests is to understand how to cache (through `TFilePrefetch` machinery) different partitions of the same TBranch, e.g. from entry `n` to entry `m` as long as these values are inside the boundaries of the branch itself.

The use case is distributing an `RDataFrame` analysis on a cluster of workers, where each one should be able to cache the data it is processing independently of the current range in use.

The current behaviour is that the cache is activated if the worker is processing the first chunk of the branch, e.g. from entry `0` to entry `n`. If the chunk instead starts from another entry, there will be no cache. In particular, this happens if the starting entry is outside of the boundaries of the first cluster in the `TTree`.

The approach so far is to create a very simple analysis, that reads a branch from a remote file on EOS and then creates a `TH1D` with the values of the branch. The following tests have been done:
1. Tested with `RDataFrame` only to confirm the behaviour on a local machine.
2. Tested with `TChain` only, the file is correctly cached independently of the entry range.
3. Tested with `TTreeReader` only, replicates the behaviour of `RDataFrame`.