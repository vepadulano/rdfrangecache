#include <iostream>
#include <TChain.h>
#include <ROOT/RDataFrame.hxx>
#include <TEnv.h>

int main(){
    gEnv->SetValue("TFile.AsyncPrefetching", 1);
    gEnv->SetValue("Cache.Directory","file:cache/");

    auto treename = "Events";
    auto filename = "root://eospublic.cern.ch//eos/opendata/cms/derived-data/AOD2NanoAODOutreachTool/Run2012BC_DoubleMuParked_Muons.root";
    
    TChain chain{treename};
    chain.Add(filename);

    // Cluster boundaries of cluster 13
    auto start = 10682035;
    auto end = 11503730;
    
    chain.SetCacheEntryRange(start, end);

    ROOT::RDataFrame rdf{chain};
    auto rdf_range = rdf.Range(start,end);

    auto h = rdf_range.Histo1D({"name","title",100,0,100},"nMuon");
    
    h->Print();
}









