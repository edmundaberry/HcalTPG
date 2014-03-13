import FWCore.ParameterSet.Config as cms

hcalRealDataTPsAnalyzer = cms.EDAnalyzer('HcalTPGAnalyzer',
  source = cms.InputTag('hcalDigis'),
  prefix = cms.string ('Data'),
  treename = cms.string('HcalDataTPTree')                                    
)

hcalEmulatedDataTPsAnalyzer = cms.EDAnalyzer('HcalTPGAnalyzer',
  source = cms.InputTag('emulDigis'),
  prefix = cms.string ('Emul'),
  treename = cms.string ('HcalEmulTPTree')
)

hcalMonteCarloTPsAnalyzer = cms.EDAnalyzer('HcalTPGAnalyzer',
  source = cms.InputTag('simHcalTriggerPrimitiveDigis'),
  prefix = cms.string('MC'),
  treename = cms.string('HcalMCTPTree')
)
