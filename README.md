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