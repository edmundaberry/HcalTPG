#ifndef HcalTPG_HcalTPGAnalyzer_HcalTPGTree_h
#define HcalTPG_HcalTPGAnalyzer_HcalTPGTree_h

class HcalTPGTree {
  
 public:
  
  // Constructor / destructor

  HcalTPGTree();
  virtual ~HcalTPGTree();

  // Array sizing info

  enum {MAXNTP           = 10000};
  enum {MAXNCONSTITUENTS = 12   };
  enum {MAXNSAMPLES      = 4    };
  
  int ntp;

  // Run/Event/LS info

  int run;
  int event;
  int lumisection;

  // General info
    
  int size              [MAXNTP];
  int ps                [MAXNTP];
  		        
  // Detector ID info   
  		        
  int ieta              [MAXNTP];
  int iphi              [MAXNTP];
  int depth             [MAXNTP];
  int zside             [MAXNTP];
  int subdet            [MAXNTP];
  int isHF              [MAXNTP];
  int isHBHE            [MAXNTP];

  // Sample of interest info
  
  int SOIfg             [MAXNTP];
  int SOIcEt            [MAXNTP];
		        
  // Energy info        
		        
  float et              [MAXNTP];

  // Constituent HcalDetId info

  int nconstituents     [MAXNTP];
  int constituent_ietas [MAXNTP][MAXNCONSTITUENTS];
  int constituent_iphis [MAXNTP][MAXNCONSTITUENTS];
  int constituent_depths[MAXNTP][MAXNCONSTITUENTS];
  int constituent_dets  [MAXNTP][MAXNCONSTITUENTS];

  // Other samples info
  
  int sample_cEt        [MAXNTP][MAXNSAMPLES];
  int sample_fg         [MAXNTP][MAXNSAMPLES];
  int sample_slb        [MAXNTP][MAXNSAMPLES];
  int sample_slbChan    [MAXNTP][MAXNSAMPLES];
  int sample_slbAndChan [MAXNTP][MAXNSAMPLES];
  
};

#endif
