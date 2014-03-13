#ifndef HcalTPG_HcalTPGAnalyzer_FillHcalTPGTree_h
#define HcalTPG_HcalTPGAnalyzer_FillHcalTPGTree_h

#include "HcalTPG/HcalTPGAnalyzer/interface/HcalTPGTree.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TTree.h"
#include "TDirectory.h"
#include "TROOT.h"

#include <string>

class FillHcalTPGTree {
  
 public:

  // Constructor / destructor

  FillHcalTPGTree();
  virtual ~FillHcalTPGTree();
  
  // Tree manipulation

  void init(std::string treeName, HcalTPGTree* treePtr);
  void fill();
  HcalTPGTree* getTreePtr();

 private:

  // Member data

  HcalTPGTree * m_treePtr;
  TTree * m_tree;
  edm::Service<TFileService> m_file_service;

};

#endif
