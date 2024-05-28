#pragma once

#ifndef DETECTORINFO_HH
#define DETECTORINFO_HH
//#include "MyEventAction.hh"

class DetectorInfo { // A || B
    friend class EventInfo;
public:
    DetectorInfo() {
        clear();      
    }

    DetectorInfo(int id) {
		clear(); 
		
        m_id = id;
    }

    ~DetectorInfo(){}
    
    void clear() {
		m_id = -1;
        m_depEnerg = 0;
        //m_ArrCF = 0.;
        m_MeanArr = 0.;
        //m_MedianArr = 0.;
       // m_MaxPulse = 0.;
        m_globalTime = 0;
        m_nofHits = false;
        m_interactionX = 0.;
        m_interactionY =0.;
        m_interactionZ =0.;
        m_numberOfCounts = 0;
        m_MeanTrackLength = 0; 
     
	}
	
	
	void AddEnergyDep(double fEdep, double globalTime, bool bHit, int id, double MeanArr, double InterActionX, double InterActionY,
    double InterActionZ, int numberOfCounts, double MeanTrackLength, int NumberOfReflection, int GammaAgain/*, double MedianArr, double MaxPulse*/) {
		m_depEnerg = fEdep;
		//m_ArrCF = ArrCF;
		m_globalTime = globalTime;
		m_nofHits = bHit;
		m_id = id;
        m_MeanArr = MeanArr;
        m_interactionX = InterActionX;
        m_interactionY = InterActionY;
        m_interactionZ = InterActionZ;
        m_numberOfCounts = numberOfCounts;
        m_MeanTrackLength = MeanTrackLength;
        m_NumberOfReflection = NumberOfReflection;
        m_GammaAgain = GammaAgain;
     
       // m_MedianArr = MedianArr;
       // m_MaxPulse = MaxPulse;
	}
	
  
    int NumberOfReflection() const {
        return m_NumberOfReflection;
    }
    int GammaAgain() const {
        return m_GammaAgain;
    }

    int id() const {
        return m_id;
    }

    double energy() const {
        return m_depEnerg;
    }
    
   /* double ArrCF() const {
        return m_ArrCF;
    }*/

    double MeanArr() const {
        return m_MeanArr;
    }
    double InterActionX() const {
        return m_interactionX;
    }
    double InterActionY() const {
        return m_interactionY;
    }
    double InterActionZ() const {
        return m_interactionZ;
    }
   int numberOfCounts() const {
       return m_numberOfCounts;
   }

/*
     double MedianArr() const {
        return m_MedianArr;
    }

    double MaxPulse() const {
        return m_MaxPulse;
    }
*/

    double MeanTrackLength() const {
        return m_MeanTrackLength;
    }

    bool isValid() const {
        return m_nofHits;
    }

private:
    int m_id; // event-id
    double m_depEnerg; // dep. energy at detector
    //double m_ArrCF; // arrival time at detector
    double m_MeanArr; //mean arrvialValue
    double m_globalTime; //globalTime counter
    double m_MedianArr; //Median value of the pulse
    double m_MaxPulse; //Pulse Peak x value
    bool m_nofHits; // incident gammay ray?
    double m_interactionX;
    double m_interactionY;
    double m_interactionZ;
    int m_numberOfCounts;

    double m_MeanTrackLength;

    int m_NumberOfReflection;
    int m_GammaAgain;
    

};

#endif
