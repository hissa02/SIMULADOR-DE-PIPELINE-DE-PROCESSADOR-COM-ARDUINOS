import React from 'react';
import '../styles/Metrics.css';

export function Metrics({ metrics = {} }) {
  const defaultMetrics = {
    cpi: 0,
    totalCycles: 0,
    totalInstructions: 0,
    totalStalls: 0,
    stalls: 0,
    flushes: 0,
    throughput: 0
  };

  const data = { ...defaultMetrics, ...metrics };

  return (
    <div className="metrics-container">
      <h3>Métricas de Performance</h3>
      <div className="metrics-grid">
        <div className="metric-card">
          <label>CPI</label>
          <span className="metric-value">{data.cpi.toFixed(2)}</span>
          <small>Ciclos por Instrução</small>
        </div>

        <div className="metric-card">
          <label>Ciclos Totais</label>
          <span className="metric-value">{data.totalCycles}</span>
          <small>Clocks executados</small>
        </div>

        <div className="metric-card">
          <label>Instruções</label>
          <span className="metric-value">{data.totalInstructions}</span>
          <small>Total emitidas</small>
        </div>

        <div className="metric-card">
          <label>Stalls</label>
          <span className="metric-value">{data.stalls}</span>
          <small>Por ciclo</small>
        </div>

        <div className="metric-card">
          <label>Flushes</label>
          <span className="metric-value">{data.flushes}</span>
          <small>Instruções descartadas</small>
        </div>

        <div className="metric-card">
          <label>Throughput</label>
          <span className="metric-value">{data.throughput}</span>
          <small>Instr./Ciclo</small>
        </div>
      </div>
    </div>
  );
}
