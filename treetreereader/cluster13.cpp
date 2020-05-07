#include <TEnv.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

int main(){
    gEnv->SetValue("TFile.AsyncPrefetching", 1);
    gEnv->SetValue("Cache.Directory","file:cache/");

    auto treename = "Events";
    auto filename = "root://eospublic.cern.ch//eos/opendata/cms/derived-data/AOD2NanoAODOutreachTool/Run2012BC_DoubleMuParked_Muons.root";
    
    auto f = TFile::Open(filename);
    auto tree = f->Get<TTree>(treename);

    // Cluster boundaries of cluster 13
    auto start = 10682035;
    auto end = 11503730;

    TTreeReader reader(tree);
    TTreeReaderValue<UInt_t> nMuon(reader, "nMuon");
    
    reader.SetEntriesRange(start,end);  // RDF never calls SetEntriesRange

    auto h = std::make_unique<TH1I>("nMuon","nMuon",100,0,10);

    std::cout << "Starting the while loop" << std::endl;
    while(reader.Next()){
        // This mimics the internal behaviour of RDF
        // auto curentry = reader.GetCurrentEntry();
        // if (curentry < start) continue;
        // if (curentry == end) break;
        h->Fill(*nMuon);
    }
    h->Print();
}









