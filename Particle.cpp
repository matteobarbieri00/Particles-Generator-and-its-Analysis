//
//  Particle.cpp
//  laboratorio_c++_root
//
//  Created by Matteo Barbieri on 16/10/2020.
//

#include <cmath>
#include <cstdlib> //for RAND_MAX
#include <iostream>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

// initializing static members
ParticleType *Particle::fParticleType[fMaxNumParticleType] = {};
int Particle::fNParticleType = 0;

// FindParticle
int Particle::FindParticle(const std::string name) {
  for (int i = 0; i < fMaxNumParticleType; ++i) {
    if (fParticleType[i] == NULL) {
      std::cout << "End of array and particle not found!" << '\n';
      return -1;
    } else if (fParticleType[i]->GetName() == name) {
      return i;
    }
  }
  std::cout << "Whole array tested and particle not found!" << '\n';
  return -1;
}

// Constructors
Particle::Particle(const std::string name, double Px, double Py, double Pz)
    : fIParticle(Particle::FindParticle(name)), fPx(Px), fPy(Py), fPz(Pz) {}

Particle::Particle() : fIParticle(-1), fPx(0), fPy(0), fPz(0) {}

// Getter for the index
int Particle::GetfIParticle() const { return fIParticle; }

// Method to fill the array
void Particle::AddParticleType(const std::string name, const double mass,
                               const int charge, const double width) {
  if (FindParticle(name) != -1) {
    std::cout << "Particle already added." << '\n';
    return;
  } else {
    for (int i = 0; i < fMaxNumParticleType; ++i) {
      if (fParticleType[i] == NULL) {
        if (width != 0) {
          fParticleType[i] = new ResonanceType(name, mass, charge, width);
          fNParticleType++; // increments the counter of the number of particles
                            // in the array;
          return;
        } else {
          fParticleType[i] = new ParticleType(name, mass, charge);
          fNParticleType++;
          return;
        }
      }
    }
    std::cout << "Error: Maximum number of particles already hitted!" << '\n';
    return;
  }
}

void Particle::SetfIParticle(int index) {
  if (fParticleType[index] == NULL) {
    std::cout << "Nothing's here yet!" << '\n';
  } else {
    fIParticle = index; // assuming that we already know which particle is
                        // stored at index index;
  }
}

void Particle::SetfIParticle(std::string name) {
  int index = FindParticle(
      name); // created a variable in order to do only one call to
             // FindParticle(), which iterates over the array and that can take
             // a lot of time in the case of a long array;
  if (index == -1) {
    std::cout << "Not here yet!" << '\n';

  } else {
    fIParticle = index;
  }
}

// Print methods
void Particle::PrintfParticleType() {
  for (int i = 0; i < fMaxNumParticleType; ++i) {
    if (fParticleType[i] == NULL) {
      return;
    } else {
      fParticleType[i]->Print();
      std::cout << "----------------------------" << '\n';
    }
  }
}

void Particle::PrintParticle() const {
  std::cout << "The index of the particle is: " << fIParticle << '\n';
  std::cout << "Particle name: " << fParticleType[fIParticle]->GetName()
            << '\n';
  std::cout << "Px: " << GetPx() << '\n';
  std::cout << "Py: " << GetPy() << '\n';
  std::cout << "Pz: " << GetPz() << '\n';
  std::cout << "***************************" << '\n';
}

// getters
double Particle::GetPx() const { return fPx; }
double Particle::GetPy() const { return fPy; }
double Particle::GetPz() const { return fPz; }

double Particle::GetMass() const {
  return fParticleType[fIParticle]->GetMass();
}

double Particle::Energy() const {
  return std::sqrt((fParticleType[fIParticle]->GetMass()) *
                       (fParticleType[fIParticle]->GetMass()) +
                   (GetPx() * GetPx() + GetPy() * GetPy() + GetPz() * GetPz()));
}

double Particle::InvMass(const Particle &p) const {
  return std::sqrt((Energy() + p.Energy()) * (Energy() + p.Energy()) -
                   ((GetPx() + p.GetPx()) * (GetPx() + p.GetPx()) +
                    (GetPy() + p.GetPy()) * (GetPy() + p.GetPy()) +
                    (GetPz() + p.GetPz()) * (GetPz() + p.GetPz())));
}

int Particle::GetCharge() const {
  return fParticleType[fIParticle]->GetCharge();
}

std::string Particle::GetName() const {
  return fParticleType[fIParticle]->GetName();
}

// setter for P
void Particle::SetP(double px, double py, double pz) {
  fPx = px;
  fPy = py;
  fPz = pz;
}

void Particle::ArrayDeleter() {
  for (int i = 0; i < fNParticleType; ++i) {
    delete fParticleType[i];
  }
}

int Particle::Decay2body(Particle &dau1, Particle &dau2) const {
  if (GetMass() == 0.0) {
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }

  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if (fIParticle > -1) { // add width effect

    // gaussian random numbers

    float x1, x2, w, y1, y2;

    double invnum = 1. / RAND_MAX;
    do {
      x1 = 2.0 * rand() * invnum - 1.0;
      x2 = 2.0 * rand() * invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while (w >= 1.0);

    w = sqrt((-2.0 * log(w)) / w);
    y1 = x1 * w;
    y2 = x2 * w;

    massMot += fParticleType[fIParticle]->GetWidth() * y1;
  }

  if (massMot < massDau1 + massDau2) {
    printf("Decayment cannot be preformed because mass is too low in this "
           "channel\n");
    return 2;
  }

  double pout =
      sqrt(
          (massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
          (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
      massMot * 0.5;

  double norm = 2 * M_PI / RAND_MAX;

  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;
  dau1.SetP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi),
            pout * cos(theta));
  dau2.SetP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi),
            -pout * cos(theta));

  double energy = sqrt(fPx * fPx + fPy * fPy + fPz * fPz + massMot * massMot);

  double bx = fPx / energy;
  double by = fPy / energy;
  double bz = fPz / energy;

  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  return 0;
}
void Particle::Boost(double bx, double by, double bz) {

  double energy = Energy();

  // Boost this Lorentz vector
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * fPx + by * fPy + bz * fPz;
  double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

  fPx += gamma2 * bp * bx + gamma * bx * energy;
  fPy += gamma2 * bp * by + gamma * by * energy;
  fPz += gamma2 * bp * bz + gamma * bz * energy;
}
