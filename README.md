CMSSW EDM code for analyzing HCAL trigger primitives.

Supported releases:
  * CMSSW_5_3_9_patch3

Recipe:
  * scram p CMSSW CMSSW_5_3_9_patch3
  * cd CMSSW_5_3_9_patch3/src
  * git clone git@github.com:FHead/HcalNoiseAnalyzerCMS HcalNoise/HcalNoiseAnalyzer
  * git clone git@github.com:edmundaberry/HcalTPG.git HcalTPG/HcalTPGAnalyzer
  * scram b -j9

Tags:
  * V00-00-00: Initial commit for CMSSW_5_3_9_patch3
  * V00-01-00: Added HcalDetId constituent info, isHF/isHBHE info, and linear ET info.  Bug fixes.
  * V00-02-00: Added placeholder strings to python config file to make batch submission easier.
  * V00-03-00: Added filters for running on data & MC in python cfg.  Condensed to one path.
  * V01-00-00: Split data and MC to separate python cfgs.
  * V01-00-01: Bug fix: added '.root' to file name in MC python cfg.