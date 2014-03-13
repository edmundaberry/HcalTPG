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
        'root://eoscms//eos/cms/store/data/Run2012C/MinimumBias/RAW-RECO/25Feb2013-v1/10000/F092B0CE-B27F-E211-9025-00259073E42E.root'
  )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

#------------------------------------------------------------------------------------
# GlobalTag info
#------------------------------------------------------------------------------------

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'GR_P_V41_AN2::All'

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
   fileName = cms.string("NoiseTree.root")
)

#------------------------------------------------------------------------------------
# Dump everything (for debuggin only)
#------------------------------------------------------------------------------------

process.dump = cms.OutputModule("PoolOutputModule",
   outputCommands = cms.untracked.vstring('keep *'),
   fileName = cms.untracked.string('dump.root')
)

#------------------------------------------------------------------------------------
# Define paths
#------------------------------------------------------------------------------------

process.raw2digi     = cms.Path    ( process.RawToDigi ) 
process.emulator     = cms.Path    ( process.emulDigis )
process.hcalNoiseAna = cms.Path    ( process.HBHENoiseFilterResultProducer * process.hcalNoiseAnalyzer )
process.hcalTPGAna   = cms.Path    ( process.hcalRealDataTPsAnalyzer * process.hcalEmulatedDataTPsAnalyzer )
process.DUMP         = cms.EndPath ( process.dump )

#------------------------------------------------------------------------------------
# Define schedule
#------------------------------------------------------------------------------------

process.schedule = cms.Schedule(
    process.raw2digi,
    process.emulator,
    process.hcalNoiseAna,
    process.hcalTPGAna
)

