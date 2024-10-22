# TM Scheduler
*The Tadashi-Mizu distributed task scheduler*

## Specifications
* Master and Worker nodes that can run across machine boundaries or locally that can communicate via TCP.
* Tasks are python code that can be submitted to the Master and distributed to worker nodes.
* Master and Worker's use RAFT consensus.
* Task data uses Apache Arrow.
* Task metadata uses Cap'n proto with Protocol buffers.
* Uses RocksDB for embedded key value store to store RAFT information. 