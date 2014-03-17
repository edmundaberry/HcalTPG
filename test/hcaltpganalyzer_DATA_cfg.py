#------------------------------------------------------------------------------------
# Preamble
#------------------------------------------------------------------------------------

import FWCore.ParameterSet.Config as cms
process = cms.Process('ANA')

#------------------------------------------------------------------------------------
# Import of standard configurations
#------------------------------------------------------------------------------------

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

#------------------------------------------------------------------------------------
# Input information
#------------------------------------------------------------------------------------

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
        #FILENAMES
  )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

#------------------------------------------------------------------------------------
# GlobalTag info
# 
# This can be used for running on data:
# process.GlobalTag.globaltag = 'GR_P_V41_AN2::All'
# 
# This can be used for running on MC:
# process.GlobalTag.globaltag = 'START53_V7N::All'
#------------------------------------------------------------------------------------

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'GLOBALTAG::All'

#------------------------------------------------------------------------------------
# HCAL noise module(s)
#------------------------------------------------------------------------------------

process.load("HcalTPG.HcalTPGAnalyzer.hcalNoiseProducer_cfi")
process.load("HcalTPG.HcalTPGAnalyzer.hcalNoiseAnalyzer_cfi")

#------------------------------------------------------------------------------------
# Run the emulator
#------------------------------------------------------------------------------------

process.load('SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff')
process.emulDigis = process.simHcalTriggerPrimitiveDigis.clone()
process.emulDigis.inputLabel = cms.VInputTag('hcalDigis', 'hcalDigis')

#------------------------------------------------------------------------------------
# HCAL TPG module(s)
#------------------------------------------------------------------------------------

process.load("HcalTPG.HcalTPGAnalyzer.hcalTPGAnalyzer_cfi")

#------------------------------------------------------------------------------------
# TFile service
#------------------------------------------------------------------------------------

process.TFileService = cms.Service("TFileService",
   fileName = cms.string("OUTPUTFILENAME.root")
)

#------------------------------------------------------------------------------------
# Filters
#------------------------------------------------------------------------------------

# HLT high level filter
process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')

# Scraping filter
process.load("HcalTPG.HcalTPGAnalyzer.hcalFilters_cfi")

# HBHE noise filter
process.load('CommonTools.RecoAlgos.HBHENoiseFilter_cfi') 

# ECAL noise filter
process.load('RecoMET.METFilters.eeBadScFilter_cfi') 

#------------------------------------------------------------------------------------
# Zero bias
#------------------------------------------------------------------------------------

import HLTrigger.HLTfilters.triggerResultsFilter_cfi as hlt 

process.ZeroBiasAve = hlt.triggerResultsFilter.clone() 
process.ZeroBiasAve.triggerConditions = cms.vstring('HLT_ZeroBias*',) 
process.ZeroBiasAve.hltResults = cms.InputTag( "TriggerResults", "", "HLT" ) 
process.ZeroBiasAve.l1tResults = cms.InputTag("") 
process.ZeroBiasAve.throw = cms.bool( False ) 
process.zerobias = cms.Path(process.ZeroBiasAve) 

process.load('HLTrigger.HLTfilters.hltHighLevel_cfi') 
process.hltHighLevel.HLTPaths = cms.vstring("HLT_ZeroBias_v*") 

#------------------------------------------------------------------------------------
# Dump everything (for debugging only)
#------------------------------------------------------------------------------------

process.dump = cms.OutputModule("PoolOutputModule",
   outputCommands = cms.untracked.vstring('keep *'),
   fileName = cms.untracked.string('dump.root')
)

#------------------------------------------------------------------------------------
# Define paths
#------------------------------------------------------------------------------------

process.analysis = cms.Path (
    # Filters
    process.hltHighLevel *    
    process.noscraping *      
    process.HBHENoiseFilter * 
    process.eeBadScFilter *   
    # Raw-to-digi
    process.RawToDigi *
    # Run the emulator (for data only)
    process.emulDigis *
    # Produce the HBHE noise results and analyze them
    process.HBHENoiseFilterResultProducer * 
    process.hcalNoiseAnalyzer * 
    # Analyze the trigger primitives
    process.hcalRealDataTPsAnalyzer *   
    process.hcalEmulatedDataTPsAnalyzer 
)

process.DUMP  = cms.EndPath ( process.dump )

#------------------------------------------------------------------------------------
# Define schedule
#------------------------------------------------------------------------------------

process.schedule = cms.Schedule(
    process.analysis
)

