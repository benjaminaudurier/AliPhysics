/// \class AliAnalysisTaskDmesonJets
/// \brief Analysis task for D meson jets
///
/// This task selects D meson candidates according to predefined cuts,
/// then runs a jet finder to reconstruct the jets that contain
/// the D meson candidates.
///
/// The main output is stored in a THnSparse histogram or in a TTree.
///
/// \author Salvatore Aiola <salvatore.aiola@cern.ch>, Yale University
/// \date Feb 6, 2016

#ifndef ALIANALYSISTASKDMESONJETS_H
#define ALIANALYSISTASKDMESONJETS_H

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

class TClonesArray;
class AliRDHFCuts;
class AliAODEvent;
class AliAODRecoDecay;
class AliAODRecoDecayHF2Prong;
class AliAODRecoCascadeHF;
class AliVParticle;
class AliAODMCParticle;
class AliHFAODMCParticleContainer;
class AliHFTrackContainer;
class AliParticleContainer;
class AliClusterContainer;
class THnSparse;
class AliFJWrapper;
class THashList;
class TTree;
class AliEMCALGeometry;
class TRandom;

#include <list>
#include <vector>
#include <map>

#include "AliTLorentzVector.h"
#include "THistManager.h"

#include "AliAnalysisTaskEmcalLight.h"
#include "AliJetContainer.h"

class AliAnalysisTaskDmesonJets : public AliAnalysisTaskEmcalLight
{
 public:

  typedef AliJetContainer::EJetType_t EJetType_t;
  typedef AliJetContainer::EJetAlgo_t EJetAlgo_t;
  typedef AliJetContainer::ERecoScheme_t ERecoScheme_t;

  enum EOutputType_t { kNoOutput, kTreeOutput, kTHnOutput };
  enum ECandidateType_t  { kD0toKpi, kDstartoKpipi, kD0toKpiLikeSign };
  enum EMCMode_t { kNoMC, kSignalOnly, kBackgroundOnly, kMCTruth, kWrongPID };
  enum EMesonOrigin_t {
    kUnknownQuark = BIT(0),
    kFromDown     = BIT(1),
    kFromUp       = BIT(2),
    kFromStrange  = BIT(3),
    kFromCharm    = BIT(4),
    kFromBottom   = BIT(5),
    kFromTop      = BIT(6),
    kFromGluon    = BIT(7),
    kAnyOrigin    = kUnknownQuark | kFromDown | kFromUp | kFromStrange | kFromCharm | kFromBottom | kFromTop | kFromGluon
  };

  enum EMesonDecayChannel_t {
    kAnyDecay            = 0,
    kUnknownDecay        = BIT(0),
    kDecayD0toKpi        = BIT(1),
    kDecayDStartoKpipi   = BIT(2)
  };

  enum EAxis_t {
   kPositionD         = BIT(0) , // Add the D meson eta/phi axis in the THnSparse
   kInvMass           = BIT(1) , // Add the invariant mass axis in the THnSparse
   k2ProngInvMass     = BIT(2) , // Add the 2 prong invariant mass axis in the THnSparse (for D* this is the inv mass of the D0)
   kSoftPionPt        = BIT(3) , // Add the soft pion pt axis in the THnSparse (for D*)
   kDeltaR            = BIT(4) , // Add the delta R axis in the THnSparse
   kDeltaEta          = BIT(5) , // Add the delta eta axis in the THnSparse
   kDeltaPhi          = BIT(6) , // Add the delta phi axis in the THnSparse
   kPositionJet       = BIT(7) , // Add the jet eta/phi axis in the THnSparse
   kJetConstituents   = BIT(8)   // Add the jet constituent axis in the THnSparse
  };

