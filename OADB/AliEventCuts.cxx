#include "AliEventCuts.h"

#include <algorithm>
#include <array>
using std::array;
#include <memory>
#include <vector>
using std::vector;

#include <TClonesArray.h>
#include <TH1D.h>
#include <TH1I.h>
#include <TH2D.h>
#include <TH2F.h>

#include <AliAnalysisManager.h>
#include <AliAODMCParticle.h>
#include <AliCentrality.h>
#include <AliESDtrackCuts.h>
#include <AliInputEventHandler.h>
#include <AliMCEventHandler.h>
#include <AliMultSelection.h>
#include <AliVEventHandler.h>
#include <AliVMultiplicity.h>

#include <AliAODEvent.h>
#include <AliESDEvent.h>

ClassImp(AliEventCutsContainer);
ClassImp(AliEventCuts);



/// Standard constructor with null selection
///
AliEventCuts::AliEventCuts(bool saveplots) : TList(),
  fUtils{},
  fMC{false},
  fRequireTrackVertex{false},
  fMinVtz{-1000.f},
  fMaxVtz{1000.f},
  fMaxDeltaSpdTrackAbsolute{1000.f},
  fMaxDeltaSpdTrackNsigmaSPD{1000.f},
  fMaxDeltaSpdTrackNsigmaTrack{20000.f},
  fMaxResolutionSPDvertex{1000.f},
  fRejectDAQincomplete{false},
  fRequiredSolenoidPolarity{0},
  fSPDpileupMinContributors{1000},
  fSPDpileupMinZdist{-1.f},
  fSPDpileupNsigmaZdist{-1.f},
  fSPDpileupNsigmaDiamXY{-1.f},
  fSPDpileupNsigmaDiamZ{-1.f},
  fTrackletBGcut{false},
  fPileUpCutMV{false},
  fCentralityFramework{0},
  fMinCentrality{-1000.f},
  fMaxCentrality{1000.f},
  fUseVariablesCorrelationCuts{false},
  fUseEstimatorsCorrelationCut{false},
  fEstimatorsCorrelationCoef{0.,1.},
  fEstimatorsSigmaPars{10000.,0.,0.,0.},
  fDeltaEstimatorNsigma{1.,1.},
  fTOFvsFB32correlationPars{0.},
  fTOFvsFB32sigmaPars{1.e8,0.,0.,0.,0.,0.},
  fTOFvsFB32nSigmaCut{1.,1.},
  fESDvsTPConlyLinearCut{1.e8,0.},
  fMultiplicityV0McorrCut{nullptr},
  fFB128vsTrklLinearCut{1.e8,0.},
  fRequireExactTriggerMask{false},
  fTriggerMask{AliVEvent::kAny},
  fContainer{},
  fkLabels{"raw","selected"},
  fManualMode{false},
  fSavePlots{saveplots},
  fCurrentRun{-1},
  fFlag{BIT(kNoCuts)},
  fCentEstimators{"V0M","CL0"},
  fCentPercentiles{-1.f},
  fPrimaryVertex{nullptr},
  fNewEvent{true},
  fOverrideAutoTriggerMask{false},
  fCutStats{nullptr},
  fVtz{nullptr},
  fDeltaTrackSPDvtz{nullptr},
  fCentrality{nullptr},
  fEstimCorrelation{nullptr},
  fMultCentCorrelation{nullptr},
  fTOFvsFB32{nullptr},
  fTPCvsAll{nullptr},
  fMultvsV0M{nullptr},
  fTPCvsTrkl{nullptr}
{
  SetName("AliEventCuts");
  SetOwner(true);
}

