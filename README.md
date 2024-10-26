# TM Scheduler
*The Tadashi-Mizu distributed task scheduler*

## Communication Architecture

```mermaid
graph TB
    subgraph Clients
        C1[Client 1]
        C2[Client 2]
        C3[Client 3]
    end

    subgraph Control Plane TB
        API[API Server]
        TS[Task Scheduler]
        KV[(Key-Value Store)]
        
        API --> TS
        TS --> KV
    end

    subgraph Worker Nodes
        direction TB
        subgraph "Partition 1"
            W1[Worker 1]
            W2[Worker 2]
        end
        
        subgraph "Partition 2"
            W3[Worker 3]
            W4[Worker 4]
        end
        
        subgraph "Partition N"
            W5[Worker 5]
            W6[Worker 6]
        end
    end

    C1 -->|TCP| API
    C2 -->|TCP| API
    C3 -->|TCP| API
    
    direction TB
    TS -->|gRPC| W1
    TS -->|gRPC| W2
    TS -->|gRPC| W3
    TS -->|gRPC| W4
    TS -->|gRPC| W5
    TS -->|gRPC| W6
```

## Specifications
* Master and Worker nodes that can run across machine boundaries or locally that can communicate via TCP.
* Need internal data store for blob storage? Maybe run against s3 compatible system to pull columnar data in to arrow format??? IDK.
* Tasks are python code that can be submitted to the Master and distributed to worker nodes (maybe? idk might do json or toml first).
* Task data uses Apache Arrow for in memory format.
* Task metadata uses Protocol buffers.
* Uses RocksDB for embedded key value store for metadata. 