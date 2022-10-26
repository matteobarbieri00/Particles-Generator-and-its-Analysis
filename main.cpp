//
//  main.cpp
//  laboratorio_c++_root
//
//  Created by Matteo Barbieri on 16/10/2020.
//

#include <cmath>
#include <iostream>
#include <string>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TMath.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TStyle.h"

int main() {
  // filling the fParticletype
  Particle::AddParticleType("pion+", 0.13957, 1, 0); // GeV/c2
  Particle::AddParticleType("pion-", 0.13957, -1, 0);
  Particle::AddParticleType("kaon+", 0.49367, 1, 0);
  Particle::AddParticleType("kaon-", 0.49367, -1, 0);
  Particle::AddParticleType("proton+", 0.93827, 1, 0);
  Particle::AddParticleType("proton-", 0.93827, -1, 0);
  Particle::AddParticleType("K*", 0.89166, 0, 0.050);
  Particle::PrintfParticleType();

  // setting the seed before the generation
  gRandom->SetSeed();

  // histograms
  TH1I *TypeOfParticles =
      new TH1I("TypeOfParticles", "Type of particles generated", 7, 0, 7);
  TH1D *TethaDistribution =
      new TH1D("TethaDistribution", "Tetha Distribution", 1000, 0, TMath::Pi());
  TH1D *PhiDistribution =
      new TH1D("PhiDistribution", "Phi Distribution", 1000, 0, 2 * TMath::Pi());
  TH1D *Impulse = new TH1D("Impulse", "Impulse", 80, 0, 2); // 100 10
  TH1D *TrasverseImpulse =
      new TH1D("TrasverseImpulse", "Trasverse Impulse", 80, 0, 2); // 100 10
  TH1D *Energy = new TH1D("Energy", "Energy", 80, 0, 2);           // 100 10
  TH1D *InvariantMass = new TH1D("InvariantMass", "Invariant Mass", 160, 0, 2);
  TH1D *InvMassDiscordCharge = new TH1D(
      "InvMassDiscordCharge", "Invariant Mass with discord charge", 160, 0, 2);
  TH1D *InvMassConcordCharge = new TH1D(
      "InvMassConcordCharge", "Invariant mass with concord charge", 160, 0, 2);
  TH1D *InvMassPionKaonDiscordCharge = new TH1D(
      "InvMassPionKaonDiscordCharge",
      "Invariant mass of pions and kaons with discord charge", 160, 0, 2);
  TH1D *InvMassPionKaonConcordCharge = new TH1D(
      "InvMassPionKaonConcordCharge",
      "Invariant mass of pions and kaons with concord charge", 160, 0, 2);
  TH1D *InvMassOfDecayedParticles =
      new TH1D("InvMassOfDecayedParticles",
               "Invariant mass of decayed particles", 80, 0, 2);

  Int_t Ngen = 1e5; // number of events
  int N = 120;
  Particle particles[N];
  for (int i = 0; i < Ngen; ++i) {
    for (int j = 0; j < 100; ++j) {
      int PosDecayedParticles =
          100; // counter used to insert the dacayed particles in the array

      Double_t phi = gRandom->Uniform(2 * TMath::Pi());
      Double_t tetha = gRandom->Uniform(TMath::Pi());
      Double_t impulse = gRandom->Exp(1); // 1 GeV
      particles[j].SetP(impulse * TMath::Sin(tetha) * TMath::Cos(phi),
                        impulse * TMath::Sin(tetha) * TMath::Sin(phi),
                        impulse * TMath::Cos(tetha));

      // variable used to generate particles with given proportions
      Double_t x = gRandom->Rndm();

      if (x < 0.01) {
        particles[j].SetfIParticle("K*");
        Double_t y = gRandom->Rndm();
        if (y < 0.5) {
          particles[PosDecayedParticles].SetfIParticle("pion+");
          ++PosDecayedParticles;
          particles[PosDecayedParticles].SetfIParticle("kaon-");
          ++PosDecayedParticles;
          particles[j].Decay2body(particles[PosDecayedParticles - 2],
                                  particles[PosDecayedParticles - 1]);
        } else {
          particles[PosDecayedParticles].SetfIParticle("pion-");
          ++PosDecayedParticles;
          particles[PosDecayedParticles].SetfIParticle("kaon+");
          ++PosDecayedParticles;
          particles[j].Decay2body(particles[PosDecayedParticles - 2],
                                  particles[PosDecayedParticles - 1]);
        }
        InvMassOfDecayedParticles->Fill(
            particles[PosDecayedParticles - 2].InvMass(
                particles[PosDecayedParticles - 1]));

      } else if (x < 0.1) {
        Double_t y = gRandom->Rndm();
        if (y < 0.5) {
          particles[j].SetfIParticle("proton-");
        } else {
          particles[j].SetfIParticle("proton+");
        }
      } else if (x < 0.2) {
        Double_t y = gRandom->Rndm();
        if (y < 0.5) {
          particles[j].SetfIParticle("kaon-");
        } else {
          particles[j].SetfIParticle("kaon+");
        }
      } else {
        Double_t y = gRandom->Rndm();
        if (y < 0.5) {
          particles[j].SetfIParticle("pion-");
        } else {
          particles[j].SetfIParticle("pion+");
        }
      }

      // filling histograms
      TypeOfParticles->Fill(particles[j].GetfIParticle());
      TethaDistribution->Fill(tetha);
      PhiDistribution->Fill(phi);
      Impulse->Fill(sqrt(particles[j].GetPx() * particles[j].GetPx() +
                         particles[j].GetPy() * particles[j].GetPy() +
                         particles[j].GetPz() * particles[j].GetPz()));
      TrasverseImpulse->Fill(sqrt(particles[j].GetPx() * particles[j].GetPx() +
                                  particles[j].GetPy() * particles[j].GetPy()));
      Energy->Fill(particles[j].Energy());
    }

    // filling InariantMass
    for (int I = 0; I < N; ++I) {
      if (particles[I].GetfIParticle() == -1)
        break;
      for (int J = I + 1; J < N; ++J) {
        if (particles[J].GetfIParticle() == -1)
          break;
        InvariantMass->Fill(particles[I].InvMass(particles[J]));
      }
    }

    // filling InvMassDiscordCharge
    for (int I = 0; I < N; ++I) {
      if (particles[I].GetfIParticle() == -1)
        break;
      for (int J = I + 1; J < N; ++J) {
        if (particles[J].GetfIParticle() == -1)
          break;
        if (particles[I].GetCharge() != particles[J].GetCharge() &&
            particles[I].GetCharge() != 0 && particles[J].GetCharge() != 0) {
          InvMassDiscordCharge->Fill(particles[I].InvMass(particles[J]));
        }
      }
    }

    // filling InvMassConcordCharge
    for (int I = 0; I < N; ++I) {
      if (particles[I].GetfIParticle() == -1)
        break;
      for (int J = I + 1; J < N; ++J) {
        if (particles[J].GetfIParticle() == -1)
          break;
        if (particles[I].GetCharge() == particles[J].GetCharge() &&
            particles[I].GetCharge() != 0 && particles[J].GetCharge() != 0) {
          InvMassConcordCharge->Fill(particles[I].InvMass(particles[J]));
        }
      }
    }

    // filling InvMasspionkaonDiscordCharge
    for (int I = 0; I < N; ++I) {
      if (particles[I].GetfIParticle() == -1)
        break;
      if (particles[I].GetName() == "pion+") {
        for (int J = I + 1; J < N; ++J) {
          if (particles[J].GetfIParticle() == -1)
            break;
          if (particles[J].GetName() == "kaon-") {
            InvMassPionKaonDiscordCharge->Fill(
                particles[I].InvMass(particles[J]));
          }
        }
      } else if (particles[I].GetName() == "pion-") {
        for (int J = I + 1; J < N; ++J) {
          if (particles[J].GetfIParticle() == -1)
            break;
          if (particles[J].GetName() == "kaon+") {
            InvMassPionKaonDiscordCharge->Fill(
                particles[I].InvMass(particles[J]));
          }
        }
      } else if (particles[I].GetName() == "kaon+") {
        for (int J = I + 1; J < N; ++J) {
          if (particles[J].GetfIParticle() == -1)
            break;
          if (particles[J].GetName() == "pion-") {
            InvMassPionKaonDiscordCharge->Fill(
                particles[I].InvMass(particles[J]));
          }
        }
      } else if (particles[I].GetName() == "kaon-") {
        for (int J = I + 1; J < N; ++J) {
          if (particles[J].GetfIParticle() == -1)
            break;
          if (particles[J].GetName() == "pion+") {
            InvMassPionKaonDiscordCharge->Fill(
                particles[I].InvMass(particles[J]));
          }
        }
      }
    }

    // filling InvMasspionkaonConcordCharge
    for (int I = 0; I < N; ++I) {
      if (particles[I].GetfIParticle() == -1)
        break;
      if (particles[I].GetName() == "pion+") {
        for (int J = I + 1; J < N; ++J) {
          if (particles[J].GetfIParticle() == -1)
            break;
          if (particles[J].GetName() == "kaon+") {
            InvMassPionKaonConcordCharge->Fill(
                particles[I].InvMass(particles[J]));
          }
        }
      } else if (particles[I].GetName() == "pion-") {
        for (int J = I + 1; J < N; ++J) {
          if (particles[J].GetfIParticle() == -1)
            break;
          if (particles[J].GetName() == "kaon-") {
            InvMassPionKaonConcordCharge->Fill(
                particles[I].InvMass(particles[J]));
          }
        }
      } else if (particles[I].GetName() == "kaon+") {
        for (int J = I + 1; J < N; ++J) {
          if (particles[J].GetfIParticle() == -1)
            break;
          if (particles[J].GetName() == "pion+") {
            InvMassPionKaonConcordCharge->Fill(
                particles[I].InvMass(particles[J]));
          }
        }
      } else if (particles[I].GetName() == "kaon-") {
        for (int J = I + 1; J < N; ++J) {
          if (particles[J].GetfIParticle() == -1)
            break;
          if (particles[J].GetName() == "pion-") {
            InvMassPionKaonConcordCharge->Fill(
                particles[I].InvMass(particles[J]));
          }
        }
      }
    }
  }
  // writing on file
  // calling file->Write() didn't work
  TFile *file = new TFile("histograms.root", "RECREATE");
  TypeOfParticles->Write();
  TethaDistribution->Write();
  PhiDistribution->Write();
  Impulse->Write();
  TrasverseImpulse->Write();
  Energy->Write();
  InvariantMass->Write();
  InvMassDiscordCharge->Write();
  InvMassConcordCharge->Write();
  InvMassPionKaonDiscordCharge->Write();
  InvMassPionKaonConcordCharge->Write();
  InvMassOfDecayedParticles->Write();
  file->Close();

  delete TypeOfParticles;
  delete TethaDistribution;
  delete PhiDistribution;
  delete Impulse;
  delete TrasverseImpulse;
  delete Energy;
  delete InvariantMass;
  delete InvMassDiscordCharge;
  delete InvMassConcordCharge;
  delete InvMassPionKaonDiscordCharge;
  delete InvMassPionKaonConcordCharge;
  delete InvMassOfDecayedParticles;
  delete file;

  Particle::ArrayDeleter();
}
