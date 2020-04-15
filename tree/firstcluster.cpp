#include <TTree.h>
#include <TFile.h>
#include <TEnv.h>
#include <TH1.h>
#include <iostream>

int main(){
    gEnv->SetValue("TFile.AsyncPrefetching", 1);
    gEnv->SetValue("Cache.Directory","file:cache/");

    auto treename = "Events";
    auto filename = "root://eospublic.cern.ch//eos/opendata/cms/derived-data/AOD2NanoAODOutreachTool/Run2012BC_DoubleMuParked_Muons.root";
    
    auto f = TFile::Open(filename);
    TTree* tree = static_cast<TTree*>(f->Get(treename));

    UInt_t nMuon;
    tree->SetBranchStatus("*",0);
    tree->SetBranchStatus("nMuon",1);
    tree->SetBranchAddress("nMuon",&nMuon);

    // Cluster boundaries of first cluster of the tree
    auto start = 0;
    auto end = 821695;
    
    tree->SetCacheEntryRange(start, end);

    auto h = std::make_unique<TH1I>("nMuon","nMuon",100,0,10);
    std::cout << "Starting event loop." << std::endl;
    for(auto i = start; i < end; i ++){
        tree->GetEntry(i);
        h->Fill(nMuon);
    }
    h->Print();
}









