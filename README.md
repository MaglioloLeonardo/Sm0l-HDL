# Sm0l-HDL
Simple Hardware Description Language (inspired by Verilog sintax) simulator; Supporting:
<ul>
	<li>Simulation on input assingment:</li>
		<ul>
			<li>Logic gates</li>
			<li>Flip flops</li>
		</ul>
	<li>Analisys:</li>
		<ul>
			<li>Shortest input-output path</li>
			<li>Longest input-output path</li>
			<li>Logic cones calculation</li>
		</ul>
</ul>

It is also possible assembling circuits together via keyword 'instance', as described in the grammar LL2 associated with the respository at: 'Documenti/Grammmatiche.pdf'.

For all modes apart from 'Library':
<ul>
	<li>All the defined circuits should be placed in the folder named 'Circuiti'.</li>
	<li>All the defined input matrix for circuits should be placed in the folder named 'Inputs', with the same file name as the circuit it refers to.</li>
</ul>
Every row of the input matrix should have lenght equals to the number of inputs of the circuit. <br>
If more row will be defined the simulator will print the circuit's output for every row in the input matrix
