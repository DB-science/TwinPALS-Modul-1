#pragma once
#ifndef TrackerHitCollection_h
#define TrackerHitCollection_h 1


#include "TrackerHit.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"
#include <array>

class TrackerHitCollection : public G4THitsCollection<TrackerHit>
{
    public:
       
        ~TrackerHitCollection();
        
        
        TrackerHitCollection(G4String detName, G4String colName);


    private: 

    G4double fMean1;
    G4double fMean2;
    G4double fTrackMean1;
    G4double fTrackMean2;

    int fnumberOfCounts1;
    int fnumberOfCounts2;
    /*G4double fmedian1;
    G4double fmedian2;
  */




  public:
    
  
    inline void SetMean1(G4double Mean1)
    {fMean1 = Mean1;}
    
    inline G4double GetMean1()
    {return fMean1;}
   
    inline void SetMean2(G4double Mean2)
    {fMean2 = Mean2;}
    
    inline G4double GetMean2()
    {return fMean2;}

    inline void SetnumberOfCounts1(int numberOfCounts1)
    {fnumberOfCounts1 =numberOfCounts1;}

    inline G4int GetnumberOfCounts1()
    {return fnumberOfCounts1;}

    inline void SetnumberOfCounts2(G4int numberOfCounts2)
    {fnumberOfCounts2 =numberOfCounts2;}

    inline G4int GetnumberOfCounts2()
    {return fnumberOfCounts2;}

    /*inline void SetMedian1(G4double median1)
    {fmedian1 = median1;}
    
    inline G4double GetMedian1()
    {return fmedian1;}
   
    inline void SetMedian2(G4double median2)
    {fmedian2 = median2;}
    
    inline G4double GetMedian2()
    {return fmedian2;}*/

    inline void SetTrackMean1(G4double TrackMean1)
    {fTrackMean1 = TrackMean1;}
    
    inline G4double GetTrackMean1()
    {return fTrackMean1;}
   
    inline void SetTrackMean2(G4double TrackMean2)
    {fTrackMean2 = TrackMean2;}
    
    inline G4double GetTrackMean2()
    {return fTrackMean2;}
};

#endif