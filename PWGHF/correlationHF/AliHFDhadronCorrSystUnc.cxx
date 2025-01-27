/**************************************************************************
 * Copyright(c) 1998-2009, ALICE Experiment at CERN, All rights reserved. *
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


/* $Id: $ */

/////////////////////////////////////////////////////////////
// class for systematic uncertainties on D meson -hadron correlation distribution
//
// Author: A. Rossi, andrea.rossi@cern.ch
//
// Responsible of the values set for the different mesons/datasets
//      D0:  in pp (2010 min bias) Fabio Colamaria, fabio.colamaria@ba.infn.it ;  p-Pb (2013 min bias): Fabio Colamaria, fabio.colamaria@ba.infn.it,  Somnath Kar, somnath.kar@cern.ch
//      D*+: in pp 2010 min. bias and p-Pb 2013 min. bias  Sandro Bjelogrlic, sandro.bjelogrlic@cern.ch
//      D+:  in pp 2010 min. bias and p-Pb 2013 min. bias  Jitendra Kumar, jitendra.kumar@cern.ch
//
/////////////////////////////////////////////////////////////
#include <Riostream.h>
#include "AliHFDhadronCorrSystUnc.h"
#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <TNamed.h>
#include "AliHFCorrelationUtils.h"

using std::cout;
using std::endl;

ClassImp(AliHFDhadronCorrSystUnc)

AliHFDhadronCorrSystUnc::AliHFDhadronCorrSystUnc() : TNamed(), 
  fmeson(),
  fstrmeson(),
  fstrptAss(),
  fstrptD(),
  fhDeltaPhiTemplate(),
  fhYieldExtraction(),
  fhBackSubtractionMin(),
  fhBackSubtractionMax(),
  fhBeautyFDmin(),
  fhBeautyFDmax(),
  fhMCclosureTestMin(),
  fhMCclosureTestMax(),
  fhMCcorrectionsMin(),
  fhMCcorrectionsMax(),
  fhMCDefficiencyMin(),
  fhMCDefficiencyMax(),
  fhSecContaminationMin(),
  fhSecContaminationMax(),
  fhTotalMin(),
  fhTotalMax(),
  fhTotalNonFDMin(),
  fhTotalNonFDMax(),
  fhTotalNonFlatDPhiMin(),
  fhTotalNonFlatDPhiMax(),
  fhtotFlatMin(),
  fhtotFlatMax(),
  fgrYieldUnc(),         
  fgrBackSubUnc(),
  fgrMCcorrections(),   
  fgrMCDefficiency(),   
  fgrSecContamination(),   
  fgrMCclosureTest(),  
  fgrBeautyFD(),
  fgrYieldUncRel(),         
  fgrBackSubUncRel(),
  fgrMCcorrectionsRel(),   
  fgrMCDefficiencyRel(),   
  fgrSecContaminationRel(),   
  fgrMCclosureTestRel(),  
  fgrBeautyFDRel(),
  fgrTotal(),
  fgrTotalRel(),
  fgrTotalNonFD(),
  fgrTotalNonFlatDPhi(),
  fgrTotalNonFlatDPhiRel(),
  fgrTotalFlatDPhi(),
  fgrTotalFlatDPhiRel()
        
{
  // default constructor
}


AliHFDhadronCorrSystUnc::AliHFDhadronCorrSystUnc(const char* name) : 
  TNamed(name,name), 						   
  fmeson(),
  fstrmeson(),
  fstrptAss(),
  fstrptD(),
  fhDeltaPhiTemplate(),
  fhYieldExtraction(),
  fhBackSubtractionMin(),
  fhBackSubtractionMax(),
  fhBeautyFDmin(),
  fhBeautyFDmax(),
  fhMCclosureTestMin(),
  fhMCclosureTestMax(),
  fhMCcorrectionsMin(),
  fhMCcorrectionsMax(),
  fhMCDefficiencyMin(),
  fhMCDefficiencyMax(),
  fhSecContaminationMin(),
  fhSecContaminationMax(),
  fhTotalMin(),
  fhTotalMax(),
  fhTotalNonFDMin(),
  fhTotalNonFDMax(),
  fhTotalNonFlatDPhiMin(),
  fhTotalNonFlatDPhiMax(),
  fhtotFlatMin(),
  fhtotFlatMax(),
  fgrYieldUnc(),         
  fgrBackSubUnc(),
  fgrMCcorrections(),   
  fgrMCDefficiency(),   
  fgrSecContamination(),   
  fgrMCclosureTest(),  
  fgrBeautyFD(),
  fgrYieldUncRel(),         
  fgrBackSubUncRel(),
  fgrMCcorrectionsRel(),   
  fgrMCDefficiencyRel(),   
  fgrSecContaminationRel(),   
  fgrMCclosureTestRel(),  
  fgrBeautyFDRel(),
  fgrTotal(),
  fgrTotalRel(),
  fgrTotalNonFD(),
  fgrTotalNonFlatDPhi(),
  fgrTotalNonFlatDPhiRel(),
  fgrTotalFlatDPhi(),
  fgrTotalFlatDPhiRel()
{
  // default constructor
}



AliHFDhadronCorrSystUnc::~AliHFDhadronCorrSystUnc(){
  // destructor
  
  delete fhDeltaPhiTemplate;
  delete fhYieldExtraction;
  delete fhBackSubtractionMin;
  delete   fhBackSubtractionMax;
  delete  fhBeautyFDmin;
  delete  fhBeautyFDmax;
  delete  fhMCclosureTestMin;
  delete  fhMCclosureTestMax;
  delete  fhMCcorrectionsMin;
  delete  fhMCcorrectionsMax;
  delete  fhMCDefficiencyMin;
  delete  fhMCDefficiencyMax;
  delete  fhSecContaminationMin;
  delete  fhSecContaminationMax;
  delete  fhTotalMin;
  delete fhTotalMax;
  delete fhTotalNonFDMin;
  delete fhTotalNonFDMax;
  delete fhTotalNonFlatDPhiMin;
  delete fhTotalNonFlatDPhiMax;
  delete fhtotFlatMin;
  delete fhtotFlatMax;
  delete fgrYieldUnc;
  delete fgrBackSubUnc;
  delete fgrMCcorrections;
  delete fgrMCDefficiency;
  delete fgrSecContamination;
  delete fgrMCclosureTest;  
  delete fgrBeautyFD;   
  delete fgrYieldUncRel;
  delete fgrBackSubUncRel;
  delete fgrMCcorrectionsRel;
  delete fgrMCDefficiencyRel;
  delete fgrSecContaminationRel;
  delete fgrMCclosureTestRel;  
  delete fgrBeautyFDRel;   
  delete fgrTotal;
  delete fgrTotalRel;
  delete fgrTotalNonFD;
  delete fgrTotalNonFlatDPhi;
  delete fgrTotalNonFlatDPhiRel;
  delete fgrTotalFlatDPhi;
  delete fgrTotalFlatDPhiRel;

}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DzeroLowPtAss03HP(){ 
  Printf("Loading syst unc for D0 pp2010 3-5 0.3 thr");
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }

  
  // MC CORRECTIONS ( associatate track efficiency):
  //  -5%  +10% for assoc track eff 
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }


  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    //    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DzeroMidPtAss03HP(){ 
  Printf("Loading syst unc for D0 pp2010 5-8 0.3 thr");

  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS:  -5%  +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DzeroHighPtAss03HP(){ 

  Printf("Loading syst unc for D0 pp2010 8-16 0.3 thr");
  
  fmeson=AliHFCorrelationUtils::kDzero;;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }

  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS,  -5% 10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}




//--------------------------------------------------
void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DstarLowPtAss03HP(){
  Printf("Loading syst unc for D*+ pp 2010, 3<pt(D)<5 GeV/c, pt(assoc)>0.3");
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS, -5%  10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }


}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DstarMidPtAss03HP(){
  Printf("Loading syst unc for D*+ pp 2010, 5<pt(D)<8 GeV/c, pt(assoc)>0.3");
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS/ -5%  10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}



void AliHFDhadronCorrSystUnc::InitEmptyHistosFromTemplate(){
  if(!fhDeltaPhiTemplate){
    Printf("Template histo not set, using standard binning");
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
   fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
   fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
   fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
   fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
   fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
   fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
   fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
   fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
   fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
   fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
   fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
   fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
   fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
}




void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DstarHighPtAss03HP(){
  Printf("Loading syst unc for D*+ pp 2010, 8<pt(D)<16 GeV/c, pt(assoc)>0.3");  
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS   -5% +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }
  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }


}


