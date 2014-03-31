#include "analysisClass.h"
#include "HcalNoiseTree.h"
#include "HcalTPGTree.h"

#include "TH1F.h"
#include "TChain.h"

#include <iostream>
#include <assert.h>  
#include <cmath>

void analysisClass::loop(){

  //--------------------------------------------------------------------------------
  // Declare HCAL trees
  //--------------------------------------------------------------------------------

  HcalTPGTree   * tpg_tree   = getTree<HcalTPGTree>  ("tps");
  HcalNoiseTree * noise_tree = getTree<HcalNoiseTree>("noise");

  //--------------------------------------------------------------------------------
  // How many events to cycle over? 
  // Is there a more elegant way to do this?
  //--------------------------------------------------------------------------------

  int n_events = noise_tree -> fChain -> GetEntries();

  //--------------------------------------------------------------------------------
  // Declare some important quantities
  //--------------------------------------------------------------------------------
  
  const int max_npv        =  50;
  const int n_trig_towers  =  64;
  const int max_trig_tower =  32;
  const int min_trig_tower = -32;
  const int abs_min_trig_tower = std::abs(min_trig_tower);

  //--------------------------------------------------------------------------------
  // Declare histograms
  //--------------------------------------------------------------------------------

  TH1F * h_sumEt_fixedIEta_fixedNPV[65][51];
  TH1F * h_sumEt_fixedIEta[65];
  float sumEt[65];

  for (int i = 0; i <= n_trig_towers; i++){
    char hist_name[100]; 
    sprintf(hist_name, "sumEt_ieta%d", i - 32 );
    h_sumEt_fixedIEta[i] = makeTH1F(hist_name,100, 0, 100 );
    for (int j = 0; j <= max_npv; ++j){
      sprintf(hist_name, "sumEt_ieta%d_npv%d", i - 32, j);
      h_sumEt_fixedIEta_fixedNPV[i][j] = makeTH1F(hist_name,100, 0, 100 );
    }
  }

  //--------------------------------------------------------------------------------
  // Loop over the events
  //--------------------------------------------------------------------------------
  
  for (int iEvent = 0; iEvent < n_events; ++iEvent){

    //--------------------------------------------------------------------------------
    // Tell the user where we are
    //--------------------------------------------------------------------------------

    if (iEvent%100 == 0) std::cout << "Processing event " << iEvent << "/" << n_events << std::endl;
    
    //--------------------------------------------------------------------------------
    // Get each entry in the event
    //--------------------------------------------------------------------------------

    tpg_tree   -> GetEntry(iEvent);
    noise_tree -> GetEntry(iEvent);

    //--------------------------------------------------------------------------------
    // Make sure the trees are in sync
    //--------------------------------------------------------------------------------

    assert ( tpg_tree -> run         == noise_tree -> RunNumber   );
    assert ( tpg_tree -> event       == noise_tree -> EventNumber );
    assert ( tpg_tree -> lumisection == noise_tree -> LumiSection );

    //--------------------------------------------------------------------------------
    // Initialize calculations (e.g. zero-out ET sums
    //--------------------------------------------------------------------------------

    for (int i = 0; i<=n_trig_towers; i++){
      sumEt[i] = 0.;
    }
    
    //--------------------------------------------------------------------------------
    // Loop over TPs to calculate sumETs
    //--------------------------------------------------------------------------------

    for (int iTP = 0; iTP < tpg_tree -> ntp; ++iTP ){
      int   ieta = tpg_tree -> ieta[iTP];
      int   iphi = tpg_tree -> iphi[iTP];
      float et   = tpg_tree -> et  [iTP];
      sumEt[ieta + abs(min_trig_tower)] += et;
    }

    //--------------------------------------------------------------------------------
    // Fill sumETs vs NPV
    //--------------------------------------------------------------------------------

    int npv = noise_tree -> NumberOfGoodPrimaryVertices;
    for (int i = 0; i<=n_trig_towers; i++){
      h_sumEt_fixedIEta[i] -> Fill(sumEt[i]);
      if ( npv <= max_npv )
	h_sumEt_fixedIEta_fixedNPV[i][npv] -> Fill(sumEt[i]);
    }
  }
}
