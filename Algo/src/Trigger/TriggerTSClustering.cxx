#include "Trigger/TriggerTSClustering.h"

/* ecxamples of how to pull in stuff from ldmx-sw framework
#include "Recon/Event/HgcrocDigiCollection.h"
#include "Recon/Event/HgcrocTrigDigi.h"
#include "DetDescr/EcalHexReadout.h"
*/


#include <argp.h>
#include <iostream>

#include "../../../Algo_HLS/TS/tb/TSDigiCollection.cpp"
#include "../../../Algo_HLS/TS/tb/TSTrackCollection.cpp"
#include "../../../Algo_HLS/TS/src/TSTriggerAlgo.cpp"

using namespace std;



namespace trigger {

void TriggerTSClustering ::configure(Parameters &ps) {

  threshold_ = ps.getParameter<double>("clustering_threshold");
  maxWidth_ = ps.getParameter<int>("max_cluster_width");
  writefile_ = ps.getParameter<std::string>("output_file_name");
  readfile_ = ps.getParameter<std::string>("input_file_name");
  verbose_ = ps.getParameter<int>("verbosity");

  
}

void TriggerTSClustering::produce(ldmx::Event &event) {

	TSDigiCollection eventsCollection;
	TSTrackCollection tracksCollection;

	// Read input data file
	if (!readfile_) {
		cerr << "An input test vector is required" << endl;
		return;
	}
	eventsCollection.read(string(readfile_));

	// Run all events through algo
	for (auto &eventIn : eventsCollection.map()) {
		TSTrackCollection::TSTrackArray trackArray;

		trackArray.tracks[0] = TSTrack(10,10,10,10);

		TSTriggerAlgo(eventIn.second.data(), trackArray.tracks);

		if (verbose_) {
			cout << "Event " << eventIn.first << ": tracks=";
			for (unsigned int i = 0; i < TS_PARAM_MAX_TRACKS; i++) {
				cout << "[" << trackArray.tracks[i].stringify() << "]";
			}
			cout << endl;
		}

		tracksCollection.add(eventIn.first, trackArray);
	}

	// Write results to file
	if (writefile_) {
		tracksCollection.write(string(writefile_));
	}

	/* //skip for now, needs more implementation
	// Compare output results to reference
	if (cmpfile_) {
		TSTrackCollection tracksCollection_ref;
		tracksCollection_ref.read(string(cmpfile_));

		if (tracksCollection == tracksCollection_ref) {
			cout << "Algo output MATCHES reference file" << endl;
			return 0;
		} else {
			cout << "Algo output DOES NOT MATCH reference file" << endl;
			return 1;
		}
	} //if comparison file
	*/

	return;


}


void TriggerTSClustering::onFileOpen() {

  ldmx_log(debug) << "Opening file!";

  return;
}

void TriggerTSClustering::onFileClose() {

  ldmx_log(debug) << "Closing file!";

  return;
}

void TriggerTSClustering::onProcessStart() {

  ldmx_log(debug) << "Process starts!";

  return;
}

void TriggerTSClustering::onProcessEnd() {

  ldmx_log(debug) << "Process ends!";

  return;
}

}

DECLARE_PRODUCER_NS(ldmx, TriggerTSClustering);
