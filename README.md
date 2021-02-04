# Sm0l-HDL
Simple Hardware Description Language (inspired by Verilog sintax) simulator; 

Supporting:
	-Simulation on input assingment:
		-Logic gates
		-Flip flops
	-Analisys:
		-Shortest input-output path
		-Longest input-output path
		-Logic cones calculation

It is also possible assembling circuits together via keyword 'instance', as described in the grammar LL2 associated with the respository at: 'Documenti/Grammmatiche.pdf'.

For all modes apart from 'Library':
	-All the defined circuits should be placed in the folder named 'Circuiti'.
	-All the defined input for circuits should be placed in the folder named 'Inputs', with the same file name as the circuit it refers to. 
