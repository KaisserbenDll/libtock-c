# Firmware Management Service
========================

This repository is made of two applications: 
1. The MGT app responsible for the firmware managing service. This app recieves a command to be executed from the SYS app over IPC. It reads the command and calls the appropriate kernel function from the capsule. All the functions the MGT app calls are described in the VPP - Concepts and Interfaces specification from p.65 to p.80. 

2. The SYS app maps commands to be executed on its IPC and sends a signal to inform the MGT app that its IPC got updated. After setting up the Firmware Management Service from the MGT app, the SYS app calls the Firmware Management kernel functions described in the specifiation p.60-p62

This is a proof of concept, where an example firmware header is given and the allocation of different sub memory partitions is performed with random bytes.

```
cd MGT_app/ 
make RISCV=1

// Change addresses in Configuration.mk file for the second application
cd SYS_app/ 
make RISCV=1 

// Concatenate both apps 
cat MGT_app/build/rv32imc_opentitan.tbf SYS_app/build/rv32imc_opentitan.tbf app.tbf 
```