bool AliEventCuts::AcceptEvent(AliVEvent *ev) {
  /// If not specified the cuts are set according to the run period
  const int current_run = ev->GetRunNumber();
  if (!fManualMode && current_run != fCurrentRun) {
    ::Info("AliEventCuts::AcceptEvent","Current run (%i) is different from the previous (%i): setting automatically the corresponding event cuts.",current_run,fCurrentRun);
    fCurrentRun = current_run;
    AutomaticSetup(ev);
  }

  if (fSavePlots && !this->Last()) {
    AddQAplotsToList();
  }

  /// Event selection flag, as soon as the event does not pass one cut this becomes false.
  fFlag = BIT(kNoCuts);

  /// Rejection of the DAQ incomplete events
  if (!fRejectDAQincomplete || !ev->IsIncompleteDAQ()) fFlag |= BIT(kDAQincomplete);

  /// Magnetic field selection
  float bField = ev->GetMagneticField();
  if (fRequiredSolenoidPolarity == 0 || fRequiredSolenoidPolarity * bField > 0.) fFlag |= BIT(kBfield);

  /// Trigger mask
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  AliInputEventHandler* handl = (AliInputEventHandler*)mgr->GetInputEventHandler();
  auto selected_trigger = handl->IsEventSelected() & fTriggerMask;
  if ((selected_trigger == fTriggerMask && fRequireExactTriggerMask) || (selected_trigger && !fRequireExactTriggerMask))
    fFlag |= BIT(kTrigger);

  /// Vertex selection
  const AliVVertex* vtTrc = ev->GetPrimaryVertex();
  const AliVVertex* vtSPD = ev->GetPrimaryVertexSPD();
  const AliVVertex* &vtx = (vtTrc->GetNContributors() < 2) ? vtSPD : vtTrc;
  double covTrc[6],covSPD[6];
  vtTrc->GetCovarianceMatrix(covTrc);
  vtSPD->GetCovarianceMatrix(covSPD);
  double dz = vtTrc->GetZ() - vtSPD->GetZ();
  double errTot = TMath::Sqrt(covTrc[5]+covSPD[5]);
  double errTrc = TMath::Sqrt(covTrc[5]);
  double nsigTot = TMath::Abs(dz) / errTot, nsigTrc = TMath::Abs(dz) / errTrc;

  /// Vertex position cut
  if (vtx->GetZ() >= fMinVtz && vtx->GetZ() <= fMaxVtz) fFlag |= BIT(kVertexPosition);

  /// Vertex quality cuts
  if (((vtTrc->GetNContributors() >= 2 ||  !fRequireTrackVertex) && vtSPD->GetNContributors() >= 1) && // Check if SPD vertex is there and (if required) check if Track vertex is present.
      (TMath::Abs(dz) <= fMaxDeltaSpdTrackAbsolute && nsigTot <= fMaxDeltaSpdTrackNsigmaSPD && nsigTrc <= fMaxDeltaSpdTrackNsigmaTrack) && // discrepancy track-SPD vertex
      (!vtSPD->IsFromVertexerZ() || TMath::Sqrt(covSPD[5]) <= fMaxResolutionSPDvertex)
     ) // quality cut on vertexer SPD z
    fFlag |= BIT(kVertexQuality);
  fPrimaryVertex = const_cast<AliVVertex*>(vtx);

  /// SPD pile-up rejection
  if (!ev->IsPileupFromSPD(fSPDpileupMinContributors,fSPDpileupMinZdist,fSPDpileupNsigmaZdist,fSPDpileupNsigmaDiamXY,fSPDpileupNsigmaDiamZ) &&
      (!fTrackletBGcut || !fUtils.IsSPDClusterVsTrackletBG(ev)) &&
      (!fPileUpCutMV || !fUtils.IsPileUpMV(ev)))
    fFlag |= BIT(kPileUp);

  /// Centrality cuts:
  /// * Check for min and max centrality
  /// * Cross check correlation between two centrality estimators
  AliVMultiplicity* mult = ev->GetMultiplicity();
  const int ntrkl = mult->GetNumberOfTracklets();
  if (fCentralityFramework) {
    if (fCentralityFramework == 2) {
      AliCentrality* cent = ev->GetCentrality();
      fCentPercentiles[0] = cent->GetCentralityPercentile(fCentEstimators[0].data());
      fCentPercentiles[1] = cent->GetCentralityPercentile(fCentEstimators[1].data());
    } else {
      AliMultSelection* cent = (AliMultSelection*)ev->FindListObject("MultSelection");
      fCentPercentiles[0] = cent->GetMultiplicityPercentile(fCentEstimators[0].data(), true);
      fCentPercentiles[1] = cent->GetMultiplicityPercentile(fCentEstimators[1].data(), true);
    }
    const auto& x = fCentPercentiles[1];
    const double center = x * fEstimatorsCorrelationCoef[1] + fEstimatorsCorrelationCoef[0];
    const double sigma = fEstimatorsSigmaPars[0] + fEstimatorsSigmaPars[1] * x + fEstimatorsSigmaPars[2] * x * x + fEstimatorsSigmaPars[3] * x * x * x;
    if ((!fUseEstimatorsCorrelationCut || fMC ||
          (fCentPercentiles[0] >= center - fDeltaEstimatorNsigma[0] * sigma && fCentPercentiles[0] <= center + fDeltaEstimatorNsigma[1] * sigma))
        && fCentPercentiles[0] >= fMinCentrality
        && fCentPercentiles[0] <= fMaxCentrality) fFlag |= BIT(kMultiplicity);
  } else fFlag |= BIT(kMultiplicity);

  if (fUseVariablesCorrelationCuts && !fMC) {
    ComputeTrackMultiplicity(ev);
    const double fb32 = fContainer.fMultTrkFB32;
    const double fb32acc = fContainer.fMultTrkFB32Acc;
    const double fb32tof = fContainer.fMultTrkFB32TOF;
    const double fb128 = fContainer.fMultTrkTPC;
    const double esd = fContainer.fMultESD;
    const double mu32tof = PolN(fb32,fTOFvsFB32correlationPars,3);
    const double sigma32tof = PolN(fb32,fTOFvsFB32sigmaPars, 5);
    const bool multV0Mcut = (fMultiplicityV0McorrCut) ? fb32acc > fMultiplicityV0McorrCut->Eval(fCentPercentiles[0]) : true;
    if ((fb32tof <= mu32tof + fTOFvsFB32nSigmaCut[0] * sigma32tof && fb32tof >= mu32tof - fTOFvsFB32nSigmaCut[1] * sigma32tof) &&
        (esd < fESDvsTPConlyLinearCut[0] + fESDvsTPConlyLinearCut[1] * fb128) &&
        multV0Mcut &&
        (fb128 < fFB128vsTrklLinearCut[0] + fFB128vsTrklLinearCut[1] * ntrkl))
      fFlag |= BIT(kCorrelations);
  } else fFlag |= BIT(kCorrelations);

  bool allcuts = (fFlag == (BIT(kAllCuts) - 1));
  if (allcuts) fFlag |= BIT(kAllCuts);
  if (fCutStats) {
    for (int iCut = kNoCuts; iCut <= kAllCuts; ++iCut) {
      if (TESTBIT(fFlag,iCut))
        fCutStats->Fill(iCut);
    }
  }


  /// Filling the monitoring histograms (first iteration always filled, second iteration only for selected events.
  for (int befaft = 0; befaft < 2; ++befaft) {
    if (fCentrality[befaft]) fCentrality[befaft]->Fill(fCentPercentiles[0]);
    if (fEstimCorrelation[befaft]) fEstimCorrelation[befaft]->Fill(fCentPercentiles[1],fCentPercentiles[0]);
    if (fMultCentCorrelation[befaft]) fMultCentCorrelation[befaft]->Fill(fCentPercentiles[0],ntrkl);
    if (fVtz[befaft]) fVtz[befaft]->Fill(vtx->GetZ());
    if (fDeltaTrackSPDvtz[befaft]) fDeltaTrackSPDvtz[befaft]->Fill(dz);
    if (fTOFvsFB32[befaft]) fTOFvsFB32[befaft]->Fill(fContainer.fMultTrkFB32,fContainer.fMultTrkFB32TOF);
    if (fTPCvsAll[befaft])  fTPCvsAll[befaft]->Fill(fContainer.fMultTrkTPC,float(fContainer.fMultESD) - fESDvsTPConlyLinearCut[1] * fContainer.fMultTrkTPC);
    if (fMultvsV0M[befaft]) fMultvsV0M[befaft]->Fill(GetCentrality(),fContainer.fMultTrkFB32Acc);
    if (fTPCvsTrkl[befaft]) fTPCvsTrkl[befaft]->Fill(ntrkl,fContainer.fMultTrkTPC);
    if (!allcuts) return false; /// Do not fill the "after" histograms if the event does not pass the cuts.
  }

  return true;
}

