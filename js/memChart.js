
const {Memory} =require("../build/Release/addon");
const memory = new Memory();
const montiorMemory=()=> {
    const descripription=document.getElementById('description');
    if(chart) {
        chart.destroy();
        clearInterval(currentInterval);
    }
    chart=createChart('Memory Useage (in GB)', 'rgba(255, 99, 132, 1)','rgba(255, 99, 132, 0.2)');
    descripription.innerHTML=`
    <h2>Memory Usage</h2>
    <div class="row">
    <div class="col-4">Total memory - <span id="total-memory"></span>GB</div>
    <div class="col-4">Memory in use - <span id="use-memory"></span>GB</div>
    </div>
    <div class="row">
    <div class="col-4">Type - <span id="type-memory"></span></div>
    <div class="col-4">Clock speed - <span id="clock-memory"></span>MHz</div>
    </div>
    <div class="row">
    <div class="col-4">Voltage - <span id="volt-memory"></span>V</div>
    </div>
    `;
    const totalmemory =memory.getTotalMemory()/(1024 ** 3);
    const memInfo = memory.ramDetails();
    document.getElementById('type-memory').innerText = memInfo.memType;
    document.getElementById('clock-memory').innerText = memInfo.clockSpeed;
    document.getElementById('volt-memory').innerText = memInfo.voltage/1000;
    // console.log(memory.ramDetails()); 
    chart.options.scales.y.max = totalmemory;
    document.getElementById('total-memory').innerText = (Math.round(totalmemory* 10) / 10);
    currentInterval=setInterval(() => {
        let memoryInUse=(totalmemory - memory.getFreeMemory()/ (1024 ** 3)) 
        chart.data.datasets[0].data.shift();
        chart.data.datasets[0].data.push(memoryInUse);
        document.getElementById('use-memory').innerText = (Math.round(memoryInUse * 1000) / 1000).toFixed(3);
        chart.update('none');
    },1000);
}
window.addEventListener('DOMContentLoaded', () => {
    montiorMemory();
});