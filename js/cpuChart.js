const {Cpu} =require("../build/Release/addon");
const cpu = new Cpu();
const monitorCPU=()=>{
    if(chart) {
        chart.destroy();
        clearInterval(currentInterval);
    }
    chart=createChart('CPU Useage (in %)', 'rgba(54, 162, 235, 1)','rgba(54, 162, 235, 0.2)');
    const descripription=document.getElementById('description');
    descripription.innerHTML=`
    <h2>Memory Usage <span id="brand-cpu"></span></h2>
    <div class="row">
    <div class="col-4">CPU useage - <span id="use-cpu"></span></div>
    </div>
    <div class="row">
    <div class="col-4">Cores - <span id="physical-core-cpu"></span></div>
    <div class="col-4">Performance Core - <span id="core-cpu"></span></div>
    </div>
    <div class="row">
    <div class="col-4"> <h4> Cache Details </h4> </div>
    </div>
    <div class="row small" id="cache-details">
    </div>
    `;
    chart.options.scales.y.max =100;
    document.getElementById('brand-cpu').innerText = cpu.model();
    document.getElementById('physical-core-cpu').innerText = cpu.cores();
    document.getElementById('core-cpu').innerText = cpu.logicalCores();
    cpu.getCacheInfo().forEach((cache)=>{
        document.getElementById(`cache-details`).innerHTML += `
        <div class="col-2">L${cache.level} : ${(cache.sizeKB)} KB</div>`;
    });
    currentInterval=setInterval(() => {
        let idleTime = cpu.getCpuIdle();
        chart.data.datasets[0].data.shift();
        chart.data.datasets[0].data.push(idleTime);
        chart.update('none');
        document.getElementById('use-cpu').innerText = `${idleTime.toFixed(2)}%`;
    },1000);
}