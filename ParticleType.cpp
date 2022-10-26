//
//  ParticleType.cpp
//  laboratorio_c++_root
//
//  Created by Matteo Barbieri on 16/10/2020.
//

#include "ParticleType.hpp"
#include <string>

ParticleType::ParticleType(const std::string name, const double mass,
                           const int charge)
    : fName(name), fMass(mass), fCharge(charge) {}
std::string ParticleType::GetName() const { return fName; }
double ParticleType::GetMass() const { return fMass; }
int ParticleType::GetCharge() const { return fCharge; }
void ParticleType::Print() const {
  std::cout << "Particle name: " << ParticleType::GetName() << '\n'
            << "Particle mass: " << ParticleType::GetMass() << '\n'
            << "Particle charge: " << ParticleType::GetCharge() << '\n';
}

double ParticleType::GetWidth() const { return 0; }
