#include <iostream>
#include <TChain.h>
#include <TEnv.h>
#include <TH1.h>

int main(){
    gEnv->SetValue("TFile.AsyncPrefetching", 1);
    gEnv->SetValue("Cache.Directory","file:cache/");

    auto treename = "Events";
    auto filename = "root://eospublic.cern.ch//eos/opendata/cms/derived-data/AOD2NanoAODOutreachTool/Run2012BC_DoubleMuParked_Muons.root";
    
    TChain chain{treename};
    chain.Add(filename);

    // Cluster boundaries from the second cluster to the end of the tree
    auto start = 821695;
    auto end = 61540413;
    
    chain.SetCacheEntryRange(start, end);

    UInt_t nMuon;
    chain.SetBranchStatus("*",0);
    chain.SetBranchStatus("nMuon",1);
    chain.SetBranchAddress("nMuon",&nMuon);

    auto h = std::make_unique<TH1I>("nMuon","nMuon",100,0,10);
    for(auto i = start; i < end; i ++){
        chain.GetEntry(i);
        h->Fill(nMuon);
    }
    h->Print();
}









