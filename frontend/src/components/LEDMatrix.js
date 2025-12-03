import React from 'react';
import { LED_STATES } from '../utils/mockData';
import '../styles/LEDMatrix.css';

export function LEDMatrix({ matrix = [], cycle = 0 }) {
  const getLEDColor = (state) => {
    switch(state) {
      case LED_STATES.ACTIVE:
        return '#10b981'; // Green
      case LED_STATES.STALL:
        return '#f59e0b'; // Amber
      case LED_STATES.HAZARD:
        return '#ef4444'; // Red
      case LED_STATES.OFF:
      default:
        return '#1f2937'; // Dark gray
    }
  };

  return (
    <div className="led-matrix-container">
      <h3>Matriz de LEDs 4x4</h3>
      <div className="led-matrix">
        {matrix.map((row, rowIdx) => (
          <div key={rowIdx} className="led-row">
            {row.map((cell, colIdx) => (
              <div
                key={`${rowIdx}-${colIdx}`}
                className={`led-cell ${cell}`}
                style={{ backgroundColor: getLEDColor(cell) }}
                title={`LED[${rowIdx}][${colIdx}]: ${cell}`}
              />
            ))}
          </div>
        ))}
      </div>
      <p className="matrix-label">Cada linha = Instrução | Cada coluna = Estágio (IF, ID, EX, MEM, WB)</p>
    </div>
  );
}
