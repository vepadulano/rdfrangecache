import ROOT

ROOT.gEnv.SetValue("TFile.AsyncPrefetching", 1)
ROOT.gEnv.SetValue("Cache.Directory","file:cache/")

treename = "Events"
filename = "root://eospublic.cern.ch//eos/opendata/cms/derived-data/AOD2NanoAODOutreachTool/Run2012BC_DoubleMuParked_Muons.root"
chain = ROOT.TChain(treename)
chain.Add(filename)

# Cluster boundaries of first half of the tree
start = 0
end = 31224410

chain.SetCacheEntryRange(start, end)

rdf = ROOT.RDataFrame(chain)
rdf_range = rdf.Range(start,end)

h = rdf_range.Histo1D(("name","title",100,0,100),"nMuon")
print(h.GetValue())