void AliEventCuts::AddQAplotsToList(TList *qaList, bool addCorrelationPlots) {
  if (!qaList) {
    if (fSavePlots)
      qaList = static_cast<TList*>(this);
    else
      ::Fatal("AliEventCuts::AddQAplotsToList","Invalid TList pointer provided");
  }
  static_cast<TList*>(this)->Delete();

  vector<string> bin_labels = {"No cuts","DAQ Incomplete","Magnetic field choice","Trigger selection","Vertex position","Vertex quality","Pile-up","Centrality selection","Correlations","All cuts"};
  fCutStats = new TH1I("fCutStats",";;Number of selected events",bin_labels.size(),-.5,bin_labels.size() - 0.5);
  for (int iB = 1; iB <= bin_labels.size(); ++iB) fCutStats->GetXaxis()->SetBinLabel(iB,bin_labels[iB-1].data());
  qaList->Add(fCutStats);

  string titles[2] = {"before event cuts","after event cuts"};
  for (int iS = 0; iS < 2; ++iS) {
    fVtz[iS] = new TH1D(Form("Vtz_%s",fkLabels[iS].data()),Form("Vertex z %s; #it{v_{z}} (cm); Events",titles[iS].data()),400,-20.,20.);
    fDeltaTrackSPDvtz[iS] = new TH1D(Form("DeltaVtz_%s",fkLabels[iS].data()),Form("Vertex tracks - Vertex SPD %s; #Delta#it{v_{z}} (cm); Events",titles[iS].data()),400,-2.,2.);
    fCentrality[iS] = new TH1D(Form("Centrality_%s",fkLabels[iS].data()),Form("Centrality percentile %s; Centrality (%%); Events",titles[iS].data()),100,0.,100.);
    fEstimCorrelation[iS] = new TH2D(Form("EstimCorrelation_%s",fkLabels[iS].data()),Form("Correlation estimators %s;%s;%s",titles[iS].data(),fCentEstimators[1].data(),fCentEstimators[0].data()),100,0.,100.,100,0.,100.);
    fMultCentCorrelation[iS] = new TH2D(Form("MultCentCorrelation_%s",fkLabels[iS].data()),Form("Correlation multiplicity-centrality %s;Percentile of %s; Number of tracklets",titles[iS].data(),fCentEstimators[0].data()),100,0.,100.,2000,0.,10000.);

    qaList->Add(fVtz[iS]);
    qaList->Add(fDeltaTrackSPDvtz[iS]);
    qaList->Add(fCentrality[iS]);
    qaList->Add(fEstimCorrelation[iS]);
    qaList->Add(fMultCentCorrelation[iS]);

    if (addCorrelationPlots) {
      fTOFvsFB32[iS] = new TH2F(Form("fTOFvsFB32_%s",fkLabels[iS].data()),Form("%s;Multiplicity FB32;Multiplicity FB32+TOF",titles[iS].data()),500,0.,3000.,500,0.,2000.);
      fTPCvsAll[iS] = new TH2F(Form("fTPCvsAll_%s",fkLabels[iS].data()),Form("%s;Multiplicity TPC;Multiplicity ESD - a_{0} #times Multiplicity TPC",titles[iS].data()),300,0.,3000.,3000,-200.,28800.);
      fMultvsV0M[iS] = new TH2F(Form("fMultvsV0M_%s",fkLabels[iS].data()),Form("%s;Centrality (V0M);FB32",titles[iS].data()),100,0.,100.,500,0.,3000.);
      fTPCvsTrkl[iS] = new TH2F(Form("fTPCvsTrkl_%s",fkLabels[iS].data()),Form("%s;SPD tracklets;FB128",titles[iS].data()),2500,0.,5000.,2500,0.,5000.);
      qaList->Add(fTOFvsFB32[iS]);
      qaList->Add(fTPCvsAll[iS]);
      qaList->Add(fMultvsV0M[iS]);
      qaList->Add(fTPCvsTrkl[iS]);
    }
  }

}

