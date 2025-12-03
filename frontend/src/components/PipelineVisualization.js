import React from 'react';
import { STAGE_NAMES } from '../utils/mockData';
import '../styles/PipelineVisualization.css';

export function PipelineVisualization({ pipeline = [], cycle = 0 }) {
  const getStageColor = (state) => {
    switch(state) {
      case 'active':
        return '#3b82f6'; // Blue
      case 'completed':
        return '#10b981'; // Green
      case 'stall':
        return '#f59e0b'; // Amber
      case 'flushed':
        return '#ef4444'; // Red
      case 'pending':
      default:
        return '#e5e7eb'; // Light gray
    }
  };

  const getStateLabel = (state) => {
    switch(state) {
      case 'active':
        return '▶';
      case 'completed':
        return '✓';
      case 'stall':
        return '⏸';
      case 'flushed':
        return '✗';
      case 'pending':
      default:
        return '○';
    }
  };

  return (
    <div className="pipeline-container">
      <h3>Pipeline Stages</h3>
      <div className="pipeline-stages-header">
        {STAGE_NAMES.map(stage => (
          <div key={stage} className="stage-header">
            {stage}
          </div>
        ))}
      </div>

      <div className="instructions-rows">
        {pipeline.map((instr) => (
          <div key={instr.id} className="instruction-row">
            <div className="instr-label">
              {instr.name}
              {instr.stalled && <span className="stall-badge">STALL</span>}
              {instr.mispredicted && <span className="hazard-badge">MISPRED</span>}
            </div>
            <div className="stages-visualization">
              {STAGE_NAMES.map(stage => {
                const state = instr.stages[stage];
                return (
                  <div
                    key={`${instr.id}-${stage}`}
                    className={`stage-cell ${state}`}
                    style={{ backgroundColor: getStageColor(state) }}
                    title={`${instr.name} - ${stage}: ${state}`}
                  >
                    <span className="stage-label">
                      {getStateLabel(state)}
                    </span>
                  </div>
                );
              })}
            </div>
          </div>
        ))}
      </div>

      <div className="pipeline-legend">
        <div className="legend-item">
          <span className="legend-box" style={{ backgroundColor: '#3b82f6' }}></span>
          <span>Ativo</span>
        </div>
        <div className="legend-item">
          <span className="legend-box" style={{ backgroundColor: '#10b981' }}></span>
          <span>Completo</span>
        </div>
        <div className="legend-item">
          <span className="legend-box" style={{ backgroundColor: '#f59e0b' }}></span>
          <span>Stall</span>
        </div>
        <div className="legend-item">
          <span className="legend-box" style={{ backgroundColor: '#ef4444' }}></span>
          <span>Flush</span>
        </div>
      </div>
    </div>
  );
}
