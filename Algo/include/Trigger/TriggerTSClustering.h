/**
 * @file TriggerTSClustering.h
 * @brief TSClustering algo
 * @author Christian Herwig, Fermilab
 * @author Lene Kristian Bryngemark, Stanford
 */

#ifndef TRIGGERTSCLUSTERING_H
#define TRIGGERTSCLUSTERING_H

//LDMX Framework
#include "Framework/Event.h"
#include "Framework/EventProcessor.h" //Needed to declare processor
#include "Framework/Configure/Parameters.h" // Needed to import parameters from configuration file

#include "ap_int.h"
#include "ap_fixed.h"

#include "Ecal/EcalTriggerGeometry.h"

namespace trigger {

  /**
   * @class TriggerTSClustering
   * @brief 
   */
  class TriggerTSClustering : public ldmx::Producer {

 public:

 TriggerTSClustering(const std::string& name, ldmx::Process& process) : ldmx::Producer(name, process) {}
    
    virtual void configure(ldmx::Parameters& ps);
    
    virtual void produce(ldmx::Event& event);
      
    virtual void onFileOpen();
      
    virtual void onFileClose();
      
    virtual void onProcessStart(); 
      
    virtual void onProcessEnd();
      
    typedef ap_ufixed<16,14> e_t; // [MeV] (Up to at least 8 GeV)
	
 private:

    //specific verbosity of this producer
    int verbose_{0}; 

	float centroid_{-1};
	float threshold_{-1};
	int maxWidth_{1};
	
	std::string readfile_{""};
	std::string writefile_{""};
	
  };
}

#endif /* TRIGGERTSCLUSTERING_H */
