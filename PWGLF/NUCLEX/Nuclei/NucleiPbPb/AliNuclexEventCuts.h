#ifndef _AliNuclexEventCuts_h_
#define _AliNuclexEventCuts_h_

#include <TF1.h>
#include <TList.h>
#include <TNamed.h>
#include <cmath>
#include <string>
using std::string;

#include "AliVEvent.h"
#include "AliAnalysisUtils.h"

class TList;
class TH1D;
class TH1I;
class TH2D;
class TH2F;

class AliNuclexEventCutsContainer : public TNamed {
  public:
    AliNuclexEventCutsContainer() : TNamed("AliNuclexEventCutsContainer","AliNuclexEventCutsContainer"),
    fEventId(0u),
    fMultESD(-1),
    fMultTrkFB32(-1),
    fMultTrkFB32Acc(-1),
    fMultTrkFB32TOF(-1),
    fMultTrkTPC(-1) {}

    unsigned long fEventId;
    int fMultESD;
    int fMultTrkFB32;
    int fMultTrkFB32Acc;
    int fMultTrkFB32TOF;
    int fMultTrkTPC;
  ClassDef(AliNuclexEventCutsContainer,1)
};

class AliNuclexEventCuts : public TList {
  public:
    AliNuclexEventCuts(bool savePlots = false) __attribute__ ((deprecated("Please use AliEventCuts for your analysis.")));
    virtual ~AliNuclexEventCuts() { if (fMultiplicityV0McorrCut) delete fMultiplicityV0McorrCut; }
    enum CutsBin {
      kNoCuts = 0,
      kDAQincomplete,
      kBfield,
      kTrigger,
      kVertexPosition,
      kVertexQuality,
      kPileUp,
      kMultiplicity,
      kCorrelations,
      kAllCuts
    };


    bool   AcceptEvent (AliVEvent *ev);
    bool   PassedCut (AliNuclexEventCuts::CutsBin cut) { return fFlag & BIT(cut); }
    void   AddQAplotsToList(TList *qaList = 0x0, bool addCorrelationPlots = false);
    void   OverrideAutomaticTriggerSelection(unsigned long tr, bool ov = true) { fTriggerMask = tr; fOverrideAutoTriggerMask = ov; }
    void   SetManualMode (bool man = true) { fManualMode = man; }
    void   SetupLHC11h();
    void   SetupLHC15o();
    void   SetupRun2pp();

    /// While the general philosophy here is to avoid setters and getters (this is not an API we expose)
    /// for some variables (like the max z vertex position) standard the cuts usually follow some patterns
    /// (e.g. the max vertex z position is always symmetric wrt the nominal beam collision point) thus
    /// is convenient having special setters in this case.
    float             GetCentrality (unsigned int estimator = 0) const;
    string            GetCentralityEstimator (unsigned int estimator = 0) const;
    const AliVVertex* GetPrimaryVertex() const { return fPrimaryVertex; }

    void          SetCentralityEstimators (string first = "V0M", string second = "CL0") { fCentEstimators[0] = first; fCentEstimators[1] = second; }
    void          SetCentralityRange (float min, float max) { fMinCentrality = min; fMaxCentrality = max; }
    void          SetMaxVertexZposition (float max) { fMinVtz = -fabs(max); fMaxVtz = fabs(max); }

    AliAnalysisUtils fUtils;                      ///< Analysis utils for the pileup rejection

    bool          fMC;                            ///< Set to true by the automatic setup when analysing MC (in manual mode *you* are responsible for it). In MC the correlations cuts are disabled.
    bool          fRequireTrackVertex;            ///< if true all the events with only the SPD vertex are rejected
    float         fMinVtz;                        ///< Min z position for the primary vertex
    float         fMaxVtz;                        ///< Max z position for the primary vertex
    float         fMaxDeltaSpdTrackAbsolute;      ///<
    float         fMaxDeltaSpdTrackNsigmaSPD;     ///<
    float         fMaxDeltaSpdTrackNsigmaTrack;   ///<
    float         fMaxResolutionSPDvertex;        ///<

    bool          fRejectDAQincomplete;           ///< Reject events that have incomplete information

    int           fRequiredSolenoidPolarity;      ///< 0: does not require any particular polarity. Positive numbers -> positive B field, negative numbers -> negative B field

    int           fSPDpileupMinContributors;      ///< Reject all the events with SPD pile-up vertices with more than fRejectPileupSPD contributors
    double        fSPDpileupMinZdist;             ///<
    double        fSPDpileupNsigmaZdist;          ///<
    double        fSPDpileupNsigmaDiamXY;         ///<
    double        fSPDpileupNsigmaDiamZ;          ///<
    bool          fTrackletBGcut;                 ///<