void AliHFDhadronCorrSystUnc::SetHistoTemplate(TH1D *h,TString strname,Bool_t clone){
  if(fhDeltaPhiTemplate)delete fhDeltaPhiTemplate;
  if(!clone){
    fhDeltaPhiTemplate=h;
  }
  else{
    if(strname.IsNull()){fhDeltaPhiTemplate=(TH1D*)h->Clone("fhDeltaPhiTemplate");
    }
    else fhDeltaPhiTemplate=(TH1D*)h->Clone(strname.Data());
  }
}


void AliHFDhadronCorrSystUnc::SetHistoYieldExtraction(TH1D *h,TString strname,Bool_t clone){
  if(fhYieldExtraction)delete fhYieldExtraction;
  if(!clone){
    fhYieldExtraction=h;
  }
  else{
    if(strname.IsNull()){fhYieldExtraction=(TH1D*)h->Clone("fhYieldExtraction");
    }
    else fhYieldExtraction=(TH1D*)h->Clone(strname.Data());
  }
}

void AliHFDhadronCorrSystUnc::SetHistoBackSubtraction(TH1D *hMax,TString strname,Bool_t clone,TH1D *hMin){
  if(!hMax){
    Printf("No Input Histo for back uncertainty");
    return;
  }
  if(fhBackSubtractionMax)delete fhBackSubtractionMax;
  if(!clone){
    fhBackSubtractionMax=hMax;
  }
  else{
    if(strname.IsNull()){fhBackSubtractionMax=(TH1D*)hMax->Clone("fhBackSubtractionMax");
    }
    else fhBackSubtractionMax=(TH1D*)hMax->Clone(strname.Data());
  }
  
  if(fhBackSubtractionMin)delete fhBackSubtractionMin;
  if(hMin){
    if(!clone){
      fhBackSubtractionMin=hMin;
    }
    else{
      if(strname.IsNull()){fhBackSubtractionMin=(TH1D*)hMin->Clone("fhBackSubtractionMin");
      }
      else fhBackSubtractionMin=(TH1D*)hMin->Clone(strname.Data());
    }
  }
  else{
    if(strname.IsNull()){
      fhBackSubtractionMin=(TH1D*)hMin->Clone("fhBackSubtractionMin");
    }
    else fhBackSubtractionMin=(TH1D*)hMin->Clone(strname.Data());
    for(Int_t k=0;k<=fhBackSubtractionMin->GetNbinsX();k++){
      fhBackSubtractionMin->SetBinContent(k,-1.*fhBackSubtractionMin->GetBinContent(k));
    }
  }

  


}


void AliHFDhadronCorrSystUnc::SetHistoMCclosureTestMax(TH1D *h,TString strname,Bool_t clone){
  if(fhMCclosureTestMax)delete fhMCclosureTestMax;
  if(!clone){
    fhMCclosureTestMax=h;
  }
  else{
    if(strname.IsNull()){fhMCclosureTestMax=(TH1D*)h->Clone("fhMCclosureTestMax");
    }
    else fhMCclosureTestMax=(TH1D*)h->Clone(strname.Data());
  }
}

void AliHFDhadronCorrSystUnc::SetHistoMCclosureTestMin(TH1D *h,TString strname,Bool_t clone){
    if(fhMCclosureTestMin)delete fhMCclosureTestMin;
    if(!clone){
      fhMCclosureTestMin=h;
    }
    else{
      if(strname.IsNull()){fhMCclosureTestMin=(TH1D*)h->Clone("fhMCclosureTestMin");
      }
      else fhMCclosureTestMin=(TH1D*)h->Clone(strname.Data());
    }
}


void AliHFDhadronCorrSystUnc::SetHistoMCcorrectionsMin(TH1D *h,TString strname,Bool_t clone){
    if(fhMCcorrectionsMin)delete fhMCcorrectionsMin;
    if(!clone){
      fhMCcorrectionsMin=h;
    }
    else{
      if(strname.IsNull()){fhMCcorrectionsMin=(TH1D*)h->Clone("fhMCcorrectionsMin");
      }
      else fhMCcorrectionsMin=(TH1D*)h->Clone(strname.Data());
    }
}


void AliHFDhadronCorrSystUnc::SetHistoMCcorrectionsMax(TH1D *h,TString strname,Bool_t clone){
    if(fhMCcorrectionsMax)delete fhMCcorrectionsMax;
    if(!clone){
      fhMCcorrectionsMax=h;
    }
    else{
      if(strname.IsNull()){fhMCcorrectionsMax=(TH1D*)h->Clone("fhMCcorrectionsMax");
      }
      else fhMCcorrectionsMax=(TH1D*)h->Clone(strname.Data());
    }
}


void AliHFDhadronCorrSystUnc::SetHistoMCDefficiencyMin(TH1D *h,TString strname,Bool_t clone){
    if(fhMCDefficiencyMin)delete fhMCDefficiencyMin;
    if(!clone){
      fhMCDefficiencyMin=h;
    }
    else{
      if(strname.IsNull()){fhMCDefficiencyMin=(TH1D*)h->Clone("fhMCDefficiencyMin");
      }
      else fhMCDefficiencyMin=(TH1D*)h->Clone(strname.Data());
    }
}


void AliHFDhadronCorrSystUnc::SetHistoMCDefficiencyMax(TH1D *h,TString strname,Bool_t clone){
    if(fhMCDefficiencyMax)delete fhMCDefficiencyMax;
    if(!clone){
      fhMCDefficiencyMax=h;
    }
    else{
      if(strname.IsNull()){fhMCDefficiencyMax=(TH1D*)h->Clone("fhMCDefficiencyMax");
      }
      else fhMCDefficiencyMax=(TH1D*)h->Clone(strname.Data());
    }
}


void AliHFDhadronCorrSystUnc::SetHistoSecContaminationMin(TH1D *h,TString strname,Bool_t clone){
    if(fhSecContaminationMin)delete fhSecContaminationMin;
    if(!clone){
      fhSecContaminationMin=h;
    }
    else{
      if(strname.IsNull()){fhSecContaminationMin=(TH1D*)h->Clone("fhSecContaminationMin");
      }
      else fhSecContaminationMin=(TH1D*)h->Clone(strname.Data());
    }
}


void AliHFDhadronCorrSystUnc::SetHistoSecContaminationMax(TH1D *h,TString strname,Bool_t clone){
    if(fhSecContaminationMax)delete fhSecContaminationMax;
    if(!clone){
      fhSecContaminationMax=h;
    }
    else{
      if(strname.IsNull()){fhSecContaminationMax=(TH1D*)h->Clone("fhSecContaminationMax");
      }
      else fhSecContaminationMax=(TH1D*)h->Clone(strname.Data());
    }
}


void AliHFDhadronCorrSystUnc::SetHistoBeautyFDmin(TH1D *h,TString strname,Bool_t clone){
    if(fhBeautyFDmin)delete fhBeautyFDmin;
    if(!clone){
      fhBeautyFDmin=h;
    }
    else{
      if(strname.IsNull()){fhBeautyFDmin=(TH1D*)h->Clone("fhBeautyFDmin");
      }
      else fhBeautyFDmin=(TH1D*)h->Clone(strname.Data());
    }
}


void AliHFDhadronCorrSystUnc::SetHistoBeautyFDmax(TH1D *h,TString strname,Bool_t clone){
    if(fhBeautyFDmax)delete fhBeautyFDmax;
    if(!clone){
      fhBeautyFDmax=h;
    }
    else{
      if(strname.IsNull()){fhBeautyFDmax=(TH1D*)h->Clone("fhBeautyFDmax");
      }
      else fhBeautyFDmax=(TH1D*)h->Clone(strname.Data());
    }
}