  /// \class AliJetInfo
  /// \brief Class that encapsulates jets
  ///
  /// This class encapsulates jet
  /// information that can be easily passed to a function.
  class AliJetInfo {
  public:
    AliJetInfo() : fMomentum(), fNConstituents(0), fNEF(0), fMaxChargedPt(0), fMaxNeutralPt(0) {}
    AliJetInfo(Double_t px, Double_t py, Double_t pz, Double_t E, Int_t nconst, Double_t nef, Double_t cpt, Double_t npt) :
      fMomentum(px, py, pz, E), fNConstituents(nconst), fNEF(nef), fMaxChargedPt(cpt), fMaxNeutralPt(npt) {}

    virtual ~AliJetInfo() {;}

    Double_t Pt()        const { return fMomentum.Pt()       ; }
    Double_t Eta()       const { return fMomentum.Eta()      ; }
    Double_t Phi()       const { return fMomentum.Phi()      ; }
    Double_t Phi_0_2pi() const { return fMomentum.Phi_0_2pi(); }
    Int_t GetNConstituents() const { return  fNConstituents; }
    Double_t GetDistance(const AliJetInfo& jet, Double_t& deta, Double_t& dphi) const;
    Double_t GetDistance(const AliJetInfo& jet) const;

    AliTLorentzVector fMomentum             ; ///< 4-momentum of the jet
    Int_t             fNConstituents        ; ///< Number of constituents of the jet
    Double_t          fNEF                  ; ///< Neutral Energy Fraction of the jet
    Double_t          fMaxChargedPt         ; ///< Transverse momentum of the leading charged particle (or track)
    Double_t          fMaxNeutralPt         ; ///< Transverse momentum of the leading neutral particle (or cluster)

    /// \cond CLASSIMP
    ClassDef(AliJetInfo, 1);
    /// \endcond
  };

  /// \class AliEmcalDmesonJetInfo
  /// \brief Class that encapsulates D meson jets
  ///
  /// This class encapsulates D meson jet
  /// information that can be easily passed to a function.
  class AliDmesonJetInfo {
  public:
    AliDmesonJetInfo();
    AliDmesonJetInfo(const AliDmesonJetInfo &source);
    AliDmesonJetInfo& operator=(const AliDmesonJetInfo& source);
    virtual ~AliDmesonJetInfo() {;}

    AliVParticle      *fDmesonParticle          ; //!<! pointer to the particle object
    AliTLorentzVector  fD                       ; //!<! 4-momentum of the D meson candidate
    Double_t           fSoftPionPt              ; //!<! Transverse momentum of the soft pion of the D* candidate
    Double_t           fInvMass2Prong           ; //!<! 2-prong mass of the D* candidate (w/o the soft pion)
    std::map<std::string, AliJetInfo>
                       fJets                    ; //!<! list of jets
    Int_t              fMCLabel                 ; //!<! MC label, i.e. index of the generator level D meson (only for detector level D meson candidates)
    Bool_t             fReconstructed           ; //!<! Whether this D meson was reconstructed (only for particle level D mesons)
    AliAODMCParticle  *fFirstParton             ; //!<! pointer to the first parton in the shower tree of the D meson (only for particle level D mesons)
    Short_t            fFirstPartonType         ; //!<! type of the first parton in the shower tree (only for particle level D mesons)
    AliAODMCParticle  *fLastParton              ; //!<! pointer to the last parton in the shower tree of the D meson (only for particle level D mesons)
    Short_t            fLastPartonType          ; //!<! type of the last parton in the shower tree (only for particle level D mesons)
    Byte_t             fSelectionType           ; //!<! for D0: 0=not selected, 1=D0, 2=D0bar, 3=both

    const AliJetInfo* GetJet(std::string n) const;
    AliJetInfo* GetJet(std::string n);
    void Reset();
    Double_t GetZ(std::string n) const;
    Double_t GetDistance(std::string n, Double_t& deta, Double_t& dphi) const;
    Double_t GetDistance(std::string n) const;
    Double_t GetDistance(const AliJetInfo& jet, Double_t& deta, Double_t& dphi) const;
    Double_t GetDistance(const AliJetInfo& jet) const;
    void Print() const;

