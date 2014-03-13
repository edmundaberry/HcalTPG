// CMSSW include files

#include "CalibFormats/CaloTPG/interface/CaloTPGTranscoder.h"
#include "CalibFormats/CaloTPG/interface/CaloTPGRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

// Package include files

#include "HcalTPG/HcalTPGAnalyzer/interface/HcalTPGAnalyzer.h"

void HcalTPGAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  // Get trigger primitives using handle/label

  edm::Handle<HcalTrigPrimDigiCollection> tps;
  iEvent.getByLabel(m_source, tps);

  // Define iterators

  HcalTrigPrimDigiCollection::const_iterator tp     = tps -> begin();
  HcalTrigPrimDigiCollection::const_iterator tp_end = tps -> end();
  
  // Define transcoder for linearizing TP energies

  edm::ESHandle<CaloTPGTranscoder> transcoder;
  iSetup.get<CaloTPGRecord>().get(transcoder);
  transcoder->setup(iSetup, CaloTPGTranscoder::HcalTPG);
  
  // Loop over trigger primitives

  int ntp = 0;

  for (; tp != tp_end; ++tp){
    
    // General info
    
    m_hcalTPGTree.size  [ntp] = (int) tp -> size();
    m_hcalTPGTree.ps    [ntp] = (int) tp -> presamples();

    // Detector ID info

    m_hcalTPGTree.ieta  [ntp] = (int) (*tp).id().ieta  ();
    m_hcalTPGTree.iphi  [ntp] = (int) (*tp).id().iphi  ();
    m_hcalTPGTree.depth [ntp] = (int) (*tp).id().depth ();
    m_hcalTPGTree.zside [ntp] = (int) (*tp).id().zside ();
    m_hcalTPGTree.subdet[ntp] = (int) (*tp).id().subdet();
    m_hcalTPGTree.isHF  [ntp] = ((*tp).id().ietaAbs() >= m_trig_tower_geometry.firstHFTower()) ? 1 : 0;
    m_hcalTPGTree.isHBHE[ntp] = ((*tp).id().ietaAbs()  < m_trig_tower_geometry.firstHFTower()) ? 1 : 0;

    // Sample of interest info

    m_hcalTPGTree.SOIfg [ntp] = (int) (*tp).SOI_fineGrain();
    m_hcalTPGTree.SOIcEt[ntp] = (int) (*tp).SOI_compressedEt();

    // Energy info
    
    m_hcalTPGTree.et    [ntp] = (float) transcoder->hcaletValue(m_hcalTPGTree.ieta  [ntp],
								m_hcalTPGTree.iphi  [ntp],
								m_hcalTPGTree.SOIcEt[ntp]);
    
    // Other samples info

    for (int isample = 0; isample < m_hcalTPGTree.size[ntp]; ++isample){
      m_hcalTPGTree.sample_cEt       [ntp][isample] = (int) (*tp).sample(isample).compressedEt ();
      m_hcalTPGTree.sample_fg        [ntp][isample] = (int) (*tp).sample(isample).fineGrain    ();
      m_hcalTPGTree.sample_slb       [ntp][isample] = (int) (*tp).sample(isample).slb          ();
      m_hcalTPGTree.sample_slbChan   [ntp][isample] = (int) (*tp).sample(isample).slbChan      ();
      m_hcalTPGTree.sample_slbAndChan[ntp][isample] = (int) (*tp).sample(isample).slbAndChan   ();
    }

    // Find constituent HcalDetIds

    std::vector<HcalDetId> constituents = m_trig_tower_geometry.detIds ((*tp).id());
    std::vector<HcalDetId>::iterator constituent     = constituents.begin();
    std::vector<HcalDetId>::iterator constituent_end = constituents.end();

    // Fill constituents info

    m_hcalTPGTree.nconstituents[ntp] = 0;
    
    for (; constituent != constituent_end; ++constituent){
      m_hcalTPGTree.constituent_ietas [ntp][m_hcalTPGTree.nconstituents[ntp]] = (int) constituent -> ieta  ();
      m_hcalTPGTree.constituent_iphis [ntp][m_hcalTPGTree.nconstituents[ntp]] = (int) constituent -> iphi  ();
      m_hcalTPGTree.constituent_depths[ntp][m_hcalTPGTree.nconstituents[ntp]] = (int) constituent -> depth ();
      m_hcalTPGTree.constituent_dets  [ntp][m_hcalTPGTree.nconstituents[ntp]] = (int) constituent -> subdet();
      ++m_hcalTPGTree.nconstituents[ntp];
    }

    // Count number of TPs
    
    ++ntp;
  }

  // Fill flat variables
  
  m_hcalTPGTree.ntp         = (int) ntp;
  m_hcalTPGTree.run         = (int) iEvent.id().run();
  m_hcalTPGTree.event       = (int) iEvent.id().event();
  m_hcalTPGTree.lumisection = (int) iEvent.luminosityBlock();

  // Fill the tree
  m_fillTree.fill();
}


// Constructor and destructor

HcalTPGAnalyzer::~HcalTPGAnalyzer(){}
HcalTPGAnalyzer::HcalTPGAnalyzer(const edm::ParameterSet& iConfig):
  m_source  (iConfig.getParameter<edm::InputTag>("source"  )),
  m_treename(iConfig.getParameter<std::string>  ("treename"))
{
  m_fillTree.init(m_treename, &m_hcalTPGTree);
}

// Begin job and end job

void HcalTPGAnalyzer::beginJob(){}
void HcalTPGAnalyzer::endJob(){}

DEFINE_FWK_MODULE(HcalTPGAnalyzer);