void AliEventCuts::AutomaticSetup(AliVEvent *ev) {
  if (dynamic_cast<AliAODEvent*>(ev)) {
    TClonesArray *stack = (TClonesArray*)ev->GetList()->FindObject(AliAODMCParticle::StdBranchName());
    fMC = (stack) ? true : false;
  } else if (!dynamic_cast<AliESDEvent*>(ev))
    AliFatal("I don't find the AOD event nor the ESD one, aborting.");
  else {
    AliMCEventHandler* eventHandler = dynamic_cast<AliMCEventHandler*> (AliAnalysisManager::GetAnalysisManager()->GetMCtruthEventHandler());
    fMC = (eventHandler) ? true : false;
  }

  if (fCurrentRun >= 166423 && fCurrentRun <= 170593) {
    SetupLHC11h();
    return;
  }

  if ((fCurrentRun >= 225000 && fCurrentRun <= 244628) ||
      (fCurrentRun >= 256146 && fCurrentRun <= 260187)) {
    SetupRun2pp();
    return;
  }

  /// Run 2 Pb-Pb
  if ( fCurrentRun >= 244917 && fCurrentRun <= 256145 ) {
    SetupLHC15o();
    return;
  }

  ::Fatal("AliEventCuts::AutomaticSetup","Automatic period detection failed, please use the manual mode. If you need this period in AliEventCuts send an email to the DPG event selection mailing list.");
}