    /// \cond CLASSIMP
    ClassDef(AliDmesonJetInfo, 1);
    /// \endcond
  };

  /// \class AliJetInfoSummary
  /// \brief Lightweight class that encapsulates D meson jets
  ///
  /// This class encapsulates D meson jet
  /// information in a very compact data structure (55 bits)
  class AliJetInfoSummary {
  public:
    AliJetInfoSummary() : fPt(0), fEta(0), fPhi(0), fR(0), fZ(0), fN(0) {;}
    AliJetInfoSummary(const AliDmesonJetInfo& source, std::string n);
    virtual ~AliJetInfoSummary() {}

    virtual void Reset();
    virtual void Set(const AliDmesonJetInfo& source, std::string n);
    virtual void Set(const AliJetInfo& source);

    /// Transverse momentum of the jet in GeV/c
    Double32_t  fPt        ; //[0,409.6,13]
    /// Eta of the jet
    Double32_t  fEta       ; //[-2.048,2.048,10]
    /// Phi of the jet
    Double32_t  fPhi       ; //[0,2*pi,10]
    /// Distance between D meson and jet axis
    Double32_t  fR         ; //[0,2.56,7]
    /// Z of the D meson
    Double32_t  fZ         ; //[0,1.024,10]
    /// Number of jet constituents
    Double32_t  fN         ; //[0, 64, 6]

    /// \cond CLASSIMP
    ClassDef(AliJetInfoSummary, 4);
    /// \endcond
  };

  /// \class AliDmesonInfoSummary
  /// \brief Lightweight class that encapsulates D meson jets
  ///
  /// This class encapsulates D meson
  /// information in a very compact data structure (32 bits)
  class AliDmesonInfoSummary {
  public:
    AliDmesonInfoSummary() : fPt(0), fEta(0), fPhi(0) {;}
    AliDmesonInfoSummary(const AliDmesonJetInfo& source);
    virtual ~AliDmesonInfoSummary() {}

    virtual void Reset();
    virtual void Set(const AliDmesonJetInfo& source);

    /// Transverse momentum of the D meson in GeV/c
    Double32_t   fPt     ; //[0,204.8,12]
    /// Eta of the D meson
    Double32_t   fEta    ; //[-2.048,2.048,10]
    /// Phi of the D meson
    Double32_t   fPhi    ; //[0,2*pi,10]

    /// \cond CLASSIMP
    ClassDef(AliDmesonInfoSummary, 2);
    /// \endcond
  };

  /// \class AliDmesonInfoSummary
  /// \brief Lightweight class that encapsulates D meson jets
  ///
  /// This class encapsulates D meson
  /// information in a very compact data structure (68 bits)
  class AliDmesonMCInfoSummary : public AliDmesonInfoSummary {
  public:
    AliDmesonMCInfoSummary() : AliDmesonInfoSummary(), fFirstPartonType(0), fFirstPartonPt(0), fLastPartonType(0), fLastPartonPt(0) {;}
    AliDmesonMCInfoSummary(const AliDmesonJetInfo& source);
    virtual ~AliDmesonMCInfoSummary() {}

    virtual void Reset();
    virtual void Set(const AliDmesonJetInfo& source);

    /// First parton type
    Double32_t   fFirstPartonType  ; //[0, 16, 4]
    /// Transverse momentum of the first parton
    Double32_t   fFirstPartonPt    ; //[0,819.2,14]
    /// Last parton type
    Double32_t   fLastPartonType   ; //[0, 16, 4]
    /// Transverse momentum of the last parton
    Double32_t   fLastPartonPt     ; //[0,819.2,14]

    /// \cond CLASSIMP
    ClassDef(AliDmesonMCInfoSummary, 2);
    /// \endcond
  };

