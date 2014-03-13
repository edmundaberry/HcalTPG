import FWCore.ParameterSet.Config as cms

hcalNoiseAnalyzer = cms.EDAnalyzer("HcalNoiseAnalyzer",
   HBHERecHitCollection = cms.untracked.string('hbhereco')
)
