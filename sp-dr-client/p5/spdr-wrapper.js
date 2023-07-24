// Throw error if p5 is not loaded
if (!window.p5) {
    throw new Error('p5 is not loaded');
}

p5.instance = true;

// Load the WASM module
const script = document.createElement('script');
script.src = 'spdr.js';

script.onload = () => {
    // Bind WASM calls to p5
    Module.onRuntimeInitialized = () => {
        Object.keys(Module.Client.prototype)
            .forEach(method => {
                window.p5.prototype[method] = Module.Client.prototype[method];
            });

        window.p5.prototype.newSPDRClient = function (host, port) {
            return new Module.Client(host, port);
        }

        new p5();
    }
}

document.head.appendChild(script);