    bool          fPileUpCutMV;                   ///< Reject pile-up based on multi-vertexer

    unsigned int  fCentralityFramework;           ///< 0: skip centrality checks, 1: multiplicity framework, 2: legacy centrality framework
    float         fMinCentrality;                 ///< Minimum centrality to be analised
    float         fMaxCentrality;                 ///< Maximum centrality to be analised
    bool          fMultSelectionEvCuts;           ///< Enable/Disable the event selection applied in the AliMultSelection framework

    bool          fUseVariablesCorrelationCuts;   ///< Switch on/off the cuts on the correlation between event variables
    bool          fUseEstimatorsCorrelationCut;   ///< Switch on/off the cut on the correlation between centrality estimators
    double        fEstimatorsCorrelationCoef[2];  ///< fCentEstimators[0] = [0] + [1] * fCentEstimators[1]
    double        fEstimatorsSigmaPars[4];        ///< Sigma parametrisation fCentEstimators[1] vs fCentEstimators[0]
    double        fDeltaEstimatorNsigma[2];       ///< Number of sigma to cut on fCentEstimators[1] vs fCentEstimators[0]
    double        fTOFvsFB32correlationPars[4];   ///< Polynomial parametrisation of the correlation between FB32+TOF tracks and FB32 tracks
    double        fTOFvsFB32sigmaPars[6];         ///< Polynomial parametrisation of the rms of the correlation between FB32+TOF tracks and FB32 tracks
    double        fTOFvsFB32nSigmaCut[2];         ///< N sigma cut in the FB32+TOF vs FB32 plane
    double        fESDvsTPConlyLinearCut[2];      ///< Linear cut in the ESD track vs TPC only track plane
    TF1          *fMultiplicityV0McorrCut;        //!<! Cut on the FB128 vs V0M plane
    double        fFB128vsTrklLinearCut[2];       ///< Cut on the FB128 vs Tracklet plane

    bool          fRequireExactTriggerMask;       ///< If true the event selection mask is required to be equal to fTriggerMask
    unsigned long fTriggerMask;                   ///< Trigger mask

    AliNuclexEventCutsContainer fContainer;       //!<! Local copy of the event cuts container (safe against user changes)
    const string  fkLabels[2];                    ///< Histograms labels (raw/selected)

  private:
    void          AutomaticSetup (AliVEvent *ev);
    void          ComputeTrackMultiplicity(AliVEvent *ev);
    template<typename F> F PolN(F x, F* coef, int n);

    bool          fManualMode;                    ///< if true the cuts are not loaded automatically looking at the run number
    bool          fSavePlots;                     ///< if true the plots are automatically added to this object
    int           fCurrentRun;                    ///<
    unsigned long fFlag;                          ///< Flag of the passed cuts

    string        fCentEstimators[2];             ///< Centrality estimators: the first is used as main estimators, that is correlated with the second to monitor spurious events.
    float         fCentPercentiles[2];            ///< Centrality percentiles
    AliVVertex   *fPrimaryVertex;                 //!<! Primary vertex pointer

    ///
    bool          fNewEvent;                      ///<  True if the AliVEvent identifier in the AcceptEvent and fIdentifier are different
    /// Overrides
    bool          fOverrideAutoTriggerMask;       ///<  If true the trigger mask chosen by the user is not overridden by the Automatic Setup

    /// The following pointers are used to avoid the intense usage of FindObject. The objects pointed are owned by (TList*)this.
    TH1I* fCutStats;               //!<! Cuts statistics
    TH1D* fVtz[2];                 //!<! Vertex z distribution
    TH1D* fDeltaTrackSPDvtz[2];    //!<! Difference between the vertex computed using SPD and the track vertex
    TH1D* fCentrality[2];          //!<! Centrality percentile distribution
    TH2D* fEstimCorrelation[2];    //!<! Correlation between centrality estimators
    TH2D* fMultCentCorrelation[2]; //!<! Correlation between main centrality estimator and multiplicity

    TH2F* fTOFvsFB32[2];           //!<!
    TH2F* fTPCvsAll[2];            //!<!
    TH2F* fMultvsV0M[2];           //!<!
    TH2F* fTPCvsTrkl[2];           //!<!

    ClassDef(AliNuclexEventCuts,1)
};

template<typename F> F AliNuclexEventCuts::PolN(F x,F* coef, int n) {
  if (n < 1) ::Fatal("AliNuclexEventCuts::PolN","PolN should be used only for n>=1.");
  F ret = coef[0] + coef[1] * x;
  for (int i = 2; i <= n; ++i)
    ret += coef[i] * std::pow(x,i);
  return ret;
}

#endif

