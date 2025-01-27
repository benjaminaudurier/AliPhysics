//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// General class to do weak decay analysis
//
// WARNING: THIS IS EXPERIMENTAL!
//
// Please send any questions, etc to:
//    david.dobrigkeit.chinellato@cern.ch
//
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#ifndef AliStrangenessModule_H
#define AliStrangenessModule_H
#include <TNamed.h>
#include <TList.h>
#include <TH3F.h>

using namespace std;

class AliStrangenessModule : public TNamed {
    
public:
    //Simple constructor
    AliStrangenessModule();
    
    //TNamed-inspired constructor
    AliStrangenessModule(const char * name, const char * title = "Result");
    
    //Simple destructor
    ~AliStrangenessModule();
    
    void Clear(Option_t* = "") {}; //dummy
    
    //Set Input
    void SetDataInput         ( TList *lDataIn ) { lDataInput         = lDataIn; }
    void SetDataInputCounters ( TList *lDataIn ) { lDataCountersInput = lDataIn; }
    void SetMCInput           ( TList *lMCIn   ) { lMCInput           = lMCIn;   }
    void SetMCInputCounters   ( TList *lMCIn   ) { lMCCountersInput   = lMCIn; }
    
    //Configuration
    void SetPtBinning   ( Long_t lRecNPtBins, Double_t *lRecPtBins );
    void SetMultBinning ( Double_t lRecLoMult, Double_t lRecHiMult ){ lLoMult = lRecLoMult; lHiMult = lRecHiMult; }
    void SetSigExtRanges (Double_t lRLoLeftBg, Double_t lRHiLeftBg,  Double_t lRLoPeak,
                          Double_t lRHiPeak,   Double_t lRLoRightBg, Double_t lRHiRightBg);
    void SetSigExtTech ( TString lRecSigExtTech );
    void SetVariableSigExtTech ( Long_t lRecNPtBins, TString* lRecSigExtTech );
    void SetVerbose ( Bool_t lVerb = kTRUE ) { lVerbose = lVerb; }
    
    //Option to use integrated multiplicity for very first fit (to get mean, sigma)  
    void SetUseIntegratedMultForFirstFit( Bool_t lOpt = kTRUE ) { lUseIntegratedMultForFirstFit = lOpt; }
    void SetIntegratedMultForFirstFit ( Double_t lRecLoMult, Double_t lRecHiMult ){ lLoMultIntegrated = lRecLoMult; lHiMultIntegrated = lRecHiMult; }
    
    //Option to change fit ranges for initial fit
    //WARNING: the first number should be negative! E.g. -0.020 MeV/c^2 (to the left) and +0.020 MeV/c^2 (to the right) of the peak
    void SetInitialFitRange ( Double_t lOffsetLeft, Double_t lOffsetRight ){ lOffsetFromMeanLeft = lOffsetLeft; lOffsetFromMeanRight = lOffsetRight; }
    
    //Do analysis based on a specific configuration
    //Return corrected result right away
    TH1D* DoAnalysis( TString lConfiguration, TString lOutputFile = "" );
    
    //Helper functions
    Bool_t CheckCompatibleMultiplicity( TH3F *lHisto );
    Bool_t CheckCompatiblePt          ( TH3F *lHisto );
    Bool_t PerformInitialFit( TH1D *lHisto, Double_t &lMean, Double_t &lMeanErr, Double_t &lSigma, Double_t &lSigmaErr, TList *lControlList );
    Bool_t PerformSignalExtraction( TH1D *lHisto, Double_t &lSignal, Double_t &lSignalErr, Double_t lMean, Double_t lSigma, TList *lControlList, TString lOption = "linear" );
    TString GetGoodFitOption( TH1D *lHisto, Int_t ilow, Int_t ihigh );
    Double_t BgPol1(const Double_t *x, const Double_t *par);
    Double_t BgPol2(const Double_t *x, const Double_t *par);
    
private:
    //Data holders (set via setters)
    TList *lDataInput;
    TList *lDataCountersInput;
    TList *lMCInput;
    TList *lMCCountersInput;
    
    //Multiplicity / Centrality boundaries to use
    Double_t lLoMult;
    Double_t lHiMult;
    
    //Multiplicity / Centrality boundaries to use if requested to do so
    Bool_t lUseIntegratedMultForFirstFit;
    Double_t lLoMultIntegrated;
    Double_t lHiMultIntegrated;
    
    //Distance from mean from which to do initial fit (in GeV/c^2)
    Double_t lOffsetFromMeanLeft;
    Double_t lOffsetFromMeanRight;
    
    //Number of sigmas to do background/peak sampling
    Double_t lLoLeftBg;
    Double_t lHiLeftBg;
    Double_t lLoPeak;
    Double_t lHiPeak;
    Double_t lLoRightBg;
    Double_t lHiRightBg;
    
    //Pt Bins to use
    Long_t lNPtBins;
    Double_t lPtBins[100];
    
    //Signal Extraction technique to use
    TString lSigExtTech[100];
    
    //Verbosity boolean
    Bool_t lVerbose; 
    
    ClassDef(AliStrangenessModule, 1)
    // 1 - original implementation
};
#endif