  /// \class AliD0InfoSummary
  /// \brief Lightweight class that encapsulates D0
  ///
  /// This class encapsulates D0 jet
  /// information in a very compact data structure (50 bits)
  class AliD0InfoSummary : public AliDmesonInfoSummary {
  public:
    AliD0InfoSummary() : AliDmesonInfoSummary(), fInvMass(0), fSelectionType(0) {}
    AliD0InfoSummary(const AliDmesonJetInfo& source);
    virtual ~AliD0InfoSummary() {}

    virtual void Reset();
    virtual void Set(const AliDmesonJetInfo& source);

    /// Invariant mass of the D0 meson candidate in GeV/c2
    Double32_t          fInvMass        ; //[0,6.5536,16]
    Double32_t          fSelectionType  ; //[0,4,2]

    /// \cond CLASSIMP
    ClassDef(AliD0InfoSummary, 3);
    /// \endcond
  };

  /// \class AliDStarInfoSummary
  /// \brief Lightweight class that encapsulates D*
  ///
  /// This class encapsulates D*
  /// information in a very compact data structure (62 bits)
  class AliDStarInfoSummary : public AliDmesonInfoSummary {
  public:
    AliDStarInfoSummary() : AliDmesonInfoSummary(), f2ProngInvMass(0), fDeltaInvMass(0) {}
    AliDStarInfoSummary(const AliDmesonJetInfo& source);
    virtual ~AliDStarInfoSummary() {}

    virtual void Reset();
    virtual void Set(const AliDmesonJetInfo& source);

    ///< Invariant mass of the D0 meson candidate in GeV/c2
    Double32_t   f2ProngInvMass   ; //[0,8.192,14]
    ///< Difference between the Kpipi and the Kpi invariant masses in GeV/c2
    Double32_t   fDeltaInvMass    ; //[0,0.8192,16]

    /// \cond CLASSIMP
    ClassDef(AliDStarInfoSummary, 2);
    /// \endcond
  };

  class AliHFJetDefinition : public TObject {
  public:
    AliHFJetDefinition();
    AliHFJetDefinition(EJetType_t type, Double_t r, EJetAlgo_t algo, ERecoScheme_t reco);
    AliHFJetDefinition(const AliHFJetDefinition &source);

    AliHFJetDefinition& operator=(const AliHFJetDefinition& source);

    const char* GetName() const;

    void SetJetPhiRange(Double_t min, Double_t max)       { fMinJetPhi    = min; fMaxJetPhi    = max; }
    void SetJetEtaRange(Double_t min, Double_t max)       { fMinJetEta    = min; fMaxJetEta    = max; }
    void SetJetPtRange(Double_t min, Double_t max)        { fMinJetPt     = min; fMaxJetPt     = max; }
    void SetChargedPtRange(Double_t min, Double_t max)    { fMinChargedPt = min; fMaxChargedPt = max; }
    void SetNeutralPtRange(Double_t min, Double_t max)    { fMinNeutralPt = min; fMaxNeutralPt = max; }
    Double_t GetRadius() const { return fRadius; }

    Bool_t IsJetInAcceptance(const AliJetInfo& jet) const;
    Bool_t IsJetInAcceptance(const AliDmesonJetInfo& dMesonJet, std::string n) const;

    friend bool        operator< (const AliHFJetDefinition& lhs, const AliHFJetDefinition& rhs);
    friend inline bool operator> (const AliHFJetDefinition& lhs, const AliHFJetDefinition& rhs){ return rhs < lhs    ; }
    friend inline bool operator<=(const AliHFJetDefinition& lhs, const AliHFJetDefinition& rhs){ return !(lhs > rhs) ; }
    friend inline bool operator>=(const AliHFJetDefinition& lhs, const AliHFJetDefinition& rhs){ return !(lhs < rhs) ; }

    friend bool        operator==(const AliHFJetDefinition& lhs, const AliHFJetDefinition& rhs);
    friend inline bool operator!=(const AliHFJetDefinition& lhs, const AliHFJetDefinition& rhs){ return !(lhs == rhs); }

  protected:
    friend class AliAnalysisTaskDmesonJets;
    friend class AnalysisEngine;

