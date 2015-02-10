#ifndef MSG4Run_h
#define MSG4Run_h 1

#include "G4Run.hh"
#include <vector>
#include <array>
class G4Event;

/// Run class
///

/// Normally, Run class holds the important physical quantity such as Energy deposit.
/// In this program, this class holds the number of capture events occured.

class MSG4Run : public G4Run {
public:
    MSG4Run();
    ~MSG4Run();

    virtual void Merge(const G4Run*);

    void inc(G4bool isScattered);
    void show_result() const;

private:
    G4int capture;
    G4int capture_without_scattering;
};

#endif