void AliHFDhadronCorrSystUnc::BuildTotalUncHisto(){
  if(fhTotalMin)delete fhTotalMin;
  if(fhTotalMax)delete fhTotalMax;

  fhTotalMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhTotalMin");
  fhTotalMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhTotalMax");
  Double_t errMin,errMax;

  for(Int_t j=1;j<=fhTotalMin->GetNbinsX();j++){
    errMin=fhMCclosureTestMin->GetBinContent(j)*fhMCclosureTestMin->GetBinContent(j);    
    errMin+=fhMCcorrectionsMin->GetBinContent(j)*fhMCcorrectionsMin->GetBinContent(j);
    errMin+=fhMCDefficiencyMin->GetBinContent(j)*fhMCDefficiencyMin->GetBinContent(j);
    errMin+=fhSecContaminationMin->GetBinContent(j)*fhSecContaminationMin->GetBinContent(j);
    errMin+=fhYieldExtraction->GetBinContent(j)*fhYieldExtraction->GetBinContent(j);
    errMin+=fhBackSubtractionMin->GetBinContent(j)*fhBackSubtractionMin->GetBinContent(j);
    errMin+=fhBeautyFDmin->GetBinContent(j)*fhBeautyFDmin->GetBinContent(j);
    
    fhTotalMin->SetBinContent(j,-TMath::Sqrt(errMin));

    errMax=fhMCclosureTestMax->GetBinContent(j)*fhMCclosureTestMax->GetBinContent(j);    
    errMax+=fhMCcorrectionsMax->GetBinContent(j)*fhMCcorrectionsMax->GetBinContent(j);
    errMax+=fhMCDefficiencyMax->GetBinContent(j)*fhMCDefficiencyMax->GetBinContent(j);
    errMax+=fhSecContaminationMax->GetBinContent(j)*fhSecContaminationMax->GetBinContent(j);
    errMax+=fhYieldExtraction->GetBinContent(j)*fhYieldExtraction->GetBinContent(j);
    errMax+=fhBackSubtractionMax->GetBinContent(j)*fhBackSubtractionMax->GetBinContent(j);
    errMax+=fhBeautyFDmax->GetBinContent(j)*fhBeautyFDmax->GetBinContent(j);
    
    fhTotalMax->SetBinContent(j,TMath::Sqrt(errMax));
    
    
  }

  fhTotalMin->SetLineColor(kBlack);
  fhTotalMin->SetLineWidth(2);
  fhTotalMin->SetFillStyle(0);
  fhTotalMin->SetFillColor(kBlack);
  fhTotalMin->SetMarkerColor(kBlack);
  fhTotalMin->SetMarkerStyle(20);

  fhTotalMax->SetLineColor(kBlack);
  fhTotalMax->SetLineWidth(2);
  fhTotalMax->SetFillStyle(0);
  fhTotalMax->SetFillColor(kBlack);
  fhTotalMax->SetMarkerColor(kBlack);
  fhTotalMax->SetMarkerStyle(20);
  
}

void AliHFDhadronCorrSystUnc::BuildTotalNonFlatUncHisto(){
  if(fhTotalNonFlatDPhiMin)delete fhTotalNonFlatDPhiMin;
  if(fhTotalNonFlatDPhiMax)delete fhTotalNonFlatDPhiMax;

  fhTotalNonFlatDPhiMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhTotalNonFlatDPhiMin");
  fhTotalNonFlatDPhiMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhTotalNonFlatDPhiMax");
  Double_t errMin,errMax,mcClosureMinmax,mcClosureMaxmin;

  mcClosureMinmax=fhMCclosureTestMin->GetBinContent(fhMCclosureTestMin->GetMaximumBin());
  mcClosureMaxmin=fhMCclosureTestMax->GetBinContent(fhMCclosureTestMax->GetMinimumBin());
  Printf("MC closure - The max of min is: %f, the min of max is: %f", mcClosureMinmax, mcClosureMaxmin);

  for(Int_t j=1;j<=fhTotalNonFlatDPhiMin->GetNbinsX();j++){
    errMin=(fhMCclosureTestMin->GetBinContent(j)*fhMCclosureTestMin->GetBinContent(j)-mcClosureMinmax*mcClosureMinmax);// Forced to this quadrature subtraction, doing: (fhMCclosureTestMin->GetBinContent(j)-mcClosureMinmax)*(fhMCclosureTestMin->GetBinContent(j)-mcClosureMinmax) gives the wrong result.. of course  

    errMin+=fhBeautyFDmin->GetBinContent(j)*fhBeautyFDmin->GetBinContent(j);
    
    fhTotalNonFlatDPhiMin->SetBinContent(j,-TMath::Sqrt(errMin));

    errMax=fhMCclosureTestMax->GetBinContent(j)*fhMCclosureTestMax->GetBinContent(j)-mcClosureMaxmin*mcClosureMaxmin; // Forced to this quadrature subtraction, doing:(fhMCclosureTestMax->GetBinContent(j)-mcClosureMaxmin)*(fhMCclosureTestMax->GetBinContent(j)-mcClosureMaxmin) gives the wrong result.. of course  
   
    errMax+=fhBeautyFDmax->GetBinContent(j)*fhBeautyFDmax->GetBinContent(j);
    
    fhTotalNonFlatDPhiMax->SetBinContent(j,TMath::Sqrt(errMax));
    
    
  }

  fhtotFlatMin=(TH1D*)fhTotalMin->Clone("hTotFlatDPhiMin");
  fhtotFlatMin->SetTitle("#Delta#phi indipendent");

  fhtotFlatMax=(TH1D*)fhTotalMax->Clone("hTotFlatDPhiMax");
  fhtotFlatMax->SetTitle("#Delta#phi indipendent");

  for(Int_t jfl=1;jfl<=fhtotFlatMin->GetNbinsX();jfl++){
    fhtotFlatMin->SetBinContent(jfl,-TMath::Sqrt(fhTotalMin->GetBinContent(jfl)*fhTotalMin->GetBinContent(jfl)-fhTotalNonFlatDPhiMin->GetBinContent(jfl)*fhTotalNonFlatDPhiMin->GetBinContent(jfl)));
    fhtotFlatMax->SetBinContent(jfl,TMath::Sqrt(fhTotalMax->GetBinContent(jfl)*fhTotalMax->GetBinContent(jfl)-fhTotalNonFlatDPhiMax->GetBinContent(jfl)*fhTotalNonFlatDPhiMax->GetBinContent(jfl)));
  }

  fhtotFlatMin->SetLineStyle(2);
  fhtotFlatMax->SetLineStyle(2);




  fhTotalNonFlatDPhiMin->SetLineColor(kBlue);
  fhTotalNonFlatDPhiMin->SetLineWidth(2);
  fhTotalNonFlatDPhiMin->SetFillStyle(0);
  fhTotalNonFlatDPhiMin->SetFillColor(kBlue);
  fhTotalNonFlatDPhiMin->SetMarkerColor(kBlue);
  fhTotalNonFlatDPhiMin->SetMarkerStyle(20);

  fhTotalNonFlatDPhiMax->SetLineColor(kBlue);
  fhTotalNonFlatDPhiMax->SetLineWidth(2);
  fhTotalNonFlatDPhiMax->SetFillStyle(0);
  fhTotalNonFlatDPhiMax->SetFillColor(kBlue);
  fhTotalNonFlatDPhiMax->SetMarkerColor(kBlue);
  fhTotalNonFlatDPhiMax->SetMarkerStyle(20);
  
}


