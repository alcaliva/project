#if !defined(__CINT__) || defined(__MAKECINT__)
#endif


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