    EJetType_t                fJetType       ; ///<  Jet type (charged, full, neutral)
    Double_t                  fRadius        ; ///<  Jet radius
    EJetAlgo_t                fJetAlgo       ; ///<  Jet algorithm (kt, anti-kt,...)
    ERecoScheme_t             fRecoScheme    ; ///<  Jet recombination scheme (pt scheme, E scheme, ...)
    Double_t                  fMinJetPt      ; ///<  Minimum jet pT
    Double_t                  fMaxJetPt      ; ///<  Maximum jet pT
    Double_t                  fMinJetPhi     ; ///<  Minimum jet phi
    Double_t                  fMaxJetPhi     ; ///<  Maximum jet phi
    Double_t                  fMinJetEta     ; ///<  Minimum jet eta
    Double_t                  fMaxJetEta     ; ///<  Maximum jet eta
    Double_t                  fMinChargedPt  ; ///<  Minimum pt of the leading charged particle (or track)
    Double_t                  fMaxChargedPt  ; ///<  Maximum pt of the leading charged particle (or track)
    Double_t                  fMinNeutralPt  ; ///<  Minimum pt of the leading neutral particle (or cluster)
    Double_t                  fMaxNeutralPt  ; ///<  Maximum pt of the leading neutral particle (or cluster)
    std::vector<AliJetInfo>   fJets          ; //!<! Inclusive jets reconstructed in the current event (includes D meson candidate daughters, if any)

  private:
    /// \cond CLASSIMP
    ClassDef(AliHFJetDefinition, 4);
    /// \endcond
  };

  /// \class AnalysisEngine
  /// \brief Struct that encapsulates analysis parameters
  ///
  /// This struct encapsulates analysis parameters
  /// for the D meson jet analysis.
  class AnalysisEngine : public TObject {
  public:
    typedef std::pair<AliJetInfo*, Double_t> jet_distance_pair;

    static std::pair<AliAnalysisTaskDmesonJets::EMesonOrigin_t, AliAODMCParticle*> CheckOrigin(const AliAODMCParticle* part, TClonesArray* mcArray, Bool_t firstParton=kFALSE);
    static EMesonDecayChannel_t CheckDecayChannel(const AliAODMCParticle* part, TClonesArray* mcArray);

    AnalysisEngine();
    AnalysisEngine(ECandidateType_t type, EMCMode_t MCmode, AliRDHFCuts* cuts = 0, Int_t nBins=80, Double_t range = 0.50);
    AnalysisEngine(const AnalysisEngine &source);
    AnalysisEngine& operator=(const AnalysisEngine& source);

    virtual ~AnalysisEngine();

    void SetCandidateType(ECandidateType_t t)       { fCandidateType  = t    ; }
    void SetMCMode(EMCMode_t m)                     { fMCMode         = m    ; }
    void SetNMassBins(Int_t n)                      { fNMassBins      = n    ; }
    void SetMassRange(Double_t min, Double_t max)   { fMinMass        = min  ; fMaxMass        = max  ; }
    void AdoptRDHFCuts(AliRDHFCuts* cuts);
    void SetRDHFCuts(AliRDHFCuts* cuts);
    void SetRejectedOriginMap(UInt_t m)             { fRejectedOrigin = m    ; }
    void SetAcceptedDecayMap(UInt_t m)              { fAcceptedDecay  = m    ; }

    const char* GetCandidateName() const { return fCandidateName.Data(); }
    const char* GetName() const;
    const char* GetName(const AliHFJetDefinition& jetDef) const;

    EMCMode_t GetMCMode()                     const { return fMCMode         ; }
    ECandidateType_t GetCandidateType()       const { return fCandidateType  ; }

