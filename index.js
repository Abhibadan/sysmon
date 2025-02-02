const { app, BrowserWindow,Menu,ipcMain,nativeTheme} = require('electron');
const path= require('path');

// const path = require('path');

const menu=Menu.buildFromTemplate([]);
Menu.setApplicationMenu(menu);
let win;
const createWindow = () => {
    win = new BrowserWindow({
        width: 900,
        height: 600,
        title: 'SysMON',
        resizable: true,
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false,
            enableRemoteModule: true,
            // preload: path.join(__dirname, '/preload.js')
        }
    })
    win.loadFile('./views/index.html');
    win.once('ready-to-show', () => {
        win.setTitle('SysMON');
    });
}


app.on('ready', () => {
    
    createWindow()
    win.setTitle('SysMON');
    ipcMain.handle('get-theme', () => {
        return nativeTheme.shouldUseDarkColors?"dark-mode":"light-mode";
    });
    nativeTheme.on('updated', () => {
        win.webContents.send('change-theme', nativeTheme.shouldUseDarkColors ? "dark-mode":"light-mode");
    });
    
})

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit()
    }
})