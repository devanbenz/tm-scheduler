# TM Scheduler
*The Tadashi-Mizu distributed task scheduler*

## Communication Architecture

```
           Clients 
   (python or http client)                       
    ┌─────┐┌─────┐┌─────┐                 
    │     ││     ││     │                 
    │     ││     ││     │                 
    └──┬──┘└──┬──┘└──┬──┘                 
┌──────┼──────┼──────┼───────────────────┐
│  ┌───▼──────▼──────▼────────────────┐  │
│  │           CONTROL PLANE          │  │
│  │            API SERVER            │  │
│  └──────┬────────────────────┬──────┘  │
│         │                    │         │
│  ┌──────▼───────┐     ┌──────▼──────┐  │
│  │              │     │             │  │
│  │   KV STORE   │     │             │  │
│  │              │     │             │  │
│  └──────┬───────┘     │    OBJECT   │  │
│         │             │    STORE    │  │
│  ┌──────▼───────┐     │             │  │
│  │              │     │             │  │
│  │  SCHEDULER   │     │             │  │
│  │              │     │             │  │
│  └──┬───────────┘     └─────┬───────┘  │
│     │                       │          │
└─────┼───────────────────────┼──────────┘
      │-RPC                   │           
   ┌──▼────────────┐          │           
   │┌───────────────┐         │           
   ││ ┌───────────────┐       │           
   ││ │               │       │           
   ││ │               │       │           
   ││ │ WORKER NODES  ◄───────┘           
   └│ │               │                   
    └─│               │                   
      └───────────────┘                   

```

## Specifications
* Many worker nodes processing partitioned data. Inspiration: https://duckdb.org/2022/03/07/aggregate-hashtable.html
* Need internal data store for blob storage? Maybe run against s3 compatible system to pull columnar data in to arrow format??? IDK.
* Python bindings for control plane API & task submission.
* Task data uses Apache Arrow for in memory format.
* Worker nodes will communicate with scheduler via RPC and visa-versa.
* Uses RocksDB for embedded key value store for metadata. 

### Ideas for client-side task submission

```python
import TmScheduler as tm

#Connect to control plane
tm.NewSession("localhost:8080")

#Register three worker nodes to the control plane
tm.RegisterWorker("localhost:50051")
tm.RegisterWorker("localhost:50052")
tm.RegisterWorker("localhost:50053")

# TODO: implement some ideas for submitting tasks
```