    AliHFJetDefinition* AddJetDefinition(EJetType_t type, Double_t r, EJetAlgo_t algo, ERecoScheme_t reco);
    AliHFJetDefinition* AddJetDefinition(const AliHFJetDefinition& def);
    std::vector<AliHFJetDefinition>::iterator FindJetDefinition(const AliHFJetDefinition& eng);
    std::vector<AliAnalysisTaskDmesonJets::AliHFJetDefinition>& GetJetDefinitions() { return fJetDefinitions; }
    Bool_t IsAnyJetInAcceptance(const AliDmesonJetInfo& dMesonJet) const;

#if !(defined(__CINT__) || defined(__MAKECINT__))
    std::map<int, AliDmesonJetInfo>& GetDmesons() { return fDmesonJets; }
#endif

    void Init(const AliEMCALGeometry* const geom, Int_t runNumber);

    TTree* BuildTree(const char* taskName);
    TTree* GetTree() const { return fTree; }
    Bool_t FillTree(Bool_t applyKinCuts);

    void SetTrackEfficiency(Double_t t)      { fTrackEfficiency       = t; }
    void AssignDataSlot(Int_t n)             { fDataSlotNumber        = n; }
    Int_t GetDataSlotNumber() const          { return fDataSlotNumber    ; }

    void BuildHnSparse(UInt_t enabledAxis);
    Bool_t FillHnSparse(Bool_t applyKinCuts);
    Bool_t FillHnSparse(THnSparse* h, const AliDmesonJetInfo& DmesonJet, std::string n);

    Bool_t FillQA(Bool_t applyKinCuts);

    Bool_t IsInhibit() const { return fInhibit; }

    jet_distance_pair FindJetMacthedToGeneratedDMeson(const AliDmesonJetInfo& dmeson, AliHFJetDefinition& jetDef, Double_t dMax, Bool_t applyKinCuts);

    friend bool        operator< (const AnalysisEngine& lhs, const AnalysisEngine& rhs);
    friend inline bool operator> (const AnalysisEngine& lhs, const AnalysisEngine& rhs){ return rhs < lhs    ; }
    friend inline bool operator<=(const AnalysisEngine& lhs, const AnalysisEngine& rhs){ return !(lhs > rhs) ; }
    friend inline bool operator>=(const AnalysisEngine& lhs, const AnalysisEngine& rhs){ return !(lhs < rhs) ; }

    friend bool        operator==(const AnalysisEngine& lhs, const AnalysisEngine& rhs);
    friend inline bool operator!=(const AnalysisEngine& lhs, const AnalysisEngine& rhs){ return !(lhs == rhs); }

    std::map<AliAODMCParticle*, Short_t> fFirstPartons ; //!<! set of the first partons in the shower that produced each D meson
    std::map<AliAODMCParticle*, Short_t> fLastPartons  ; //!<! set of the last partons in the shower that produced each D meson

  protected:
    void RunAnalysis();
    void FindJets(AliHFJetDefinition& jetDef);

