#if !defined(__CINT__) || defined(__MAKECINT__)
#endif

#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TGraph.h"
#include "TFile.h"
#include "TList.h"



//________________________________________________________________________________________________________________________________________
void code1 ()  {
    
    //Get Input Files
    TFile *file_antip = TFile::Open ("output/corr_yield_antiprotons.root");
    TFile *file_antid = TFile::Open ("output/corr_yield_antideuterons.root");
    
    //Get Input Spectra
    TH1F *antip_jet = (TH1F*) file_antip->Get("corr_yield_jetminusue_antip");
    TH1F *antip_ue  = (TH1F*) file_antip->Get("corr_yield_ue_antip");
    TH1F *antid_jet = (TH1F*) file_antid->Get("corr_yield_jetminusue_antid");
    TH1F *antid_ue  = (TH1F*) file_antid->Get("corr_yield_ue_antid");
    
    //Get Parameters
    TFile *inputParam = TFile::Open ("output/projections.root");
    TH1F *param = (TH1F*)inputParam->Get ("param");
    double Rjet   = param->GetBinContent(1);
    double ptLead = param->GetBinContent(2);
    double ptJet  = param->GetBinContent(3);
    
    //Deuteron Spectra in pt/A
    TH1F *antid_jet_ptoverA = (TH1F*) antip_jet->Clone("antid_jet_ptoverA");
    TH1F *antid_ue_ptoverA  = (TH1F*) antip_jet->Clone("antid_ue_ptoverA");
    get_spectrum_in_ptoverA (antid_jet,antid_jet_ptoverA);
    get_spectrum_in_ptoverA (antid_ue,antid_ue_ptoverA);
    
    //d/p
    TH1F *d_over_p_jet = (TH1F*) antid_jet_ptoverA ->Clone("d_over_p_jet");
    TH1F *d_over_p_ue  = (TH1F*) antid_ue_ptoverA ->Clone("d_over_p_ue");
    d_over_p_jet -> Divide (antip_jet);
    d_over_p_ue  -> Divide (antip_ue);
    style (d_over_p_jet,"#it{p}_{T}/#it{A} (GeV/#it{c})","d / p",20,2);
    style (d_over_p_ue,"#it{p}_{T}/#it{A} (GeV/#it{c})","d / p",21,4);
    
    //plot
    plot (d_over_p_jet,d_over_p_ue,Rjet,ptLead,ptJet);
}
//_______________________________________________________________________________________________________________________________________
void style (TH1F *histogram, const char *titleXaxis, const char *titleYaxis, Int_t marker, Int_t color)  {
    
    histogram -> SetStats(false);
    histogram -> GetXaxis() -> SetTitle(titleXaxis);
    histogram -> SetTitleSize(0.055,"x");
    histogram -> SetLabelSize(0.055,"x");
    histogram -> GetXaxis() -> SetTitleOffset(1.1);
    histogram -> GetYaxis() -> SetTitle(titleYaxis);
    histogram -> SetTitleSize(0.055,"y");
    histogram -> SetLabelSize(0.055,"y");
    histogram -> GetYaxis() -> SetTitleOffset(1.5);
    histogram -> GetYaxis() -> CenterTitle();
    histogram -> SetLineStyle(1);
    histogram -> SetLineColor(color);
    histogram -> SetMarkerColor(color);
    histogram -> SetMarkerStyle(marker);
    histogram -> SetMarkerSize(1.2);
    histogram -> SetLineWidth(2);
}
//________________________________________________________________________________________________________________________________________
void plot  (TH1F *jet, TH1F *ue,double Rjet,double ptLead,double ptJet)  {
    
    jet->GetYaxis()->SetRangeUser(0,0.06);
    
    //Legend
    TLegend *legend = new TLegend(0.22,0.62,0.5,0.75,"");
    legend -> SetFillColor(0);
    legend -> SetTextSize(0.05);
    legend -> SetTextFont(42);
    legend -> SetTextColor(1);
    legend -> SetBorderSize(0);
    legend -> AddEntry (jet,"JET","P");
    legend -> AddEntry (ue,"UE","P");

    
    //Plot
    TCanvas *c = new TCanvas (Form("cdp%s",jet->GetName()),"",900,700);
    c -> cd();
    c -> SetTickx(1);
    c -> SetTicky(1);
    c -> SetLeftMargin(0.2);
    c -> SetRightMargin(0.06);
    c -> SetTopMargin(0.11);
    c -> SetBottomMargin(0.14);
    jet -> Draw("E");
    ue ->Draw("Esame");
    legend -> Draw();
    text(Rjet,ptLead,ptJet) -> Draw();
}
//_______________________________________________________________________________________________________________________________________
TPaveText *text (double Rjet,double ptLead,double ptJet)  {
    
    //Text
    TPaveText *text = new TPaveText(0.5,0.58,0.85,0.86, "NDC");
    text -> SetTextSize(0.05);
    text -> SetTextFont(42);
    text -> SetTextColor(1);
    text -> SetFillColor(0);
    text -> SetBorderSize(0);
    text -> AddText ("ALICE, pp #sqrt{#it{s}} = 13.6 TeV");
    text -> AddText (Form("#it{p}_{T}^{lead} > %.1f GeV/#it{c}",ptLead));
    text -> AddText (Form("#it{p}_{T}^{jet} > %.1f GeV/#it{c}",ptJet));
    text -> AddText (Form("R_{jet} < %.1f",Rjet));

    return text;
}
//_______________________________________________________________________________________________________________________________________
void get_spectrum_in_ptoverA (TH1F *spectrum_pt, TH1F *spectrum_pt_overA)  {
    
    for (Int_t i=1 ; i<=spectrum_pt->GetNbinsX() ; i++)  {
        
        Double_t value = spectrum_pt->GetBinContent(i);
        Double_t error = spectrum_pt->GetBinError(i);

        spectrum_pt_overA->SetBinContent(i,value);
        spectrum_pt_overA->SetBinError(i,error);
    }
}
//_______________________________________________________________________________________________________________________________________
