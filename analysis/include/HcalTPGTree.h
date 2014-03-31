//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 27 21:04:09 2014 by ROOT version 5.34/18
// from TTree HcalDataTPTree/
// found on file: data/TPG_Data_V01-00-01_0.root
//////////////////////////////////////////////////////////

#ifndef HcalTPGTree_h
#define HcalTPGTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class HcalTPGTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           ntp;
   Int_t           run;
   Int_t           event;
   Int_t           lumisection;
   Int_t           size[4176];   //[ntp]
   Int_t           ps[4176];   //[ntp]
   Int_t           ieta[4176];   //[ntp]
   Int_t           iphi[4176];   //[ntp]
   Int_t           depth[4176];   //[ntp]
   Int_t           zside[4176];   //[ntp]
   Int_t           subdet[4176];   //[ntp]
   Int_t           isHF[4176];   //[ntp]
   Int_t           isHBHE[4176];   //[ntp]
   Int_t           nconstituents[4176];   //[ntp]
   Int_t           constituent_dets[4176][10];   //[ntp]
   Int_t           constituent_ietas[4176][10];   //[ntp]
   Int_t           constituent_iphis[4176][10];   //[ntp]
   Int_t           constituent_depths[4176][10];   //[ntp]
   Int_t           SOI_FG[4176];   //[ntp]
   Int_t           SOI_cEt[4176];   //[ntp]
   Float_t         et[4176];   //[ntp]
   Int_t           sample_cEt[4176][4];   //[ntp]
   Int_t           sample_FG[4176][4];   //[ntp]
   Int_t           sample_slb[4176][4];   //[ntp]
   Int_t           sample_slbChan[4176][4];   //[ntp]
   Int_t           sample_slbAndChan[4176][4];   //[ntp]

   // List of branches
   TBranch        *b_ntp;   //!
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumisection;   //!
   TBranch        *b_size;   //!
   TBranch        *b_ps;   //!
   TBranch        *b_ieta;   //!
   TBranch        *b_iphi;   //!
   TBranch        *b_depth;   //!
   TBranch        *b_zside;   //!
   TBranch        *b_subdet;   //!
   TBranch        *b_isHF;   //!
   TBranch        *b_isHBHE;   //!
   TBranch        *b_nconstituents;   //!
   TBranch        *b_constituent_dets;   //!
   TBranch        *b_constituent_ietas;   //!
   TBranch        *b_constituent_iphis;   //!
   TBranch        *b_constituent_depths;   //!
   TBranch        *b_SOI_FG;   //!
   TBranch        *b_SOI_cEt;   //!
   TBranch        *b_et;   //!
   TBranch        *b_sample_cEt;   //!
   TBranch        *b_sample_FG;   //!
   TBranch        *b_sample_slb;   //!
   TBranch        *b_sample_slbChan;   //!
   TBranch        *b_sample_slbAndChan;   //!

   HcalTPGTree(TTree *tree=0);
   virtual ~HcalTPGTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HcalTPGTree_cxx
HcalTPGTree::HcalTPGTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("data/TPG_Data_V01-00-01_0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("data/TPG_Data_V01-00-01_0.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("data/TPG_Data_V01-00-01_0.root:/hcalRealDataTPsAnalyzer");
      dir->GetObject("HcalDataTPTree",tree);

   }
   Init(tree);
}

HcalTPGTree::~HcalTPGTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HcalTPGTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HcalTPGTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void HcalTPGTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("ntp", &ntp, &b_ntp);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumisection", &lumisection, &b_lumisection);
   fChain->SetBranchAddress("size", size, &b_size);
   fChain->SetBranchAddress("ps", ps, &b_ps);
   fChain->SetBranchAddress("ieta", ieta, &b_ieta);
   fChain->SetBranchAddress("iphi", iphi, &b_iphi);
   fChain->SetBranchAddress("depth", depth, &b_depth);
   fChain->SetBranchAddress("zside", zside, &b_zside);
   fChain->SetBranchAddress("subdet", subdet, &b_subdet);
   fChain->SetBranchAddress("isHF", isHF, &b_isHF);
   fChain->SetBranchAddress("isHBHE", isHBHE, &b_isHBHE);
   fChain->SetBranchAddress("nconstituents", nconstituents, &b_nconstituents);
   fChain->SetBranchAddress("constituent_dets", constituent_dets, &b_constituent_dets);
   fChain->SetBranchAddress("constituent_ietas", constituent_ietas, &b_constituent_ietas);
   fChain->SetBranchAddress("constituent_iphis", constituent_iphis, &b_constituent_iphis);
   fChain->SetBranchAddress("constituent_depths", constituent_depths, &b_constituent_depths);
   fChain->SetBranchAddress("SOI_FG", SOI_FG, &b_SOI_FG);
   fChain->SetBranchAddress("SOI_cEt", SOI_cEt, &b_SOI_cEt);
   fChain->SetBranchAddress("et", et, &b_et);
   fChain->SetBranchAddress("sample_cEt", sample_cEt, &b_sample_cEt);
   fChain->SetBranchAddress("sample_FG", sample_FG, &b_sample_FG);
   fChain->SetBranchAddress("sample_slb", sample_slb, &b_sample_slb);
   fChain->SetBranchAddress("sample_slbChan", sample_slbChan, &b_sample_slbChan);
   fChain->SetBranchAddress("sample_slbAndChan", sample_slbAndChan, &b_sample_slbAndChan);
   Notify();
}

Bool_t HcalTPGTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HcalTPGTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HcalTPGTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HcalTPGTree_cxx
