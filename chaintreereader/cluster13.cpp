#include <TEnv.h>
#include <TFile.h>
#include <TChain.h>
#include <TH1.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

int main(){
    gEnv->SetValue("TFile.AsyncPrefetching", 1);
    gEnv->SetValue("Cache.Directory","file:cache/");

    auto treename = "Events";
    auto filename = "root://eospublic.cern.ch//eos/opendata/cms/derived-data/AOD2NanoAODOutreachTool/Run2012BC_DoubleMuParked_Muons.root";
    
    auto  chain = std::make_shared<TChain>(treename);
    chain->Add(filename);

    // Cluster boundaries of cluster 13
    auto start = 10682035;
    auto end = 11503730;
    
    chain->SetCacheEntryRange(start, end);

    TTreeReader reader(chain.get());
    TTreeReaderValue<UInt_t> nMuon(reader, "nMuon");
    
    reader.SetEntriesRange(start,end);

    auto h = std::make_unique<TH1I>("nMuon","nMuon",100,0,10);
    
    while(reader.Next()){
        h->Fill(*nMuon);
    }
    h->Print();
}









