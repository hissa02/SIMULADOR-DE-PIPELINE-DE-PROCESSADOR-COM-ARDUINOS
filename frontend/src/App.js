import React, { useState, useEffect } from 'react';
import { generateMockData, MODES, MODE_NAMES } from './utils/mockData';

function App() {
  const [currentMode, setCurrentMode] = useState(MODES.NORMAL);
  const [isConnected, setIsConnected] = useState(false);
  const [cycle, setCycle] = useState(0);
  const [pipelineData, setPipelineData] = useState(null);

  useEffect(() => {
    if (!isConnected) {
      setCycle(0);
      setPipelineData(null);
      return;
    }

    const interval = setInterval(() => {
      setCycle(prev => prev + 1);
    }, 1000);

    return () => clearInterval(interval);
  }, [isConnected]);

  useEffect(() => {
    if (!isConnected) return;
    const data = generateMockData(cycle, currentMode);
    setPipelineData(data);
  }, [cycle, currentMode, isConnected]);

  return (
    <div style={{ padding: '20px', minHeight: '100vh' }}>
      <h1 style={{ textAlign: 'center', marginBottom: '20px' }}>
        Dashboard Simulador Pipeline
      </h1>
      
      <div style={{ textAlign: 'center', marginBottom: '20px' }}>
        {!isConnected ? (
          <button 
            onClick={() => setIsConnected(true)}
            style={{ 
              padding: '10px 20px', 
              fontSize: '16px',
              backgroundColor: '#0EA5E9',
              color: 'white',
              border: 'none',
              borderRadius: '8px',
              cursor: 'pointer'
            }}
          >
            Conectar Arduino
          </button>
        ) : (
          <button 
            onClick={() => setIsConnected(false)}
            style={{ 
              padding: '10px 20px', 
              fontSize: '16px',
              backgroundColor: '#EF4444',
              color: 'white',
              border: 'none',
              borderRadius: '8px',
              cursor: 'pointer'
            }}
          >
            Desconectar
          </button>
        )}
      </div>

      {pipelineData && (
        <div style={{ textAlign: 'center' }}>
          <h2>Modo: {MODE_NAMES[currentMode]}</h2>
          <p>Ciclo: {pipelineData.cycle}</p>
          <p>CPI: {pipelineData.metrics.cpi.toFixed(2)}</p>
          <p>Status LED: {pipelineData.rgb}</p>
        </div>
      )}
    </div>
  );
}

export default App;