float AliEventCuts::GetCentrality (unsigned int estimator) const {
  if (estimator > 1) {
    /// Escalate to Fatal
    ::Fatal("AliEventCuts::GetCentrality","You asked for the centrality estimator with index %i, but you should choose between index 0 and 1.", estimator);
    return -1.f;
  } else
    return fCentPercentiles[estimator];
}

string AliEventCuts::GetCentralityEstimator (unsigned int estimator) const {
  if (estimator > 1) {
    /// Escalate to Fatal
    ::Fatal("AliEventCuts::GetCentralityEstimator","You asked for the centrality estimator with index %i, but you should choose between index 0 and 1.", estimator);
    return "";
  } else
    return fCentEstimators[estimator];
}


void AliEventCuts::ComputeTrackMultiplicity(AliVEvent *ev) {
  AliEventCutsContainer* tmp_cont = static_cast<AliEventCutsContainer*>(ev->FindListObject("AliEventCutsContainer"));
  if (tmp_cont) {
    unsigned long evid = ((unsigned long)(ev->GetBunchCrossNumber()) << 32) + ev->GetTimeStamp();
    fNewEvent = (tmp_cont->fEventId != evid);
    tmp_cont->fEventId = evid;
    //if (fNewEvent) ::Info("AliEventCuts::AcceptEvent","New event. %Lu", evid);
    //else ::Info("AliEventCuts::AcceptEvent","Old event. %Lu", evid);

    if (!fNewEvent) {
      fContainer = *tmp_cont;
      return;
    }
  } else tmp_cont = new AliEventCutsContainer;

  bool isAOD = false;
  if (dynamic_cast<AliAODEvent*>(ev))
    isAOD = true;
  else if (!dynamic_cast<AliESDEvent*>(ev))
    AliFatal("I don't find the AOD event nor the ESD one, aborting.");

  std::unique_ptr<AliESDtrackCuts> FB32cuts{AliESDtrackCuts::GetStandardITSTPCTrackCuts2011()};
  std::unique_ptr<AliESDtrackCuts> TPConlyCuts{AliESDtrackCuts::GetStandardTPCOnlyTrackCuts()};

  const int nTracks = ev->GetNumberOfTracks();
  tmp_cont->fMultESD = (isAOD) ? ((AliAODHeader*)ev->GetHeader())->GetNumberOfESDTracks() : dynamic_cast<AliESDEvent*>(ev)->GetNumberOfTracks();
  tmp_cont->fMultTrkFB32 = 0;
  tmp_cont->fMultTrkFB32Acc = 0;
  tmp_cont->fMultTrkFB32TOF = 0;
  tmp_cont->fMultTrkTPC = 0;
  for (int it = 0; it < nTracks; it++) {
    if (isAOD) {
      AliAODTrack* trk = (AliAODTrack*)ev->GetTrack(it);
      if (!trk) continue;
      if (trk->TestFilterBit(32)) {
        tmp_cont->fMultTrkFB32++;
        if ( TMath::Abs(trk->GetTOFsignalDz()) <= 10. && trk->GetTOFsignal() >= 12000. && trk->GetTOFsignal() <= 25000.)
          tmp_cont->fMultTrkFB32TOF++;
        if ((fabs(trk->Eta()) < 0.8) && (trk->GetTPCNcls() >= 70) && (trk->Pt() >= 0.2) && (trk->Pt() < 50))
          tmp_cont->fMultTrkFB32Acc++;
      }
      if (trk->TestFilterBit(128))
        tmp_cont->fMultTrkTPC++;
    } else {
      AliESDtrack* esdTrack = (AliESDtrack*)ev->GetTrack(it);
      if (!esdTrack) continue;

      if (FB32cuts->AcceptTrack(esdTrack)) {
        tmp_cont->fMultTrkFB32++;
        if (TMath::Abs(esdTrack->GetTOFsignalDz()) <= 10 && esdTrack->GetTOFsignal() >= 12000 && esdTrack->GetTOFsignal() <= 25000)
          tmp_cont->fMultTrkFB32TOF++;

        if ((TMath::Abs(esdTrack->Eta()) < 0.8) && (esdTrack->GetTPCNcls() > 70) && (esdTrack->Pt() > 0.2) && (esdTrack->Pt() < 50))
          tmp_cont->fMultTrkFB32Acc++;
      }

      /// TPC only tracks, with the same cuts of the filter bit 128
      AliESDtrack tpcParam;
      if (!esdTrack->FillTPCOnlyTrack(tpcParam)) continue;
      if (!TPConlyCuts->AcceptTrack(&tpcParam)) continue;
      if (tpcParam.Pt() > 0.) {
        // only constrain tracks above threshold
        AliExternalTrackParam exParam;
        // take the B-field from the ESD, no 3D fieldMap available at this point
        bool relate = false;
        relate = tpcParam.RelateToVertexTPC((AliESDVertex*)ev->GetPrimaryVertexSPD(),ev->GetMagneticField(),kVeryBig, &exParam);
        if(!relate) continue;
      }
      tmp_cont->fMultTrkTPC++;
    }
  }
  ev->AddObject(tmp_cont);
  fContainer = *tmp_cont;
}

