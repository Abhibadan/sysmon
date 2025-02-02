const monitorGPU=()=>{
    if(chart) {
        chart.destroy();
        clearInterval(currentInterval);
    }
    chart=createChart('CPU Useage (in %)', 'rgba(75, 192, 192, 1)','rgba(75, 192, 192, 0.2)');
    const descripription=document.getElementById('description');
    descripription.innerHTML=`
    <h2>Memory Usage (<span id="brand-cpu"> - </span>)</h2>
    <div class="row">
    <div class="col-4">CPU useage - <span id="use-cpu"></span></div>
    <div class="col-4">Clock Speed - <span id="clock-speed-cpu"></span></div>
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

    si.cpu()
    .then((data)=>{
        console.log(data);
        document.getElementById('brand-cpu').innerText = data.brand;
        document.getElementById('clock-speed-cpu').innerText = `${(data.speed).toFixed(2)} GHz`;
        document.getElementById('physical-core-cpu').innerText = data.physicalCores;
        document.getElementById('core-cpu').innerText = data.cores;
        document.getElementById(`cache-details`).innerHTML = '';
        Object.keys(data.cache).forEach((cache)=>{
            document.getElementById(`cache-details`).innerHTML += `
            <div class="col-2">${cache} : ${(data.cache[cache]/ (1024))} KB</div>`;
        });
    }).catch((error)=>console.log(error));
    currentInterval=setInterval(() => {
        si.currentLoad().then((data)=>{
            chart.data.datasets[0].data.shift();
            chart.data.datasets[0].data.push(data.currentLoad);
            chart.update('none');
            document.getElementById('use-cpu').innerText = `${(data.currentLoad).toFixed(2)} %`;
        })
        .catch((error)=>console.log(error));
    },1000);
}