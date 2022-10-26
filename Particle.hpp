//
//  Particle.hpp
//  laboratorio_c++_root
//
//  Created by Matteo Barbieri on 16/10/2020.
//

#ifndef Particle_hpp
#define Particle_hpp

#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include <stdio.h>

static const int fMaxNumParticleType = 10;

class Particle {
public:
  Particle(const std::string name, double Px = 0, double Py = 0, double Pz = 0);
  Particle();

  static void AddParticleType(const std::string name, const double mass,
                              const int charge, const double width);
  int GetfIParticle() const;

  void SetfIParticle(int index);
  void SetfIParticle(std::string name);

  static void PrintfParticleType();
  void PrintParticle() const;

  double GetPx() const;
  double GetPy() const;
  double GetPz() const;

  double GetMass() const;
  double Energy() const;
  double InvMass(const Particle &p) const;

  void SetP(double px, double py, double pz);

  static void ArrayDeleter();

  int Decay2body(Particle &dau1, Particle &dau2) const;

  int GetCharge() const;
  std::string GetName() const;

private:
  static ParticleType *fParticleType[fMaxNumParticleType];
  static int fNParticleType;
  int fIParticle;
  double fPx;
  double fPy;
  double fPz;
  static int FindParticle(const std::string name);

  void Boost(double bx, double by, double bz);
};

#endif /* Particle_hpp */
