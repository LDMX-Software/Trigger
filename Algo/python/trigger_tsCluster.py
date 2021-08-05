
from LDMX.Framework.ldmxcfg import Producer

class TriggerTSClustering(Producer) :
    """Configuration for TriggerTSClustering
    """

    def __init__(self, instance_name = 'myTriggerTSClustering') :
        super().__init__(instance_name , 'ldmx::TriggerTSClustering','Trigger')


        self.max_cluster_width = 1
        self.input_file_name = "qieDataTag.txt"
        self.output_file_name = "algoOutput.txt"
        self.verbosity = 0
