/**************************************************************************
 * Copyright(c) 1998-2016, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/
#include <functional>
#include <iostream>
#include <vector>

#include "AliAODTrack.h"
#include "AliESDtrackCuts.h"
#include "AliEmcalTrackSelection.h"
#include "AliEmcalTrackSelectionESD.h"
#include "AliEmcalTrackSelectionAOD.h"
#include "AliEmcalTriggerOfflineSelection.h"
#include "AliEMCalTriggerExtraCuts.h"

#include "AliEmcalAnalysisFactory.h"

/// \cond CLASSIMP
ClassImp(EMCalTriggerPtAnalysis::AliEmcalAnalysisFactory)
/// \endcond
///
namespace EMCalTriggerPtAnalysis {

AliEmcalTrackSelection *AliEmcalAnalysisFactory::TrackCutsFactory(TString cut, Bool_t aod){
  AliEmcalTrackSelection *result = NULL;
  if(!aod){
    std::vector<AliVCuts *> trackcuts;
    if(cut.Contains("standard")){
      AliESDtrackCuts *esdcuts = AliESDtrackCuts::GetStandardITSTPCTrackCuts2011(true, 1);
      esdcuts->DefineHistograms(kRed);
      esdcuts->SetName("Standard Track cuts");
      esdcuts->SetMinNCrossedRowsTPC(120);
      esdcuts->SetMaxDCAToVertexXYPtDep("0.0182+0.0350/pt^1.01");
      trackcuts.push_back(esdcuts);
    }
    if(cut.Contains("hybrid")){
      AliESDtrackCuts *esdcuts = AliESDtrackCuts::GetStandardITSTPCTrackCuts2011(kFALSE);
      esdcuts->SetName("Global Hybrid tracks, loose DCA");
      esdcuts->SetMaxDCAToVertexXY(2.4);
      esdcuts->SetMaxDCAToVertexZ(3.2);
      esdcuts->SetDCAToVertex2D(kTRUE);
      esdcuts->SetMaxChi2TPCConstrainedGlobal(36);
      esdcuts->SetMaxFractionSharedTPCClusters(0.4);
      trackcuts.push_back(esdcuts);
    }
    if(cut.Contains("ITSchi2")){
      // Definition: ITSchi2XXXX
      // - 3 Digits before . (to be filled with 0)
      // - 1 Digit after .
      int strmin = cut.Index("ITSchi2") + 7;
      int cutvalue = TString(cut(strmin , strmin+4)).Atoi();
      float itscut = static_cast<float>(cutvalue)/10.;

      std::cout << "Using ITS chi2 cut variation: " << itscut << std::endl;

      AliESDtrackCuts *esdcuts = AliESDtrackCuts::GetStandardITSTPCTrackCuts2011(false, 1);
      esdcuts->DefineHistograms(kRed);
      esdcuts->SetName("Standard Track cuts");
      esdcuts->SetMinNCrossedRowsTPC(120);
      esdcuts->SetMaxDCAToVertexXY(2.4);
      esdcuts->SetMaxDCAToVertexZ(3.2);
      esdcuts->SetDCAToVertex2D(kTRUE);
      esdcuts->SetMaxChi2PerClusterITS(itscut);
      // Set cut on the TPC global constrained chi2 to very loose
      esdcuts->SetMaxChi2TPCConstrainedGlobal(100);
    }
    if(cut.Contains("TPCchi2Constrained")){
      // Definition: TPCchi2ConstrainedXXXX
      // - 3 Digits before . (to be filled with 0)
      // - 1 Digit after .
      int strmin = cut.Index("TPCchi2Constrained") + 18;
      int cutvalue = TString(cut(strmin , strmin+4)).Atoi();
      float tpcconstrainedcut = static_cast<float>(cutvalue) / 10.;

      std::cout << "Using TOC chi2 constrained cut variation: " << tpcconstrainedcut << std::endl;

      AliESDtrackCuts *esdcuts = AliESDtrackCuts::GetStandardITSTPCTrackCuts2011(false, 1);
      esdcuts->DefineHistograms(kRed);
      esdcuts->SetName("Standard Track cuts");
      esdcuts->SetMinNCrossedRowsTPC(120);
      esdcuts->SetMaxDCAToVertexXY(2.4);
      esdcuts->SetMaxDCAToVertexZ(3.2);
      esdcuts->SetDCAToVertex2D(kTRUE);
      esdcuts->SetMaxChi2TPCConstrainedGlobal(tpcconstrainedcut);
      // Set ITS chi2 cut to very loose
      esdcuts->SetMaxChi2PerClusterITS(100);
    }
    if(cut.Contains("geo")){
      AliEMCalTriggerExtraCuts *geocuts = new AliEMCalTriggerExtraCuts();
      geocuts->SetMinTPCTrackLengthCut();
      trackcuts.push_back(geocuts);
    }
    result = new AliEmcalTrackSelectionESD;
    for(std::vector<AliVCuts *>::iterator it = trackcuts.begin(); it != trackcuts.end(); ++it)
      result->AddTrackCuts(*it);
  } else {
    AliEmcalTrackSelectionAOD *aodsel = new AliEmcalTrackSelectionAOD;
    result = aodsel;
    std::vector<AliVCuts *> trackcuts;
    // C++11 Lambda: Do not create multiple extra cut objects in case of AODs. If extra cut object does already exist -
    // specify new cut in the same object.
    std::function<AliEMCalTriggerExtraCuts *(const std::vector<AliVCuts *> &)> FindTrackCuts = [] (const std::vector<AliVCuts *> &cuts) -> AliEMCalTriggerExtraCuts * {
      AliEMCalTriggerExtraCuts *found = nullptr;
      for(std::vector<AliVCuts *>::const_iterator cutiter = cuts.begin(); cutiter != cuts.end(); ++cutiter){
        if((*cutiter)->IsA() == AliEMCalTriggerExtraCuts::Class()){
          found = static_cast<AliEMCalTriggerExtraCuts *>(*cutiter);
          break;
        }
      }
      return found;
    };
    if(cut.Contains("standard")){
      aodsel->AddFilterBit(AliAODTrack::kTrkGlobal);
      AliEMCalTriggerExtraCuts *extracuts = FindTrackCuts(trackcuts);
      if(!extracuts){
        extracuts = new AliEMCalTriggerExtraCuts;
        trackcuts.push_back(extracuts);
      }
      extracuts->SetMinTPCCrossedRows(120);
    }
    if(cut.Contains("hybrid")){
      aodsel->AddFilterBit(256);
      aodsel->AddFilterBit(512);
    }
    if(cut.Contains("geo")){
      AliEMCalTriggerExtraCuts *extracuts = FindTrackCuts(trackcuts);
      if(!extracuts){
        extracuts = new AliEMCalTriggerExtraCuts;
        trackcuts.push_back(extracuts);
      }
      extracuts->SetMinTPCTrackLengthCut();
    }
    for(std::vector<AliVCuts *>::iterator it = trackcuts.begin(); it != trackcuts.end(); ++it)
      result->AddTrackCuts(*it);
  }

  return result;
}

AliEmcalTriggerOfflineSelection *AliEmcalAnalysisFactory::TriggerSelectionFactory(Double_t el0, Double_t eg1, Double_t eg2, Double_t ej1, Double_t ej2, AliEmcalTriggerOfflineSelection::EmcalEnergyDefinition_t endef){
  AliEmcalTriggerOfflineSelection *result = new AliEmcalTriggerOfflineSelection;
  result->SetOfflineEnergyThreshold(AliEmcalTriggerOfflineSelection::kTrgEL0, el0);
  result->SetOfflineEnergyThreshold(AliEmcalTriggerOfflineSelection::kTrgEG1, eg1);
  result->SetOfflineEnergyThreshold(AliEmcalTriggerOfflineSelection::kTrgEG2, eg2);
  result->SetOfflineEnergyThreshold(AliEmcalTriggerOfflineSelection::kTrgEJ1, ej1);
  result->SetOfflineEnergyThreshold(AliEmcalTriggerOfflineSelection::kTrgEJ2, ej2);
  result->SetEnergyDefinition(endef);
  return result;
}

TString AliEmcalAnalysisFactory::ClusterContainerNameFactory(Bool_t isAOD){
  return isAOD ? "caloClusters" : "CaloClusters";
}

} /* namespace EMCalTriggerPtAnalysis */