    ECandidateType_t                   fCandidateType         ; ///<  Candidate type
    TString                            fCandidateName         ; ///<  Candidate name
    UInt_t                             fCandidatePDG          ; ///<  Candidate PDG
    UChar_t                            fNDaughters            ; ///<  Number of daughters
    TArrayI                            fPDGdaughters          ; ///<  List of the PDG code of the daughters
    TString                            fBranchName            ; ///<  AOD branch where the D meson candidate are found
    EMCMode_t                          fMCMode                ; ///<  MC mode: No MC (data and MC detector level), background-only (MC), signal-only (MC), MC truth (particle level)
    Int_t                              fNMassBins             ; ///<  Mass number of bins
    Double_t                           fMinMass               ; ///<  Min mass in histogram axis
    Double_t                           fMaxMass               ; ///<  Max mass in histogram axis
    AliRDHFCuts                       *fRDHFCuts              ; ///<  D meson candidates cuts
    UInt_t                             fRejectedOrigin        ; ///<  Bit mask with D meson origins that are rejected (used for MC analysis, i.e. signal-only, background-only and particle-level)
    UInt_t                             fAcceptedDecay         ; ///<  Bit mask with D meson decays that are accepted (only used for particle-level analysis)
    Bool_t                             fInhibit               ; ///<  Inhibit the task
    std::vector<AliHFJetDefinition>    fJetDefinitions        ; ///<  Jet definitions
    Float_t                            fPtBinWidth            ; ///<  Histogram pt bin width
    Float_t                            fMaxPt                 ; ///<  Histogram pt limit
    TRandom                           *fRandomGen             ; //!<! Random number generator
    Double_t                           fTrackEfficiency       ; //!<! Artificial tracking inefficiency (0...1) -> set automatically at ExecOnce by AliAnalysisTaskDmesonJets
    Int_t                              fDataSlotNumber        ; //!<! Data slot where the tree output is posted
    TTree                             *fTree                  ; //!<! Output tree
    AliDmesonInfoSummary              *fCurrentDmesonJetInfo  ; //!<! Current D meson jet info
    AliJetInfoSummary                **fCurrentJetInfo        ; //!<! Current jet info
    std::map<int, AliDmesonJetInfo>    fDmesonJets            ; //!<! Array containing the D meson jets
    TClonesArray                      *fCandidateArray        ; //!<! D meson candidate array
    AliHFAODMCParticleContainer       *fMCContainer           ; //!<! MC particle container
    AliHFTrackContainer               *fTrackContainer        ; //!<! Track container
    AliClusterContainer               *fClusterContainer      ; //!<! Cluster container
    AliAODEvent                       *fAodEvent              ; //!<! AOD event
    AliFJWrapper                      *fFastJetWrapper        ; //!<! Fastjet wrapper
    THistManager                      *fHistManager           ; //!<! Histograms

    friend class AliAnalysisTaskDmesonJets;

  private:

    void                AddInputVectors(AliEmcalContainer* cont, Int_t offset, TH2* rejectHist=0, Double_t eff=0.);
    void                SetCandidateProperties(Double_t range);
    AliAODMCParticle*   MatchToMC() const;
    void                RunDetectorLevelAnalysis();
    void                RunParticleLevelAnalysis();

    Bool_t              ExtractRecoDecayAttributes(const AliAODRecoDecayHF2Prong* Dcand, AliDmesonJetInfo& DmesonJet, UInt_t i);
    Bool_t              ExtractD0Attributes(const AliAODRecoDecayHF2Prong* Dcand, AliDmesonJetInfo& DmesonJet, UInt_t i);
    Bool_t              ExtractDstarAttributes(const AliAODRecoCascadeHF* DstarCand, AliDmesonJetInfo& DmesonJet, UInt_t i);
    Bool_t              FindJet(AliAODRecoDecayHF2Prong* Dcand, AliDmesonJetInfo& DmesonJet, AliHFJetDefinition& jetDef);

    /// \cond CLASSIMP
    ClassDef(AnalysisEngine, 2);
    /// \endcond
  };

  AliAnalysisTaskDmesonJets();
  AliAnalysisTaskDmesonJets(const char* name, Int_t nOutputTrees=2);
  virtual ~AliAnalysisTaskDmesonJets();

  AnalysisEngine* AddAnalysisEngine(ECandidateType_t type, EMCMode_t bkgMode, EJetType_t jettype, Double_t jetradius, TString cutfname = "");
  AnalysisEngine* AddAnalysisEngine(ECandidateType_t type, EMCMode_t bkgMode, const AliHFJetDefinition& jetDef, TString cutfname = "");
  std::list<AnalysisEngine>::iterator FindAnalysisEngine(const AnalysisEngine& eng);

