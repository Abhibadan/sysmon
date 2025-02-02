const { ipcRenderer } = require('electron');

ipcRenderer.invoke('get-system-theme').then(currentMode => {
  console.log(`Current system mode is: ${currentMode}`);
});
window.addEventListener('DOMContentLoaded', () => {
})