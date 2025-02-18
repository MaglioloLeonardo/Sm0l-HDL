<!DOCTYPE html>
<html lang="en">
<body>
  <h1>⚡ Sm0l-HDL: A Simple Hardware Description Language Simulator</h1>
  <p><strong>Sm0l-HDL</strong> is a simulator for <strong>Hardware Description Language (HDL)</strong>, inspired by the syntax of <strong>Verilog</strong> and developed in <strong>C++</strong>. It allows the simulation and analysis of <strong>digital circuits</strong>, supporting <strong>logic gates, flip-flops, hierarchical circuit composition, and logic analysis</strong>.</p>

  <h2>📄 Project Features</h2>
  <ul>
    <li>
      <strong>Digital Circuit Simulation</strong>
      <ul>
        <li>Supports <strong>combinational circuits</strong> (logic gates) and <strong>sequential circuits</strong> (D flip-flops).</li>
        <li>Executes circuit descriptions similar to <strong>Verilog</strong>, using a simplified grammar.</li>
      </ul>
    </li>
    <li>
      <strong>Circuit Analysis Tools</strong>
      <ul>
        <li>Calculates the <strong>shortest paths</strong> and <strong>longest paths</strong> from inputs to outputs.</li>
        <li>Determines <strong>logic cones</strong>, identifying the inputs that affect each output.</li>
      </ul>
    </li>
    <li>
      <strong>Hierarchical Circuit Composition</strong>
      <ul>
        <li>Supports modular circuit design through the <code>instance</code> keyword.</li>
        <li>Circuits can be <strong>assembled together</strong> using hierarchical descriptions.</li>
      </ul>
    </li>
  </ul>

  <h2>🚀 Implementation Details</h2>
  <h3>Circuit Description Syntax</h3>
  <p>Sm0l-HDL uses a <strong>simplified Verilog-like syntax</strong>. Below are some examples of circuit descriptions:</p>
  
  <h4>Example: Combinational Circuit</h4>
  <pre><code class="language-verilog">module AND_GATE (
  input a, b,
  output x
);
  assign x = a AND b;
endmodule</code></pre>
  
  <h4>Example: Sequential Circuit with Flip-Flops</h4>
  <pre><code class="language-verilog">module SEQ_CIRCUIT (
  clk,
  input a, b,
  output x
);
  FF1 = a AND b;
  FF2 = FF1 OR (NOT clk);
  assign x = FF1 OR FF2;
endmodule</code></pre>
  
  <h3>Logic Analysis</h3>
  <p>The simulator provides advanced tools to understand the circuit's behavior:</p>
  <ul>
    <li><strong>Shortest Path Analysis:</strong> Identifies the shortest signal propagation path from input to output.</li>
    <li><strong>Longest Path Analysis:</strong> Determines the maximum propagation delay within the circuit.</li>
    <li><strong>Logic Cones:</strong> Analyzes the dependencies between inputs and outputs, mapping the influence of each input on the final result.</li>
  </ul>
  <p><strong>Example: Logic Cone for Output X</strong></p>
  <p>If <code>X = A AND (B OR C)</code>, the logic cone for <code>X</code> includes <code>{A, B, C}</code> since all three inputs contribute to the final result.</p>

  <h2>📂 Project Structure</h2>
  <ul>
    <li><strong>Circuits/</strong> → Folder containing the defined circuits.</li>
    <li><strong>Inputs/</strong> → Folder containing the input matrices for each circuit.</li>
    <li><strong>Documents/Grammars.pdf</strong> → Detailed specification of the LL(2) grammar.</li>
  </ul>

  <h2>📈 Future Enhancements</h2>
  <ul>
    <li><strong>Power Analysis:</strong> Estimation of energy consumption per logic transition.</li>
    <li><strong>Loop Detection:</strong> Identification of feedback loops in sequential circuits.</li>
    <li><strong>Optimized Parsing:</strong> Improvement of execution speed for large circuits.</li>
  </ul>
  
  <p>🔥 <strong>Sm0l-HDL</strong> is a lightweight and efficient simulator for modeling and analyzing digital circuits. Explore, test, and contribute! 🚀</p>
</body>
</html>