  void SetShowPositionD(Bool_t b = kTRUE)         { fEnabledAxis = b ?  fEnabledAxis | kPositionD         : fEnabledAxis & ~kPositionD         ; }
  void SetShowInvMass(Bool_t b = kTRUE)           { fEnabledAxis = b ?  fEnabledAxis | kInvMass           : fEnabledAxis & ~kInvMass           ; }
  void SetShow2ProngInvMass(Bool_t b = kTRUE)     { fEnabledAxis = b ?  fEnabledAxis | k2ProngInvMass     : fEnabledAxis & ~k2ProngInvMass     ; }
  void SetShowSoftPionPt(Bool_t b = kTRUE)        { fEnabledAxis = b ?  fEnabledAxis | kSoftPionPt        : fEnabledAxis & ~kSoftPionPt        ; }
  void SetShowDeltaR(Bool_t b = kTRUE)            { fEnabledAxis = b ?  fEnabledAxis | kDeltaR            : fEnabledAxis & ~kDeltaR            ; }
  void SetShowDeltaEta(Bool_t b = kTRUE)          { fEnabledAxis = b ?  fEnabledAxis | kDeltaEta          : fEnabledAxis & ~kDeltaEta          ; }
  void SetShowDeltaPhi(Bool_t b = kTRUE)          { fEnabledAxis = b ?  fEnabledAxis | kDeltaPhi          : fEnabledAxis & ~kDeltaPhi          ; }
  void SetShowPositionJet(Bool_t b = kTRUE)       { fEnabledAxis = b ?  fEnabledAxis | kPositionJet       : fEnabledAxis & ~kPositionJet       ; }
  void SetShowJetConstituents(Bool_t b = kTRUE)   { fEnabledAxis = b ?  fEnabledAxis | kJetConstituents   : fEnabledAxis & ~kJetConstituents   ; }

  void SetApplyKinematicCuts(Bool_t b)            { fApplyKinematicCuts = b ; }
  void SetOutputType(EOutputType_t b)             { SetOutputTypeInternal(b); }
  void SetTrackEfficiency(Double_t t)             { fTrackEfficiency    = t ; }

  virtual void         UserCreateOutputObjects();
  virtual void         ExecOnce();
  virtual Bool_t       Run();
  virtual Bool_t       FillHistograms();

  static AliAnalysisTaskDmesonJets* AddTaskDmesonJets(TString ntracks = "usedefault", TString nclusters = "usedefault", TString nMCpart = "", Int_t nMaxTrees = 2, TString suffix = "");

 protected:

  virtual void SetOutputTypeInternal(EOutputType_t b)             { fOutputType         = b; }

  AliRDHFCuts*         LoadDMesonCutsFromFile(TString cutfname, TString cutsname);
  
  static const char*   GetHFEventRejectionReasonLabel(UInt_t& bitmap);
  static void          CalculateMassLimits(Double_t range, Int_t pdg, Int_t nbins, Double_t& minMass, Double_t& maxMass);

  Int_t                PostDataFromAnalysisEngine(const AnalysisEngine& eng);

  void                 FillPartonLevelHistograms();

  std::list<AnalysisEngine>
                       fAnalysisEngines           ; ///<  Array of analysis parameters
  UInt_t               fEnabledAxis               ; ///<  Use bit defined in EAxis_t to enable axis in the THnSparse
  EOutputType_t        fOutputType                ; ///<  Output type: none, TTree or THnSparse
  THistManager         fHistManager               ; ///<  Histogram manager
  Bool_t               fApplyKinematicCuts        ; ///<  Apply jet kinematic cuts
  Int_t                fNOutputTrees              ; ///<  Maximum number of output trees
  Double_t             fTrackEfficiency           ; ///<  Artificial tracking inefficiency (0...1)
  AliAODEvent         *fAodEvent                  ; //!<! AOD event
  AliFJWrapper        *fFastJetWrapper            ; //!<! Fastjet wrapper
  AliHFAODMCParticleContainer
                      *fMCContainer               ; //!<! MC particle container

 private:
   
  AliAnalysisTaskDmesonJets(const AliAnalysisTaskDmesonJets &source);
  AliAnalysisTaskDmesonJets& operator=(const AliAnalysisTaskDmesonJets& source);

  /// \cond CLASSIMP
  ClassDef(AliAnalysisTaskDmesonJets, 7);
  /// \endcond
};

#endif
