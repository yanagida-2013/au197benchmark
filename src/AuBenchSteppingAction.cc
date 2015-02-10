#include "AuBenchSteppingAction.hh"
#include "AuBenchDetectorConstruction.hh"
#include "AuBenchRun.hh"
#include "AuBenchPrimaryGeneratorAction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4Material.hh"
#include "G4Element.hh"

#include "G4VProcess.hh"
#include "G4ProcessType.hh"
#include "G4HadronicProcessType.hh"
#include "G4Neutron.hh"

#include "G4SteppingManager.hh"

MSG4SteppingAction::MSG4SteppingAction(): G4UserSteppingAction(), isScattered(false)
{
}

MSG4SteppingAction::~MSG4SteppingAction()
{}

void MSG4SteppingAction::UserSteppingAction(const G4Step* step) {
    const G4VProcess* pro;
    if ( (pro = step->GetPostStepPoint()->GetProcessDefinedStep()) &&
         pro->GetProcessType() == fHadronic ) {
        switch(pro->GetProcessSubType()) {
            // Elastic
        case fHadronElastic:
            {
                isScattered = true;
                break;
            }

            // Capture
        case fCapture:
            {
                MSG4Run* run = static_cast<MSG4Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());

                G4int nSecAtRest = fpSteppingManager->GetfN2ndariesAtRestDoIt();
                G4int nSecAlong = fpSteppingManager->GetfN2ndariesAlongStepDoIt();
                G4int nSecPost = fpSteppingManager->GetfN2ndariesPostStepDoIt();
                G4int nSecTotal = nSecAtRest+nSecAlong+nSecPost;
                G4TrackVector* secVec = fpSteppingManager->GetfSecondary();
                if(nSecTotal>0) {
                    for(size_t lp1=(*secVec).size()-nSecTotal; lp1 < (*secVec).size(); lp1++) {
                        G4String captured = (*secVec)[lp1]->GetDefinition()->GetParticleName();
                        if (captured == "Au198") {
                            run->inc(isScattered);
                            break;
                        }
                    }
                }
                break;
            }
        }
    }

}

G4String MSG4SteppingAction::GetReactionName() {
    const G4TrackVector* secVec = fpSteppingManager->GetSecondary();
    return secVec->back()->GetCreatorProcess()->GetProcessName();
}

G4String MSG4SteppingAction::GetSecondaryParticle() {
    const G4TrackVector* secVec = fpSteppingManager->GetSecondary();
    return secVec->back()->GetDefinition()->GetParticleName();
}


// memo
// enum G4HadronicProcessType
// {
//   fHadronElastic =    111,
//   fHadronInelastic =  121,
//   fCapture =          131,
//   fFission =          141,
//   fHadronAtRest =     151,
//   fLeptonAtRest =     152,
//   fChargeExchange =   161,
//   fRadioactiveDecay = 210
// };