void AliHFDhadronCorrSystUnc::BuildTotalNonFDUncHisto(){
  if(fhTotalNonFDMin)delete fhTotalNonFDMin;
  if(fhTotalNonFDMax)delete fhTotalNonFDMax;

  fhTotalNonFDMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhTotalNonFDMin");
  fhTotalNonFDMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhTotalNonFDMax");
  Double_t errMin,errMax;

  for(Int_t j=1;j<=fhTotalNonFDMin->GetNbinsX();j++){
    errMin=fhMCclosureTestMin->GetBinContent(j)*fhMCclosureTestMin->GetBinContent(j);    
    errMin+=fhMCcorrectionsMin->GetBinContent(j)*fhMCcorrectionsMin->GetBinContent(j);
    errMin+=fhMCDefficiencyMin->GetBinContent(j)*fhMCDefficiencyMin->GetBinContent(j);
    errMin+=fhSecContaminationMin->GetBinContent(j)*fhSecContaminationMin->GetBinContent(j);
    errMin+=fhYieldExtraction->GetBinContent(j)*fhYieldExtraction->GetBinContent(j);
    errMin+=fhBackSubtractionMin->GetBinContent(j)*fhBackSubtractionMin->GetBinContent(j);

    fhTotalNonFDMin->SetBinContent(j,-TMath::Sqrt(errMin));

    errMax=fhMCclosureTestMax->GetBinContent(j)*fhMCclosureTestMax->GetBinContent(j);    
    errMax+=fhMCcorrectionsMax->GetBinContent(j)*fhMCcorrectionsMax->GetBinContent(j);
    errMax+=fhMCDefficiencyMax->GetBinContent(j)*fhMCDefficiencyMax->GetBinContent(j);
    errMax+=fhSecContaminationMax->GetBinContent(j)*fhSecContaminationMax->GetBinContent(j);
    errMax+=fhYieldExtraction->GetBinContent(j)*fhYieldExtraction->GetBinContent(j);
    errMax+=fhBackSubtractionMax->GetBinContent(j)*fhBackSubtractionMax->GetBinContent(j);
    
    fhTotalNonFDMax->SetBinContent(j,TMath::Sqrt(errMax));
    
    
  }

}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010(Int_t meson,Double_t ptD,Double_t minptAss){
  
  if(meson==AliHFCorrelationUtils::kDzero){
    
    // 0.3 GeV/c
    if(TMath::Abs(minptAss-0.3)<0.0001){
      if(ptD>2&&ptD<5){
	InitStandardUncertaintiesPP2010DzeroLowPtAss03HP();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPP2010DzeroMidPtAss03HP();        
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPP2010DzeroHighPtAss03HP();
      }
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }     
    // 0.5 GeV/c
    else if(TMath::Abs(minptAss-0.5)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPP2010DzeroLowPtAss05();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPP2010DzeroMidPtAss05();               
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPP2010DzeroHighPtAss05();
      }      
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }       
    // 1 GeV/c
    else if(TMath::Abs(minptAss-1.)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPP2010DzeroLowPtAss1();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPP2010DzeroMidPtAss1();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPP2010DzeroHighPtAss1();
      }
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    else {
      printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
    }
  }    
  else if(meson==AliHFCorrelationUtils::kDstar){
    // 0.3 GeV/c
    if(TMath::Abs(minptAss-0.3)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPP2010DstarLowPtAss03HP();	
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPP2010DstarMidPtAss03HP();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPP2010DstarHighPtAss03HP();
      }
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    // 0.5 GeV/c
    else if(TMath::Abs(minptAss-0.5)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPP2010DstarLowPtAss05();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPP2010DstarMidPtAss05();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPP2010DstarHighPtAss05();
      }
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    
    // 1 GeV/c
    else if(TMath::Abs(minptAss-1.)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPP2010DstarLowPtAss1();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPP2010DstarMidPtAss1();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPP2010DstarHighPtAss1();
      }
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    else {
      printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
    }
  }
  else if(meson==AliHFCorrelationUtils::kDplus){
    // 0.3 GeV/c
    if(TMath::Abs(minptAss-0.3)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPP2010DplusLowPtAss03();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPP2010DplusMidPtAss03();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPP2010DplusHighPtAss03();
      }
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    // 0.5 GeV/c
    else if(TMath::Abs(minptAss-0.5)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPP2010DplusLowPtAss05();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPP2010DplusMidPtAss05();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPP2010DplusHighPtAss05();
      }
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    // 1 GeV/c
    else if(TMath::Abs(minptAss-1.)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPP2010DplusLowPtAss1();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPP2010DplusMidPtAss1();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPP2010DplusHighPtAss1();
      }
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    else {
      printf("Methods for syst unc not ready yet for this pt(ass) bin \n");
    }
  }
  else {
    printf("PP:No meson is found  Check your input \n");
  }
}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013(Int_t meson,Double_t ptD,Double_t minptAss){
  
  if(meson==AliHFCorrelationUtils::kDzero){
    // 0.3 GeV/c
    if(TMath::Abs(minptAss-0.3)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPPb2013DzeroLowPtAss03();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPPb2013DzeroMidPtAss03();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPPb2013DzeroHighPtAss03();
      }
      
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    // 0.5 GeV/c
    else if(TMath::Abs(minptAss-0.5)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPPb2013DzeroLowPtAss05();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPPb2013DzeroMidPtAss05();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPPb2013DzeroHighPtAss05();
      }
      
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    
    // 1 GeV/c
    else if(TMath::Abs(minptAss-1.)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPPb2013DzeroLowPtAss1();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPPb2013DzeroMidPtAss1();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPPb2013DzeroHighPtAss1();
      } 
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    else {
      printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
    }
  }
  else if(meson==AliHFCorrelationUtils::kDstar){
    // 0.3 GeV/c
    if(TMath::Abs(minptAss-0.3)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPPb2013DstarLowPtAss03();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPPb2013DstarMidPtAss03();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPPb2013DstarHighPtAss03();
      }
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    // 0.5 GeV/c
    else if(TMath::Abs(minptAss-0.5)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPPb2013DstarLowPtAss05();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPPb2013DstarMidPtAss05();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPPb2013DstarHighPtAss05();
      }
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    // 1 GeV/c
    else if(TMath::Abs(minptAss-1.)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPPb2013DstarLowPtAss1();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPPb2013DstarMidPtAss1();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPPb2013DstarHighPtAss1();
      }
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    else {
      printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
    }
  }
  else if(meson==AliHFCorrelationUtils::kDplus){
    // 0.3 GeV/c
    if(TMath::Abs(minptAss-0.3)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPPb2013DplusLowPtAss03();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPPb2013DplusMidPtAss03();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPPb2013DplusHighPtAss03();
      }
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    // 0.5 GeV/c
    else if(TMath::Abs(minptAss-0.5)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPPb2013DplusLowPtAss05();
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPPb2013DplusMidPtAss05();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPPb2013DplusHighPtAss05();
      }      
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    // 1 GeV/c
    else if(TMath::Abs(minptAss-1.)<0.0001){
      if(ptD>3&&ptD<5){
	InitStandardUncertaintiesPPb2013DplusLowPtAss1();      
      }
      else if(ptD>5&&ptD<8){
	InitStandardUncertaintiesPPb2013DplusMidPtAss1();
      }
      else if(ptD>8&&ptD<16){
	InitStandardUncertaintiesPPb2013DplusHighPtAss1();
      }
      else {
	printf("Methods for syst unc not ready yet for this pt(ass) bin  \n");
      }
    }
    else {
      printf("Methods for syst unc not ready yet for this pt(ass) bin \n");
    }
  }
  else {
        printf("pPb-No meson is found  Check your input \n");
  }
}


TGraphAsymmErrors* AliHFDhadronCorrSystUnc::GetUncGraphFromHistos(TH1D *hRef,TH1D *hMin,TH1D *hMax){
  
  //  Int_t npoints=hMin->GetNbinsX();
  Double_t ew=hMin->GetBinWidth(1)/2.;
  Double_t value,eyl,eym;
  
  TGraphAsymmErrors *gr=new TGraphAsymmErrors();
  for(Int_t j=1;j<=hMin->GetNbinsX();j++){
    if(hRef){
      value=hRef->GetBinContent(j);
      eyl=hMin->GetBinContent(j)*value;
      if(eyl<0.)eyl*=-1.;
      if(hMax)eym=hMax->GetBinContent(j)*value;
      else eym=eyl;
    }
    else {
      value=0.;
      eyl=hMin->GetBinContent(j);
      if(eyl<0.)eyl*=-1.;
      if(hMax)eym=hMax->GetBinContent(j);
      else eym=eyl;
    }
    
    gr->SetPoint(j-1,hMin->GetBinCenter(j),value);
    gr->SetPointError(j-1,ew,ew,eyl,eym);
  }
  
  return gr;
}

