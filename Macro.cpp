// no includes as the compiled mode as it gives problem with the computer

TFile *file = new TFile("histograms.root", "READ");
TH1D *h0 = (TH1D *)file->Get("TypeOfParticles");
TH1D *h1 = (TH1D *)file->Get("TethaDistribution");
TH1D *h2 = (TH1D *)file->Get("PhiDistribution");
TH1D *h3 = (TH1D *)file->Get("Impulse");
TH1D *h4 = (TH1D *)file->Get("TrasverseImpulse");
TH1D *h5 = (TH1D *)file->Get("Energy");
TH1D *h6 = (TH1D *)file->Get("InvariantMass");
TH1D *h7 = (TH1D *)file->Get("InvMassDiscordCharge");
TH1D *h8 = (TH1D *)file->Get("InvMassConcordCharge");
TH1D *h9 = (TH1D *)file->Get("InvMassPionKaonDiscordCharge");
TH1D *h10 = (TH1D *)file->Get("InvMassPionKaonConcordCharge");
TH1D *h11 = (TH1D *)file->Get("InvMassOfDecayedParticles");

TH1D *diff1 = new TH1D("diff1", "Difference of all particles", 160, 0, 2);
TH1D *diff2 = new TH1D("diff2", "Difference of pions and kaons", 160, 0, 2);

// defined here to avoid the default canvas
TCanvas *Canvas1 =
    new TCanvas("Canvas1", "Main Informations", 200, 10, 800, 600);
TCanvas *Canvas2 = new TCanvas("Canvas2", "K* histograms", 200, 10, 800, 600);

void SetStyle() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptFit(1111);
}

void ControlEntries() {
  std::cout << "CONTROL ENTRIES IN HISTOGRAMS" << '\n';
  std::cout << "Number of entries in " << h0->GetName() << ": "
            << h0->GetEntries() << '\n';
  std::cout << "Number of entries in " << h1->GetName() << ": "
            << h1->GetEntries() << '\n';
  std::cout << "Number of entries in " << h2->GetName() << ": "
            << h2->GetEntries() << '\n';
  std::cout << "Number of entries in " << h3->GetName() << ": "
            << h3->GetEntries() << '\n';
  std::cout << "Number of entries in " << h4->GetName() << ": "
            << h4->GetEntries() << '\n';
  std::cout << "Number of entries in " << h5->GetName() << ": "
            << h5->GetEntries() << '\n';
  std::cout << "Number of entries in " << h6->GetName() << ": "
            << h6->GetEntries() << '\n';
  std::cout << "Number of entries in " << h7->GetName() << ": "
            << h7->GetEntries() << '\n';
  std::cout << "Number of entries in " << h8->GetName() << ": "
            << h8->GetEntries() << '\n';
  std::cout << "Number of entries in " << h9->GetName() << ": "
            << h9->GetEntries() << '\n';
  std::cout << "Number of entries in " << h10->GetName() << ": "
            << h10->GetEntries() << '\n';
  std::cout << "Number of entries in " << h11->GetName() << ": "
            << h11->GetEntries() << '\n';
  std::cout << '\n' << '\n' << '\n';
}

void ControlProportions() {
  std::cout << "PROPORTIONS OF PARTICLES GENERATED" << '\n';
  for (int i = 1; i < 8; ++i) {
    std::cout << "Content of bin " << i << " is: " << h0->GetBinContent(i)
              << " ± " << h0->GetBinError(i) << '\n'
              << "which is (" << h0->GetBinContent(i) / h0->GetEntries()
              << " ± "
              << (h0->GetBinError(i) / h0->GetBinContent(i)) *
                     (h0->GetBinContent(i) / h0->GetEntries())
              << ")%" << '\n';
  }
  std::cout << '\n' << '\n' << '\n';
}

void FitAngDistr() {
  std::cout << '\n' << "CHI SQUARE OF THE ANGULAR DISTRIBUTIONS" << '\n';
  h1->Fit("pol0", "Q"); // quiet mode in order to have on screen only the stats
                        // needed for the report (did the same with all fits)
  TF1 *fitTetha = h1->GetFunction("pol0");
  fitTetha->SetLineColor(kRed);
  std::cout << "POLAR ANGLE:" << '\n'
            << "Parameter 0: " << fitTetha->GetParameter(0) << " ± "
            << fitTetha->GetParError(0) << '\n'
            << "Chi Sqaure of the tetha distribution: "
            << fitTetha->GetChisquare() << '\n'
            << "DOF of the Chi Square test: " << fitTetha->GetNDF() << '\n'
            << "Chi Square over DOF: "
            << fitTetha->GetChisquare() / fitTetha->GetNDF() << '\n';

  h2->Fit("pol0", "Q");
  TF1 *fitPhi = h2->GetFunction("pol0");
  fitPhi->SetLineColor(kRed);
  std::cout << "AZIMUTHAL ANGLE:" << '\n'
            << "Parameter 0: " << fitPhi->GetParameter(0) << " ± "
            << fitPhi->GetParError(0) << '\n'
            << "Chi Square of the phi distribution: " << fitPhi->GetChisquare()
            << '\n'
            << "DOF of the Chi Square test: " << fitPhi->GetNDF() << '\n'
            << "Chi Square over DOF: "
            << fitPhi->GetChisquare() / fitPhi->GetNDF() << '\n';
  std::cout << '\n' << '\n' << '\n';
}

