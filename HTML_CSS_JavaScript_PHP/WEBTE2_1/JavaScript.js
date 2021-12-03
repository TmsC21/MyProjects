var button = document.querySelector("#posli");
window.onload = Table("files/");
var tabulka = document.getElementById("table");

var az = document.createElement("button");
var icko1 = document.createElement("i");
icko1.setAttribute("class","fas fa-sort-alpha-down")
az.appendChild(icko1);
az.setAttribute("class","btn btn-primary")

var za = document.createElement("button");
var icko1 = document.createElement("i");
icko1.setAttribute("class","fas fa-sort-alpha-up-alt")
za.appendChild(icko1);
za.setAttribute("class","btn btn-primary")


var azc = document.createElement("button")
var icko1 = document.createElement("i");
icko1.setAttribute("class","fas fa-sort-numeric-down-alt")
azc.appendChild(icko1)
azc.setAttribute("class","btn btn-primary")




var zac = document.createElement("button")
var icko1 = document.createElement("i");
icko1.setAttribute("class","fas fa-sort-numeric-up")
zac.appendChild(icko1)
zac.setAttribute("class","btn btn-primary")

var zacd = document.createElement("button")
var icko1 = document.createElement("i");
icko1.setAttribute("class","fas fa-sort-numeric-up")
zacd.appendChild(icko1)
zacd.setAttribute("class","btn btn-primary")

var azcd = document.createElement("button")
var icko1 = document.createElement("i");
icko1.setAttribute("class","fas fa-sort-numeric-down-alt")
azcd.appendChild(icko1)
azcd.setAttribute("class","btn btn-primary")

