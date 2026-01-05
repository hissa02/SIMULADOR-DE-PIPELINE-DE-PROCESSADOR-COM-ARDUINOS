import React, { useState, useEffect } from 'react';
import { generateMockData, MODES } from './utils/mockData';
import { serialService } from './services/serialService';
import { SimulationControl } from './components/SimulationControl';
import { LEDMatrix } from './components/LEDMatrix';
import { RGBStatus } from './components/RGBStatus';
import { PipelineVisualization } from './components/PipelineVisualization';
import { Metrics } from './components/Metrics';
import { EventLog } from './components/EventLog';
import './App.css';

function App() {
  const [currentMode, setCurrentMode] = useState(MODES.NORMAL);
  const [isRunning, setIsRunning] = useState(false);
  const [cycle, setCycle] = useState(0);
  const [pipelineData, setPipelineData] = useState(null);
  const [isConnected, setIsConnected] = useState(false);
  const [useArduino, setUseArduino] = useState(false);
  const [connectionStatus, setConnectionStatus] = useState('Desconectado');

  // Conecta ao Arduino
  const handleConnectArduino = async () => {
    const result = await serialService.connect();
    
    if (result.success) {
      setIsConnected(true);
      setConnectionStatus('Conectado ao Arduino');
      setUseArduino(true);
      
      // Inicia leitura de dados
      serialService.readData(
        (data) => {
          // Atualiza o dashboard com dados do Arduino
          setPipelineData({
            ...data,
            description: `Ciclo ${data.cycle}: Recebendo dados do Arduino`
          });
          setCycle(data.cycle);
        },
        (error) => {
          console.error("Erro ao ler Arduino:", error);
          setConnectionStatus('Erro na leitura: ' + error);
        }
      );
    } else {
      setConnectionStatus('Erro: ' + result.message);
    }
  };

  // Desconecta do Arduino
  const handleDisconnectArduino = async () => {
    const result = await serialService.disconnect();
    
    if (result.success) {
      setIsConnected(false);
      setUseArduino(false);
      setConnectionStatus('Desconectado');
      setCycle(0);
    }
  };

  // Simulação local (sem Arduino)
  useEffect(() => {
    if (useArduino) return; // Não usa simulação se Arduino está conectado

    if (!isRunning) {
      setCycle(0);
      return;
    }

    const interval = setInterval(() => {
      setCycle(prev => prev + 1);
    }, 1000);

    return () => clearInterval(interval);
  }, [isRunning, useArduino]);

  // Atualiza dados (simulação ou Arduino)
  useEffect(() => {
    if (useArduino) return; // Arduino já atualiza os dados

    const data = generateMockData(cycle, currentMode);
    setPipelineData(data);
  }, [cycle, currentMode, useArduino]);

  const handleModeChange = (mode) => {
    setCurrentMode(mode);
    if (!isRunning) {
      setCycle(0);
    }
  };

  const handlePlayPause = () => {
    setIsRunning(!isRunning);
  };

  const handleReset = () => {
    setCycle(0);
    setIsRunning(false);
  };

  if (!pipelineData) {
    return <div className="app-loading">Carregando...</div>;
  }

  return (
    <div className="app-container">
      <header className="app-header">
        <div className="header-content">
          <h1>Pipeline Simulator Dashboard</h1>
          <p className="header-subtitle">Simulador didático de pipeline de processadores</p>
          <div style={{ marginTop: '16px', fontSize: '12px', color: '#cbd5e1' }}>
            Status: <strong>{connectionStatus}</strong>
          </div>
        </div>
      </header>

      <main className="app-main">
        <section className="content-section">
          <div style={{ display: 'flex', gap: '12px', marginBottom: '20px', justifyContent: 'center' }}>
            {!isConnected ? (
              <button
                onClick={handleConnectArduino}
                style={{
                  padding: '10px 20px',
                  fontSize: '14px',
                  backgroundColor: '#3b82f6',
                  color: 'white',
                  border: 'none',
                  borderRadius: '6px',
                  cursor: 'pointer',
                  fontWeight: '600'
                }}
              >
                🔌 Conectar Arduino
              </button>
            ) : (
              <button
                onClick={handleDisconnectArduino}
                style={{
                  padding: '10px 20px',
                  fontSize: '14px',
                  backgroundColor: '#ef4444',
                  color: 'white',
                  border: 'none',
                  borderRadius: '6px',
                  cursor: 'pointer',
                  fontWeight: '600'
                }}
              >
                🔌 Desconectar Arduino
              </button>
            )}
            
            <button
              onClick={() => setUseArduino(!useArduino)}
              style={{
                padding: '10px 20px',
                fontSize: '14px',
                backgroundColor: useArduino ? '#10b981' : '#6366f1',
                color: 'white',
                border: 'none',
                borderRadius: '6px',
                cursor: 'pointer',
                fontWeight: '600'
              }}
            >
              {useArduino ? '✓ Usando Arduino' : '📊 Simulação Local'}
            </button>
          </div>

          <SimulationControl
            currentMode={currentMode}
            onModeChange={handleModeChange}
            isRunning={isRunning}
            onPlayPause={handlePlayPause}
            onReset={handleReset}
            cycle={cycle}
          />
        </section>

        <div className="content-grid">
          <div className="grid-column">
            <section className="content-section">
              <LEDMatrix
                matrix={pipelineData.ledMatrix}
                cycle={cycle}
              />
            </section>

            <section className="content-section">
              <RGBStatus
                color={pipelineData.rgb}
                mode={pipelineData.mode}
              />
            </section>
          </div>

          <div className="grid-column">
            <section className="content-section">
              <Metrics metrics={pipelineData.metrics} />
            </section>

            <section className="content-section">
              <EventLog
                events={pipelineData.events}
                description={pipelineData.description}
              />
            </section>
          </div>
        </div>

        <section className="content-section full-width">
          <PipelineVisualization
            pipeline={pipelineData.pipeline}
            cycle={cycle}
          />
        </section>
      </main>

      <footer className="app-footer">
        <p>ARQUITETURA DE COMPUTADORES | Simulador de Pipeline com Arduino</p>
      </footer>
    </div>
  );
}

export default App;