void AliHFDhadronCorrSystUnc::BuildGraphsRelUnc(){
  if(fgrYieldUncRel)delete fgrYieldUncRel;
  if(fgrBackSubUncRel)delete fgrBackSubUncRel;
  if(fgrMCcorrectionsRel)delete fgrMCcorrectionsRel;
  if(fgrMCDefficiencyRel)delete fgrMCDefficiencyRel;
  if(fgrSecContaminationRel)delete fgrSecContaminationRel;
  if(fgrMCclosureTestRel)delete fgrMCclosureTestRel;  
  if(fgrBeautyFDRel)delete fgrBeautyFDRel;   
  
  fgrYieldUncRel=GetUncGraphFromHistos(0x0,fhYieldExtraction,0x0);
  fgrYieldUncRel->SetName("fgrYieldUncRel");
  fgrYieldUncRel->SetTitle("D meson yield");


  fgrBackSubUncRel=GetUncGraphFromHistos(0x0,fhBackSubtractionMin,fhBackSubtractionMax);
  fgrBackSubUncRel->SetName("fgrBackSubUncRel");
  fgrBackSubUncRel->SetTitle("Background D correlation subtraction");



  fgrMCcorrectionsRel=GetUncGraphFromHistos(0x0,fhMCcorrectionsMin,fhMCcorrectionsMax);
  fgrMCcorrectionsRel->SetName("fgrMCcorrectionsRel");
  fgrMCcorrectionsRel->SetTitle("Associated track efficiency");

  fgrMCDefficiencyRel=GetUncGraphFromHistos(0x0,fhMCDefficiencyMin,fhMCDefficiencyMax);
  fgrMCDefficiencyRel->SetName("fgrMCDefficiencyRel");
  fgrMCDefficiencyRel->SetTitle("D meson efficiency");

  fgrSecContaminationRel=GetUncGraphFromHistos(0x0,fhSecContaminationMin,fhSecContaminationMax);
  fgrSecContaminationRel->SetName("fgrSecContaminationRel");
  fgrSecContaminationRel->SetTitle("Secondary contamination");

  fgrMCclosureTestRel=GetUncGraphFromHistos(0x0,fhMCclosureTestMin,fhMCclosureTestMax);
  fgrMCclosureTestRel->SetName("fgrMCclosureTestRel");
  fgrMCclosureTestRel->SetTitle("MC closure test");

  fgrBeautyFDRel=GetUncGraphFromHistos(0x0,fhBeautyFDmin,fhBeautyFDmax);
  fgrBeautyFDRel->SetName("fgrBeautyFDRel");
  fgrBeautyFDRel->SetTitle("Feed-down");

  fgrYieldUncRel->SetLineColor(kBlue);
  fgrYieldUncRel->SetLineWidth(2);
  fgrYieldUncRel->SetFillStyle(3002);
  fgrYieldUncRel->SetFillColor(kBlue);
  fgrYieldUncRel->SetMarkerColor(kBlue);
  fgrYieldUncRel->SetMarkerStyle(20);


  fgrBackSubUncRel->SetLineColor(kMagenta);
  fgrBackSubUncRel->SetLineWidth(2);
  fgrBackSubUncRel->SetFillStyle(3008);
  fgrBackSubUncRel->SetFillColor(kMagenta);
  fgrBackSubUncRel->SetMarkerColor(kBlue);
  fgrBackSubUncRel->SetMarkerStyle(20);


  fgrMCcorrectionsRel->SetLineColor(kGreen);
  fgrMCcorrectionsRel->SetLineWidth(2);
  fgrMCcorrectionsRel->SetFillStyle(3006);
  fgrMCcorrectionsRel->SetFillColor(kGreen);
  fgrMCcorrectionsRel->SetMarkerColor(kGreen);
  fgrMCcorrectionsRel->SetMarkerStyle(22);

  fgrMCDefficiencyRel->SetLineColor(kCyan);
  fgrMCDefficiencyRel->SetLineWidth(2);
  fgrMCDefficiencyRel->SetFillStyle(3004);
  fgrMCDefficiencyRel->SetFillColor(kCyan);
  fgrMCDefficiencyRel->SetMarkerColor(kCyan);
  fgrMCDefficiencyRel->SetMarkerStyle(22);

  fgrSecContaminationRel->SetLineColor(kOrange);
  fgrSecContaminationRel->SetLineWidth(2);
  fgrSecContaminationRel->SetFillStyle(3007);
  fgrSecContaminationRel->SetFillColor(kOrange);
  fgrSecContaminationRel->SetMarkerColor(kOrange);
  fgrSecContaminationRel->SetMarkerStyle(22);

  fgrMCclosureTestRel->SetLineColor(kRed);
  fgrMCclosureTestRel->SetLineWidth(2);
  fgrMCclosureTestRel->SetFillStyle(3005);
  fgrMCclosureTestRel->SetFillColor(kRed);
  fgrMCclosureTestRel->SetMarkerColor(kRed);
  fgrMCclosureTestRel->SetMarkerStyle(26);

  fgrBeautyFDRel->SetLineColor(kViolet);
  fgrBeautyFDRel->SetLineWidth(2);
  fgrBeautyFDRel->SetFillStyle(3021);
  fgrBeautyFDRel->SetFillColor(kViolet);
  fgrBeautyFDRel->SetMarkerColor(kViolet);
  fgrBeautyFDRel->SetMarkerStyle(28);


  

}

void AliHFDhadronCorrSystUnc::BuildGraphsUnc(TH1D *hRef){

  if(fgrYieldUnc)delete fgrYieldUnc;
  if(fgrBackSubUnc)delete fgrBackSubUnc;
  if(fgrMCcorrections)delete fgrMCcorrections;
  if(fgrMCDefficiency)delete fgrMCDefficiency;
  if(fgrSecContamination)delete fgrSecContamination;
  if(fgrMCclosureTest)delete fgrMCclosureTest;  
  if(fgrBeautyFD)delete fgrBeautyFD;   
  if(fgrTotalRel)delete fgrTotalRel;
  if(fgrTotal)delete fgrTotal;
  if(fgrTotalNonFlatDPhi)delete fgrTotalNonFlatDPhi;
  if(fgrTotalNonFlatDPhiRel)delete fgrTotalNonFlatDPhiRel;
  if(fgrTotalFlatDPhi)delete fgrTotalFlatDPhi;
  if(fgrTotalFlatDPhiRel)delete fgrTotalFlatDPhiRel;

  fgrYieldUnc=GetUncGraphFromHistos(hRef,fhYieldExtraction,0x0);
  fgrYieldUnc->SetName("fgrYieldUnc");
  fgrYieldUnc->SetTitle("D meson yield");

  fgrBackSubUnc=GetUncGraphFromHistos(hRef,fhBackSubtractionMin,fhBackSubtractionMax);
  fgrBackSubUnc->SetName("fgrBackSubUnc");
  fgrBackSubUnc->SetTitle("Background D correlation subtraction");


  fgrMCcorrections=GetUncGraphFromHistos(hRef,fhMCcorrectionsMin,fhMCcorrectionsMax);
  fgrMCcorrections->SetName("fgrMCcorrections");
  fgrMCcorrections->SetTitle("Associated track efficiency");

  fgrMCDefficiency=GetUncGraphFromHistos(hRef,fhMCDefficiencyMin,fhMCDefficiencyMax);
  fgrMCDefficiency->SetName("fgrMCDefficiency");
  fgrMCDefficiency->SetTitle("D meson efficiency");

  fgrSecContamination=GetUncGraphFromHistos(hRef,fhSecContaminationMin,fhSecContaminationMax);
  fgrSecContamination->SetName("fgrSecContamination");
  fgrSecContamination->SetTitle("Secondary contamination");

  fgrMCclosureTest=GetUncGraphFromHistos(hRef,fhMCclosureTestMin,fhMCclosureTestMax);
  fgrMCclosureTest->SetName("fgrMCclosureTest");
  fgrMCclosureTest->SetTitle("MC closure test");

  fgrBeautyFD=GetUncGraphFromHistos(hRef,fhBeautyFDmin,fhBeautyFDmax);
  fgrBeautyFD->SetName("fgrBeautyFD");
  fgrBeautyFD->SetTitle("Feed-down");

  fgrYieldUnc->SetLineColor(kBlue);
  fgrYieldUnc->SetLineWidth(2);
  fgrYieldUnc->SetFillStyle(0);
  fgrYieldUnc->SetFillColor(kBlue);
  fgrYieldUnc->SetMarkerColor(kBlue);
  fgrYieldUnc->SetMarkerStyle(20);


  fgrBackSubUnc->SetLineColor(kMagenta);
  fgrBackSubUnc->SetLineWidth(2);
  fgrBackSubUnc->SetFillStyle(0);
  fgrBackSubUnc->SetFillColor(kMagenta);
  fgrBackSubUnc->SetMarkerColor(kBlue);
  fgrBackSubUnc->SetMarkerStyle(20);


  fgrMCcorrections->SetLineColor(kGreen);
  fgrMCcorrections->SetLineWidth(2);
  fgrMCcorrections->SetFillStyle(0);
  fgrMCcorrections->SetFillColor(kGreen);
  fgrMCcorrections->SetMarkerColor(kGreen);
  fgrMCcorrections->SetMarkerStyle(22);

  fgrMCDefficiency->SetLineColor(kCyan);
  fgrMCDefficiency->SetLineWidth(2);
  fgrMCDefficiency->SetFillStyle(0);
  fgrMCDefficiency->SetFillColor(kCyan);
  fgrMCDefficiency->SetMarkerColor(kCyan);
  fgrMCDefficiency->SetMarkerStyle(22);

  fgrSecContamination->SetLineColor(kOrange);
  fgrSecContamination->SetLineWidth(2);
  fgrSecContamination->SetFillStyle(0);
  fgrSecContamination->SetFillColor(kOrange);
  fgrSecContamination->SetMarkerColor(kOrange);
  fgrSecContamination->SetMarkerStyle(22);

  fgrMCclosureTest->SetLineColor(kRed);
  fgrMCclosureTest->SetLineWidth(2);
  fgrMCclosureTest->SetFillStyle(0);
  fgrMCclosureTest->SetFillColor(kRed);
  fgrMCclosureTest->SetMarkerColor(kRed);
  fgrMCclosureTest->SetMarkerStyle(26);

  fgrBeautyFD->SetLineColor(kViolet);
  fgrBeautyFD->SetLineWidth(2);
  fgrBeautyFD->SetFillStyle(0);
  fgrBeautyFD->SetFillColor(kViolet);
  fgrBeautyFD->SetMarkerColor(kViolet);
  fgrBeautyFD->SetMarkerStyle(28);

  //  fgrTotalRel=GetUncGraphFromHistos(0x0,fhTotalMin,fhTotalMax);
  if(fhTotalMin){
    fgrTotalRel=GetUncGraphFromHistos(0x0,fhTotalMin,fhTotalMax);
    fgrTotalRel->SetLineColor(kBlack);
    fgrTotalRel->SetLineWidth(2);
    fgrTotalRel->SetFillStyle(0);
    //    fgrTotalRel->SetFillColor(kRed);
    fgrTotalRel->SetMarkerColor(kBlack);
    fgrTotalRel->SetMarkerStyle(26);

    fgrTotal=GetUncGraphFromHistos(hRef,fhTotalMin,fhTotalMax);
    fgrTotal->SetLineColor(kBlack);
    fgrTotal->SetLineWidth(2);
    fgrTotal->SetFillStyle(0);
    fgrTotal->SetFillColor(kRed);
    fgrTotal->SetMarkerColor(kBlack);
    fgrTotal->SetMarkerStyle(26);
  }
  
  if(fhTotalNonFDMin){
    fgrTotalNonFD=GetUncGraphFromHistos(hRef,fhTotalNonFDMin,fhTotalNonFDMax);
    fgrTotalNonFD->SetLineColor(kBlue);
    fgrTotalNonFD->SetLineWidth(2);
    fgrTotalNonFD->SetFillStyle(3005);
    fgrTotalNonFD->SetFillColor(kBlue);
    fgrTotalNonFD->SetMarkerColor(kBlue);
    fgrTotalNonFD->SetMarkerStyle(26);  
  }

  if(fhTotalNonFlatDPhiMin){
    fgrTotalNonFlatDPhiRel=GetUncGraphFromHistos(0x0,fhTotalNonFlatDPhiMin,fhTotalNonFlatDPhiMax);
    fgrTotalNonFlatDPhiRel->SetLineColor(kBlack);
    fgrTotalNonFlatDPhiRel->SetLineWidth(2);
    fgrTotalNonFlatDPhiRel->SetFillStyle(0);
    //    fgrTotalRel->SetFillColor(kRed);
    fgrTotalNonFlatDPhiRel->SetMarkerColor(kBlack);
    fgrTotalNonFlatDPhiRel->SetMarkerStyle(26);

    fgrTotalNonFlatDPhi=GetUncGraphFromHistos(hRef,fhTotalNonFlatDPhiMin,fhTotalNonFlatDPhiMax);
    fgrTotalNonFlatDPhi->SetLineColor(kBlack);
    fgrTotalNonFlatDPhi->SetLineWidth(2);
    fgrTotalNonFlatDPhi->SetFillStyle(3005);
    fgrTotalNonFlatDPhi->SetFillColor(kRed);
    fgrTotalNonFlatDPhi->SetMarkerColor(kBlack);
    fgrTotalNonFlatDPhi->SetMarkerStyle(26);  

    fgrTotalFlatDPhiRel=GetUncGraphFromHistos(0x0,fhtotFlatMin,fhtotFlatMax);
    fgrTotalFlatDPhiRel->SetLineColor(kBlack);
    fgrTotalFlatDPhiRel->SetLineWidth(2);
    fgrTotalFlatDPhiRel->SetFillStyle(0);
    //    fgrTotalRel->SetFillColor(kRed);
    fgrTotalFlatDPhiRel->SetMarkerColor(kBlack);
    fgrTotalFlatDPhiRel->SetMarkerStyle(26);

    fgrTotalFlatDPhi=GetUncGraphFromHistos(hRef,fhtotFlatMin,fhtotFlatMax);
    fgrTotalFlatDPhi->SetLineColor(kBlack);
    fgrTotalFlatDPhi->SetLineWidth(2);
    fgrTotalFlatDPhi->SetFillStyle(3005);
    fgrTotalFlatDPhi->SetFillColor(kBlack);
    fgrTotalFlatDPhi->SetMarkerColor(kBlack);
    fgrTotalFlatDPhi->SetMarkerStyle(26);  
  }

}