button.addEventListener("click",()=>{
    tabulka.innerHTML = " ";
    let formular = new FormData(document.querySelector("#formular"))
    let request_btn = new Request("/upload.php",{
        method: "POST",
        body: formular
    });
    fetch(request_btn)
        .then(request => request.json())
        .then(data =>{document.getElementById("Text_upload").innerText ="The file "+data.message+" uploaded."
            Table("files/");
        })
})
let myPath;
function Table(path){
    let request_table = new Request("/table.php",{
        method: "POST",
        body: JSON.stringify({path: path})
    })
    fetch(request_table)
        .then(request => request.json())
        .then(data =>{
            var arr = [];
            for(let x of data){
                arr.push(x["id"]);
            }
            let k = 0;
            myPath = data[0]["path"];
            CreateTable();
            az.onclick = function (){
                a_z("fileName",1)
            };
            za.onclick = function (){
                a_z("fileName",2)
            };
            azc.onclick = function (){
                a_z("fileSize",1)
            }
            zac.onclick =function (){
                a_z("fileSize",2)
            }
            zacd.onclick = function (){
                a_z("fileDate",1)
            }
            azcd.onclick = function (){
                a_z("fileDate",2)
            }
            function CreateTable(){
                var tbl = document.createElement('table');
                tbl.setAttribute("class","table")
                var tbdy = document.createElement('tbody');
                tbl.style.width = '100%';
                tbl.setAttribute('border', '2');
                tbl.style.borderCollapse = "collapse";
                tbl.style.textAlign = "center";
                var trr = document.createElement('tr');

                var th = document.createElement("th");
                var dv = document.createElement("div")
                dv.setAttribute("class","filter")
                dv.appendChild(za);
                dv.appendChild(az);
                th.appendChild(dv);
                th.appendChild(document.createTextNode("File name"));

                trr.appendChild(th);
                var th = document.createElement("th");
                var dv = document.createElement("div")
                dv.setAttribute("class","filterCis")
                dv.appendChild(zac);
                dv.appendChild(azc);
                th.appendChild(dv);
                th.appendChild(document.createTextNode("File size(bytes)"));

                trr.appendChild(th);
                var th = document.createElement("th");
                var dv = document.createElement("div")
                dv.setAttribute("class","filterCisDat")
                dv.appendChild(zacd);
                dv.appendChild(azcd);
                th.appendChild(dv);
                th.appendChild(document.createTextNode("File date upload"));
                trr.appendChild(th);
                trr.setAttribute("class","thead")
                tbdy.appendChild(trr);
                for(let d of arr){
                    for(let i of data){
                        if(d === i["id"]){
                            var tr = document.createElement('tr');
                            if(path !== "files/" && k === 0){
                                var td = document.createElement('td');
                                td.appendChild(document.createTextNode(".."));
                                td.onclick = function() {
                                    tabulka.innerHTML = " ";
                                    let arra = myPath.split("/");
                                    let o = 0;
                                    let name = "";
                                    for(let x of arra){
                                        if(arra.length-2 !== o){
                                            name += x + "/";
                                        }
                                        o++;
                                    }
                                    name = name.slice(0,-1);
                                    Table(name);
                                };
                                td.style.cursor = "pointer";
                                tr.appendChild(td);
                                var td = document.createElement('td');
                                td.appendChild(document.createTextNode(" "))
                                tr.appendChild(td);
                                var td = document.createElement('td');
                                td.appendChild(document.createTextNode(" "))
                                tr.appendChild(td);
                                tbdy.appendChild(tr);
                                k = 1;
                            }
                            else{
                                myPath = data[0]["path"]
                            }
                            var tr = document.createElement('tr');
                            for(let y in i){
                                if(i[y] === "directory"){
                                    var td = document.createElement('td');
                                    var icko = document.createElement("i");
                                    icko.setAttribute("class","far fa-folder")
                                    td.appendChild(icko)
                                    td.appendChild(document.createTextNode(" "+i["fileName"]))
                                    td.onclick = function() {
                                        let name = i.fileName;
                                        name = myPath + name + "/";
                                        tabulka.innerHTML = " ";
                                        Table(name);
                                    };
                                    td.setAttribute("class", "direc")
                                    tr.appendChild(td);
                                    var td = document.createElement('td');
                                    td.appendChild(document.createTextNode(" "))
                                    tr.appendChild(td);
                                    var td = document.createElement('td');
                                    td.appendChild(document.createTextNode(" "))
                                    tr.appendChild(td);

                                }
                            }
                            for (let x in i){
                                if(x === "id" || i["fileType"] === "directory" || x === "fileType" || x === "path"){
                                    continue;
                                }else{
                                    var td = document.createElement('td');
                                    if(x === "fileName"){
                                        var icko = document.createElement("i");
                                        icko = icons(i["fileType"],icko)
                                        td.appendChild(icko)
                                    }
                                    td.appendChild(document.createTextNode(" "+i[x]));
                                    td.setAttribute("style","padding: 0")
                                    if(x === "fileName" || x === "fileSize"){
                                        td.setAttribute("style","padding-top: 12px")
                                    }
                                    tr.setAttribute("style","text-align: center")
                                    tr.appendChild(td);
                                }
                            }
                            tbdy.appendChild(tr)
                        }
                    }
                }
                tbl.appendChild(tbdy)
                tabulka.appendChild(tbl)
            }function a_z(name,zaa){
                let filesNames = [];
                for (let x of data){
                    filesNames.push(x[name]);
                }
                filesNames = filesNames.filter(function (el) {return el !== undefined});
                console.log(filesNames)
                if(name === "fileSize"){
                    filesNames.sort(function(a, b){return b-a})
                }
                else{
                    filesNames.sort(function (a, b) {
                        return ('' + a).localeCompare(b);
                    });
                }
                arr = [];
                if (zaa === 2){
                    filesNames.reverse()
                }
                for (let x of filesNames){
                    for(let y of data){
                        if(x === y[name]){
                            arr.push(y["id"]);
                        }
                    }
                }
                function onlyUnique(value, index, self) {
                    return self.indexOf(value) === index;
                }
                arr = arr.filter(onlyUnique)
                tabulka.innerHTML = " ";
                k = 0;
                CreateTable();
            }
        })
}

function icons(fileType,icko){
    if(fileType === "txt"){
        icko.setAttribute("class", "far fa-file-alt")
        return icko;
    }
    else if (fileType === "pdf"){
        icko.setAttribute("class", "far fa-file-pdf")
        return icko;
    }
    else if(fileType === "jpg" || fileType === "png" || fileType === "jpeg" || fileType === "gif"){
        icko.setAttribute("class", "far fa-file-image")
        return icko;
    }
    else{
        icko.setAttribute("class", "far fa-file")
        return icko;
    }
}