void FitImpulse() {
  std::cout << '\n' << "CHI SQUARE OF THE IMPULSE DISTRIBUTION" << '\n';
  h3->Fit("expo", "Q");
  TF1 *fitImpulse = h3->GetFunction("expo");
  fitImpulse->SetLineColor(kRed);
  fitImpulse->SetLineStyle(kDashed);
  fitImpulse->SetLineWidth(2);
  std::cout << "IMPULSE:" << '\n'
            << "Mean: " << fitImpulse->GetParameter(1) << " ± "
            << fitImpulse->GetParError(1) << '\n'
            << "Chi Square of the impulse distribution: "
            << fitImpulse->GetChisquare() << '\n'
            << "DOF of the Chi Square test: " << fitImpulse->GetNDF() << '\n'
            << "Chi Square over DOF: "
            << fitImpulse->GetChisquare() / fitImpulse->GetNDF() << '\n';
  std::cout << '\n' << '\n' << '\n';
}

// Two different scopes for the subtraction in order to avoid problems linked
// with the call of Sumw2() in the same scope

void InvariantMassAnalisys1() {
  diff1->Sumw2();
  diff1->Add(h7, h8, 1, -1);
  diff1->SetEntries(diff1->Integral());
}

void InvariantMassAnalisys2() {
  diff2->Sumw2();
  diff2->Add(h9, h10, 1, -1);
  diff2->SetEntries(diff2->Integral());
}

void Cosmetics() {

  // Type of particles
  h0->SetTitle("Types of particles");
  h0->SetFillColor(kBlue);
  h0->SetLineColor(kBlack);
  h0->GetYaxis()->SetTitle("Occurrences");
  h0->GetXaxis()->SetTitle("fIParticle");
  h0->GetXaxis()->SetTitleSize(0.04);
  h0->GetYaxis()->SetTitleSize(0.02);

  // Angular Distribution
  h1->SetLineColor(kBlack);
  h1->GetXaxis()->SetTitle("Tetha");
  h1->GetYaxis()->SetTitle("Occurrences");
  h1->GetXaxis()->SetTitleSize(0.04);
  h1->GetYaxis()->SetTitleSize(0.02);

  h2->SetLineColor(kBlack);
  h2->GetXaxis()->SetTitle("Phi");
  h2->GetYaxis()->SetTitle("Occurrences");
  h2->GetXaxis()->SetTitleSize(0.04);
  h2->GetYaxis()->SetTitleSize(0.02);

  // Impulse
  h3->SetFillColor(kBlue);
  h3->SetLineColor(kBlack);
  h3->GetYaxis()->SetTitle("Occurrences");
  h3->GetXaxis()->SetTitle("Impulse (GeV)");
  h3->GetXaxis()->SetTitleSize(0.04);
  h3->GetYaxis()->SetTitleSize(0.02);

  // InvMassOfDecayedParticles
  h11->SetFillColor(kBlue);
  h11->SetLineColor(kBlack);
  h11->GetYaxis()->SetTitle("Occurrences");
  h11->GetXaxis()->SetTitle("Invariant mass (GeV)");
  h11->GetXaxis()->SetTitleSize(0.04);
  h11->GetYaxis()->SetTitleSize(0.02);

  // diff1 cosmetics
  diff1->SetFillColor(kBlue);
  diff1->SetLineColor(kBlack);
  diff1->GetXaxis()->SetTitle("Invariant mass (GeV)");
  diff1->GetYaxis()->SetTitle("Occurrences");
  diff1->GetXaxis()->SetTitleSize(0.04);
  diff1->GetYaxis()->SetTitleSize(0.02);

  // diff2 cosmetics
  diff2->SetFillColor(kBlue);
  diff2->SetLineColor(kBlack);
  diff2->GetXaxis()->SetTitle("Invariant mass (GeV)");
  diff2->GetYaxis()->SetTitle("Occurrences");
  diff2->GetXaxis()->SetTitleSize(0.04);
  diff2->GetYaxis()->SetTitleSize(0.02);
}

