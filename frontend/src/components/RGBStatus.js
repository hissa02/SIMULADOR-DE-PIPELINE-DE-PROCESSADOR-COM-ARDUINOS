import React from 'react';
import '../styles/RGBStatus.css';

export function RGBStatus({ color = '#22c55e', mode = '' }) {
  return (
    <div className="rgb-status-container">
      <h3>Status LED RGB</h3>
      <div className="rgb-display">
        <div
          className="rgb-led"
          style={{ backgroundColor: color }}
          title="Status LED"
        />
        <div className="rgb-info">
          <p className="rgb-mode">{mode}</p>
          <p className="rgb-hex">{color}</p>
        </div>
      </div>
    </div>
  );
}