TCanvas* AliHFDhadronCorrSystUnc::BuildSystUncertaintyPlotVsDeltaPhi(TH1D *hCorrPlot,Int_t doInit){

  if(doInit!=0){
    BuildTotalUncHisto();
    BuildTotalNonFDUncHisto();
    BuildTotalNonFlatUncHisto();
    BuildGraphsUnc(hCorrPlot);
    BuildGraphsRelUnc();

  }

  // Easy canva with relative uncertainties
  TCanvas *cCanvaRelUnc=new TCanvas("cCanvaRelUnc","cCanvaRelUnc",700,700);
  cCanvaRelUnc->cd();
  TH2D *hDraw=new TH2D("hDraw","hDraw",32,-TMath::Pi()/2.,3./2.*TMath::Pi(),200,-2.,2.);
  hDraw->SetXTitle("#Delta#phi (rad)");
  hDraw->SetYTitle("Relative uncertainty");
  hDraw->Draw();
  
  
  fgrYieldUncRel->Draw("E2");
  fgrBackSubUncRel->Draw("E2");
  fgrMCcorrectionsRel->Draw("E2");
  fgrMCDefficiencyRel->Draw("E2");
  fgrSecContaminationRel->Draw("E2");
  fgrMCclosureTestRel->Draw("E2");
  fgrBeautyFDRel->Draw("E2");
  //  fgrTotalRel->Draw("E2");

  fhtotFlatMin->Draw("same");
  fhtotFlatMax->Draw("same");

  fhTotalMin->Draw("same");
  fhTotalMax->Draw("same");

  TCanvas *cCanvaFinalPlot=new TCanvas("cCanvaFinalPlot","cCanvaFinalPlot",700,700);
  cCanvaFinalPlot->cd();
  hCorrPlot->Draw();
  //  fgrYieldUnc->Draw("pE2");
  //  fgrBackSubUnc->Draw("pE2");
  //  fgrMCcorrections->Draw("pE2");
  //  fgrMCclosureTest->Draw("pE2");
  //  fgrBeautyFD->Draw("pE2");
  fgrTotal->Draw("E2");


  TCanvas *cCanvaFinalPlotFD=new TCanvas("cCanvaFinalPlotFD","cCanvaFinalPlotFD",700,700);
  cCanvaFinalPlotFD->cd();
  hCorrPlot->Draw();
  //  fgrYieldUnc->Draw("pE2");
  //  fgrBackSubUnc->Draw("pE2");
  //  fgrMCcorrections->Draw("pE2");
  //  fgrMCclosureTest->Draw("pE2");
  //  fgrBeautyFD->Draw("pE2");
  fgrBeautyFD->Draw("E2");
  fgrTotalNonFD->Draw("E2");
  fgrTotalNonFlatDPhi->Draw("E2");
  fgrTotalFlatDPhi->Draw("E2");

  return cCanvaFinalPlot;
}
  
  
TH1D* AliHFDhadronCorrSystUnc::GetVariedHisto(const TH1D *hIn,const TGraphAsymmErrors *gr,Int_t minmax){

  TH1D *hOut;
  if(minmax==0){
    hOut=(TH1D*)hIn->Clone(Form("%sVariedMin",hIn->GetName()));
  }
  else if(minmax==1){
    hOut=(TH1D*)hIn->Clone(Form("%sVariedMax",hIn->GetName()));
  }
  //  Int_t np=gr->GetN();
  Double_t *x,*y,*ely,*ehy;//*elx,*ehx,
  x=gr->GetX();
  y=gr->GetY();
  //  elx=gr->GetEXlow();
  // ehx=gr->GetEXhigh();
   ely=gr->GetEYlow();
  ehy=gr->GetEYhigh();

  for(Int_t jp=1;jp<=hIn->GetNbinsX();jp++){
    if(TMath::Abs(x[jp-1]-hIn->GetBinCenter(jp))>0.0001){
      Printf("Bin Mismatch: this method assumes that the graph has the points in the center of the histo bin centers");
      return 0x0;
    }
    if(TMath::Abs(y[jp-1]-hIn->GetBinContent(jp))>0.0001){
      Printf("Value Mismatch: this method relies on the fact that the graph central values are the same as those of the histo");
      return 0x0;
    }
    if(minmax==0){
      hOut->SetBinContent(jp,y[jp-1]-ely[jp-1]);
    }
    else if(minmax==1){
      hOut->SetBinContent(jp,y[jp-1]+ehy[jp-1]);
    }
    hOut->SetBinError(jp,hIn->GetBinError(jp));
  }

  return hOut;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////
/////
///// METHODS WITH UNCERTAINTIES: PP 2010, for kinematic cases approved after HP2013
/////
////////////////////////////////////////////////////////////////////////////////////////////////////////


// START FROM DPLUS FOR PT(ASSOC)>0.3
void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DplusLowPtAss03(){ Printf("TEMPORARY VALUES (PP 2010 ass 03)");
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }

  
  // MC CORRECTIONS ( associatate track efficiency):
  //  -5%  +10% for assoc track eff 
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }


  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    //    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DplusMidPtAss03(){ Printf("TEMPORARY VALUES (PP 2010 ass 03)");

  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS:  -5%  +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DplusHighPtAss03(){ Printf("TEMPORARY VALUES (PP 2010 ass 03)");
  
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }

  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS,  -5% 10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}



