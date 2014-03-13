#ifndef HcalTPG_HcalTPGAnalyzer_HcalTPGAnalyzer_h
#define HcalTPG_HcalTPGAnalyzer_HcalTPGAnalyzer_h

// system include files

#include <memory>
#include <string>

// CMSSW include files

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"

// ROOT include files

#include "TTree.h"
#include "TFile.h"

// Package include files

#include "HcalTPG/HcalTPGAnalyzer/interface/HcalTPGTree.h"
#include "HcalTPG/HcalTPGAnalyzer/interface/FillHcalTPGTree.h"

class HcalTPGAnalyzer : public edm::EDAnalyzer {
public:

  // Constructor and destructor

  explicit HcalTPGAnalyzer(const edm::ParameterSet&);
  ~HcalTPGAnalyzer();
  
private:
  
  // Private functions

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  // Member data

  edm::InputTag   m_source;
  std::string     m_treename;
  TTree *         m_tree;
  FillHcalTPGTree m_fillTree;
  HcalTPGTree     m_hcalTPGTree;

};

#endif
