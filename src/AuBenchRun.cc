#include "AuBenchRun.hh"
#include "G4RunManager.hh"


MSG4Run::MSG4Run():capture(0),capture_without_scattering(0) {}

MSG4Run::~MSG4Run()
{}

void MSG4Run::Merge(const G4Run* run) {
    // Function for multi-threading

    // Get the local run pointer
    const MSG4Run* localRun = static_cast<const MSG4Run*>(run);

    // Get each data of the local Run
    capture += localRun->capture;
    capture_without_scattering += localRun->capture_without_scattering;

    // Merge
    G4Run::Merge(run);
}

void MSG4Run::inc(G4bool isScattered) {
    MSG4Run* localRun = static_cast<MSG4Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    capture++;
    if (!isScattered) {
        capture_without_scattering++;
    }
}

void MSG4Run::show_result() const{
    G4cout << "All Capture                 : " << capture << G4endl;
    G4cout << "Capture without scattering  : " << capture_without_scattering << G4endl;
}