void AliEventCuts::SetupRun2pp() {
  ::Info("AliEventCuts::SetupRun2pp","Setup event cuts for the Run2 pp periods.");
  SetName("StandardRun2ppEventCuts");

  fRequireTrackVertex = true;
  fMinVtz = -10.f;
  fMaxVtz = 10.f;
  fMaxDeltaSpdTrackAbsolute = 0.5f;
  fMaxDeltaSpdTrackNsigmaSPD = 2000.f;
  fMaxDeltaSpdTrackNsigmaTrack = 2000.f;
  fMaxResolutionSPDvertex = 0.25f;

  fRejectDAQincomplete = true;

  fRequiredSolenoidPolarity = 0;

  fSPDpileupMinContributors = 3;
  fSPDpileupMinZdist = 0.8;
  fSPDpileupNsigmaZdist = 3.;
  fSPDpileupNsigmaDiamXY = 2.;
  fSPDpileupNsigmaDiamZ = 5.;
  fTrackletBGcut = true;

  if (fCentralityFramework > 1)
    ::Fatal("AliEventCutsSetupRun2pp","You cannot use the legacy centrality framework in pp. Please set the fCentralityFramework to 0 to disable the multiplicity selection or to 1 to use AliMultSelection.");
  fCentEstimators[0] = "V0M";
  fCentEstimators[1] = "CL0";
  fMinCentrality = 0.f;
  fMaxCentrality = 100.f;

  fFB128vsTrklLinearCut[0] = 32.077;
  fFB128vsTrklLinearCut[1] = 0.932;

  if (!fOverrideAutoTriggerMask) fTriggerMask = AliVEvent::kINT7;

  fUtils.SetMinPlpContribMV(5);
  fUtils.SetMaxPlpChi2MV(5);
  fUtils.SetMinWDistMV(15);
  fUtils.SetCheckPlpFromDifferentBCMV(kFALSE);
}

