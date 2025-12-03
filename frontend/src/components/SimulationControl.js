import React from 'react';
import { MODES, MODE_NAMES } from '../utils/mockData';
import '../styles/SimulationControl.css';

export function SimulationControl({
  currentMode,
  onModeChange,
  isRunning,
  onPlayPause,
  onReset,
  cycle
}) {
  const modes = Object.values(MODES);

  return (
    <div className="simulation-control-container">
      <div className="control-section">
        <h3>Seleção de Modo</h3>
        <div className="mode-buttons">
          {modes.map(mode => (
            <button
              key={mode}
              className={`mode-button ${currentMode === mode ? 'active' : ''}`}
              onClick={() => onModeChange(mode)}
              disabled={isRunning}
              title={MODE_NAMES[mode]}
            >
              {MODE_NAMES[mode]}
            </button>
          ))}
        </div>
      </div>

      <div className="control-section">
        <h3>Controles</h3>
        <div className="control-buttons">
          <button
            className={`play-pause-btn ${isRunning ? 'pause' : 'play'}`}
            onClick={onPlayPause}
          >
            {isRunning ? '⏸ Pausar' : '▶ Iniciar'}
          </button>

          <button
            className="reset-btn"
            onClick={onReset}
            disabled={isRunning}
          >
            ↻ Resetar
          </button>
        </div>
      </div>

      <div className="cycle-display">
        <p>
          <span className="cycle-label">Ciclo Atual:</span>
          <span className="cycle-value">{cycle}</span>
        </p>
      </div>
    </div>
  );
}
