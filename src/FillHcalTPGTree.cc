#include "HcalTPG/HcalTPGAnalyzer/interface/FillHcalTPGTree.h"

// Constructor and destructor

FillHcalTPGTree::FillHcalTPGTree(){}
FillHcalTPGTree::~FillHcalTPGTree(){}

// Initializing the tree

void FillHcalTPGTree::init(std::string treeName, HcalTPGTree* treePtr){

  // Save the ptr

  m_treePtr = treePtr;

  // Initialize the tree

  m_tree = m_file_service -> make<TTree>(treeName.c_str(), "");
  
  // Set memory address for array sizing info

  m_tree -> Branch("ntp"               , &(m_treePtr -> ntp               ), "ntp/I"                        );
									  				    
  // Set memory address for Run/Event/LS info				  				    
									  				    
  m_tree -> Branch("run"               , &(m_treePtr -> run               ), "run/I"                        );
  m_tree -> Branch("event"             , &(m_treePtr -> event             ), "event/I"                      );
  m_tree -> Branch("lumisection"       , &(m_treePtr -> lumisection       ), "lumisection/I"                );
  									  				    
  // Set memory address for general info				  				    
  									  				    
  m_tree -> Branch("size"              , &(m_treePtr -> size              ), "size[ntp]/I"                  );
  m_tree -> Branch("ps"                , &(m_treePtr -> ps                ), "ps[ntp]/I"                    );
			              				          			            
  // Set memory address for detector ID info				  				    
  									  				    
  m_tree -> Branch("ieta"              , &(m_treePtr -> ieta              ), "ieta[ntp]/I"                  );
  m_tree -> Branch("iphi"              , &(m_treePtr -> iphi              ), "iphi[ntp]/I"                  );
  m_tree -> Branch("depth"             , &(m_treePtr -> depth             ), "depth[ntp]/I"                 );
  m_tree -> Branch("zside"             , &(m_treePtr -> zside             ), "zside[ntp]/I"                 );
  m_tree -> Branch("subdet"            , &(m_treePtr -> subdet            ), "subdet[ntp]/I"                );
  m_tree -> Branch("isHF"              , &(m_treePtr -> isHF              ), "isHF[ntp]/I"                  );
  m_tree -> Branch("isHBHE"            , &(m_treePtr -> isHBHE            ), "isHBHE[ntp]/I"                );

  // Set memory address for HcalDetId constituent info
  
  m_tree -> Branch("nconstituents"     , &(m_treePtr -> nconstituents     ), "nconstituents[ntp]/I"         );
  m_tree -> Branch("constituent_dets"  , &(m_treePtr -> constituent_dets  ), "constituent_dets[ntp][10]/I"  );
  m_tree -> Branch("constituent_ietas" , &(m_treePtr -> constituent_ietas ), "constituent_ietas[ntp][10]/I" );
  m_tree -> Branch("constituent_iphis" , &(m_treePtr -> constituent_iphis ), "constituent_iphis[ntp][10]/I" );
  m_tree -> Branch("constituent_depths", &(m_treePtr -> constituent_depths), "constituent_depths[ntp][10]/I");
			              				        			         
  // Set memory address for sample of interest info

  m_tree -> Branch("SOI_FG"            , &(m_treePtr -> SOIfg             ), "SOI_FG[ntp]/I"                );
  m_tree -> Branch("SOI_cEt"           , &(m_treePtr -> SOIcEt            ), "SOI_cEt[ntp]/I"               );
									  				    
  // Set memory address for energy info					  				    
  									  				    
  m_tree -> Branch("et"                , &(m_treePtr -> et                ), "et[ntp]/F"                    );
									  				    
  // Set memory address for other samples info				  				    
  									  				    
  m_tree -> Branch("sample_cEt"        , &(m_treePtr -> sample_cEt        ), "sample_cEt[ntp][4]/I"         );
  m_tree -> Branch("sample_FG"         , &(m_treePtr -> sample_fg         ), "sample_FG[ntp][4]/I"          );
  m_tree -> Branch("sample_slb"        , &(m_treePtr -> sample_slb        ), "sample_slb[ntp][4]/I"         );
  m_tree -> Branch("sample_slbChan"    , &(m_treePtr -> sample_slbChan    ), "sample_slbChan[ntp][4]/I"     );
  m_tree -> Branch("sample_slbAndChan" , &(m_treePtr -> sample_slbAndChan ), "sample_slbAndChan[ntp][4]/I"  );
  
}

// Fill the tree

void FillHcalTPGTree::fill(){
  m_tree -> Fill();
}
