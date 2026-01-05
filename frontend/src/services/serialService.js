// Serviço para comunicação com Arduino via Web Serial API

export const serialService = {
  port: null,
  reader: null,
  isConnected: false,

  // Lista portas disponíveis
  async listPorts() {
    const ports = await navigator.serial.getPorts();
    return ports;
  },

  // Conecta ao Arduino
  async connect() {
    try {
      this.port = await navigator.serial.requestPort();
      await this.port.open({ baudRate: 9600 });
      this.isConnected = true;
      return { success: true, message: "Conectado ao Arduino" };
    } catch (error) {
      this.isConnected = false;
      return { success: false, message: error.message };
    }
  },

  // Desconecta do Arduino
  async disconnect() {
    try {
      if (this.reader) {
        await this.reader.cancel();
        this.reader = null;
      }
      if (this.port) {
        await this.port.close();
        this.port = null;
      }
      this.isConnected = false;
      return { success: true, message: "Desconectado do Arduino" };
    } catch (error) {
      return { success: false, message: error.message };
    }
  },

  // Lê dados do Arduino continuamente
  async readData(onDataReceived, onError) {
    if (!this.port || !this.isConnected) {
      onError("Arduino não conectado");
      return;
    }

    try {
      const textDecoder = new TextDecoderStream();
      this.reader = this.port.readable.pipeThrough(textDecoder).getReader();

      let buffer = "";

      while (true) {
        const { value, done } = await this.reader.read();

        if (done) break;

        buffer += value;

        // Procura por linhas completas (JSON terminado com \n)
        const lines = buffer.split("\n");
        buffer = lines[lines.length - 1]; // Guarda linha incompleta

        // Processa linhas completas
        for (let i = 0; i < lines.length - 1; i++) {
          if (lines[i].trim()) {
            try {
              const data = JSON.parse(lines[i]);
              onDataReceived(data);
            } catch (parseError) {
              console.warn("JSON inválido:", lines[i]);
            }
          }
        }
      }
    } catch (error) {
      onError(error.message);
    }
  },

  // Envia comando para Arduino (opcional)
  async sendCommand(command) {
    if (!this.port || !this.isConnected) {
      return { success: false, message: "Arduino não conectado" };
    }

    try {
      const writer = this.port.writable.getWriter();
      await writer.write(new TextEncoder().encode(command + "\n"));
      writer.releaseLock();
      return { success: true, message: "Comando enviado" };
    } catch (error) {
      return { success: false, message: error.message };
    }
  }
};