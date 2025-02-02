const { ipcRenderer } = require('electron');
const handleTheme = (theme) => {
    document.body.classList.remove('dark-mode','light-mode');
    document.body.classList.add(theme);
    document.querySelector('.sidebar').classList.remove('dark-mode','light-mode');
    document.querySelector('.sidebar').classList.add(theme);
}

ipcRenderer.invoke('get-theme').then((theme) => {
    handleTheme(theme);
});

ipcRenderer.on('change-theme',(_, theme) => {
    handleTheme(theme);
})