void Canvases() {
  Canvas1->Divide(2, 2);
  Canvas1->cd(1);
  h0->DrawCopy("", ""); // to delete "_copy" from the stat box name
  Canvas1->cd(2);
  h1->DrawCopy("", "");
  Canvas1->cd(3);
  h2->DrawCopy("", "");
  Canvas1->cd(4);
  h3->DrawCopy("", "");

  Canvas1->Print("MainInformations.pdf");
  Canvas1->Print("MainInformations.C");
  Canvas1->Print("MainInformations.root");
  std::cout << '\n' << '\n';

  Canvas2
      ->Clear(); // otherwise i'll have the impulse histogram in the background
  Canvas2->Divide(1, 3);
  Canvas2->cd(1);
  h11->Fit("gaus", "Q", "", 0.7, 1.1);
  TF1 *fitKStar = h11->GetFunction("gaus");
  fitKStar->SetParName(0, "Amplitude");
  fitKStar->SetLineColor(kRed);
  std::cout << "INVARIANT MASS REAL K*" << '\n'
            << "Mean of fit: " << fitKStar->GetParameter(1) << " ± "
            << fitKStar->GetParError(1) << '\n'
            << "RMS of fit: " << fitKStar->GetParameter(2) << " ± "
            << fitKStar->GetParError(2) << '\n'
            << "Amplitude of fit: " << fitKStar->GetParameter(0) << " ± "
            << fitKStar->GetParError(0) << '\n'
            << "Chi Suqare over DOF: "
            << fitKStar->GetChisquare() / fitKStar->GetNDF() << '\n'
            << '\n';
  h11->DrawCopy("", "");

  Canvas2->cd(2);
  diff1->Fit("gaus", "Q");
  TF1 *fitDiff1 = diff1->GetFunction("gaus");
  fitDiff1->SetParName(0, "Amplitude");
  std::cout << "INVARIANT MASS OBTAINED SUBTRACTING PARTICLES WITH CONCORD AND "
               "DISCORD CHARGE"
            << '\n'
            << "Mean of fit: " << fitDiff1->GetParameter(1) << " ± "
            << fitDiff1->GetParError(1) << '\n'
            << "RMS of fit: " << fitDiff1->GetParameter(2) << " ± "
            << fitDiff1->GetParError(2) << '\n'
            << "Amplitude of fit: " << fitDiff1->GetParameter(0) << " ± "
            << fitDiff1->GetParError(0) << '\n'
            << "Chi Suqare over DOF: "
            << fitDiff1->GetChisquare() / fitDiff1->GetNDF() << '\n'
            << '\n';
  fitDiff1->SetLineColor(kRed);
  diff1->DrawCopy("", "");
  diff1->DrawCopy("HIST SAMES", ""); // for statistics box and cosmetics
  fitDiff1->DrawCopy(
      "SAME"); // in order to do not have the fit in the background

  Canvas2->cd(3);
  diff2->Fit("gaus", "Q");
  TF1 *fitDiff2 = diff2->GetFunction("gaus");
  fitDiff2->SetParName(0, "Amplitude");
  std::cout << "INVARIANT MASS OBTAINED SUBTRACTING PIONS AND KAONS WITH "
               "CONCORD AND DISCORD CHARGE"
            << '\n'
            << "Mean of fit: " << fitDiff2->GetParameter(1) << " ± "
            << fitDiff2->GetParError(1) << '\n'
            << "RMS of fit: " << fitDiff2->GetParameter(2) << " ± "
            << fitDiff2->GetParError(2) << '\n'
            << "Amplitude of fit: " << fitDiff2->GetParameter(0) << " ± "
            << fitDiff2->GetParError(0) << '\n'
            << "Chi Suqare over DOF: "
            << fitDiff2->GetChisquare() / fitDiff2->GetNDF() << '\n'
            << '\n';
  fitDiff2->SetLineColor(kRed);
  diff2->DrawCopy("", "");
  diff2->DrawCopy("HIST SAMES", ""); // for statistics box and cosmetics
  fitDiff2->DrawCopy(
      "SAME"); // in order to do not have the fit in the background
  Canvas2->Print("K*Histograms.pdf");
  Canvas2->Print("K*Histograms.C");
  Canvas2->Print("K*Histograms.root");
}

void CloseFile() { file->Close(); }

void DoEverything() {
  SetStyle();
  ControlEntries();
  ControlProportions();
  FitAngDistr();
  FitImpulse();
  InvariantMassAnalisys1();
  InvariantMassAnalisys2();
  Cosmetics();
  Canvases();
  CloseFile();
}
