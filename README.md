<!DOCTYPE html>
<html lang="it">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      font-family: Arial, sans-serif;
      margin: 20px;
      line-height: 1.6;
      background-color: #fff;
      color: #333;
    }
    h1, h2, h3, h4 {
      color: #222;
    }
    pre {
      background-color: #f4f4f4;
      padding: 10px;
      border: 1px solid #ddd;
      overflow: auto;
    }
    code {
      background-color: #f4f4f4;
      padding: 2px 4px;
    }
    ul {
      list-style: none;
      padding-left: 0;
    }
    ul li {
      margin-bottom: 0.5em;
    }
    ul li ul {
      margin-top: 0.5em;
      margin-left: 20px;
      list-style-type: disc;
    }
    hr {
      margin: 2em 0;
    }
  </style>
</head>
<body>
  <h1>⚡ Sm0l-HDL: A Simple Hardware Description Language Simulator</h1>
  <p><strong>Sm0l-HDL</strong> è un simulatore per <strong>Hardware Description Language (HDL)</strong>, ispirato alla sintassi di <strong>Verilog</strong> e sviluppato in <strong>C++</strong>. Consente la simulazione e l'analisi di <strong>circuiti digitali</strong>, supportando <strong>porte logiche, flip-flop, composizione gerarchica dei circuiti e analisi logica</strong>.</p>

  <h2>📄 Caratteristiche del Progetto</h2>
  <ul>
    <li>
      <strong>Simulazione di Circuiti Digitali</strong>
      <ul>
        <li>Supporta circuiti <strong>combinazionali</strong> (porte logiche) e circuiti <strong>sequenziali</strong> (D flip-flop).</li>
        <li>Esegue descrizioni dei circuiti simili a <strong>Verilog</strong>, utilizzando una grammatica semplificata.</li>
      </ul>
    </li>
    <li>
      <strong>Strumenti di Analisi del Circuito</strong>
      <ul>
        <li>Calcola i <strong>percorsi più brevi</strong> e i <strong>percorsi più lunghi</strong> dagli ingressi alle uscite.</li>
        <li>Determina i <strong>logic cones</strong>, identificando gli ingressi che influenzano ciascuna uscita.</li>
      </ul>
    </li>
    <li>
      <strong>Composizione Gerarchica dei Circuiti</strong>
      <ul>
        <li>Supporta il design modulare dei circuiti tramite la parola chiave <code>instance</code>.</li>
        <li>I circuiti possono essere <strong>assemblati insieme</strong> usando descrizioni gerarchiche.</li>
      </ul>
    </li>
  </ul>

  <h2>🚀 Dettagli di Implementazione</h2>
  <h3>Sintassi per la Descrizione dei Circuiti</h3>
  <p>Sm0l-HDL utilizza una sintassi <strong>semplificata in stile Verilog</strong>. Di seguito alcuni esempi di descrizioni dei circuiti:</p>
  
  <h4>Esempio: Circuito Combinazionale</h4>
  <pre><code class="language-verilog">module AND_GATE (
  input a, b,
  output x
);
  assign x = a AND b;
endmodule</code></pre>
  
  <h4>Esempio: Circuito Sequenziale con Flip-Flop</h4>
  <pre><code class="language-verilog">module SEQ_CIRCUIT (
  clk,
  input a, b,
  output x
);
  FF1 = a AND b;
  FF2 = FF1 OR (NOT clk);
  assign x = FF1 OR FF2;
endmodule</code></pre>
  
  <h3>Analisi Logica</h3>
  <p>Il simulatore fornisce strumenti avanzati per comprendere il comportamento del circuito:</p>
  <ul>
    <li><strong>Shortest Path Analysis:</strong> Identifica il percorso di propagazione del segnale più breve dall'ingresso all'uscita.</li>
    <li><strong>Longest Path Analysis:</strong> Determina il ritardo di propagazione massimo all'interno del circuito.</li>
    <li><strong>Logic Cones:</strong> Analizza le dipendenze tra ingressi e uscite, mappando l'influenza di ogni ingresso sul risultato finale.</li>
  </ul>
  <p><strong>Esempio: Logic Cone per l'Uscita X</strong></p>
  <p>Se <code>X = A AND (B OR C)</code>, il logic cone per <code>X</code> include <code>{A, B, C}</code>, poiché tutti e tre gli ingressi contribuiscono al risultato finale.</p>

  <h2>📂 Struttura del Progetto</h2>
  <ul>
    <li><strong>Circuiti/</strong> → Cartella contenente i circuiti definiti.</li>
    <li><strong>Inputs/</strong> → Cartella contenente le matrici di input per ciascun circuito.</li>
    <li><strong>Documenti/Grammatiche.pdf</strong> → Specifica dettagliata della grammatica LL(2).</li>
  </ul>

  <h2>📈 Possibili Sviluppi Futuri</h2>
  <ul>
    <li><strong>Analisi del Consumo Energetico:</strong> Stima del consumo energetico per ogni transizione logica.</li>
    <li><strong>Rilevamento di Loop:</strong> Identificazione dei loop di retroazione nei circuiti sequenziali.</li>
    <li><strong>Parsing Ottimizzato:</strong> Miglioramento della velocità di esecuzione per circuiti di grandi dimensioni.</li>
  </ul>

  <hr>
  
  <h3>Cosa Include:</h3>
  <ul>
    <li>Tutto in un unico file Markdown</li>
    <li>Formattazione GitHub corretta per una facile visualizzazione</li>
    <li>Esempi di codice, logic cones e analisi dei percorsi</li>
    <li>⚡ Icona del circuito al posto di 🖧</li>
    <li>Pronto per essere copiato direttamente in <code>README.md</code></li>
  </ul>
  
  <hr>
  
  <p>🔥 <strong>Sm0l-HDL</strong> è un simulatore leggero ed efficiente per la modellazione e l'analisi dei circuiti digitali. Esplora, testa e contribuisci! 🚀</p>
</body>
</html>
