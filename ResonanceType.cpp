//
//  ResonanceType.cpp
//  laboratorio_c++_root
//
//  Created by Matteo Barbieri on 16/10/2020.
//

#include "ResonanceType.hpp"

ResonanceType::ResonanceType(const std::string name, const double mass,
                             const int charge, const double width)
    : ParticleType(name, mass, charge), fWidth(width) {}

double ResonanceType::GetWidth() const { return fWidth; }

void ResonanceType::Print() const {
  ParticleType::Print();
  std::cout << "Resonance width: " << ResonanceType::GetWidth() << '\n';
}
