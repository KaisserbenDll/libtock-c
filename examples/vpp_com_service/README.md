# Communication Service
========================

This repository is made of two applications: One is the COM Process and the other is the MAIN Process. The communication service managing two data chunk FIFO queues in VPP - Concepts and Interfaces in p.63 is implemented here. 

```
cd COM_app/ 
make RISCV=1

// Change addresses in Configuration.mk file
cd MAIN_app/ 
make RISCV=1 

// Concatenate both apps 
cat COM_app/build/rv32imc_opentitan.tbf MAIN_app/build/rv32imc_opentitan.tbf app.tbf 
```