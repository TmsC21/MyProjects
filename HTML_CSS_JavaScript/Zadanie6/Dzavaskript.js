var chart;
var hodnota_text;
var hodnota_number;
var source;
document.addEventListener("DOMContentLoaded", ()=>{
    hodnota_text = document.getElementById('majComponent').shadowRoot.querySelector('#input_text');
    hodnota_number = document.getElementById('majComponent').shadowRoot.querySelector("#input_number");
    var ctx = document.getElementById('myChart').getContext('2d');
    chart = new Chart(ctx, {
        // The type of chart we want to create
        type: 'line',

        // The data for our dataset
        data: {
            labels:[],
            datasets: [{
                label: 'y1',
                backgroundColor: 'rgb(150, 200, 100)',
                borderColor: 'rgb(150, 200, 100)',
                data:[],
                fill: false,
                hidden:false,
            },{
                label: 'y2',
                backgroundColor: 'rgb(10, 80, 200)',
                borderColor: 'rgb(10, 80, 200)',
                data:[],
                fill: false,
                hidden:false,
            }]
        },
        options: {
            legend: {
                display:false,
            },
            plugins: {
                zoom: {

                    // Container for zoom options
                    zoom: {
                        // Boolean to enable zooming
                        enabled: true,

                        // Enable drag-to-zoom behavior
                        drag: true,
                        mode: 'xy',

                        rangeMin: {
                            // Format of min zoom range depends on scale type
                            x: null,
                            y: null
                        },
                        rangeMax: {
                            // Format of max zoom range depends on scale type
                            x: null,
                            y: null
                        },

                        // Speed of zoom via mouse wheel
                        // (percentage of zoom on a wheel event)
                        speed: 0.1,

                        // Minimal zoom distance required before actually applying zoom
                        threshold: 2,

                        // On category scale, minimal zoom level before actually applying zoom
                        sensitivity: 3,

                        // Function called while the user is zooming
                        onZoom: function({chart}) { console.log(`I'm zooming!!!`); },
                        // Function called once zooming is completed
                        onZoomComplete: function({chart}) { console.log(`I was zoomed!!!`); }
                    }
                }
            }
        }
    });
    if(typeof(EventSource) !== "undefined") {
        source = new EventSource("http://vmzakova.fei.stuba.sk/sse/sse.php");

        source.addEventListener("message", function(e) {
            var data = JSON.parse(e.data);
            console.log(data);
            chart.data.labels.push(data.x);
            chart.data.datasets[0].data.push(hodnota_number.value * data.y1);
            chart.data.datasets[1].data.push(hodnota_number.value * data.y2);
            chart.update();
        }, false);

    } else {
        document.getElementById("result").innerHTML = "Sorry, your browser does not support server-sent events...";
    }
})
function check_inputs(num){
    if(num === 1){
        hodnota_number.value = hodnota_text.value;
    }
    else{
        hodnota_text.value = hodnota_number.value;
    }

}
function zmena(hod,num){
    if(hod.checked === true){
        chart.data.datasets[num].hidden = false;
    }
    else{
        chart.data.datasets[num].hidden = true;
    }
}
function koniec(){
    source.close();
}
function checkBox(input,num){
    if(input.checked == true){
        if(num == 0){
            document.getElementById("majComponent").shadowRoot.querySelector('#input_text').style.display = "block";
            document.getElementById("majComponent").shadowRoot.querySelector('#label_text').style.display = "block";
        }
        else{
            document.getElementById("majComponent").shadowRoot.querySelector('#input_number').style.display = "block";
            document.getElementById("majComponent").shadowRoot.querySelector('#label_number').style.display = "block";
        }
    }
    else{
        if(num == 0){
            document.getElementById("majComponent").shadowRoot.querySelector('#input_text').style.display = "none";
            document.getElementById("majComponent").shadowRoot.querySelector('#label_text').style.display = "none";
        }
        else{
            document.getElementById("majComponent").shadowRoot.querySelector('#input_number').style.display = "none";
            document.getElementById("majComponent").shadowRoot.querySelector('#label_number').style.display = "none";

        }
    }
}
const template = document.createElement('template');
template.innerHTML = '<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.5.3/dist/css/bootstrap.min.css" integrity="sha384-TX8t27EcRE3e/ihU7zmQxVncDAy5uIKz4rEkgIXeMed4M0jlfIDPvg6uqKI2xXr2" crossorigin="anonymous">\n' +
    '<div class="form-group cont">\n' +
    '            <div class="input-group col-md-12 inp">\n' +
    '                <div class="row-md-6">\n' +
    '                    <div class="input-group-text" style="display: none" id="label_text">Amplituda</div>\n' +
    '                    <input type="number" class="" value="1" max="5" min="0" id="input_text" placeholder="1" onchange=check_inputs(1) style="display: none">\n' +
    '                </div>\n' +
    '                <div class="row-md-6 kos">\n' +
    '                    <label id="label_number" style="display: none"><input type="range" class="custom-range" min="0" max="5" id="input_number" value="1" onchange=check_inputs(2) style="display: none">Amplituda </label>\n' +
    '                    \n' +
    '                </div>\n' +
    '            </div>\n' +
    '        </div>' +
    '<style>' +
    '.cont{\n' +
    '    font-size: 25px;\n' +
    '}\n' +
    '.inp{\n' +
    '    justify-content: center;\n' +
    '    align-items: center;\n' +
    '}\n' +
    '.kos{\n' +
    '    margin-left: 5px;\n' +
    '}' +
    '</style>'+
    '';

class Custom_component extends HTMLElement{
    constructor() {
        super();
        this.attachShadow({mode: "open"})
        this.shadowRoot.appendChild(template.content.cloneNode(true));
    }
}
window.customElements.define('my-component',Custom_component);