//////// HIGHER PT ASS THRESHOLDS

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DzeroLowPtAss05(){ 
  Printf("Setting syst for D0 pp 2010 3-5 0.5 thr");
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }

  
  // MC CORRECTIONS ( associatate track efficiency):
  //  -5%  +10% for assoc track eff 
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }


  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    //    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DzeroMidPtAss05(){ 
  Printf("Setting syst for D0 pp 2010 5-8 0.5 thr");

  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS:  -5%  +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DzeroHighPtAss05(){ 
  Printf("Setting syst for D0 pp 2010 8-16 0.5 thr");
  
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }

  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS,  -5% 10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}




//--------------------------------------------------
void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DstarLowPtAss05(){ 
  Printf("Setting uncertainties for Dstar pp 2010, 3<pt(D)<5, pt(assoc)>0.5 GeV/c ");
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS, -5%  10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,0.);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }


}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DstarMidPtAss05(){ 
  Printf("Setting uncertainties for Dstar pp 2010, 5<pt(D)<8, pt(assoc)>0.5 GeV/c ");
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS/ -5%  10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}



void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DstarHighPtAss05(){
  Printf("Setting uncertainties for Dstar pp 2010, 8<pt(D)<16, pt(assoc)>0.5 GeV/c ");  
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }
// check those values
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1); // check this one in particular
  }
  
  // MC CORRECTIONS   -5% +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }
  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }


}



void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DplusLowPtAss05(){ 
  Printf("Setting uncertainties for Dplus pp 2010, 3<pt(D)<5, pt(assoc)>0.5 GeV/c ");
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }

  
  // MC CORRECTIONS ( associatate track efficiency):
  //  -5%  +10% for assoc track eff 
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }


  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    //    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DplusMidPtAss05(){ Printf("TEMPORARY VALUES (PP 2010 ass 03)");
  Printf("Setting uncertainties for Dstar pp 2010, 5<pt(D)<8, pt(assoc)>0.5 GeV/c ");
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS:  -5%  +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DplusHighPtAss05(){ Printf("TEMPORARY VALUES (PP 2010 ass 03)");
  Printf("Setting uncertainties for Dstar pp 2010, 8<pt(D)<16, pt(assoc)>0.5 GeV/c ");  
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }

  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS,  -5% 10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}



// pt(assoc)> 1 GeV/c
void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DzeroLowPtAss1(){
  Printf("Setting uncertainties for Dzero pp 2010, 3<pt(D)<5, pt(assoc)>1 GeV/c ");
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }

  
  // MC CORRECTIONS ( associatate track efficiency):
  //  -5%  +10% for assoc track eff 
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }


  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    //    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DzeroMidPtAss1(){
  Printf("Setting uncertainties for Dzero pp 2010, 5<pt(D)<8, pt(assoc)>1 GeV/c ");
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS:  -5%  +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DzeroHighPtAss1(){
  Printf("Setting uncertainties for Dzero pp 2010, 8<pt(D)<16, pt(assoc)>1 GeV/c ");  
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }

  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS,  -5% 10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}




//--------------------------------------------------
void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DstarLowPtAss1(){ Printf("TEMPORARY VALUES (PP 2010 ass 03)");
  Printf("Setting uncertainties for Dstar pp 2010, 3<pt(D)<5, pt(assoc)>1 GeV/c ");
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS, -5%  10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }


}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DstarMidPtAss1(){
  Printf("Setting uncertainties for Dstar pp 2010, 5<pt(D)<8, pt(assoc)>1 GeV/c ");
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS/ -5%  10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,0.);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}



void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DstarHighPtAss1(){ 
  Printf("Setting uncertainties for Dstar pp 2010, 8<pt(D)<16, pt(assoc)>1 GeV/c ");  
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
  
      fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS   -5% +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }
  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,0.);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }


}



void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DplusLowPtAss1(){
  Printf("Setting uncertainties for Dplus pp 2010, 3<pt(D)<5, pt(assoc)>1 GeV/c ");
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }

  
  // MC CORRECTIONS ( associatate track efficiency):
  //  -5%  +10% for assoc track eff 
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }


  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    //    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DplusMidPtAss1(){ 
  Printf("Setting uncertainties for Dplus pp 2010, 5<pt(D)<8, pt(assoc)>1 GeV/c ");
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS:  -5%  +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPP2010DplusHighPtAss1(){
  Printf("Setting uncertainties for Dplus pp 2010, 8<pt(D)<16, pt(assoc)>1 GeV/c ");  
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }

  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS,  -5% 10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.05);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.10);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.05);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.05);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.0);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}






////////////////////////////////////////////////////////////////////////////////////////////////////////
/////
///// METHODS WITH UNCERTAINTIES: pPb 2013
/////
////////////////////////////////////////////////////////////////////////////////////////////////////////


// pt assoc > 0.3 GeV/c

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DzeroLowPtAss03(){ 
  Printf("Setting uncertainties for Dzero pPb 2013, 3<pt(D)<5, pt(assoc)>0.3 GeV/c ");  
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }

  
  // MC CORRECTIONS ( associatate track efficiency):
  //  -5%  +10% for assoc track eff 
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }


  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    //    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DzeroMidPtAss03(){ 
  Printf("Setting uncertainties for Dzero pPb 2013, 5<pt(D)<8, pt(assoc)>0.3 GeV/c ");  
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS:  -5%  +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DzeroHighPtAss03(){ 
  Printf("Setting uncertainties for Dzero pPb 2013, 8<pt(D)<16, pt(assoc)>0.3 GeV/c ");    
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }

  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS,  -5% 10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}




//--------------------------------------------------
void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DstarLowPtAss03(){ 
  Printf("Setting uncertainties for Dstar pPb 2013, 3<pt(D)<5, pt(assoc)>0.3 GeV/c ");  
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS, -5%  10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }


}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DstarMidPtAss03(){ 
  Printf("Setting uncertainties for Dstar pPb 2013, 5<pt(D)<8, pt(assoc)>0.3 GeV/c ");  
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS/ -5%  10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}



void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DstarHighPtAss03(){ 
  Printf("Setting uncertainties for Dstar pPb 2013, 8<pt(D)<16, pt(assoc)>0.3 GeV/c ");    
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS   -5% +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }
  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }


}




void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DplusLowPtAss03(){
  Printf("Setting uncertainties for Dplus pPb 2013, 3<pt(D)<5, pt(assoc)>0.3 GeV/c ");    
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }

  
  // MC CORRECTIONS ( associatate track efficiency):
  //  -5%  +10% for assoc track eff 
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.1);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.1);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }


  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    //    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DplusMidPtAss03(){
  Printf("Setting uncertainties for Dplus pPb 2013, 5<pt(D)<8, pt(assoc)>0.3 GeV/c ");    
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS:  -5%  +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.1);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.1);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DplusHighPtAss03(){ 
  Printf("Setting uncertainties for Dplus pPb 2013, 8<pt(D)<16, pt(assoc)>0.3 GeV/c ");    
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore03";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }

  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS,  -5% 10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.1);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.1);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}



//////// HIGHER PT ASS THRESHOLDS

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DzeroLowPtAss05(){ 
  Printf("Setting uncertainties for Dzero pPb 2013, 3<pt(D)<5, pt(assoc)>0.5 GeV/c ");    
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }

  
  // MC CORRECTIONS ( associatate track efficiency):
  //  -5%  +10% for assoc track eff 
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }


  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    //    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DzeroMidPtAss05(){ 
  Printf("Setting uncertainties for Dzero pPb 2013, 5<pt(D)<8, pt(assoc)>0.5 GeV/c ");    
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS:  -5%  +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DzeroHighPtAss05(){ 
  Printf("Setting uncertainties for Dzero pPb 2013, 8<pt(D)<16, pt(assoc)>0.5 GeV/c ");      
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }

  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS,  -5% 10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}




//--------------------------------------------------
void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DstarLowPtAss05(){ 
  Printf("Setting uncertainties for Dstar pPb 2013, 3<pt(D)<5, pt(assoc)>0.5 GeV/c ");      
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS, -5%  10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }


}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DstarMidPtAss05(){ 
  Printf("Setting uncertainties for Dstar pPb 2013, 5<pt(D)<8, pt(assoc)>0.5 GeV/c ");      
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS/ -5%  10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}



void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DstarHighPtAss05(){ 
  Printf("Setting uncertainties for Dstar pPb 2013, 8<pt(D)<16, pt(assoc)>0.5 GeV/c ");        
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS   -5% +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }
  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }


}



