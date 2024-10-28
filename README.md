# TM Scheduler
*The Tadashi-Mizu distributed task scheduler*

*Code is still 100% a work in progress and is mostly scratch code wiring things up (I don't really know C++ sorry :P)*

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

## Specification planning
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

### To do list
- [ ] Open http session with python client
- [ ] Register workers with python client 
- [ ] Round robin scheduler implementation 
- [ ] Key value store implementation 
  - [ ] store for workers
  - [ ] store for tasks
- [ ] Control API
  - [ ] Get all running tasks
  - [ ] Get all running workers with health
  - [ ] Get task by ID
- [ ] Object store
  - [ ] Load data from object store in to Arrow memory
- [ ] Worker nodes
  - [ ] TO DO: Plan RPCs for workers 
  - [ ] TO DO: Plan data partitioning between workers