#include "HcalTPG/HcalTPGAnalyzer/interface/HcalTPGAnalyzer.h"

void HcalTPGAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  // Get trigger primitives using handle/label

  edm::Handle<HcalTrigPrimDigiCollection> tps;
  iEvent.getByLabel(m_source, tps);

  // Define iterators

  HcalTrigPrimDigiCollection::const_iterator tp     = tps -> begin();
  HcalTrigPrimDigiCollection::const_iterator tp_end = tps -> end();
  
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

    // Sample of interest info

    m_hcalTPGTree.SOIfg [ntp] = (int) (*tp).SOI_fineGrain();
    m_hcalTPGTree.SOIcEt[ntp] = (int) (*tp).SOI_compressedEt();

    // Other samples info

    for (int isample = 0; isample < m_hcalTPGTree.size[ntp]; ++isample){
      m_hcalTPGTree.sample_cEt       [ntp][isample] = (int) (*tp).sample(isample).compressedEt ();
      m_hcalTPGTree.sample_fg        [ntp][isample] = (int) (*tp).sample(isample).fineGrain    ();
      m_hcalTPGTree.sample_slb       [ntp][isample] = (int) (*tp).sample(isample).slb          ();
      m_hcalTPGTree.sample_slbChan   [ntp][isample] = (int) (*tp).sample(isample).slbChan      ();
      m_hcalTPGTree.sample_slbAndChan[ntp][isample] = (int) (*tp).sample(isample).slbAndChan   ();
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