void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DplusLowPtAss05(){ 
  Printf("Setting uncertainties for Dplus pPb 2013, 3<pt(D)<5, pt(assoc)>0.5 GeV/c ");        
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }

  
  // MC CORRECTIONS ( associatate track efficiency):
  //  -5%  +10% for assoc track eff 
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.1);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.1);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }


  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    //    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DplusMidPtAss05(){ 
  Printf("Setting uncertainties for Dplus pPb 2013, 5<pt(D)<8, pt(assoc)>0.5 GeV/c ");        
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS:  -5%  +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.1);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.1);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DplusHighPtAss05(){ 
  Printf("Setting uncertainties for Dplus pPb 2013, 8<pt(D)<16, pt(assoc)>0.5 GeV/c ");          
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore05";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }

  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS,  -5% 10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.1);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.1);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}



// pt(assoc)> 1 GeV/c
void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DzeroLowPtAss1(){
  Printf("Setting uncertainties for Dzero pPb 2013, 3<pt(D)<5, pt(assoc)>1 GeV/c ");          
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }

  
  // MC CORRECTIONS ( associatate track efficiency):
  //  -5%  +10% for assoc track eff 
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }


  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    //    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DzeroMidPtAss1(){
  Printf("Setting uncertainties for Dzero pPb 2013, 5<pt(D)<8, pt(assoc)>1 GeV/c ");          
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS:  -5%  +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DzeroHighPtAss1(){ 
  Printf("Setting uncertainties for Dzero pPb 2013, 8<pt(D)<16, pt(assoc)>1 GeV/c ");            
  fmeson=AliHFCorrelationUtils::kDzero;
  fstrmeson="Dzero";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }

  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.05);
  }
  
  // MC CORRECTIONS,  -5% 10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}




//--------------------------------------------------
void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DstarLowPtAss1(){ 
 Printf("Setting uncertainties for Dstar pPb 2013, 3<pt(D)<5, pt(assoc)>1 GeV/c ");            
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS, -5%  10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }


}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DstarMidPtAss1(){ 
 Printf("Setting uncertainties for Dstar pPb 2013, 5<pt(D)<8, pt(assoc)>1 GeV/c ");            
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS/ -5%  10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}



void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DstarHighPtAss1(){ 
  Printf("Setting uncertainties for Dstar pPb 2013, 8<pt(D)<16, pt(assoc)>1 GeV/c ");            
  fmeson=AliHFCorrelationUtils::kDstar;
  fstrmeson="Dstar";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.05);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS   -5% +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }
  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.05);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.05);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }


}



void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DplusLowPtAss1(){ 
  Printf("Setting uncertainties for Dplus pPb 2013, 3<pt(D)<5, pt(assoc)>1 GeV/c ");            
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt3to5";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }

  
  // MC CORRECTIONS ( associatate track efficiency):
  //  -5%  +10% for assoc track eff 
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }

  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.1);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.1);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }


  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    //    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}

void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DplusMidPtAss1(){ 
  Printf("Setting uncertainties for Dplus pPb 2013, 5<pt(D)<8, pt(assoc)>1 GeV/c ");            
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt5to8";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }
  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS:  -5%  +10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.1);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.1);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }
  
}


void AliHFDhadronCorrSystUnc::InitStandardUncertaintiesPPb2013DplusHighPtAss1(){ 
  Printf("Setting uncertainties for Dplus pPb 2013, 8<pt(D)<16, pt(assoc)>1 GeV/c ");            
  fmeson=AliHFCorrelationUtils::kDplus;
  fstrmeson="Dplus";
  fstrptAss="ptAsMore1";
  fstrptD="Dpt8to16";
  if(!fhDeltaPhiTemplate){
    fhDeltaPhiTemplate=new TH1D("fhDeltaPhiTemplate","fhDeltaPhiTemplate",32,-TMath::Pi()/2.,3./2.*TMath::Pi());
  }

  Double_t x;
  // D MESON YIELD EXTRACTION (->NORMALIZATION): relative uncertainty is constant
  fhYieldExtraction=(TH1D*)fhDeltaPhiTemplate->Clone("fhYieldExtraction");
  for(Int_t j=1;j<=fhYieldExtraction->GetNbinsX();j++){
    fhYieldExtraction->SetBinContent(j,0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMin");
  for(Int_t j=1;j<=fhBackSubtractionMin->GetNbinsX();j++){
    fhBackSubtractionMin->SetBinContent(j,-0.1);
  }

  // Background D MESON candidate subtraction (side-band variations, etc.)
  fhBackSubtractionMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBackSubtractionMax");
  for(Int_t j=1;j<=fhBackSubtractionMax->GetNbinsX();j++){
    fhBackSubtractionMax->SetBinContent(j,0.1);
  }
  
  // MC CORRECTIONS,  -5% 10% for assoc track eff
  fhMCcorrectionsMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMin");
  for(Int_t j=1;j<=fhMCcorrectionsMin->GetNbinsX();j++){
    fhMCcorrectionsMin->SetBinContent(j,-0.04);
  }

  fhMCcorrectionsMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCcorrectionsMax");
  for(Int_t j=1;j<=fhMCcorrectionsMax->GetNbinsX();j++){
    fhMCcorrectionsMax->SetBinContent(j,0.04);
  }


  // MC D EFF CORRECTION
  fhMCDefficiencyMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMin");
  for(Int_t j=1;j<=fhMCDefficiencyMin->GetNbinsX();j++){
    fhMCDefficiencyMin->SetBinContent(j,-0.1);
  }

  fhMCDefficiencyMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCDefficiencyMax");
  for(Int_t j=1;j<=fhMCDefficiencyMax->GetNbinsX();j++){
    fhMCDefficiencyMax->SetBinContent(j,0.1);
  }


  // Contamination from secondary tracks
  fhSecContaminationMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMin");
  for(Int_t j=1;j<=fhSecContaminationMin->GetNbinsX();j++){
    fhSecContaminationMin->SetBinContent(j,-0.035);
  }

  fhSecContaminationMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhSecContaminationMax");
  for(Int_t j=1;j<=fhSecContaminationMax->GetNbinsX();j++){
    fhSecContaminationMax->SetBinContent(j,0.035);
  }

  // MC CLOSURETEST (D meson efficiency)
  fhMCclosureTestMin=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMin");
  for(Int_t j=1;j<=fhMCclosureTestMin->GetNbinsX();j++){
    x=fhMCclosureTestMin->GetBinLowEdge(j);
    fhMCclosureTestMin->SetBinContent(j,-0.02);
    
    if(-0.4<x&&x<-0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
    else if(-0.2<x&&x<-0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    else if(-0.1<x&&x<0.1){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.02);      
    }
    else if(0.1<x&&x<0.2){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.015);      
    }
    if(0.2<x&&x<0.4){    
      fhMCclosureTestMin->SetBinContent(j,fhMCclosureTestMin->GetBinContent(j)-0.01);      
    }
  }

  fhMCclosureTestMax=(TH1D*)fhDeltaPhiTemplate->Clone("fhMCclosureTestMax");
  for(Int_t j=1;j<=fhMCclosureTestMax->GetNbinsX();j++){
    x=fhMCclosureTestMax->GetBinLowEdge(j);
    fhMCclosureTestMax->SetBinContent(j,0.02);
    
    //     if(-0.4<x&&x<-0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.2<x&&x<-0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     else if(-0.1<x&&x<0.1){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.08);      
    //     }
    //     else if(0.1<x&&x<0.2){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.06);      
    //     }
    //     if(0.2<x&&x<0.4){    
    //       fhMCclosureTestMax->SetBinContent(j,fhMCclosureTestMax->GetBinContent(j)-0.04);      
    //     }
    
  }
  
  // Feed-down 

  fhBeautyFDmin=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmin");
  for(Int_t j=1;j<=fhBeautyFDmin->GetNbinsX();j++){
    x=fhBeautyFDmin->GetBinLowEdge(j);
    fhBeautyFDmin->SetBinContent(j,-0.05);
    
  //   if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmin->SetBinContent(j,fhBeautyFDmin->GetBinContent(j)-0.04);      
//     }
  }

  fhBeautyFDmax=(TH1D*)fhDeltaPhiTemplate->Clone("fhBeautyFDmax");
  for(Int_t j=1;j<=fhBeautyFDmax->GetNbinsX();j++){
    x=fhBeautyFDmax->GetBinLowEdge(j);
    fhBeautyFDmax->SetBinContent(j,0.03);
   
//     if(-0.4<x&&x<-0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.2<x&&x<-0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     else if(-0.1<x&&x<0.1){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.08);      
//     }
//     else if(0.1<x&&x<0.2){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.06);      
//     }
//     if(0.2<x&&x<0.4){    
//       fhBeautyFDmax->SetBinContent(j,fhBeautyFDmax->GetBinContent(j)+0.04);      
//     } 
    
  }

}



// this comment serves no purpose
