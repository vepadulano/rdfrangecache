import ROOT
from pprint import pprint

treename = "Events"
filename = "root://eospublic.cern.ch//eos/opendata/cms/derived-data/AOD2NanoAODOutreachTool/Run2012BC_DoubleMuParked_Muons.root"
f = ROOT.TFile.Open(filename)
t = f.Get(treename)

entries = t.GetEntriesFast()
it = t.GetClusterIterator(0)
start = it()
end = 0

clusters = {}
i = 0
while start < entries:
    end = it()
    cluster = (start, end)
    clusters[i]= cluster
    start = end
    i += 1

print("Clusters in tree: ", len(clusters))
pprint(clusters)