void AliEventCuts::SetupLHC15o() {
  ::Info("AliEventCuts::SetupLHC15o","Setup event cuts for the LHC15o period.");
  SetName("StandardLHC15oEventCuts");

  fRequireTrackVertex = true;
  fMinVtz = -10.f;
  fMaxVtz = 10.f;
  fMaxDeltaSpdTrackAbsolute = 0.2f;
  fMaxDeltaSpdTrackNsigmaSPD = 10.f;
  fMaxDeltaSpdTrackNsigmaTrack = 20.f;
  fMaxResolutionSPDvertex = 0.25f;

  fRejectDAQincomplete = true;

  fRequiredSolenoidPolarity = 0;

  fSPDpileupMinContributors = 5;
  fSPDpileupMinZdist = 0.8;
  fSPDpileupNsigmaZdist = 3.;
  fSPDpileupNsigmaDiamXY = 2.;
  fSPDpileupNsigmaDiamZ = 5.;
  fTrackletBGcut = false;

  fCentralityFramework = 1;
  fCentEstimators[0] = "V0M";
  fCentEstimators[1] = "CL0";
  fMinCentrality = 0.f;
  fMaxCentrality = 90.f;

  fUseEstimatorsCorrelationCut = true;
  fEstimatorsCorrelationCoef[0] = 0.0157497;
  fEstimatorsCorrelationCoef[1] = 0.973488;
  fEstimatorsSigmaPars[0] = 0.673612;
  fEstimatorsSigmaPars[1] = 0.0290718;
  fEstimatorsSigmaPars[2] = -0.000546728;
  fEstimatorsSigmaPars[3] = 5.82749e-06;
  fDeltaEstimatorNsigma[0] = 5.;
  fDeltaEstimatorNsigma[1] = 5.5;

  array<double,4> tof_fb32_corr = {-1.0178, 0.333132, 9.10282e-05, -1.61861e-08};
  std::copy(tof_fb32_corr.begin(),tof_fb32_corr.end(),fTOFvsFB32correlationPars);
  array<double,6> tof_fb32_sigma = {1.47848, 0.0385923, -5.06153e-05, 4.37641e-08, -1.69082e-11, 2.35085e-15};
  std::copy(tof_fb32_sigma.begin(),tof_fb32_sigma.end(),fTOFvsFB32sigmaPars);
  fTOFvsFB32nSigmaCut[0] = 4.;
  fTOFvsFB32nSigmaCut[1] = 4.;

  fESDvsTPConlyLinearCut[0] = 15000.;
  fESDvsTPConlyLinearCut[1] = 3.38;

  if(!fMultiplicityV0McorrCut) fMultiplicityV0McorrCut = new TF1("fMultiplicityV0McorrCut","[0]+[1]*x+[2]*exp([3]-[4]*x) - 5.*([5]+[6]*exp([7]-[8]*x))",0,100);
  fMultiplicityV0McorrCut->SetParameters(-6.15980e+02, 4.89828e+00, 4.84776e+03, -5.22988e-01, 3.04363e-02, -1.21144e+01, 2.95321e+02, -9.20062e-01, 2.17372e-02);

  if (!fOverrideAutoTriggerMask) fTriggerMask = AliVEvent::kINT7;

}

void AliEventCuts::SetupLHC11h() {
  fRequireTrackVertex = true;
  fMinVtz = -10.f;
  fMaxVtz = 10.f;

  fCentralityFramework = 2;
  fCentEstimators[0] = "V0M";
  fCentEstimators[1] = "CL0";
  fMinCentrality = 0.f;
  fMaxCentrality = 90.f;

  fUseEstimatorsCorrelationCut = false;

  if (!fOverrideAutoTriggerMask) fTriggerMask = AliVEvent::kMB | AliVEvent::kCentral | AliVEvent::kSemiCentral;
}
