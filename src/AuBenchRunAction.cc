#include "AuBenchRunAction.hh"
#include "AuBenchPrimaryGeneratorAction.hh"
#include "AuBenchRun.hh"
#include "AuBenchSteppingAction.hh"


#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <chrono>  // std:C++11
#include <fstream>


MSG4RunAction::MSG4RunAction()
: G4UserRunAction()
{
}

MSG4RunAction::~MSG4RunAction()
{}

G4Run* MSG4RunAction::GenerateRun()
{
  return new MSG4Run;
}

void MSG4RunAction::BeginOfRunAction(const G4Run*) {
  // This function is called when the Run started.
  // So, it's normally called only once.
  starting_time = std::chrono::system_clock::now();
}


void MSG4RunAction::EndOfRunAction(const G4Run* run) {
  // This function is called when the Run ended.
  // So, it's normally called only once.

  // Print
  if (IsMaster()) {
    G4cout << "\n--------------------End of Global Run-----------------------\n";
    G4cout << "\n Time Elapsed:  ";
    // Show the time elapsed
    auto time_elapsed = std::chrono::system_clock::now() - starting_time;
    G4cout << std::chrono::duration_cast<std::chrono::seconds>(time_elapsed).count() << " [sec]"  << G4endl;
    // Data acquisition
    G4int nofEvents = run->GetNumberOfEvent();
    const MSG4Run* msg4Run = static_cast<const MSG4Run*>(run);

    // Print Results
    G4cout << "\nNumber of Events            : " << nofEvents << G4endl;
    msg4Run->show_result();
  }
}
